// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "checkpoints.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb4;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0x83;
        pchMessageStart[3] = 0xe7;
        vAlertPubKey = ParseHex("04a2f222989769417eb053cd9f16a9a2894ad5eb9fd13c016ed91528241bcf3bd55023679be17f0bd3a16e6fbebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 11628;
        nRPCPort = 11629;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		
        const char* pszTimestamp = "https://www.theguardian.com/money/2017/nov/29/value-of-uks-housing-stock-soars-past-6tn"; // Value of UK's housing stock soars past £6 trillion
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 4867235 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1511976360, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1511976360;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 527493;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xd2e6738f0f0f436fd639462ffe49433802c793e439ea2af5fd6cc4f000fa19d5"));
        assert(genesis.hashMerkleRoot == uint256("0xb34392195c9c24abc651be9d0b7caffebd14b2bf97a3cc5cd4057376f8c2980d"));

        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(12);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(24);
        base58Prefixes[SECRET_KEY] =     list_of(48);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x44)(0xA6)(0x9C);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x44)(0xD7)(0x3B);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x9a;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xd0;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04a2f222989769417eb053cd9f16a9a2894ad5eb9fd13c016ed91528241bcf3bd55023679be17f0bd3a16e6fbebbbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 21628;
        nRPCPort = 21629;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 510649249; 
        genesis.nNonce = 94387;

        //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(13);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(26);
        base58Prefixes[SECRET_KEY]     = list_of(52);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x66)(0xD2)(0xC4);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x66)(0x9B)(0x3F);


        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nPOSStartBlock = 150;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
