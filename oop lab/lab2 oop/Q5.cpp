#include <iostream>
using namespace std;

int **createMatrix(int r, int c)
{
    int **m = new int *[r];
    for (int i = 0; i < r; i++)
        m[i] = new int[c];
    return m;
}

void inputMatrix(int **m, int r, int c)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> m[i][j];
}

void displayMatrix(int **m, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}

int **addMatrix(int **a, int **b, int r, int c)
{
    int **res = createMatrix(r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}

int **subMatrix(int **a, int **b, int r, int c)
{
    int **res = createMatrix(r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res[i][j] = a[i][j] - b[i][j];
    return res;
}

int **mulMatrix(int **a, int **b, int r1, int c1, int c2)
{
    int **res = createMatrix(r1, c2);
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
    return res;
}

void deleteMatrix(int **m, int r)
{
    for (int i = 0; i < r; i++)
        delete[] m[i];
    delete[] m;
}

int main()
{
    int r1, c1, r2, c2;
    cin >> r1 >> c1;
    int **A = createMatrix(r1, c1);
    inputMatrix(A, r1, c1);

    cin >> r2 >> c2;
    int **B = createMatrix(r2, c2);
    inputMatrix(B, r2, c2);

    if (r1 == r2 && c1 == c2)
    {
        int **add = addMatrix(A, B, r1, c1);
        int **sub = subMatrix(A, B, r1, c1);
        displayMatrix(add, r1, c1);
        displayMatrix(sub, r1, c1);
        deleteMatrix(add, r1);
        deleteMatrix(sub, r1);
    }

    if (c1 == r2)
    {
        int **mul = mulMatrix(A, B, r1, c1, c2);
        displayMatrix(mul, r1, c2);
        deleteMatrix(mul, r1);
    }

    deleteMatrix(A, r1);
    deleteMatrix(B, r2);
}
