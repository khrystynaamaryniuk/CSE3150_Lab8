#include <iostream>
#include <memory>
#include <vector>
#include "NfToken.h"
#include "ShaMessageDigestHash.h"
#include "ManageTokens.h"

using namespace std;

ostream &operator<<(ostream &os, const NfToken &nft) {
    os << nft.getName() << " (" << nft.getHash() << ")";
    return os;
}

int main() {
    ManageTokens manager;
    vector<unique_ptr<NfToken>> wallet1, wallet2, wallet3;

    int count;
    cout << "How many NFTs to mint into wallet1? ";
    cin >> count;

    for (int i = 0; i < count; ++i) {
        string name;
        cout << "Enter name for NFT " << i + 1 << ": ";
        cin >> name;
        manager.mintToken(wallet1, name);
    }

    cout << "\n--- Wallet 1 Before Transfer ---\n";
    for (auto &nft : wallet1) cout << *nft << endl;

    string response;
    cout << "\nDo you want to transfer NFTs to Wallet 2? (yes/no): ";
    cin >> response;

    if (response == "yes") {
        manager.transferAll(wallet2, wallet1);

        cout << "\n--- Wallet 1 After Transfer ---\n";
        for (auto &nft : wallet1) cout << *nft << endl;

        cout << "\n--- Wallet 2 After Transfer ---\n";
        for (auto &nft : wallet2) cout << *nft << endl;

        cout << "\n--- Wallet 3 After Transfer ---\n";
        for (auto &nft : wallet3) cout << *nft << endl;

        cout << "\nDo you want to transfer NFTs from Wallet 2 to Wallet 3? (yes/no): ";
        cin >> response;

        if (response == "yes") {
            manager.transferAll(wallet3, wallet2);

            cout << "\n--- Wallet 1 After Transfer ---\n";
            for (auto &nft : wallet1) cout << *nft << endl;

            cout << "\n--- Wallet 2 After Transfer to Wallet 3 ---\n";
            for (auto &nft : wallet2) cout << *nft << endl;

            cout << "\n--- Wallet 3 After Transfer ---\n";
            for (auto &nft : wallet3) cout << *nft << endl;
        } else {
            cout << "Transfer to Wallet 3 was not made." << endl;
        }
    } else {
        cout << "Transfer to Wallet 2 was not made." << endl;
    }

    return 0;
}
