#pragma once
#include <iostream>
#include "Vehicle.h"
using namespace std;

class Bike_Inventory
{
    Bike *bikes[maxVehicles];
    bool isUsed;
    int count;
    string inventoryName;
    string lastUpdated;

    static int totalInventories;

public:
    Bike_Inventory(Bike *srcBikes, bool used, string name = "Bikes Inventory", string date = "N/A") : isUsed(used), count(0), inventoryName(name), lastUpdated(date)
    {
        for (int i = 0; i < maxVehicles; i++)
            bikes[i] = nullptr;
        for (int i = 0; i < maxVehicles; i++)
        {
            if (srcBikes[i].getIsUsed() == used)
                bikes[count++] = new Bike(srcBikes[i]);
        }
        totalInventories++;
    }

    Bike_Inventory(bool used, string name = "Bikes Inventory") : isUsed(used), count(0), inventoryName(name), lastUpdated("N/A")
    {
        for (int i = 0; i < maxVehicles; i++)
            bikes[i] = nullptr;
        totalInventories++;
    }

    int getCount() const { return count; }
    string getInventoryName() const { return inventoryName; }
    bool getIsUsed() const { return isUsed; }
    static int getTotalInventories() { return totalInventories; }

    void setLastUpdated(const string &d) { lastUpdated = d; }

    void addBike(const Bike &bike)
    {
        if (bike.getIsUsed() != isUsed)
        {
            cout << "Bike condition mismatch for this inventory.\n";
            return;
        }
        if (count >= maxVehicles)
        {
            cout << "Inventory full.\n";
            return;
        }
        bikes[count++] = new Bike(bike);
        cout << "Bike added to " << inventoryName << ".\n";
    }

    void removeBike(int vehicleID)
    {
        for (int i = 0; i < count; i++)
        {
            if (bikes[i] != nullptr && bikes[i]->getID() == vehicleID)
            {
                delete bikes[i];
                for (int j = i; j < count - 1; j++)
                    bikes[j] = bikes[j + 1];
                bikes[--count] = nullptr;
                cout << "Bike #" << vehicleID << " removed.\n";
                return;
            }
        }
        cout << "Bike #" << vehicleID << " not found.\n";
    }

    bool updateBike(int vehicleID, const Bike &updated)
    {
        for (int i = 0; i < count; i++)
        {
            if (bikes[i] != nullptr && bikes[i]->getID() == vehicleID)
            {
                delete bikes[i];
                bikes[i] = new Bike(updated);
                cout << "Bike #" << vehicleID << " updated.\n";
                return true;
            }
        }
        cout << "Bike #" << vehicleID << " not found for update.\n";
        return false;
    }

    Bike *findByID(int vehicleID) const
    {
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr && bikes[i]->getID() == vehicleID)
                return bikes[i];
        return nullptr;
    }

    void filterByBrand(const string &brand) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr && bikes[i]->matchesBrand(brand))
            {
                bikes[i]->display();
                found = true;
            }
        if (!found)
            cout << "No bikes found for brand: " << brand << "\n";
    }

    void filterByModel(const string &model) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr && bikes[i]->matchesModel(model))
            {
                bikes[i]->display();
                found = true;
            }
        if (!found)
            cout << "No bikes found for model: " << model << "\n";
    }

    void filterByPrice(double lo, double hi) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr && bikes[i]->isInPriceRange(lo, hi))
            {
                bikes[i]->display();
                found = true;
            }
        if (!found)
            cout << "No bikes in price range.\n";
    }

    void filterByYear(int lo, int hi) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr && bikes[i]->isInYearRange(lo, hi))
            {
                bikes[i]->display();
                found = true;
            }
        if (!found)
            cout << "No bikes found in year range.\n";
    }

    void displayBikeInventory() const
    {
        cout << "\n══ " << inventoryName << " (" << count << " vehicles) ══\n";
        if (count == 0)
        {
            cout << "  (empty)\n";
            return;
        }
        for (int i = 0; i < count; i++)
            if (bikes[i] != nullptr)
            {
                bikes[i]->display();
                cout << "\n";
            }
    }

    ~Bike_Inventory()
    {
        for (int i = 0; i < maxVehicles; i++)
            if (bikes[i] != nullptr)
            {
                delete bikes[i];
                bikes[i] = nullptr;
            }
    }
};
int Bike_Inventory::totalInventories = 0;