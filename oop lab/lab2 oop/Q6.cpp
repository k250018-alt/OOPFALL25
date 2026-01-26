#include <iostream>
using namespace std;

int main()
{
    int capacity = 5;
    int size = 0;
    int *arr = new int[capacity];
    int x;

    while (true)
    {
        cin >> x;
        if (x == -1)
            break;

        if (size == capacity)
        {
            capacity *= 2;
            int *temp = new int[capacity];
            for (int i = 0; i < size; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }

        arr[size++] = x;
    }

    int *finalArr = new int[size];
    for (int i = 0; i < size; i++)
        finalArr[i] = arr[i];

    delete[] arr;

    for (int i = 0; i < size; i++)
        cout << finalArr[i] << " ";

    delete[] finalArr;
}
