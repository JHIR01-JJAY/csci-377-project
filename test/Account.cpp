#include "Account.h"
#include <sstream>
#include <iomanip>

Account::Account(int accNum, std::string name_, double balance_)
    : accountNumber(accNum), name(std::move(name_)), balance(balance_) {}

int Account::getAccountNumber() const { return accountNumber; }
const std::string& Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount < 0) return;
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount < 0) return false;
    if (amount > balance) return false;
    balance -= amount;
    return true;
}

bool Account::operator<(const Account& other) const {
    return accountNumber < other.accountNumber;
}

bool Account::operator==(const Account& other) const {
    return accountNumber == other.accountNumber;
}

std::string Account::toString() const {
    std::ostringstream oss;
    oss << "Acct#: " << accountNumber << " | Name: " << name
        << " | Balance: $" << std::fixed << std::setprecision(2) << balance;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Account& a) {
    os << a.toString();
    return os;
}
