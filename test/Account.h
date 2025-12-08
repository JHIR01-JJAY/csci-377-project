#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
public:
    Account() = default;
    Account(int accNum, std::string name, double balance=0.0);

    int getAccountNumber() const;
    const std::string& getName() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount); // returns false if insufficient funds

    // For sorting & comparison
    bool operator<(const Account& other) const;
    bool operator==(const Account& other) const;

    // For printing
    std::string toString() const;

private:
    int accountNumber{0};
    std::string name;
    double balance{0.0};
};

std::ostream& operator<<(std::ostream& os, const Account& a);

#endif // ACCOUNT_H

