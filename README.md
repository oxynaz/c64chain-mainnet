# C64 Chain — Privacy-First CPU-Mineable Cryptocurrency

![C64 Chain](https://img.shields.io/badge/C64_Chain-v0.8.0-blue)
![License](https://img.shields.io/badge/license-GPLv3-green)
![Algorithm](https://img.shields.io/badge/algorithm-rx%2Fc64-orange)
![Mining](https://img.shields.io/badge/mining-CPU%20only-brightgreen)
![Network](https://img.shields.io/badge/network-TESTNET-yellow)

**C64 Chain** is a privacy-focused, CPU-mineable cryptocurrency inspired by the legendary Commodore 64.
Forked from [Wownero](https://codeberg.org/wownero/wownero) (itself a fork of Monero), C64 Chain is a **new crypto project** featuring CryptoNote privacy, RandomX CPU mining, anti-dump vesting, and a unique retro computing aesthetic.

**Keywords:** cryptocurrency, privacy coin, CPU mining, RandomX, CryptoNote, Monero fork, new crypto, altcoin, mineable coin, decentralized, open source blockchain, proof of work, PoW, crypto mining, solo mining, peer-to-peer, anonymous cryptocurrency, fair launch, no premine, community coin

## ⚠️ Current Status: TESTNET

> **C64 Chain is currently in TESTNET phase.** The mainnet has not launched yet.
> Coins mined on testnet will be transferred to mainnet at a reduced ratio (details TBD).
> Early testnet miners will be rewarded for helping test the network.

## Why C64 Chain?

- **Fair launch** — no premine, no ICO, no VC funding, no insider allocation
- **CPU mining only** — rx/c64 algorithm levels the playing field, anyone can mine from home
- **Privacy by default** — built on CryptoNote/Monero technology with ring signatures, stealth addresses, and RingCT
- **Anti-dump vesting** — block rewards unlock over 90 days, protecting price stability
- **Audited codebase** — security audit completed with all critical fixes applied
- **Active development** — regular updates, responsive team, transparent roadmap
- **Unique identity** — Commodore 64-themed node and miner with retro TUI

## The C64 Spirit 🕹️

C64 Chain is built as a love letter to the Commodore 64, the best-selling home computer of all time. Every detail pays homage:

- **Node TUI**: Full ncurses Commodore 64 boot screen — blue border, PETSCII font, `**** C64 CHAIN NODE V0.1 ****` / `64K RAM SYSTEM  38911 BASIC BYTES FREE` / `READY.`
- **Datasette loading**: The node startup simulates a Datasette tape loading animation with colored bars, just like loading a game in 1984
- **BASIC-style display**: Node status displayed as `LIST` output with numbered lines, like a BASIC program
- **Max supply**: **19,640,000 C64** — 1964 is the year the MOS 6502 CPU was designed, the processor that powered the C64
- **Algorithm name**: `rx/c64` — RandomX variant customized for C64 Chain
- **Miner TUI**: The C64 Miner features its own Commodore 64-themed terminal with `READY.` / `RUN C64MINER` prompt

## Tokenomics

| Parameter | Value |
|-----------|-------|
| **Max supply** | **19,640,000 C64** |
| **Algorithm** | rx/c64 (RandomX variant, CPU-only) |
| **Block time** | 5 minutes (300 seconds) |
| **Initial block reward** | ~149 C64 |
| **Emission speed factor** | 21 |
| **50% mined in** | ~10 months |
| **80% mined in** | ~2 years |
| **96% mined in** | ~4 years |
| **Dev fund** | 2% of each block reward (consensus-enforced) |
| **Emission curve** | Smooth exponential decay (no halving cliffs) |

The emission follows Monero's smooth curve formula: `reward = (supply_cap - already_mined) >> ESF`. This means block rewards decrease gradually with every block, unlike Bitcoin's sudden halvings. Combined with the 19.64M cap, this creates a fair and predictable monetary policy.

### Vesting (Anti-Dump Protection)

Every block reward is split into **4 equal outputs** with staggered unlock times. This prevents miners from dumping all rewards immediately at listing:

| Portion | Unlock after | Blocks |
|---------|-------------|--------|
| 25% | ~24 hours | 288 |
| 25% | ~30 days | 8,640 |
| 25% | ~60 days | 17,280 |
| 25% | ~90 days | 25,920 |

The 2% dev fund unlocks after ~24 hours (288 blocks).

Each coinbase transaction has **5 outputs**: 4 vesting outputs for the miner + 1 dev fund output. Both vesting and the dev fund are enforced at consensus level — blocks without proper structure are rejected by the network.

### Why Vesting Matters

Without vesting, early miners could accumulate large amounts of C64 and dump them as soon as the coin is listed on exchanges, crashing the price for everyone. The 90-day staggered unlock ensures that selling pressure is distributed over time, protecting the coin's value for all participants.

## Security

C64 Chain has undergone a code audit covering all modifications from the Wownero/Monero codebase. Key security features:

- **Dev fund consensus validation** — every node verifies that coinbase transactions contain exactly 5 outputs with correct 2% dev fund amount and 4x25% vesting split
- **Vesting triple enforcement** — enforced at database, node consensus, and wallet level
- **LWMA-1 difficulty algorithm** — responsive difficulty adjustment (Zawy's algorithm) protecting against hashrate manipulation, activated at HF20 (block 2100)
- **Clean codebase** — all legacy Wownero checkpoints, hardcoded difficulty values, and workarounds have been removed

## Hard Fork History

| HF | Block | Description |
|----|-------|-------------|
| HF17 | 0 (genesis) | RandomWOW mining algorithm |
| HF18 | 2 | Fixed unlock time (288 blocks) |
| HF19 | 3 | Tokenomics: 19.64M supply, vesting 4x25%, dev fund 2% |
| HF20 | 2100 | LWMA-1 difficulty algorithm (faster adjustment, 145-block window) |

### HF20 — LWMA-1 Difficulty (v0.7.0+)

At block 2100, C64 Chain activates the LWMA-1 difficulty algorithm (Zawy's Linearly Weighted Moving Average). This replaces the legacy CryptoNote difficulty calculation with a much more responsive algorithm:

- **145-block window** (vs 720 blocks previously) — adjusts ~5x faster
- **Better protection** against hashrate oscillation and timewarp attacks
- **Smoother mining experience** — difficulty tracks actual hashrate more closely

**All nodes must run v0.8.0 or later.**

## Features

- 🖥️ Commodore 64-themed ncurses TUI built into the node
- 📼 Datasette loading animation on startup
- ⛏️ CPU-only mining (rx/c64 algorithm, RandomX variant)
- 💰 2% dev fund for project development (consensus-enforced)
- ⏱️ 5 minute block time
- 🔒 Vesting on block rewards (4x25% staggered unlock over 90 days)
- 🕶️ Privacy by default (Monero/CryptoNote-based)
- 🚫 No premine, no ICO, no VC funding
- 📊 LWMA-1 difficulty algorithm for responsive hashrate adjustment
- 🔍 Security audited codebase

## Quick Start

### Option A: Pre-compiled binaries (Ubuntu 24.04 x86_64)

Download from [Releases](https://github.com/oxynaz/c64chain/releases/tag/v0.8.0):
```bash
wget https://github.com/oxynaz/c64chain/releases/download/v0.8.0/c64chain-v0.8.0-ubuntu24-x86_64.tar.gz
tar xzf c64chain-v0.8.0-ubuntu24-x86_64.tar.gz
chmod +x c64chaind c64wallet c64chain-wallet-rpc
```

### Option B: Build from source

#### 1. Install dependencies (Ubuntu 22.04 / 24.04)
```bash
sudo apt update
sudo apt install -y build-essential cmake pkg-config libboost-all-dev libssl-dev \
    libzmq3-dev libsodium-dev libunwind-dev liblzma-dev libreadline-dev \
    libexpat1-dev libpgm-dev libhidapi-dev libusb-1.0-0-dev \
    libprotobuf-dev protobuf-compiler libudev-dev libncurses5-dev libncursesw5-dev \
    libunbound-dev liblmdb-dev libminiupnpc-dev libuv1-dev git screen
```

#### 2. Disable IPv6 (required for peer discovery)
```bash
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
```

To make it permanent:
```bash
echo "net.ipv6.conf.all.disable_ipv6=1" | sudo tee -a /etc/sysctl.conf
echo "net.ipv6.conf.default.disable_ipv6=1" | sudo tee -a /etc/sysctl.conf
```

#### 3. Build the node and wallet
```bash
git clone https://github.com/oxynaz/c64chain.git
cd c64chain
mkdir build && cd build
cmake ..
make -j$(nproc)
```

#### 4. Verify the build
```bash
./bin/c64chaind --version
```
Should display: `C64 Chain 'Genesis' (v0.8.0-release)`

This produces binaries in `build/bin/`:
- `c64chaind` — the node daemon
- `c64wallet` — the wallet CLI
- `c64chain-wallet-rpc` — wallet RPC server (for exchange/pool integration)

### Updating to a new version

```bash
cd ~/c64chain
git fetch --tags --force
git pull
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
./bin/c64chaind --version
```

> ⚠️ **Always use `git fetch --tags --force`** before `git pull`. Without this, the version will display incorrectly (commit hash instead of `release`).
> The `rm -rf build` ensures a clean build with no cached artifacts.
> Always verify with `--version` after building — it should show `release`, not a commit hash.

## Run the node
```bash
./c64chaind --testnet --data-dir=$HOME/.c64chain --rpc-bind-port=29641 --log-level=1
```

The node will automatically connect to seed nodes and sync the blockchain.

> **Tip:** Use `screen` to run in background:
> ```bash
> screen -dmS node bash -c "cd ~/c64chain/build/bin && ./c64chaind --testnet --data-dir=\$HOME/.c64chain --log-level=1 --out-peers 64 --in-peers 128"
> ```
> View the TUI: `screen -r node` (detach with Ctrl+A then D)

### Verify the node is running
```bash
curl -s http://127.0.0.1:29641/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_info"}' -H 'Content-Type: application/json' | python3 -c 'import sys,json;d=json.load(sys.stdin)["result"];print("Height:",d["height"],"Peers:",d["outgoing_connections_count"],"out /",d["incoming_connections_count"],"in")'
```

### LAN Mining Setup

If you have multiple machines behind the same internet connection (same external IP), only one machine can run a node. The others mine directly on the node's RPC via your local network:

**On the node machine** — add these flags to open RPC on the local network:
```bash
./c64chaind --testnet --data-dir=$HOME/.c64chain --rpc-bind-ip=0.0.0.0 --confirm-external-bind --log-level=1
```

**On other LAN machines** — point the miner to the node machine's local IP:
```json
{
    "url": "192.168.X.X:29641",
    "daemon": true
}
```

No node needed on the miner-only machines.

## Create a wallet

> ⚠️ **You need a wallet address before you can mine.** Follow this step first.
```bash
./c64wallet --testnet --daemon-address=127.0.0.1:29641 --generate-new-wallet=$HOME/.c64chain/mywallet
```

It will ask for a password. **Save your wallet address** (starts with `9...`) and your **seed phrase** (25 words). You will need the address to configure the miner.

## Open an existing wallet
```bash
./c64wallet --testnet --daemon-address=127.0.0.1:29641 --wallet-file=$HOME/.c64chain/mywallet
```

### Wallet commands

| Command | Description |
|---------|-------------|
| `balance` | Check your balance (shows locked/unlocked due to vesting) |
| `vesting` | Show full vesting unlock timeline with per-tier status |
| `address` | Show your address |
| `transfer ADDRESS AMOUNT` | Send C64 coins |
| `seed` | Display your recovery seed phrase |
| `help` | Show available commands |
| `exit` | Quit the wallet |

### The `vesting` command

The `vesting` command displays a complete overview of your mined rewards and their unlock schedule:

```
  === C64 VESTING STATUS ===

  Network height:  1685
  Total balance:   158811.2489 C64
  Unlocked:        34156.1846 C64 (21.5%)
  Locked:          124655.0643 C64 (78.5%)

  --- Per-Tier Status ---
  Tier 1 (24h): 33811.3783 unlocked, 5805.2324 locked
  Tier 2 (30d): 0.0000 unlocked, 39616.6106 locked
  Tier 3 (60d): 0.0000 unlocked, 39616.6106 locked
  Tier 4 (90d): 0.0000 unlocked, 39616.6106 locked

  --- Unlock Timeline ---
  When                   Date                 + Unlocked   Total available       %
  Now                    -                             -     34156.1846 C64   21.5%
  + 24 hours             2026-02-16 13:19   5805.2324 C64    39961.4170 C64   25.2%
  + 30 days              2026-03-17 13:19  39616.6106 C64    79578.0276 C64   50.1%
  + 60 days              2026-04-16 14:19  39616.6106 C64   119194.6383 C64   75.1%
  + 90 days              2026-05-16 14:19  39616.6106 C64   158811.2489 C64  100.0%

  100% unlocked: 2026-05-16 14:09 (in ~89 days)
  Total: 158811.2489 C64
```

This shows exactly when your mined coins will become spendable, with projected dates for each vesting tier.

## Mine C64

Download the miner from [C64 Miner Releases](https://github.com/oxynaz/c64miner/releases/tag/v0.2.1), or build from [source](https://github.com/oxynaz/c64miner).

Create a `config.json`:
```json
{
    "autosave": false,
    "donate-level": 0,
    "cpu": { "enabled": true },
    "opencl": false,
    "cuda": false,
    "pools": [{
        "url": "127.0.0.1:29641",
        "user": "YOUR_C64_WALLET_ADDRESS_HERE",
        "algo": "rx/c64",
        "coin": "c64chain",
        "daemon": true,
        "daemon-poll-interval": 1000
    }],
    "print-time": 5
}
```

> ⚠️ `"daemon": true` and `"coin": "c64chain"` are **required**.

Run the miner:
```bash
sudo ./c64miner -c config.json -t $(nproc)
```

Always run with `sudo` for best performance (huge pages). The miner features a Commodore 64-themed TUI showing hashrate, accepted blocks, and live mining logs.

## Network Configuration

| Parameter | Testnet | Mainnet |
|-----------|---------|---------|
| P2P Port | 29640 | 19640 |
| RPC Port | 29641 | 19641 |
| Algorithm | rx/c64 | rx/c64 |
| Block time | 5 minutes | 5 minutes |
| Max supply | 19,640,000 | 19,640,000 |
| Dev fund | 2% | 2% |

## Seed Nodes

5 seed nodes are hardcoded in the node binary across 3 continents (Europe, North America, Asia). Your node will automatically discover and connect to them.

## Block Explorer

- **[c64chain.com](https://c64chain.com)** — search blocks, transactions, network stats

## Downloads

| Component | Binary | Source |
|-----------|--------|--------|
| Node + Wallet | [v0.8.0 Release](https://github.com/oxynaz/c64chain/releases/tag/v0.8.0) | [oxynaz/c64chain](https://github.com/oxynaz/c64chain) |
| Miner | [v0.2.1 Release](https://github.com/oxynaz/c64miner/releases/tag/v0.2.1) | [oxynaz/c64miner](https://github.com/oxynaz/c64miner) |

## Comparison with Similar Projects

| Feature | C64 Chain | Monero | Wownero |
|---------|-----------|--------|---------|
| Algorithm | rx/c64 | RandomX | RandomWOW |
| Max supply | 19.64M | 18.4M + tail | Unlimited |
| Block time | 5 min | 2 min | 5 min |
| Dev fund | 2% consensus | Community funded | None |
| Vesting | 90-day 4-tier | None | None |
| Privacy | Full CryptoNote | Full CryptoNote | Full CryptoNote |
| Difficulty algo | LWMA-1 (HF20) | LWMA-1 | LWMA-1 |

## Roadmap

- [x] Testnet launch
- [x] Security audit & fixes (v0.6.0)
- [x] HF20: LWMA-1 difficulty algorithm (v0.7.0), dev fund crypto verification (v0.8.0)
- [ ] Mining pool support
- [ ] Mainnet launch
- [ ] Exchange listings


## Community

- Discord: [discord.gg/MTRgHT8r45](https://discord.gg/MTRgHT8r45)
- GitHub: [github.com/oxynaz](https://github.com/oxynaz)
- Block Explorer: [c64chain.com](https://c64chain.com)

## Credits & License

C64 Chain is a fork of [Wownero](https://codeberg.org/wownero/wownero), which is a fork of [Monero](https://github.com/monero-project/monero).

Licensed under the **GNU General Public License v3.0** — see [LICENSE](LICENSE).

All original Monero and Wownero copyrights remain intact.
