#include <iostream>
using namespace std;

void calculate(int *a, int *b, char op)
{
    int *p1 = a, *p2 = b;
    if (op == '+')
        cout << "Result: " << (*p1 + *p2);
    else if (op == '-')
        cout << "Result: " << (*p1 - *p2);
    else if (op == '*')
        cout << "Result: " << (*p1 * *p2);
    else if (op == '/')
        cout << "Result: " << (*p1 / *p2);
    else
        cout << "Invalid operator";
}

int main()
{
    int x, y;
    char op;

    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "Enter operator (+ - * /): ";
    cin >> op;

    calculate(&x, &y, op);
}
