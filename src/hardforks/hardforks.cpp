// Copyright (c) 2014-2022, The Monero Project
// C64 CHAIN fork - all rights reserved under original BSD license
#include "hardforks.h"
#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "blockchain.hardforks"

// C64 CHAIN hard forks — MAINNET Option A
// Genesis = v17 (forced). v21 activated at block 2 via vote threshold=1.
// Block 0 (genesis): major=17, minor=17 → fork index 0 (v17)
// Block 1: major=17, minor=21 (vote) → 1 vote v21, threshold=1 reached → fork index 1 (v21)
// Block 2+: major=21, minor=21
const hardfork_t mainnet_hard_forks[] = {
  { 17, 0, 1, 1700000000 },
  { 21, 2, 1, 1700000001 },
};
const size_t num_mainnet_hard_forks = sizeof(mainnet_hard_forks) / sizeof(mainnet_hard_forks[0]);
const uint64_t mainnet_hard_fork_version_1_till = 0;

const hardfork_t testnet_hard_forks[] = {
  { 17, 0, 1, 1700000000 },
  { 18, 2, 1, 1700000001 },
  { 19, 3, 1, 1700000002 },
  { 20, 2100, 1, 1739739600 },
};
const size_t num_testnet_hard_forks = sizeof(testnet_hard_forks) / sizeof(testnet_hard_forks[0]);
const uint64_t testnet_hard_fork_version_1_till = 0;

const hardfork_t stagenet_hard_forks[] = {
  { 17, 0, 1, 1700000000 },
  { 18, 2, 1, 1700000001 },
  { 19, 3, 1, 1700000002 },
  { 20, 2100, 1, 1739739600 },
};
const size_t num_stagenet_hard_forks = sizeof(stagenet_hard_forks) / sizeof(stagenet_hard_forks[0]);
