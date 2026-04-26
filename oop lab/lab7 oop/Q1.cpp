#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Account {
protected:
    string accountNumber, accountHolderName, accountType;
    double balance;
    vector<string> transactions;
public:
    Account(string num, double bal, string name, string type = "General")
        : accountNumber(num), balance(bal), accountHolderName(name), accountType(type) {}

    virtual void deposit(double amount) {
        if (amount <= 0) { cout << "Invalid amount." << endl; return; }
        balance += amount;
        transactions.push_back("Deposited: $" + to_string(amount));
        cout << "Deposited $" << amount << endl;
    }
    virtual void withdraw(double amount) {
        if (amount <= 0 || amount > balance) { cout << "Invalid/Insufficient." << endl; return; }
        balance -= amount;
        transactions.push_back("Withdrew: $" + to_string(amount));
        cout << "Withdrew $" << amount << endl;
    }
    virtual double calculateInterest() { return 0; }
    virtual void printStatement() {
        cout << "\n--- Statement: " << accountHolderName << " ---" << endl;
        for (auto& t : transactions) cout << t << endl;
        cout << "Balance: $" << balance << endl;
    }
    virtual void getAccountInfo() {
        cout << "Account: " << accountNumber << " | Holder: " << accountHolderName
             << " | Type: " << accountType << " | Balance: $" << balance << endl;
    }
    virtual ~Account() {}
};

class SavingsAccount : public Account {
    double interestRate, minimumBalance;
public:
    SavingsAccount(string num, double bal, string name, double rate=0.05, double minBal=500)
        : Account(num, bal, name, "Savings"), interestRate(rate), minimumBalance(minBal) {}

    void withdraw(double amount) override {
        if (balance - amount < minimumBalance)
            { cout << "Cannot go below minimum balance $" << minimumBalance << endl; return; }
        Account::withdraw(amount);
    }
    double calculateInterest() override {
        double interest = balance * interestRate;
        cout << "Savings Interest: $" << interest << endl;
        return interest;
    }
    void printStatement() override {
        cout << "Interest Rate: " << interestRate * 100 << "% | Min Balance: $" << minimumBalance << endl;
        Account::printStatement();
    }
};

class CheckingAccount : public Account {
    double overdraftLimit;
public:
    CheckingAccount(string num, double bal, string name, double overdraft=200)
        : Account(num, bal, name, "Checking"), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount > balance + overdraftLimit)
            { cout << "Exceeds overdraft limit." << endl; return; }
        balance -= amount;
        transactions.push_back("Withdrew: $" + to_string(amount));
        cout << "Withdrew $" << amount << " (overdraft may apply)" << endl;
    }
    double calculateInterest() override { return 0; }
};

class FixedDepositAccount : public Account {
    string maturityDate;
    double fixedInterestRate;
public:
    FixedDepositAccount(string num, double bal, string name, string matDate, double rate)
        : Account(num, bal, name, "FixedDeposit"), maturityDate(matDate), fixedInterestRate(rate) {}

    void withdraw(double amount) override {
        cout << "Withdrawal not allowed before maturity: " << maturityDate << endl;
    }
    double calculateInterest() override {
        double interest = balance * fixedInterestRate;
        cout << "Fixed Deposit Interest: $" << interest << endl;
        return interest;
    }
    void printStatement() override {
        cout << "Maturity Date: " << maturityDate << " | Rate: " << fixedInterestRate * 100 << "%" << endl;
        Account::printStatement();
    }
};

int main() {
    SavingsAccount sa("SA001", 2000, "Alice", 0.05, 500);
    sa.deposit(500);
    sa.withdraw(1800);
    sa.calculateInterest();
    sa.printStatement();

    CheckingAccount ca("CA001", 1000, "Bob", 300);
    ca.deposit(200);
    ca.withdraw(1200);
    ca.printStatement();

    FixedDepositAccount fda("FD001", 5000, "Carol", "2026-01-01", 0.08);
    fda.withdraw(100);
    fda.calculateInterest();
    fda.printStatement();

    return 0;
}

