#include <iostream>
#include <limits>
#include "Bank.h"

static void pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Bank bank;
    bool running = true;

    while (running) {
        std::cout << "\n=== Banking Management System ===\n";
        std::cout << "1) Create account\n";
        std::cout << "2) Balance inquiry (vector)\n";
        std::cout << "3) Balance inquiry (map)\n";
        std::cout << "4) Deposit\n";
        std::cout << "5) Withdraw\n";
        std::cout << "6) Transfer\n";
        std::cout << "7) List accounts (vector)\n";
        std::cout << "8) List accounts (map)\n";
        std::cout << "0) Exit\n";
        std::cout << "Choose: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 0) break;

        if (choice == 1) {
            int acc; std::string name; double bal;
            std::cout << "Account number: "; std::cin >> acc; std::cin.ignore();
            std::cout << "Name: "; std::getline(std::cin, name);
            std::cout << "Initial balance: "; std::cin >> bal;
            if (bank.createAccount(acc, name, bal)) std::cout << "Created account.\n";
            else std::cout << "Account number already exists.\n";
        } else if (choice == 2 || choice == 3) {
            int acc; std::cout << "Account number: "; std::cin >> acc;
            auto opt = (choice==2) ? bank.findAccountByVector(acc) : bank.findAccountByMap(acc);
            if (opt) std::cout << opt->toString() << "\n";
            else std::cout << "Account not found.\n";
        } else if (choice == 4) {
            int acc; double amt; std::cout << "Account number: "; std::cin >> acc;
            std::cout << "Amount: "; std::cin >> amt;
            if (bank.depositToAccount(acc, amt)) std::cout << "Deposit successful.\n";
            else std::cout << "Deposit failed.\n";
        } else if (choice == 5) {
            int acc; double amt; std::cout << "Account number: "; std::cin >> acc;
            std::cout << "Amount: "; std::cin >> amt;
            if (bank.withdrawFromAccount(acc, amt)) std::cout << "Withdraw successful.\n";
            else std::cout << "Withdraw failed (insufficient or not found).\n";
        } else if (choice == 6) {
            int a,b; double amt; std::cout << "From account: "; std::cin >> a;
            std::cout << "To account: "; std::cin >> b;
            std::cout << "Amount: "; std::cin >> amt;
            if (bank.transfer(a, b, amt)) std::cout << "Transfer successful.\n";
            else std::cout << "Transfer failed.\n";
        } else if (choice == 7) {
            auto list = bank.listAccountsVector();
            if (list.empty()) std::cout << "No accounts.\n";
            for (const auto& a : list) std::cout << a << '\n';
        } else if (choice == 8) {
            auto list = bank.listAccountsMap();
            if (list.empty()) std::cout << "No accounts.\n";
            for (const auto& a : list) std::cout << a << '\n';
        } else {
            std::cout << "Unknown option.\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        pause();
    }

    std::cout << "Goodbye.\n";
    return 0;
}

