#include "c64_tui.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <regex>
#include <algorithm>

namespace c64tui {

// ---------- NodeStats ----------

static NodeStats g_stats;

NodeStats& get_stats() { return g_stats; }

void NodeStats::set_status(const std::string& s) {
    std::lock_guard<std::mutex> lock(mtx);
    status = s;
}

void NodeStats::add_log(const std::string& line, int color_type) {
    std::lock_guard<std::mutex> lock(mtx);
    log_lines.push_back({line, color_type});
    if (log_lines.size() > 500)
        log_lines.pop_front();
}

void NodeStats::set_block_info(const std::string& id, const std::string& pow, const std::string& reward) {
    std::lock_guard<std::mutex> lock(mtx);
    last_block_id = id;
    last_pow = pow;
    last_reward = reward;
}

// ---------- Datasette Animation ----------

void play_datasette_animation() {
    const char* colors[] = {
        "\033[41m", "\033[42m", "\033[43m", "\033[44m",
        "\033[45m", "\033[46m", "\033[47m", "\033[44m",
        "\033[41m", "\033[43m", "\033[42m", "\033[45m",
        "\033[46m", "\033[41m", "\033[44m", "\033[47m"
    };
    const char* reset = "\033[0m";

    // Get terminal width
    struct winsize ws;
    int tw = 60;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0)
        tw = ws.ws_col - 4;

    fprintf(stderr, "\033[2J\033[H"); // clear screen
    fprintf(stderr, "\n\033[36m    PRESS PLAY ON TAPE\033[0m\n\n");
    fflush(stderr);
    usleep(1500000);
    fprintf(stderr, "\033[36m    OK\033[0m\n\n");
    fflush(stderr);
    usleep(500000);

    srand(time(NULL));
    for (int f = 0; f < 120; f++) {
        std::string ln = "    ";
        for (int x = 0; x < tw; x++) {
            int ci = (x + f * 3 + (rand() % 3)) % 16;
            ln += colors[ci];
            ln += " ";
        }
        ln += reset;
        fprintf(stderr, "%s\n", ln.c_str());
        fflush(stderr);
        usleep(50000);
    }

    fprintf(stderr, "\n");
    fflush(stderr);
    usleep(500000);
    fprintf(stderr, "\033[36m    FOUND C64CHAIN\033[0m\n");
    fflush(stderr);
    usleep(1000000);
    fprintf(stderr, "\033[36m    LOADING...\033[0m\n");
    fflush(stderr);
    usleep(1500000);
    fprintf(stderr, "\033[36m    READY.\033[0m\n\n");
    fflush(stderr);
    usleep(500000);
}

// ---------- ncurses TUI ----------

// Color pair IDs
enum {
    CP_NORMAL = 1,
    CP_HEADER = 2,
    CP_SUCCESS = 3,
    CP_ERROR = 4,
    CP_WARNING = 5,
    CP_LOG_GREEN = 6,
    CP_LOG_BLUE = 7
};

static void init_colors() {
    start_color();
    if (can_change_color()) {
        init_color(20, 260, 220, 560);    // C64 dark blue bg
        init_color(21, 420, 370, 710);    // C64 light blue
        init_color(22, 1000, 1000, 1000); // White
        init_color(23, 700, 1000, 700);   // Green bright
        init_color(24, 1000, 400, 400);   // Red bright
        init_color(25, 1000, 1000, 700);  // Yellow bright
        init_color(26, 400, 900, 400);    // Log green
        init_color(27, 400, 600, 1000);   // Log blue
        init_pair(CP_NORMAL,    22, 20);
        init_pair(CP_HEADER,    21, 20);
        init_pair(CP_SUCCESS,   23, 20);
        init_pair(CP_ERROR,     24, 20);
        init_pair(CP_WARNING,   25, 20);
        init_pair(CP_LOG_GREEN, 26, 20);
        init_pair(CP_LOG_BLUE,  27, 20);
    } else {
        init_pair(CP_NORMAL,    COLOR_WHITE,  COLOR_BLUE);
        init_pair(CP_HEADER,    COLOR_CYAN,   COLOR_BLUE);
        init_pair(CP_SUCCESS,   COLOR_GREEN,  COLOR_BLUE);
        init_pair(CP_ERROR,     COLOR_RED,    COLOR_BLUE);
        init_pair(CP_WARNING,   COLOR_YELLOW, COLOR_BLUE);
        init_pair(CP_LOG_GREEN, COLOR_GREEN,  COLOR_BLUE);
        init_pair(CP_LOG_BLUE,  COLOR_CYAN,   COLOR_BLUE);
    }
}

static void draw_border(int h, int w) {
    attron(COLOR_PAIR(CP_NORMAL));
    mvaddstr(0, 0, "+");
    for (int x = 1; x < w - 1; x++) mvaddch(0, x, '-');
    mvaddch(0, w - 1, '+');
    for (int y = 1; y < h - 1; y++) {
        mvaddch(y, 0, '|');
        mvaddch(y, w - 1, '|');
    }
    mvaddch(h - 1, 0, '+');
    for (int x = 1; x < w - 1; x++) mvaddch(h - 1, x, '-');
    mvaddch(h - 1, w - 1, '+');
    attroff(COLOR_PAIR(CP_NORMAL));
}

static void draw_centered(int y, int w, const char* text, int cp) {
    int len = strlen(text);
    int x = (w - len) / 2;
    if (x < 0) x = 0;
    attron(COLOR_PAIR(cp) | A_BOLD);
    mvaddnstr(y, x, text, w);
    attroff(COLOR_PAIR(cp) | A_BOLD);
}

void run_tui(std::atomic<bool>& stop_signal) {
    auto start_time = std::chrono::steady_clock::now();

    // Open /dev/tty directly so ncurses works even if stdout is redirected
    FILE* tty = fopen("/dev/tty", "r+");
    SCREEN* scr = newterm(NULL, tty, tty);
    set_term(scr);
    clear();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);

    init_colors();
    bkgd(COLOR_PAIR(CP_NORMAL));


    NodeStats& stats = get_stats();

    auto last_rpc_poll = std::chrono::steady_clock::now() - std::chrono::seconds(10);
    while (!stop_signal.load()) {
        // Poll RPC for peer count every 5 seconds
        {
            auto now_poll = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now_poll - last_rpc_poll).count() >= 5) {
                last_rpc_poll = now_poll;
                FILE* rpc = popen("curl -s http://127.0.0.1:29641/get_info 2>/dev/null", "r");
                if (rpc) {
                    char rb[4096]; std::string rd;
                    while (fgets(rb, sizeof(rb), rpc)) rd += rb;
                    pclose(rpc);
                    auto fv = [&](const char* k) -> uint64_t {
                        auto p = rd.find(k);
                        if (p == std::string::npos) return 0;
                        auto c = rd.find(':', p);
                        if (c == std::string::npos) return 0;
                        auto s = rd.find_first_of("0123456789", c);
                        if (s == std::string::npos) return 0;
                        return std::stoull(rd.substr(s));
                    };
                    try {
                        stats.peers_out.store(fv("outgoing_connections_count"));
                        stats.peers_in.store(fv("incoming_connections_count"));
                    } catch (...) {}
                }
            }
        }
        int h, w;
        getmaxyx(stdscr, h, w);
        erase();

        draw_border(h, w);

        int y = 2;

        // Header
        draw_centered(y++, w, "**** C64 CHAIN NODE V1.0 ****", CP_HEADER);
        draw_centered(y++, w, "64K RAM SYSTEM  38911 BASIC BYTES FREE", CP_NORMAL);
        y++;

        // READY. / LIST
        attron(COLOR_PAIR(CP_HEADER) | A_BOLD);
        mvaddstr(y++, 3, "READY.");
        attroff(A_BOLD);
        attron(COLOR_PAIR(CP_NORMAL));
        mvaddstr(y++, 3, "LIST");
        attroff(COLOR_PAIR(CP_NORMAL));
        y++;

        // Stats
        auto elapsed = std::chrono::steady_clock::now() - start_time;
        int uptime = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
        int hrs = uptime / 3600, mins = (uptime % 3600) / 60, secs = uptime % 60;

        std::string status_str;
        {
            std::lock_guard<std::mutex> lock(stats.mtx);
            status_str = stats.status.empty() ? "LOADING BLOCKCHAIN..." : stats.status;
        }

        char buf[256];
        auto print_stat = [&](int idx, const char* key, const char* val, int cp) {
            snprintf(buf, sizeof(buf), "%2d  %-14s %s", idx, key, val);
            attron(COLOR_PAIR(cp));
            mvaddnstr(y++, 3, buf, w - 6);
            attroff(COLOR_PAIR(cp));
        };

        char tmp[64];
        snprintf(tmp, sizeof(tmp), "%s", status_str.c_str());
        print_stat(0, "STATUS:", tmp, status_str == "MINING" ? CP_SUCCESS : CP_NORMAL);

        snprintf(tmp, sizeof(tmp), "%lu", stats.height.load());
        print_stat(1, "HEIGHT:", tmp, CP_NORMAL);

        snprintf(tmp, sizeof(tmp), "%lu", stats.difficulty.load());
        print_stat(2, "DIFFICULTY:", tmp, CP_NORMAL);

        snprintf(tmp, sizeof(tmp), "%lu", stats.blocks_added.load());
        print_stat(3, "BLOCKS OK:", tmp, stats.blocks_added.load() > 0 ? CP_SUCCESS : CP_NORMAL);

        snprintf(tmp, sizeof(tmp), "%lu", stats.blocks_alt.load());
        print_stat(4, "BLOCKS ALT:", tmp, stats.blocks_alt.load() > 0 ? CP_WARNING : CP_NORMAL);

        std::string reward_str;
        {
            std::lock_guard<std::mutex> lock(stats.mtx);
            reward_str = stats.last_reward.empty() ? "" : stats.last_reward;
        }
        snprintf(tmp, sizeof(tmp), "%s C64", reward_str.c_str());
        print_stat(5, "REWARD:", tmp, CP_NORMAL);

        snprintf(tmp, sizeof(tmp), "%lu", stats.rpc_calls.load());
        print_stat(6, "RPC CALLS:", tmp, CP_NORMAL);
        snprintf(tmp, sizeof(tmp), "%lu OUT / %lu IN", stats.peers_out.load(), stats.peers_in.load());
        print_stat(7, "PEERS:", tmp, stats.peers_out.load() + stats.peers_in.load() > 0 ? CP_SUCCESS : CP_WARNING);
        {
            uint64_t h = stats.height.load();
            uint64_t t = stats.target_height.load();
            if (stats.synced.load() || t == 0 || h >= t) {
                snprintf(tmp, sizeof(tmp), "SYNCED");
                print_stat(8, "SYNC:", tmp, CP_SUCCESS);
            } else {
                uint64_t pct = t > 0 ? (h * 100 / t) : 0;
                snprintf(tmp, sizeof(tmp), "%lu / %lu (%lu%%)", h, t, pct);
                print_stat(8, "SYNC:", tmp, CP_WARNING);
            }
        }
        snprintf(tmp, sizeof(tmp), "%02d:%02d:%02d", hrs, mins, secs);
        print_stat(9, "UPTIME:", tmp, CP_NORMAL);
        y++;

        // Last block info
        attron(COLOR_PAIR(CP_HEADER) | A_BOLD);
        mvaddstr(y++, 3, "LAST BLOCK:");
        attroff(COLOR_PAIR(CP_HEADER) | A_BOLD);

        {
            std::lock_guard<std::mutex> lock(stats.mtx);
            if (!stats.last_block_id.empty()) {
                std::string id_short = stats.last_block_id.substr(0, 32) + "...";
                std::string pow_short = stats.last_pow.substr(0, 32) + "...";
                attron(COLOR_PAIR(CP_NORMAL));
                snprintf(buf, sizeof(buf), "  ID:  %s", id_short.c_str());
                mvaddnstr(y++, 3, buf, w - 6);
                snprintf(buf, sizeof(buf), "  POW: %s", pow_short.c_str());
                mvaddnstr(y++, 3, buf, w - 6);
                attroff(COLOR_PAIR(CP_NORMAL));
            } else {
                attron(COLOR_PAIR(CP_NORMAL));
                mvaddstr(y++, 3, "  WAITING FOR BLOCKS...");
                attroff(COLOR_PAIR(CP_NORMAL));
            }
        }
        y++;

        // Log section
        attron(COLOR_PAIR(CP_HEADER) | A_BOLD);
        mvaddstr(y++, 3, "LOG:");
        attroff(COLOR_PAIR(CP_HEADER) | A_BOLD);

        int available = h - y - 3;
        if (available > 0) {
            std::lock_guard<std::mutex> lock(stats.mtx);
            int start = (int)stats.log_lines.size() - available;
            if (start < 0) start = 0;

            for (int i = start; i < (int)stats.log_lines.size() && y < h - 3; i++) {
                auto& entry = stats.log_lines[i];
                int cp = CP_NORMAL;
                switch (entry.second) {
                    case LOG_SUCCESS: cp = CP_LOG_GREEN; break;
                    case LOG_ERROR:   cp = CP_ERROR;     break;
                    case LOG_WARNING: cp = CP_WARNING;   break;
                    case LOG_INFO:    cp = CP_LOG_BLUE;  break;
                    default:          cp = CP_NORMAL;    break;
                }
                std::string display = entry.first.substr(0, w - 6);
                attron(COLOR_PAIR(cp));
                mvaddnstr(y++, 3, display.c_str(), w - 6);
                attroff(COLOR_PAIR(cp));
            }
        }

        // Blinking cursor
        {
            const char* cursor = (time(NULL) % 2) ? "READY. _" : "READY.  ";
            attron(COLOR_PAIR(CP_HEADER) | A_BOLD);
            mvaddstr(h - 3, 3, cursor);
            attroff(COLOR_PAIR(CP_HEADER) | A_BOLD);
        }

        // Footer
        draw_centered(h - 2, w, "CTRL+C TO QUIT  -  C64 CHAIN (C) 2026", CP_HEADER);

        refresh();

        // Input handling
        for (int i = 0; i < 5 && !stop_signal.load(); i++) {
            int ch = getch();
            if (ch == 'q' || ch == 'Q' || ch == 27) {
                stop_signal.store(true);
                break;
            }
            usleep(50000);
        }
    }

    endwin();
    if (scr) delscreen(scr);
    if (tty) fclose(tty);
}

// ---------- Log handler ----------

void tui_log_handler(const std::string& message) {
    NodeStats& stats = get_stats();
    stats.log_msgs_received++;
    if (message.empty()) return;

    // Filter out connection spam (NEW/CLOSE CONNECTION + before_handshake)
    if (message.find("before_handshake") != std::string::npos) return;
    if (message.find("INC] NEW CONNECTION") != std::string::npos) return;
    if (message.find("INC] CLOSE CONNECTION") != std::string::npos) return;
    if (message.find("No available peer in gray list") != std::string::npos) return;
    if (message.find("No available peer in white list") != std::string::npos) return;
    if (message.find("Failed to connect to any") != std::string::npos) return;
    if (message.find("OUT] NEW CONNECTION") != std::string::npos) return;
    if (message.find("OUT] CLOSE CONNECTION") != std::string::npos) return;
    if (message.find("bytes sent for category") != std::string::npos) return;
    if (message.find("bytes received for category") != std::string::npos) return;
    if (message.find("COMMAND_HANDSHAKE") != std::string::npos) return;
    if (message.find("Failed to HANDSHAKE") != std::string::npos) return;
    if (message.find("Failed to invoke command") != std::string::npos) return;
    if (message.find("switching safe mode") != std::string::npos) return;
    if (message.find("clearing used stripe") != std::string::npos) return;
    if (message.find("Resolving node address") != std::string::npos) return;
    if (message.find("Added node:") != std::string::npos) return;
    if (message.find("state: requesting") != std::string::npos) return;
    if (message.find("NOTIFY_GET_TXPOOL") != std::string::npos) return;
    if (message.find("NOTIFY_NEW_TRANSACTIONS") != std::string::npos) return;
    if (message.find("0Connect failed") != std::string::npos) return;
    if (message.find("pruning seed") != std::string::npos) return;

    // --- Always update stats from raw message ---

    // HEIGHT XXXX, difficulty: YYY
    {
        auto p = message.find("HEIGHT ");
        auto d = message.find(", difficulty:");
        if (p != std::string::npos && d != std::string::npos && d > p) {
            try {
                uint64_t h = std::stoull(message.substr(p + 7, d - p - 7));
                auto ds = message.find_first_of("0123456789", d + 13);
                if (ds != std::string::npos) {
                    auto de = message.find_first_not_of("0123456789", ds);
                    uint64_t dv = std::stoull(message.substr(ds, de - ds));
                    stats.height.store(h);
                    stats.difficulty.store(dv);
                    stats.set_status("MINING");
                }
            } catch (...) {}
        }
    }

    // "last block: XXXX,"
    {
        auto p = message.find("last block: ");
        if (p != std::string::npos) {
            try {
                stats.height.store(std::stoull(message.substr(p + 12)));
                stats.set_status("READY");
            } catch (...) {}
        }
    }

    // "block reward: XXX("
    {
        auto p = message.find("block reward: ");
        if (p != std::string::npos) {
            auto e = message.find('(', p + 14);
            if (e != std::string::npos)
                stats.set_block_info("", "", message.substr(p + 14, e - p - 14));
        }
    }

    // "id:   <hash>"
    {
        auto p = message.find("id:");
        if (p != std::string::npos) {
            auto lt = message.find('<', p);
            auto gt = message.find('>', lt != std::string::npos ? lt : 0);
            if (lt != std::string::npos && gt != std::string::npos && gt > lt) {
                std::lock_guard<std::mutex> lock(stats.mtx);
                stats.last_block_id = message.substr(lt + 1, gt - lt - 1);
            }
        }
    }

    // "PoW:  <hash>"
    {
        auto p = message.find("PoW:");
        if (p != std::string::npos) {
            auto lt = message.find('<', p);
            auto gt = message.find('>', lt != std::string::npos ? lt : 0);
            if (lt != std::string::npos && gt != std::string::npos && gt > lt) {
                std::lock_guard<std::mutex> lock(stats.mtx);
                stats.last_pow = message.substr(lt + 1, gt - lt - 1);
            }
        }
    }

    // RPC calls
    if (message.find("Calling RPC") != std::string::npos)
        stats.rpc_calls++;

    // Track blocks received from peers
    static bool block_from_peer = false;
    if (message.find("Received NOTIFY_NEW_FLUFFY_BLOCK") != std::string::npos ||
        message.find("Received NOTIFY_NEW_BLOCK") != std::string::npos) {
        block_from_peer = true;
    }
    // Block counts + generate clean log entries
    bool is_block_added = (message.find("BLOCK SUCCESSFULLY ADDED") != std::string::npos ||
                           message.find("+++++") != std::string::npos);
    bool is_alt_block = (message.find("ALTERNATIVE") != std::string::npos);

    if (is_block_added) {
        stats.blocks_added++;
        char buf[128];
        if (block_from_peer) {
            snprintf(buf, sizeof(buf), "<<<<< BLOCK RECEIVED HEIGHT %lu", stats.height.load());
            stats.add_log(std::string(buf), LOG_NORMAL);
            block_from_peer = false;
        } else {
            stats.set_status("MINING");
            snprintf(buf, sizeof(buf), "+++++ BLOCK MINED! HEIGHT %lu", stats.height.load());
            stats.add_log(std::string(buf), LOG_SUCCESS);
        }
        return;
    }

    if (is_alt_block) {
        stats.blocks_alt++;
        // Don't log alt blocks - too noisy at low difficulty
        return;
    }

    // --- Filter out noisy messages for display ---
    static const char* filters[] = {
        "build/bin/", "__cxa_throw", "Unwound call", "bad_alloc",
        "Exception:", "libboost", "libc.so", "PERF", "HTTP [",
        "POST /json", "GET /get", "Calling RPC", "calling /",
        "Setting LIMIT", "Set limit-", "coinbase_weight",
        "submitblock", "getblocktemplate", "net_service",
        "Starting core", "Starting p2p", "ZMQ", "Set server type",
        "Binding on", "prefix_name", "block reward:", "PoW:",
        "difficulty:", "cumulative", "Run net_service",
        nullptr
    };
    for (int i = 0; filters[i]; i++) {
        if (message.find(filters[i]) != std::string::npos) {
            // Exception: keep lines with "HEIGHT" or "Blockchain" or "BLOCK"
            if (message.find("HEIGHT") != std::string::npos) break;
            if (message.find("Blockchain") != std::string::npos) break;
            if (message.find("BLOCK") != std::string::npos) break;
            return;
        }
    }

    // Also filter "id:  <" lines that aren't block messages
    if (message.find("id:") != std::string::npos && message.find("BLOCK") == std::string::npos)
        return;

    // Determine color
    int color = LOG_NORMAL;
    if (message.find("error") != std::string::npos || message.find("ERROR") != std::string::npos)
        color = LOG_ERROR;
    else if (message.find("initialized OK") != std::string::npos || message.find("READY") != std::string::npos)
        color = LOG_SUCCESS;

    // Strip timestamp prefix "2026-02-11 14:59:56.260     I "
    std::string clean = message;
    auto ts = clean.find(" I ");
    if (ts != std::string::npos && ts < 30)
        clean = clean.substr(ts + 3);
    // Also try " W ", " E " etc
    if (clean == message) {
        for (const char* lvl : {" W ", " E ", " D "}) {
            auto p = clean.find(lvl);
            if (p != std::string::npos && p < 30) {
                clean = clean.substr(p + 3);
                break;
            }
        }
    }

    if (!clean.empty()) {
        // Anti-spam: normalize connection messages (strip UUID and port)
        static std::string last_msg;
        static int repeat_count = 0;
        std::string cmp = clean;
        // Strip UUID patterns (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)
        while (true) {
            auto p = cmp.find_first_of("0123456789abcdef");
            if (p == std::string::npos) break;
            // Check if this looks like a UUID (8-4-4-4-12 with dashes)
            if (p + 36 <= cmp.size() && cmp[p+8] == '-' && cmp[p+13] == '-') {
                cmp.erase(p, 36);
            } else break;
        }
        // Strip port numbers after IPs (e.g. :42340 -> :*)
        for (size_t i = 0; i < cmp.size(); i++) {
            if (cmp[i] == ':' && i + 1 < cmp.size() && isdigit(cmp[i+1])) {
                size_t j = i + 1;
                while (j < cmp.size() && isdigit(cmp[j])) j++;
                cmp.replace(i+1, j-i-1, "*");
            }
        }
        if (cmp == last_msg) {
            repeat_count++;
            if (repeat_count == 5) {
                stats.add_log("  ... (repeated messages hidden)", LOG_WARNING);
            }
            // Only show every 50th repeat after that
            if (repeat_count > 5 && repeat_count % 50 != 0) return;
        } else {
            repeat_count = 0;
            last_msg = cmp;
        }
        stats.add_log(clean, color);
    }
}

// ---------- Easylogging++ Callback ----------

void C64TuiLogCallback::handle(const el::LogDispatchData* data) {
    try {
        if (!data || !data->logMessage()) return;

        const std::string& msg = data->logMessage()->message();
        if (msg.empty()) return;

        // Forward to TUI log handler
        tui_log_handler(msg);
    } catch (...) {
        // Never let exceptions escape the log callback
    }
}

void install_tui_log_callback() {
    el::Helpers::installLogDispatchCallback<C64TuiLogCallback>("C64TuiCallback");
}

} // namespace c64tui

