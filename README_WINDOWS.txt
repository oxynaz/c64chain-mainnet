================================================================================
C64 CHAIN — MINING ON WINDOWS (WSL Ubuntu 24) — STEP BY STEP
================================================================================
From zero to mining in ~20 minutes
Tested on Windows 10/11 with WSL2
================================================================================


WHAT IS WSL?
================================================================================

WSL (Windows Subsystem for Linux) lets you run a full Linux environment
directly inside Windows, no dual boot or virtual machine needed. It's built
into Windows 10/11 and is the easiest way to mine C64 Chain from a Windows PC.


STEP 1 — INSTALL WSL2 + UBUNTU 24.04
================================================================================

Open PowerShell as Administrator (right-click → Run as Administrator) and run:

wsl --install -d Ubuntu-24.04

Wait for the download and installation to complete.
It will ask for a username: just press Enter to use the default.
Then it will ask you to set an admin password — type it and remember it!
(The password won't show on screen when you type, that's normal.)

Restart your computer if asked.

After reboot, open "Ubuntu 24.04" from the Start menu.
You should see a terminal ready to use.


STEP 2 — UPDATE SYSTEM & INSTALL DEPENDENCIES
================================================================================

Copy and paste this entire block into your Ubuntu terminal:

sudo apt update && sudo apt upgrade -y && sudo apt install -y build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libsodium-dev libunwind-dev liblzma-dev libreadline-dev libexpat1-dev libpgm-dev libhidapi-dev libusb-1.0-0-dev libprotobuf-dev protobuf-compiler libudev-dev libncurses5-dev libncursesw5-dev libunbound-dev liblmdb-dev libminiupnpc-dev libuv1-dev git screen


STEP 3 — DISABLE IPv6
================================================================================

sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1


STEP 4 — BUILD THE NODE
================================================================================

cd ~
git clone https://github.com/oxynaz/c64chain-mainnet.git
cd c64chain-mainnet
mkdir build && cd build
cmake ..
make -j$(nproc)

This will take 10-20 minutes depending on your CPU.
When done, verify:

./bin/c64chaind-mainnet --version

You should see: C64 Chain 'Mainnet' (v1.0.0-...)


STEP 5 — START THE NODE
================================================================================

screen -dmS node bash -c "cd ~/c64chain-mainnet/build/bin && ./c64chaind-mainnet --non-interactive --log-level=1 --out-peers 64 --in-peers 128"

To view the node (Commodore 64 boot screen!):

screen -r node

Detach with: Ctrl+A then D

Wait about 2 minutes for the node to sync, then verify with this command:

curl -s http://127.0.0.1:19641/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_info"}' -H 'Content-Type: application/json' | python3 -c 'import sys,json;d=json.load(sys.stdin)["result"];print("Height:",d["height"],"Synced:",d["synchronized"])'

You should see a block height matching the explorer (https://c64chain.com)
and "Synced: True". If not, wait a bit more and try again.


STEP 6 — CREATE A WALLET
================================================================================

cd ~/c64chain-mainnet/build/bin
./c64wallet-mainnet --daemon-address=127.0.0.1:19641 --generate-new-wallet=$HOME/c64wallet

It will ask you to:
1. Set a password (remember it!)
2. Choose a language for the seed phrase

⚠️ IMPORTANT: Write down your 25-word seed phrase and keep it safe!
This is the ONLY way to recover your wallet.

Type "address all" to see your wallet address (starts with "Wo...").
Copy it, you need it for Step 8.

Type "exit" to close the wallet.


STEP 7 — BUILD THE MINER
================================================================================

cd ~
git clone https://github.com/oxynaz/c64miner.git
cd c64miner
mkdir build && cd build
cmake .. -DWITH_OPENCL=OFF -DWITH_CUDA=OFF -DWITH_HWLOC=OFF
make -j$(nproc)


STEP 8 — CONFIGURE POOL MINING (Suprnova)
================================================================================

Replace YOUR_WALLET_ADDRESS with your actual Wo... address:

cd ~/c64miner/build
cat > config.json << 'EOF'
{
    "autosave": false,
    "donate-level": 0,
    "cpu": { "enabled": true },
    "opencl": false,
    "cuda": false,
    "pools": [{
        "url": "stratum+tcp://c64.suprnova.cc:6465",
        "user": "YOUR_WALLET_ADDRESS",
        "pass": "x",
        "algo": "rx/c64",
        "coin": "c64chain"
    }],
    "print-time": 5
}
EOF

⚠️ Don't forget to replace YOUR_WALLET_ADDRESS before pressing Enter!


STEP 9 — START MINING!
================================================================================

sudo ./c64miner -c config.json -t $(nproc)

It will ask for your admin password (the one you set in Step 1).
The miner is now sending shares to Suprnova pool!

Check your stats at: https://c64.suprnova.cc/index.html

⚠️ Disclaimer: Suprnova is mentioned as an example only. The C64 Chain team
is not affiliated with this pool. You are free to use any compatible pool.
See the #mining channel on Discord for other options.


================================================================================
USEFUL COMMANDS
================================================================================

--- Node ---

Start node:
screen -dmS node bash -c "cd ~/c64chain-mainnet/build/bin && ./c64chaind-mainnet --non-interactive --log-level=1 --out-peers 64 --in-peers 128"

Check node status:
curl -s http://127.0.0.1:19641/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_info"}' -H 'Content-Type: application/json' | python3 -c 'import sys,json;d=json.load(sys.stdin)["result"];print("Height:",d["height"],"Synced:",d["synchronized"])'

--- Wallet ---

Open your wallet:
cd ~/c64chain-mainnet/build/bin
./c64wallet-mainnet --daemon-address=127.0.0.1:19641 --wallet-file=$HOME/c64wallet

Inside wallet:
balance — Check your balance (locked/unlocked)
vesting — Show vesting unlock timeline
address all — Show your wallet address
transfer ADDR AMOUNT — Send C64 coins
seed — Display recovery seed phrase
exit — Quit wallet

--- Miner ---

Start mining:
cd ~/c64miner/build
sudo ./c64miner -c config.json -t $(nproc)

Stop mining:
Ctrl+C

--- Screen ---

List running screens:
screen -ls

Attach to node screen:
screen -r node

Detach from screen:
Ctrl+A then D

Kill a screen session:
screen -X -S node quit

--- Git (updating to a new version) ---

Update the node:
cd ~/c64chain-mainnet
git fetch --tags --force
git pull
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)

Update the miner:
cd ~/c64miner
git fetch --tags --force
git pull
rm -rf build
mkdir build && cd build
cmake .. -DWITH_OPENCL=OFF -DWITH_CUDA=OFF -DWITH_HWLOC=OFF
make -j$(nproc)

--- After WSL Reboot ---

Every time you close and reopen Ubuntu, you need to:
1. Disable IPv6: sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1 && sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
2. Start the node (see above)
3. Wait for sync
4. Start the miner (see above)


================================================================================
TROUBLESHOOTING
================================================================================

"Cannot connect to daemon"
→ Your node is not running or not synced yet. Check Step 5.

"Miner shows 0 H/s"
→ Try running with sudo: sudo ./c64miner -c config.json

Build errors during cmake/make
→ Make sure you installed ALL dependencies from Step 2.

Node stuck syncing
→ Give it time, initial sync can take a few minutes.
→ Check internet access in WSL: ping google.com

WSL not found / wsl command not recognized
→ Enable WSL in Windows Features:
Control Panel → Programs → Turn Windows features on or off
→ Check "Windows Subsystem for Linux" and "Virtual Machine Platform"
→ Restart your computer


================================================================================
RESOURCES
================================================================================

Block Explorer: https://c64chain.com
Suprnova Pool: https://c64.suprnova.cc/index.html
rplant Pool: https://pool.rplant.xyz
Discord: https://discord.gg/MTRgHT8r45
GitHub (Node): https://github.com/oxynaz/c64chain-mainnet
GitHub (Miner): https://github.com/oxynaz/c64miner

================================================================================
Happy mining! 🕹️⛏️
================================================================================
