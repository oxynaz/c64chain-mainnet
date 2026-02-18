#pragma once

#include <vector>
#include "ringct/rctSigs.h"
#include "ringct/bulletproofs.h"

namespace hw { class device; }

namespace rct {

Bulletproof proveRangeBulletproof_old(key &C, key &mask, uint64_t amount);
Bulletproof proveRangeBulletproof_old(keyV &C, keyV &masks, const std::vector<uint64_t> &amounts);

bool verBulletproof_old(const Bulletproof &proof);
bool verBulletproof_old(const std::vector<const Bulletproof*> &proofs);

rctSig genRctSimple_old(const key &message, const ctkeyV & inSk, const keyV & destinations, const std::vector<xmr_amount> &inamounts, const std::vector<xmr_amount> &outamounts, xmr_amount txnFee, const ctkeyM & mixRing, const keyV &amount_keys, const std::vector<unsigned int> & index, ctkeyV &outSk, const RCTConfig &rct_config, hw::device &hwdev);
rctSig genRctSimple_old(const key &message, const ctkeyV & inSk, const ctkeyV & inPk, const keyV & destinations, const std::vector<xmr_amount> &inamounts, const std::vector<xmr_amount> &outamounts, const keyV & amount_keys, xmr_amount txnFee, unsigned int mixin, const RCTConfig &rct_config, hw::device &hwdev);

} // namespace rct
