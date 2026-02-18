#include <vector>
#include "misc_log_ex.h"
#include "misc_language.h"
#include "common/perf_timer.h"
#include "common/threadpool.h"
#include "common/util.h"
#include "ringct/rctSigs.h"
#include "ringct/bulletproofs.h"
#include "ringct/bulletproofs_plus.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_config.h"
#include "rctSigs_old.h"

using std::vector;

namespace rct {

Bulletproof proveRangeBulletproof_old(key &C, key &mask, uint64_t amount)
    {
        mask = rct::skGen();
        Bulletproof proof = bulletproof_PROVE_old(amount, mask);
        CHECK_AND_ASSERT_THROW_MES(proof.V.size() == 1, "V has not exactly one element");
        C = proof.V[0];
        return proof;
    }

Bulletproof proveRangeBulletproof_old(keyV &C, keyV &masks, const std::vector<uint64_t> &amounts)
    {
        masks = rct::skvGen(amounts.size());
        Bulletproof proof = bulletproof_PROVE_old(amounts, masks);
        CHECK_AND_ASSERT_THROW_MES(proof.V.size() == amounts.size(), "V does not have the expected size");
        C = proof.V;
        return proof;
    }

bool verBulletproof_old(const Bulletproof &proof)
    {
      try { return bulletproof_VERIFY_old(proof); }
      catch (...) { return false; }
    }

bool verBulletproof_old(const std::vector<const Bulletproof*> &proofs)
    {
      try { return bulletproof_VERIFY_old(proofs); }
      catch (...) { return false; }
    }

xmr_amount populateFromBlockchainSimple(ctkeyV & mixRing, const ctkey & inPk, int mixin);

rctSig genRctSimple_old(const key &message, const ctkeyV & inSk, const keyV & destinations, const vector<xmr_amount> &inamounts, const vector<xmr_amount> &outamounts, xmr_amount txnFee, const ctkeyM & mixRing, const keyV &amount_keys, const std::vector<unsigned int> & index, ctkeyV &outSk, const RCTConfig &rct_config, hw::device &hwdev) {
        const bool bulletproof = rct_config.range_proof_type != RangeProofBorromean;
        CHECK_AND_ASSERT_THROW_MES(inamounts.size() > 0, "Empty inamounts");
        CHECK_AND_ASSERT_THROW_MES(inamounts.size() == inSk.size(), "Different number of inamounts/inSk");
        CHECK_AND_ASSERT_THROW_MES(outamounts.size() == destinations.size(), "Different number of amounts/destinations");
        CHECK_AND_ASSERT_THROW_MES(amount_keys.size() == destinations.size(), "Different number of amount_keys/destinations");
        CHECK_AND_ASSERT_THROW_MES(index.size() == inSk.size(), "Different number of index/inSk");
        CHECK_AND_ASSERT_THROW_MES(mixRing.size() == inSk.size(), "Different number of mixRing/inSk");
        for (size_t n = 0; n < mixRing.size(); ++n) {
          CHECK_AND_ASSERT_THROW_MES(index[n] < mixRing[n].size(), "Bad index into mixRing");
        }

        rctSig rv;
        rv.type = bulletproof ? RCTTypeSimpleBulletproof : RCTTypeSimple;
        rv.message = message;
        rv.outPk.resize(destinations.size());
        if (bulletproof)
          rv.p.bulletproofs.resize(destinations.size());
        else
          rv.p.rangeSigs.resize(destinations.size());
        rv.ecdhInfo.resize(destinations.size());

        size_t i;
        keyV masks(destinations.size()); //sk mask..
        outSk.resize(destinations.size());
        key sumout = zero();
        for (i = 0; i < destinations.size(); i++) {

            //add destination to sig
            rv.outPk[i].dest = copy(destinations[i]);
            //compute range proof
            if (bulletproof)
              rv.p.bulletproofs[i] = proveRangeBulletproof_old(rv.outPk[i].mask, outSk[i].mask, outamounts[i]);
            else
              rv.p.rangeSigs[i] = proveRange(rv.outPk[i].mask, outSk[i].mask, outamounts[i]);
            #ifdef DBG
            if (bulletproof)
                CHECK_AND_ASSERT_THROW_MES(verBulletproof_old(rv.p.bulletproofs[i]), "verBulletproof failed on newly created proof");
            else
                CHECK_AND_ASSERT_THROW_MES(verRange(rv.outPk[i].mask, rv.p.rangeSigs[i]), "verRange failed on newly created proof");
            #endif
         
            sc_add(sumout.bytes, outSk[i].mask.bytes, sumout.bytes);

            //mask amount and mask
            rv.ecdhInfo[i].mask = copy(outSk[i].mask);
            rv.ecdhInfo[i].amount = d2h(outamounts[i]);
            hwdev.ecdhEncode(rv.ecdhInfo[i], amount_keys[i], rv.type == RCTTypeSimpleBulletproof);
        }

        rv.txnFee = txnFee;
        rv.mixRing = mixRing;
        keyV &pseudoOuts = bulletproof ? rv.p.pseudoOuts : rv.pseudoOuts;
        pseudoOuts.resize(inamounts.size());
        rv.p.MGs.resize(inamounts.size());
        key sumpouts = zero(); //sum pseudoOut masks
        keyV a(inamounts.size());
        for (i = 0 ; i < inamounts.size() - 1; i++) {
            skGen(a[i]);
            sc_add(sumpouts.bytes, a[i].bytes, sumpouts.bytes);
            genC(pseudoOuts[i], a[i], inamounts[i]);
        }
        rv.mixRing = mixRing;
        sc_sub(a[i].bytes, sumout.bytes, sumpouts.bytes);
        genC(pseudoOuts[i], a[i], inamounts[i]);
        DP(pseudoOuts[i]);

        key full_message = get_pre_mlsag_hash(rv,hwdev);
        for (i = 0 ; i < inamounts.size(); i++) {
            rv.p.MGs[i] = proveRctMGSimple(full_message, rv.mixRing[i], inSk[i], a[i], pseudoOuts[i], index[i], hwdev);
        }
        return rv;
    }

rctSig genRctSimple_old(const key &message, const ctkeyV & inSk, const ctkeyV & inPk, const keyV & destinations, const vector<xmr_amount> &inamounts, const vector<xmr_amount> &outamounts, const keyV &amount_keys, xmr_amount txnFee, unsigned int mixin, const RCTConfig &rct_config, hw::device &hwdev) {
        std::vector<unsigned int> index;
        index.resize(inPk.size());
        ctkeyM mixRing;
        ctkeyV outSk;
        mixRing.resize(inPk.size());
        for (size_t i = 0; i < inPk.size(); ++i) {
          mixRing[i].resize(mixin+1);
          index[i] = populateFromBlockchainSimple(mixRing[i], inPk[i], mixin);
        }
        return genRctSimple_old(message, inSk, destinations, inamounts, outamounts, txnFee, mixRing, amount_keys, index, outSk, rct_config, hwdev);
    }

} // namespace rct
