#pragma once
#include <iostream>
#include "Vehicle.h"
using namespace std;

class Cars_Inventory
{
    Car *cars[maxVehicles];
    bool isUsed;
    int count;
    string inventoryName;
    string lastUpdated;

    static int totalInventories;

public:
    Cars_Inventory(Car *srcCars, bool used, string name = "Cars Inventory", string date = "N/A") : isUsed(used), count(0), inventoryName(name), lastUpdated(date)
    {
        for (int i = 0; i < maxVehicles; i++)
            cars[i] = nullptr;
        for (int i = 0; i < maxVehicles; i++)
        {
            if (srcCars[i].getIsUsed() == used)
            {
                cars[count++] = new Car(srcCars[i]);
            }
        }
        totalInventories++;
    }

    Cars_Inventory(bool used, string name = "Cars Inventory") : isUsed(used), count(0), inventoryName(name), lastUpdated("N/A")
    {
        for (int i = 0; i < maxVehicles; i++)
            cars[i] = nullptr;
        totalInventories++;
    }

    int getCount() const { return count; }
    string getInventoryName() const { return inventoryName; }
    bool getIsUsed() const { return isUsed; }
    static int getTotalInventories() { return totalInventories; }

    void setLastUpdated(const string &d) { lastUpdated = d; }

    void addCar(const Car &car)
    {
        if (car.getIsUsed() != isUsed)
        {
            cout << "Car condition mismatch for this inventory.\n";
            return;
        }
        if (count >= maxVehicles)
        {
            cout << "Inventory full.\n";
            return;
        }
        cars[count++] = new Car(car);
        cout << "Car added to " << inventoryName << ".\n";
    }

    void removeCar(int vehicleID)
    {
        for (int i = 0; i < maxVehicles; i++)
        {
            if (cars[i] != nullptr && cars[i]->getID() == vehicleID)
            {
                delete cars[i];
                cars[i] = nullptr;

                for (int j = i; j < count - 1; j++)
                    cars[j] = cars[j + 1];
                cars[--count] = nullptr;
                cout << "Car #" << vehicleID << " removed.\n";
                return;
            }
        }
        cout << "Car #" << vehicleID << " not found.\n";
    }

    bool updateCar(int vehicleID, const Car &updated)
    {
        for (int i = 0; i < count; i++)
        {
            if (cars[i] != nullptr && cars[i]->getID() == vehicleID)
            {
                delete cars[i];
                cars[i] = new Car(updated);
                cout << "Car #" << vehicleID << " updated.\n";
                return true;
            }
        }
        cout << "Car #" << vehicleID << " not found for update.\n";
        return false;
    }

    Car *findByID(int vehicleID) const
    {
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->getID() == vehicleID)
                return cars[i];
        return nullptr;
    }

    void filterByBrand(const string &brand) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->matchesBrand(brand))
            {
                cars[i]->display();
                found = true;
            }
        if (!found)
            cout << "No cars found for brand: " << brand << "\n";
    }

    void filterByModel(const string &model) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->matchesModel(model))
            {
                cars[i]->display();
                found = true;
            }
        if (!found)
            cout << "No cars found for model: " << model << "\n";
    }

    void filterByPrice(double minPrice, double maxPrice) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->isInPriceRange(minPrice, maxPrice))
            {
                cars[i]->display();
                found = true;
            }
        if (!found)
            cout << "No cars in price range $" << minPrice << "-$" << maxPrice << "\n";
    }

    void filterByYear(int minYear, int maxYear) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->isInYearRange(minYear, maxYear))
            {
                cars[i]->display();
                found = true;
            }
        if (!found)
            cout << "No cars found in year range.\n";
    }

    void filterByMileage(int minKm, int maxKm) const
    {
        bool found = false;
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr && cars[i]->isInMileageRange(minKm, maxKm))
            {
                cars[i]->display();
                found = true;
            }
        if (!found)
            cout << "No cars found in mileage range.\n";
    }

    void displayCarsInventory() const
    {
        cout << "\n══ " << inventoryName << " (" << count << " vehicles) ══\n";
        if (count == 0)
        {
            cout << "  (empty)\n";
            return;
        }
        for (int i = 0; i < count; i++)
            if (cars[i] != nullptr)
            {
                cars[i]->display();
                cout << "\n";
            }
    }

    ~Cars_Inventory()
    {
        for (int i = 0; i < maxVehicles; i++)
            if (cars[i] != nullptr)
            {
                delete cars[i];
                cars[i] = nullptr;
            }
    }
};
int Cars_Inventory::totalInventories = 0;