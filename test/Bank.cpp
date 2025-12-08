#include "Bank.h"
#include <algorithm>

// ---- Public ----
bool Bank::createAccount(int accountNumber, const std::string& name, double initialBalance) {
    // If account exists in map, reject
    if (accountsMap.find(accountNumber) != accountsMap.end()) return false;

    Account acc(accountNumber, name, initialBalance);
    accountsMap[accountNumber] = acc;
    insertToVectorMaintainingSorted(acc);
    return true;
}

std::optional<Account> Bank::findAccountByVector(int accountNumber) const {
    int idx = binarySearchVector(accountNumber);
    if (idx >= 0) return accountsVec[idx];
    return std::nullopt;
}

std::optional<Account> Bank::findAccountByMap(int accountNumber) const {
    auto it = accountsMap.find(accountNumber);
    if (it == accountsMap.end()) return std::nullopt;
    return it->second;
}

bool Bank::depositToAccount(int accountNumber, double amount) {
    if (amount < 0) return false;
    // Update map
    auto it = accountsMap.find(accountNumber);
    if (it == accountsMap.end()) return false;
    it->second.deposit(amount);

    // Update vector (find index and update)
    int idx = binarySearchVector(accountNumber);
    if (idx >= 0) accountsVec[idx].deposit(amount);
    return true;
}

bool Bank::withdrawFromAccount(int accountNumber, double amount) {
    if (amount < 0) return false;
    auto it = accountsMap.find(accountNumber);
    if (it == accountsMap.end()) return false;
    if (!it->second.withdraw(amount)) return false;

    int idx = binarySearchVector(accountNumber);
    if (idx >= 0) {
        if (!accountsVec[idx].withdraw(amount)) {
            // Shouldn't happen because map succeeded, but keep consistent
            return false;
        }
    }
    return true;
}

bool Bank::transfer(int fromAccount, int toAccount, double amount) {
    if (amount < 0) return false;
    // Check both exist
    auto itFrom = accountsMap.find(fromAccount);
    auto itTo = accountsMap.find(toAccount);
    if (itFrom == accountsMap.end() || itTo == accountsMap.end()) return false;
    if (itFrom->second.getBalance() < amount) return false;

    // Withdraw then deposit (atomicity note: here it's simple sequence)
    if (!itFrom->second.withdraw(amount)) return false;
    itTo->second.deposit(amount);

    // Update vector entries
    int idxFrom = binarySearchVector(fromAccount);
    int idxTo = binarySearchVector(toAccount);
    if (idxFrom >= 0) accountsVec[idxFrom].withdraw(amount);
    if (idxTo >= 0) accountsVec[idxTo].deposit(amount);

    return true;
}

std::vector<Account> Bank::listAccountsVector() const {
    return accountsVec;
}

std::vector<Account> Bank::listAccountsMap() const {
    std::vector<Account> out;
    out.reserve(accountsMap.size());
    for (const auto &p : accountsMap) out.push_back(p.second);
    return out;
}

// ---- Private helpers ----

void Bank::insertToVectorMaintainingSorted(const Account& acc) {
    // Insert in sorted position by accountNumber using binary search
    int lo = 0;
    int hi = static_cast<int>(accountsVec.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (accountsVec[mid].getAccountNumber() == acc.getAccountNumber()) {
            // duplicate (shouldn't happen because map prevented it)
            accountsVec.insert(accountsVec.begin() + mid, acc);
            return;
        } else if (accountsVec[mid].getAccountNumber() < acc.getAccountNumber()) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    accountsVec.insert(accountsVec.begin() + lo, acc);
}

int Bank::binarySearchVector(int accountNumber) const {
    int lo = 0;
    int hi = static_cast<int>(accountsVec.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int midAcct = accountsVec[mid].getAccountNumber();
        if (midAcct == accountNumber) return mid;
        if (midAcct < accountNumber) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// sortVector left as future extension in case you want to re-sort entire vector:
void Bank::sortVector() {
    if (accountsVec.size() <= 1) return;
    // We'll implement an in-place merge sort using temporary vector
    std::vector<Account> tmp(accountsVec.size());
    std::function<void(int,int)> mergeSortRec = [&](int l, int r) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSortRec(l, m);
        mergeSortRec(m+1, r);
        // merge
        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r) {
            if (accountsVec[i].getAccountNumber() <= accountsVec[j].getAccountNumber()) tmp[k++] = accountsVec[i++];
            else tmp[k++] = accountsVec[j++];
        }
        while (i <= m) tmp[k++] = accountsVec[i++];
        while (j <= r) tmp[k++] = accountsVec[j++];
        for (int p = l; p <= r; ++p) accountsVec[p] = tmp[p];
    };
    mergeSortRec(0, static_cast<int>(accountsVec.size())-1);
}

