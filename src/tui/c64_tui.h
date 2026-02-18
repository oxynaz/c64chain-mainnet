#pragma once

#include <ncurses.h>
#include <string>
#include <deque>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdint>
#include "misc_log_ex.h"

namespace c64tui {

// Shared state between daemon and TUI
struct NodeStats {
    std::atomic<uint64_t> height{0};
    std::atomic<uint64_t> difficulty{0};
    std::atomic<uint64_t> blocks_added{0};
    std::atomic<uint64_t> blocks_alt{0};
    std::atomic<uint64_t> rpc_calls{0};
    std::atomic<uint64_t> log_msgs_received{0};
    std::atomic<uint64_t> peers_out{0};
    std::atomic<uint64_t> peers_in{0};
    std::atomic<uint64_t> target_height{0};
    std::atomic<bool> synced{false};
    std::atomic<bool> mining{false};

    std::mutex mtx;
    std::string last_block_id;
    std::string last_pow;
    std::string last_reward;
    std::string status;
    std::deque<std::pair<std::string, int>> log_lines; // text + color type

    void set_status(const std::string& s);
    void add_log(const std::string& line, int color_type = 0);
    void set_block_info(const std::string& id, const std::string& pow, const std::string& reward);
};

// Global stats instance
NodeStats& get_stats();

// Custom log sink that feeds into TUI
void tui_log_handler(const std::string& message);

// Datasette animation (pre-curses, raw ANSI)
void play_datasette_animation();

// Main TUI loop (blocks until quit)
void run_tui(std::atomic<bool>& stop_signal);

// Color types for log lines
enum LogColor {
    LOG_NORMAL = 0,
    LOG_SUCCESS = 1,
    LOG_ERROR = 2,
    LOG_WARNING = 3,
    LOG_INFO = 4
};

// Easylogging++ callback to intercept logs
class C64TuiLogCallback : public el::LogDispatchCallback {
protected:
    void handle(const el::LogDispatchData* data) override;
};

// Install the log callback (call after mlog_configure)
void install_tui_log_callback();

} // namespace c64tui
