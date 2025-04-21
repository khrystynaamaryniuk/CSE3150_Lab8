#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>
#include <memory>
#include <vector>
#include "NfToken.h"
#include "ShaMessageDigestHash.h"
#include "ManageTokens.h"

using namespace std;

// Test the NfToken class
TEST_CASE("Test NfToken class") {
    NfToken nft("test_token");

  
    CHECK(nft.getName() == "test_token");

  
    nft.setHash("1234567890");
    CHECK(nft.getHash() == "1234567890");


    nft.setName("updated_name");
    CHECK(nft.getName() == "updated_name");
}

// Test the ShaMessageDigestHash class
TEST_CASE("Test ShaMessageDigestHash class") {
    ShaMessageDigestHash sha;

    
    sha.compHash("test_string");
    // 4b641e9a923d1ea57e18fe41dcb543e2c4005c41ff210864a710b0fbb2654c11 is a hash before for test_string
    CHECK(sha.getHash() == "4b641e9a923d1ea57e18fe41dcb543e2c4005c41ff210864a710b0fbb2654c11");
}

// Test the ManageTokens class
TEST_CASE("Test ManageTokens class") {
    ManageTokens manager;
    vector<unique_ptr<NfToken>> wallet1, wallet2;

  
    manager.mintToken(wallet1, "one");
    manager.mintToken(wallet1, "two");

  
    CHECK(wallet1.size() == 2);

    manager.walletTransfer(wallet2, wallet1, wallet1.begin());

   
    CHECK(wallet1.size() == 1);
    CHECK(wallet2.size() == 1);

    
    manager.transferAll(wallet2, wallet1);

    
    CHECK(wallet1.empty());
    CHECK(wallet2.size() == 2);
}

// Test 3 transfers 
TEST_CASE("Test 3 transfers ") {
    ManageTokens manager;
    vector<unique_ptr<NfToken>> wallet1, wallet2, wallet3;


    manager.mintToken(wallet1, "NFT1");
    manager.mintToken(wallet1, "NFT2");


    manager.transferAll(wallet2, wallet1);
    CHECK(wallet1.empty());
    CHECK(wallet2.size() == 2);


    manager.transferAll(wallet3, wallet2);
    CHECK(wallet2.empty());
    CHECK(wallet3.size() == 2);
}
