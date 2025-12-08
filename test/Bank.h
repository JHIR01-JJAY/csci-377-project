#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <vector>
#include <map>
#include <optional>
#include <string>

class Bank {
public:
    Bank() = default;

    // Create account (returns false if account number already exists)
    bool createAccount(int accountNumber, const std::string& name, double initialBalance=0.0);

    // Lookup: vector (binary search) and map lookup, return optional<Account>
    std::optional<Account> findAccountByVector(int accountNumber) const;
    std::optional<Account> findAccountByMap(int accountNumber) const;

    // Deposit / Withdraw / Transfer
    bool depositToAccount(int accountNumber, double amount);
    bool withdrawFromAccount(int accountNumber, double amount);
    bool transfer(int fromAccount, int toAccount, double amount);

    // List accounts (vector is kept sorted)
    std::vector<Account> listAccountsVector() const;
    std::vector<Account> listAccountsMap() const;

    // For testing & maintenance
    size_t vectorSize() const { return accountsVec.size(); }
    size_t mapSize() const { return accountsMap.size(); }

private:
    std::vector<Account> accountsVec;
    std::map<int, Account> accountsMap;

    // Internal helpers
    void sortVector(); // MergeSort implementation
    int binarySearchVector(int accountNumber) const; // index or -1
    void insertToVectorMaintainingSorted(const Account& acc);
};

#endif // BANK_H

