#include <iostream>
#include <string>
using namespace std;

class Stationary_shop_item
{
    string name;
    double price;
    int quantity;

public:
    Stationary_shop_item() : price(0), quantity(0) {}

    void setDetails(string n, double p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    }

    string getName() { return name; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }

    void increaseQuantity(int q) { quantity += q; }
    void decreaseQuantity(int q) { quantity -= q; }
};

class Inventory
{
public:
    void createInventory(Stationary_shop_item items[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            string n;
            double p;
            int q;
            cout << "\nItem " << i + 1 << endl;
            cout << "Name: ";
            cin >> n;
            cout << "Price: ";
            cin >> p;
            cout << "Quantity: ";
            cin >> q;
            items[i].setDetails(n, p, q);
        }
    }

    void displayInventory(Stationary_shop_item items[], int size)
    {
        cout << "\nInventory:\n";
        for (int i = 0; i < size; i++)
        {
            cout << items[i].getName()
                 << " | Price: " << items[i].getPrice()
                 << " | Quantity: " << items[i].getQuantity() << endl;
        }
    }

    int findItem(Stationary_shop_item items[], int size, string name)
    {
        for (int i = 0; i < size; i++)
            if (items[i].getName() == name)
                return i;
        return -1;
    }
};

class Cart
{
    Stationary_shop_item cart[50];
    int cartSize = 0;

public:
    void addToCart(Stationary_shop_item inventory[], int invSize, Inventory &inv)
    {
        string name;
        cout << "Enter item name: ";
        cin >> name;

        int idx = inv.findItem(inventory, invSize, name);
        if (idx == -1 || inventory[idx].getQuantity() == 0)
        {
            cout << "Item not available\n";
            return;
        }

        inventory[idx].decreaseQuantity(1);

        for (int i = 0; i < cartSize; i++)
        {
            if (cart[i].getName() == name)
            {
                cart[i].increaseQuantity(1);
                cout << "Item added to cart\n";
                return;
            }
        }

        cart[cartSize++].setDetails(
            inventory[idx].getName(),
            inventory[idx].getPrice(),
            1);
        cout << "Item added to cart\n";
    }

    void viewCart()
    {
        cout << "\nCart Items:\n";
        for (int i = 0; i < cartSize; i++)
        {
            cout << cart[i].getName()
                 << " | Qty: " << cart[i].getQuantity()
                 << " | Price: " << cart[i].getPrice() << endl;
        }
    }

    void checkout()
    {
        double total = 0;
        for (int i = 0; i < cartSize; i++)
        {
            total += cart[i].getPrice() * cart[i].getQuantity();
        }
        cout << "\nTotal Amount: " << total << endl;
        cartSize = 0;
    }
};

class System
{
    Stationary_shop_item inventory[50];
    int inventorySize;
    Inventory inv;
    Cart cart;

public:
    void startup()
    {
        cout << "Enter inventory size: ";
        cin >> inventorySize;
        inv.createInventory(inventory, inventorySize);
    }

    void employeeMenu()
    {
        int choice;
        do
        {
            cout << "\nEmployee Menu\n";
            cout << "1. View Inventory\n";
            cout << "9. Back\n";
            cin >> choice;

            if (choice == 1)
                inv.displayInventory(inventory, inventorySize);

        } while (choice != 9);
    }

    void customerMenu()
    {
        int choice;
        do
        {
            cout << "\nCustomer Menu\n";
            cout << "1. Add to Cart\n";
            cout << "2. View Cart\n";
            cout << "3. Checkout\n";
            cout << "9. Back\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cart.addToCart(inventory, inventorySize, inv);
                break;
            case 2:
                cart.viewCart();
                break;
            case 3:
                cart.checkout();
                break;
            }
        } while (choice != 9);
    }

    void mainMenu()
    {
        int choice;
        do
        {
            cout << "\nMain Menu\n";
            cout << "1. Employee\n";
            cout << "2. Customer\n";
            cout << "9. Exit\n";
            cin >> choice;

            if (choice == 1)
                employeeMenu();
            else if (choice == 2)
                customerMenu();

        } while (choice != 9);
    }
};

int main()
{
    System s;
    s.startup();
    s.mainMenu();
    return 0;
}
