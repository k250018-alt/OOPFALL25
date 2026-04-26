#include<iostream>
#include<string>
using namespace std;

class Currency {
protected:
    double amount;
    string currencyCode, currencySymbol;
    double exchangeRate;
public:
    Currency(double amt, string code, string symbol, double rate = 1.0)
        : amount(amt), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    virtual double convertToBase() { return amount * exchangeRate; }
    virtual double convertTo(Currency& target) {
        return convertToBase() / target.exchangeRate;
    }
    virtual void displayCurrency() {
        cout << currencySymbol << amount << " (" << currencyCode << ")" << endl;
    }
    double getRate() const { return exchangeRate; }
    virtual ~Currency() {}
};

class Dollar : public Currency {
public:
    Dollar(double amt) : Currency(amt, "USD", "$", 1.0) {}

    double convertToBase() override { return amount; }
    void displayCurrency() override {
        cout << "US Dollar: $" << amount << " (USD) | Rate: 1.0 (base)" << endl;
    }
};

class Euro : public Currency {
public:
    Euro(double amt) : Currency(amt, "EUR", "€", 1.08) {}

    double convertToBase() override { return amount * 1.08; }
    void displayCurrency() override {
        cout << "Euro: €" << amount << " (EUR) | Rate: 1.08 USD" << endl;
    }
};

class Rupee : public Currency {
public:
    Rupee(double amt) : Currency(amt, "PKR", "₨", 0.0036) {}

    double convertToBase() override { return amount * 0.0036; }
    void displayCurrency() override {
        cout << "Pakistani Rupee: Rs." << amount << " (PKR) | Rate: 0.0036 USD" << endl;
    }
};

int main() {
    Dollar d(100);
    Euro e(100);
    Rupee r(100);

    d.displayCurrency();
    e.displayCurrency();
    r.displayCurrency();

    cout << "\n100 EUR to USD: $" << e.convertToBase() << endl;
    cout << "100 PKR to USD: $" << r.convertToBase() << endl;

    Dollar base(1);
    cout << "100 EUR to PKR: Rs." << e.convertTo(r) * 100 << endl;

    return 0;
}
