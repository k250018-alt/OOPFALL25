#include <iostream>
using namespace std;

int *allocateArray(int n)
{
    int *arr = new int[n];
    return arr;
}

int main()
{
    int n;
    cin >> n;
    int *a = allocateArray(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    delete[] a;
}
