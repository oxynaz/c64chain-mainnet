# C64 Chain — Privacy-First CPU-Mineable Cryptocurrency

[![C64 Chain](https://img.shields.io/badge/C64_Chain-v1.0.0-blue)](https://github.com/oxynaz/c64chain-mainnet)
[![License](https://img.shields.io/badge/license-GPLv3-green)](LICENSE)
[![Algorithm](https://img.shields.io/badge/algorithm-rx%2Fc64-orange)](https://github.com/oxynaz/c64chain-mainnet)
[![Mining](https://img.shields.io/badge/mining-CPU%20only-brightgreen)](https://github.com/oxynaz/c64chain-mainnet)
[![Network](https://img.shields.io/badge/network-MAINNET%20LIVE-brightgreen)](https://github.com/oxynaz/c64chain-mainnet)

**C64 Chain** is a privacy-focused, CPU-mineable cryptocurrency inspired by the legendary Commodore 64.
Forked from [Wownero](https://codeberg.org/wownero/wownero) (itself a fork of Monero), C64 Chain is a **new crypto project** featuring CryptoNote privacy, RandomX CPU mining, anti-dump vesting, and a unique retro computing aesthetic.

**Keywords:** cryptocurrency, privacy coin, CPU mining, RandomX, CryptoNote, Monero fork, new crypto, altcoin, mineable coin, decentralized, open source blockchain, proof of work, PoW, crypto mining, solo mining, peer-to-peer, anonymous cryptocurrency, fair launch, no premine, community coin

## 🚀 MAINNET IS LIVE

> **C64 Chain mainnet launched on February 19, 2026.**
> Mining is open to everyone. Download, build, and start mining now!

## Why C64 Chain?

* **Fair launch** — no premine, no ICO, no VC funding, no insider allocation
* **CPU mining only** — rx/c64 algorithm levels the playing field, anyone can mine from home
* **Privacy by default** — built on CryptoNote/Monero technology with ring signatures, stealth addresses, and RingCT
* **Anti-dump vesting** — block rewards unlock over 90 days, protecting price stability
* **Audited codebase** — security audit completed with all critical fixes applied
* **Active development** — regular updates, responsive team, transparent roadmap
* **Unique identity** — Commodore 64-themed node and miner with retro TUI

## The C64 Spirit 🕹️

C64 Chain is built as a love letter to the Commodore 64, the best-selling home computer of all time. Every detail pays homage:

* **Node TUI**: Full ncurses Commodore 64 boot screen — blue border, PETSCII font, `**** C64 CHAIN NODE V1.0 ****` / `64K RAM SYSTEM 38911 BASIC BYTES FREE` / `READY.`
* **Datasette loading**: The node startup simulates a Datasette tape loading animation with colored bars, just like loading a game in 1984
* **BASIC-style display**: Node status displayed as `LIST` output with numbered lines, like a BASIC program
* **Max supply**: **19,640,000 C64** — 1964 is the year the MOS 6502 CPU was designed, the processor that powered the C64
* **Algorithm name**: `rx/c64` — RandomX variant customized for C64 Chain
* **Miner TUI**: The C64 Miner features its own Commodore 64-themed terminal with `READY.` / `RUN C64MINER` prompt

## Tokenomics

| Parameter | Value |
| --- | --- |
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
| --- | --- | --- |
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

* **Dev fund consensus validation** — every node verifies that coinbase transactions contain exactly 5 outputs with correct 2% dev fund amount and 4x25% vesting split
* **Vesting triple enforcement** — enforced at database, node consensus, and wallet level
* **LWMA-1 difficulty algorithm** — responsive difficulty adjustment (Zawy's algorithm) protecting against hashrate manipulation, activated at HF20 (block 2100)
* **Clean codebase** — all legacy Wownero checkpoints, hardcoded difficulty values, and workarounds have been removed

## Hard Fork History

| HF | Block | Description |
| --- | --- | --- |
| HF17 | 0 (genesis) | RandomWOW mining algorithm |
| HF18 | 2 | Fixed unlock time (288 blocks) |
| HF19 | 3 | Tokenomics: 19.64M supply, vesting 4x25%, dev fund 2% |
| HF20 | 2100 | LWMA-1 difficulty algorithm (faster adjustment, 145-block window) |

### HF20 — LWMA-1 Difficulty (v1.0.0)

At block 2100, C64 Chain activates the LWMA-1 difficulty algorithm (Zawy's Linearly Weighted Moving Average). This replaces the legacy CryptoNote difficulty calculation with a much more responsive algorithm:

* **145-block window** (vs 720 blocks previously) — adjusts ~5x faster
* **Better protection** against hashrate oscillation and timewarp attacks
* **Smoother mining experience** — difficulty tracks actual hashrate more closely

## Features

* 🖥️ Commodore 64-themed ncurses TUI built into the node
* 📼 Datasette loading animation on startup
* ⛏️ CPU-only mining (rx/c64 algorithm, RandomX variant)
* 💰 2% dev fund for project development (consensus-enforced)
* ⏱️ 5 minute block time
* 🔒 Vesting on block rewards (4x25% staggered unlock over 90 days)
* 🕶️ Privacy by default (Monero/CryptoNote-based)
* 🚫 No premine, no ICO, no VC funding
* 📊 LWMA-1 difficulty algorithm for responsive hashrate adjustment
* 🔍 Security audited codebase

## Quick Start — Build from source

### 1. Install dependencies (Ubuntu 22.04 / 24.04)

```
sudo apt update
sudo apt install -y build-essential cmake pkg-config libboost-all-dev libssl-dev \
    libzmq3-dev libsodium-dev libunwind-dev liblzma-dev libreadline-dev \
    libexpat1-dev libpgm-dev libhidapi-dev libusb-1.0-0-dev \
    libprotobuf-dev protobuf-compiler libudev-dev libncurses5-dev libncursesw5-dev \
    libunbound-dev liblmdb-dev libminiupnpc-dev libuv1-dev git screen
```

### 2. Disable IPv6 (required for peer discovery)

```
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
```

To make it permanent:

```
echo "net.ipv6.conf.all.disable_ipv6=1" | sudo tee -a /etc/sysctl.conf
echo "net.ipv6.conf.default.disable_ipv6=1" | sudo tee -a /etc/sysctl.conf
```

### 3. Build the node and wallet

```
git clone https://github.com/oxynaz/c64chain-mainnet.git
cd c64chain-mainnet
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### 4. Verify the build

```
./bin/c64chaind-mainnet --version
```

Should display: `C64 Chain 'Mainnet' (v1.0.0-...)`

This produces binaries in `build/bin/`:

* `c64chaind-mainnet` — the node daemon
* `c64wallet-mainnet` — the wallet CLI
* `c64chain-wallet-rpc-mainnet` — wallet RPC server (for exchange/pool integration)

### Updating to a new version

```
cd ~/c64chain-mainnet
git fetch --tags --force
git pull
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
./bin/c64chaind-mainnet --version
```

> ⚠️ **Always use `git fetch --tags --force`** before `git pull`. Without this, the version will display incorrectly.
> The `rm -rf build` ensures a clean build with no cached artifacts.

## Run the node

```
./c64chaind-mainnet --non-interactive --rpc-bind-port=19641 --log-level=1
```

The node will automatically connect to seed nodes and sync the blockchain.

> **Tip:** Use `screen` to run in background:
>
> ```
> screen -dmS node bash -c "cd ~/c64chain-mainnet/build/bin && ./c64chaind-mainnet --non-interactive --log-level=1 --out-peers 64 --in-peers 128"
> ```
>
> View the TUI: `screen -r node` (detach with Ctrl+A then D)

### Verify the node is running

```
curl -s http://127.0.0.1:19641/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_info"}' -H 'Content-Type: application/json' | python3 -c 'import sys,json;d=json.load(sys.stdin)["result"];print("Height:",d["height"],"Peers:",d["outgoing_connections_count"],"out /",d["incoming_connections_count"],"in")'
```

### LAN Mining Setup

If you have multiple machines behind the same internet connection (same external IP), only one machine can run a node. The others mine directly on the node's RPC via your local network:

**On the node machine** — add these flags to open RPC on the local network:

```
./c64chaind-mainnet --non-interactive --rpc-bind-ip=0.0.0.0 --confirm-external-bind --log-level=1
```

**On other LAN machines** — point the miner to the node machine's local IP:

```
{
    "url": "192.168.X.X:19641",
    "daemon": true
}
```

No node needed on the miner-only machines.

## Create a wallet

```
./c64wallet-mainnet --daemon-address=127.0.0.1:19641 --generate-new-wallet=$HOME/.c64chain_mainnet/mywallet
```

It will ask for a password. **Save your wallet address** (starts with `Wo...`) and your **seed phrase** (25 words). You will need the address to configure the miner.

## Open an existing wallet

```
./c64wallet-mainnet --daemon-address=127.0.0.1:19641 --wallet-file=$HOME/.c64chain_mainnet/mywallet
```

### Wallet commands

| Command | Description |
| --- | --- |
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

Build the miner from [source](https://github.com/oxynaz/c64miner):

```
git clone https://github.com/oxynaz/c64miner.git
cd c64miner
mkdir build && cd build
cmake .. -DWITH_OPENCL=OFF -DWITH_CUDA=OFF -DWITH_HWLOC=OFF
make -j$(nproc)
```

Create a `config.json`:

```
{
    "autosave": false,
    "donate-level": 0,
    "cpu": { "enabled": true },
    "opencl": false,
    "cuda": false,
    "pools": [{
        "url": "127.0.0.1:19641",
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

```
sudo ./c64miner -c config.json -t $(nproc)
```

Always run with `sudo` for best performance (huge pages). The miner features a Commodore 64-themed TUI showing hashrate, accepted blocks, and live mining logs.

## Network Configuration

| Parameter | Value |
| --- | --- |
| P2P Port | 19640 |
| RPC Port | 19641 |
| Algorithm | rx/c64 |
| Block time | 5 minutes |
| Max supply | 19,640,000 |
| Dev fund | 2% |

## Seed Nodes

5 seed nodes are hardcoded in the node binary across 3 continents (Europe, North America). Your node will automatically discover and connect to them.

## Block Explorer

* **[c64chain.com](https://c64chain.com)** — search blocks, transactions, network stats

## Comparison with Similar Projects

| Feature | C64 Chain | Monero | Wownero |
| --- | --- | --- | --- |
| Algorithm | rx/c64 | RandomX | RandomWOW |
| Max supply | 19.64M | 18.4M + tail | Unlimited |
| Block time | 5 min | 2 min | 5 min |
| Dev fund | 2% consensus | Community funded | None |
| Vesting | 90-day 4-tier | None | None |
| Privacy | Full CryptoNote | Full CryptoNote | Full CryptoNote |
| Difficulty algo | LWMA-1 (HF20) | LWMA-1 | LWMA-1 |

## Roadmap

* ~~Testnet launch~~
* ~~Security audit & fixes~~
* ~~HF20: LWMA-1 difficulty algorithm, dev fund crypto verification~~
* ✅ **Mainnet launch — February 19, 2026**
* Mining pool support
* Exchange listings

## Community

* Discord: https://discord.gg/yj2vACFJCj
* GitHub: [github.com/oxynaz](https://github.com/oxynaz)
* Block Explorer: [c64chain.com](https://c64chain.com)

## Credits & License

C64 Chain is a fork of [Wownero](https://codeberg.org/wownero/wownero), which is a fork of [Monero](https://github.com/monero-project/monero).

Licensed under the **GNU General Public License v3.0** — see [LICENSE](LICENSE).

All original Monero and Wownero copyrights remain intact.
