#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    std::string name;
    double monthlySalary;
    double taxPercentage; // stored as percent (e.g., 2.0 for 2%)
public:
    Employee();
    void get_data();
    double Salary_after_tax() const;
    void update_tax_percentage(double increasePercent); // increases rate by given percent
    void display() const;
};

#endif // EMPLOYEE_H
