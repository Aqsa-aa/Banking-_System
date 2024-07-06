#include <iostream>
#include <string>
using namespace std;

const int MAX_TRANSACTIONS = 100;
const int MAX_ACCOUNTS = 10;
const int MAX_CUSTOMERS = 10;

class Transaction {
public:
    string type;
    double amount;

    Transaction() : type(""), amount(0.0) {}
    Transaction(string t, double a) : type(t), amount(a) {}
};

class Account {
public:
    int accountNumber;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;

    Account() : accountNumber(0), balance(0.0), transactionCount(0) {}
    Account(int accNum, double bal) : accountNumber(accNum), balance(bal), transactionCount(0) {}

    void deposit(double amount) {
        balance += amount;
        transactions[transactionCount++] = Transaction("Deposit", amount);
        cout << "Deposit successful. New balance: $" << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return false;
        } else {
            balance -= amount;
            transactions[transactionCount++] = Transaction("Withdrawal", amount);
            cout << "Withdrawal successful. New balance: $" << balance << endl;
            return true;
        }
    }

    void transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transfer successful." << endl;
        }
    }

    void viewTransactions() {
        cout << "Transactions for Account " << accountNumber << ":\n";
        for (int i = 0; i < transactionCount; ++i) {
            cout << transactions[i].type << ": $" << transactions[i].amount << endl;
        }
    }
};

class Customer {
public:
    string name;
    int customerID;
    Account accounts[MAX_ACCOUNTS];
    int accountCount;

    Customer() : name(""), customerID(0), accountCount(0) {}
    Customer(string n, int id) : name(n), customerID(id), accountCount(0) {}

    void addAccount(Account account) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount++] = account;
        } else {
            cout << "Maximum accounts reached." << endl;
        }
    }

    Account* getAccount(int accountNumber) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].accountNumber == accountNumber) {
                return &accounts[i];
            }
        }
        cout << "Account not found." << endl;
        return nullptr;
    }

    void viewAccounts() {
        cout << "Accounts for Customer " << name << ":\n";
        for (int i = 0; i < accountCount; ++i) {
            cout << "Account Number: " << accounts[i].accountNumber << ", Balance: $" << accounts[i].balance << endl;
        }
    }
};

class BankingSystem {
public:
    Customer customers[MAX_CUSTOMERS];
    int customerCount;

    BankingSystem() : customerCount(0) {}

    void addCustomer(Customer customer) {
        if (customerCount < MAX_CUSTOMERS) {
            customers[customerCount++] = customer;
        } else {
            cout << "Maximum customers reached." << endl;
        }
    }

    Customer* getCustomer(int customerID) {
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].customerID == customerID) {
                return &customers[i];
            }
        }
        cout << "Customer not found." << endl;
        return nullptr;
    }
};

int main() {
    BankingSystem bank;

    // Add a customer
    Customer customer1("Alice", 1);
    bank.addCustomer(customer1);

    // Add accounts to the customer
    Account account1(101, 500.0);
    Account account2(102, 1000.0);

    Customer* customer = bank.getCustomer(1);
    if (customer != nullptr) {
        customer->addAccount(account1);
        customer->addAccount(account2);

        // Perform transactions
        Account* acc = customer->getAccount(101);
        if (acc != nullptr) {
            acc->deposit(200.0);
            acc->withdraw(100.0);
            acc->viewTransactions();
        }

        acc = customer->getAccount(102);
        if (acc != nullptr) {
            acc->withdraw(150.0);
            acc->viewTransactions();
        }

        // Transfer money
        acc = customer->getAccount(101);
        Account* toAcc = customer->getAccount(102);
        if (acc != nullptr && toAcc != nullptr) {
            acc->transfer(*toAcc, 100.0);
            acc->viewTransactions();
            toAcc->viewTransactions();
        }

        // View accounts
        customer->viewAccounts();
    }

    return 0;
}
