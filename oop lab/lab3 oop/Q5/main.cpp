#include <iostream>
#include <iomanip>
#include "Employee.h"
using namespace std;

int main() {
    cout << fixed << setprecision(2);

    Employee e1, e2, e3;

    cout << "Enter data for Employee 1:\n";
    e1.get_data();
    cout << "Employee 1 — after initial tax: " << e1.Salary_after_tax() << "\n";
    e1.update_tax_percentage(1.0); // increase by 1%
    cout << "Employee 1 — after increasing tax by 1%: " << e1.Salary_after_tax() << "\n\n";

    cout << "Enter data for Employee 2:\n";
    e2.get_data();
    cout << "Employee 2 — after initial tax: " << e2.Salary_after_tax() << "\n";
    e2.update_tax_percentage(1.0);
    cout << "Employee 2 — after increasing tax by 1%: " << e2.Salary_after_tax() << "\n\n";

    cout << "Enter data for Employee 3:\n";
    e3.get_data();
    cout << "Employee 3 — after initial tax: " << e3.Salary_after_tax() << "\n";
    e3.update_tax_percentage(1.0);
    cout << "Employee 3 — after increasing tax by 1%: " << e3.Salary_after_tax() << "\n\n";

    return 0;
}
