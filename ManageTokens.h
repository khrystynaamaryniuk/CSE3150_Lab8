#ifndef MANAGETOKENS_H
#define MANAGETOKENS_H

#include <vector>
#include <memory>
#include <string>
#include "NfToken.h"
#include "ShaMessageDigestHash.h"

using namespace std;

class ManageTokens {
    ShaMessageDigestHash sha256;

public:
    void mintToken(vector<unique_ptr<NfToken>> &wallet, const string &name) {
        sha256.compHash(name);
        auto token = make_unique<NfToken>(name);
        token->setHash(sha256.getHash());
        wallet.push_back(move(token));
    }

    void walletTransfer(vector<unique_ptr<NfToken>> &toWallet,
                        vector<unique_ptr<NfToken>> &fromWallet,
                        vector<unique_ptr<NfToken>>::iterator pos) {
        toWallet.push_back(move(*pos));
        (*pos).release();
        fromWallet.erase(pos);
    }

    void transferAll(vector<unique_ptr<NfToken>> &toWallet,
                     vector<unique_ptr<NfToken>> &fromWallet) {
        while (!fromWallet.empty()) {
            walletTransfer(toWallet, fromWallet, fromWallet.begin());
        }
    }
};

#endif
