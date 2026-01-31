#include "Employee.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
Employee::Employee() : name(""), monthlySalary(0.0), taxPercentage(2.0) {}

void Employee::get_data() {
    cout << "Enter employee name: ";
    getline(cin, name);

    cout << "Enter monthly salary: ";
    while (!(cin >> monthlySalary) || monthlySalary < 0) {
        cout << "Invalid salary. Enter monthly salary: ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << "Enter tax percentage (e.g., 2 for 2%): ";
    while (!(cin >> taxPercentage) || taxPercentage < 0) {
        cout << "Invalid tax percentage. Enter tax percentage: ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // consume leftover newline
}

double Employee::Salary_after_tax() const {
    return monthlySalary * (1.0 - taxPercentage / 100.0);
}

void Employee::update_tax_percentage(double increasePercent) {
    if (increasePercent < 0) return;
    taxPercentage += increasePercent;
}

void Employee::display() const {
    cout << fixed << setprecision(2);
    cout << "Name: " << name << "\n";
    cout << "Monthly Salary: " << monthlySalary << "\n";
    cout << "Tax Percent: " << taxPercentage << "%\n";
    cout << "Salary after tax: " << Salary_after_tax() << "\n";
}
