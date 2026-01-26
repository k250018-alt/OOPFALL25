#include <iostream>
using namespace std;

class Product
{
public:
    int id;
    string name;
    float price;
    int quantity;
};

void addProduct(Product p[], int &count)
{
    cout << "Enter Product ID: ";
    cin >> p[count].id;
    cout << "Enter Product Name: ";
    cin >> p[count].name;
    cout << "Enter Price: ";
    cin >> p[count].price;
    cout << "Enter Quantity: ";
    cin >> p[count].quantity;
    count++;
}

void displayProduct(Product p[], int count, int pid)
{
    for (int i = 0; i < count; i++)
    {
        if (p[i].id == pid)
        {
            cout << "ID: " << p[i].id << endl;
            cout << "Name: " << p[i].name << endl;
            cout << "Price: " << p[i].price << endl;
            cout << "Quantity: " << p[i].quantity << endl;
            return;
        }
    }
    cout << "Product not found" << endl;
}

void updateProduct(Product p[], int count, int pid)
{
    for (int i = 0; i < count; i++)
    {
        if (p[i].id == pid)
        {
            cout << "Enter new price: ";
            cin >> p[i].price;
            cout << "Enter new quantity: ";
            cin >> p[i].quantity;
            cout << "Product updated" << endl;
            return;
        }
    }
    cout << "Product not found" << endl;
}

void removeProduct(Product p[], int &count, int pid)
{
    for (int i = 0; i < count; i++)
    {
        if (p[i].id == pid)
        {
            for (int j = i; j < count - 1; j++)
                p[j] = p[j + 1];
            count--;
            cout << "Product removed" << endl;
            return;
        }
    }
    cout << "Product not found" << endl;
}

int main()
{
    Product p[100];
    int count = 0, choice, id;

    do
    {
        cout << "\n1.Add Product\n2.Display Product\n3.Update Product\n4.Remove Product\n5.Exit\n";
        cin >> choice;

        if (choice == 1)
            addProduct(p, count);
        else if (choice == 2)
        {
            cout << "Enter Product ID: ";
            cin >> id;
            displayProduct(p, count, id);
        }
        else if (choice == 3)
        {
            cout << "Enter Product ID: ";
            cin >> id;
            updateProduct(p, count, id);
        }
        else if (choice == 4)
        {
            cout << "Enter Product ID: ";
            cin >> id;
            removeProduct(p, count, id);
        }
    } while (choice != 5);
}
