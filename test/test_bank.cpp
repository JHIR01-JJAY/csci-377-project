// Minimal functional tests that can be run manually
#include "../include/Bank.h"
#include <cassert>
#include <iostream>

int main() {
    Bank bank;
    assert(bank.createAccount(1001, "Alice", 500.0));
    assert(!bank.createAccount(1001, "Alice Duplicate", 10.0)); // duplicate
    assert(bank.createAccount(1002, "Bob", 300.0));

    // deposit
    assert(bank.depositToAccount(1001, 200.0));
    auto a = bank.findAccountByMap(1001);
    assert(a && a->getBalance() == 700.0);

    // withdraw
    assert(bank.withdrawFromAccount(1002, 100.0));
    auto b = bank.findAccountByVector(1002);
    assert(b && b->getBalance() == 200.0);

    // transfer success
    assert(bank.transfer(1001, 1002, 200.0));
    a = bank.findAccountByMap(1001); b = bank.findAccountByMap(1002);
    assert(a && b && a->getBalance() == 500.0 && b->getBalance() == 400.0);

    // transfer fail (insufficient)
    assert(!bank.transfer(1002, 1001, 1000.0));

    std::cout << "All tests passed.\n";
    return 0;
}

