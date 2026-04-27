#include <iostream>
#include <string>

using namespace std;

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool processPayment(double amount) = 0;
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;
public:
    CreditCard(const string& number) : cardNumber(number) {}

    bool processPayment(double amount) override {
        if (cardNumber.empty() || cardNumber.length() < 12) {
            cout << "CreditCard payment failed: invalid card number.\n";
            return false;
        }
        if (amount <= 0) {
            cout << "CreditCard payment failed: invalid amount.\n";
            return false;
        }

        cout << "CreditCard payment successful: $" << amount << " charged to card " << cardNumber << ".\n";
        return true;
    }
};

class DigitalWallet : public PaymentMethod {
private:
    double balance;
public:
    DigitalWallet(double initialBalance) : balance(initialBalance) {}

    bool processPayment(double amount) override {
        if (amount <= 0) {
            cout << "DigitalWallet payment failed: invalid amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "DigitalWallet payment failed: insufficient funds. Balance is $" << balance << ".\n";
            return false;
        }

        balance -= amount;
        cout << "DigitalWallet payment successful: $" << amount << " deducted. Remaining balance: $" << balance << ".\n";
        return true;
    }
};

int main() {
    CreditCard visa("4111111111111111");
    DigitalWallet wallet(100.00);

    cout << "Simulating payments...\n";

    double amount1 = 45.50;
    if (visa.processPayment(amount1)) {
        cout << "Transaction 1 completed.\n";
    }

    double amount2 = 75.25;
    if (!wallet.processPayment(amount2)) {
        cout << "Transaction 2 failed. Trying smaller amount...\n";
        wallet.processPayment(50.00);
    }

    CreditCard invalidCard("123");
    invalidCard.processPayment(25.00);

    return 0;
}
