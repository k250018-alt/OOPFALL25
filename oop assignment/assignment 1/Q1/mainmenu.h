#pragma once
#include <iostream>
#include "User.h"
using namespace std;

class MainMenu
{
    Cars_Inventory *usedCars;
    Cars_Inventory *newCars;
    Bike_Inventory *usedBikes;
    Bike_Inventory *newBikes;

    Admin *admin;
    Seller *sellers[50];
    Buyer *buyers[50];

    Listing *listings[maxVehicles];
    int listingCount;
    int sellerCount;
    int buyerCount;

    string systemName;
    bool isOpen;

    static int sessionCount;

public:
    MainMenu(Admin *admin, string systemName = "Vehicle Marketplace") : admin(admin), listingCount(0), sellerCount(0), buyerCount(0),
                                                                        systemName(systemName), isOpen(true)
    {
        usedCars = new Cars_Inventory(true, "Used Cars");
        newCars = new Cars_Inventory(false, "New Cars");
        usedBikes = new Bike_Inventory(true, "Used Bikes");
        newBikes = new Bike_Inventory(false, "New Bikes");
        for (int i = 0; i < maxVehicles; i++)
            listings[i] = nullptr;
        for (int i = 0; i < 50; i++)
        {
            sellers[i] = nullptr;
            buyers[i] = nullptr;
        }
        sessionCount++;
        cout << "✦ " << systemName << " started. Session #" << sessionCount << "\n";
    }

    Cars_Inventory &getUsedCars() const { return *usedCars; }
    Cars_Inventory &getNewCars() const { return *newCars; }
    Bike_Inventory &getUsedBikes() const { return *usedBikes; }
    Bike_Inventory &getNewBikes() const { return *newBikes; }
    static int getSessionCount() { return sessionCount; }

    void registerSeller(Seller *s)
    {
        if (sellerCount < 50)
            sellers[sellerCount++] = s;
    }

    void registerBuyer(Buyer *b)
    {
        if (buyerCount < 50)
            buyers[buyerCount++] = b;
    }

    Listing *submitCarListing(Seller &seller, const Car &car)
    {

        if (car.getIsUsed())
            usedCars->addCar(car);
        else
            newCars->addCar(car);

        Listing *l = new Listing(car.getID(), "Car", seller.getName(), "2025-01-01");
        if (listingCount < maxVehicles)
            listings[listingCount++] = l;
        if (admin)
            admin->registerListing(l);
        cout << "Listing submitted for admin review.\n";
        return l;
    }

    Listing *submitBikeListing(Seller &seller, const Bike &bike)
    {
        if (bike.getIsUsed())
            usedBikes->addBike(bike);
        else
            newBikes->addBike(bike);

        Listing *l = new Listing(bike.getID(), "Bike", seller.getName(), "2025-01-01");
        if (listingCount < maxVehicles)
            listings[listingCount++] = l;
        if (admin)
            admin->registerListing(l);
        cout << "Bike listing submitted for admin review.\n";
        return l;
    }

    void displayAllInventories() const
    {
        newCars->displayCarsInventory();
        usedCars->displayCarsInventory();
        newBikes->displayBikeInventory();
        usedBikes->displayBikeInventory();
    }

    void searchCarsByBrand(const string &brand) const
    {
        cout << "\n── New Cars: ──\n";
        newCars->filterByBrand(brand);
        cout << "\n── Used Cars: ──\n";
        usedCars->filterByBrand(brand);
    }

    void searchCarsByPrice(double lo, double hi) const
    {
        cout << "\n── New Cars: ──\n";
        newCars->filterByPrice(lo, hi);
        cout << "\n── Used Cars: ──\n";
        usedCars->filterByPrice(lo, hi);
    }

    void searchCarsByYear(int lo, int hi) const
    {
        cout << "\n── New Cars: ──\n";
        newCars->filterByYear(lo, hi);
        cout << "\n── Used Cars: ──\n";
        usedCars->filterByYear(lo, hi);
    }

    void searchBikesByBrand(const string &brand) const
    {
        cout << "\n── New Bikes: ──\n";
        newBikes->filterByBrand(brand);
        cout << "\n── Used Bikes: ──\n";
        usedBikes->filterByBrand(brand);
    }

    void printSystemStats() const
    {
        cout << "\n═══ System Stats ═══\n"
             << "  Total Users   : " << User::getTotalUsers() << "\n"
             << "  Total Cars    : " << Car::getTotalCars() << "\n"
             << "  Total Bikes   : " << Bike::getTotalBikes() << "\n"
             << "  Total Messages: " << Message::getMessageCount() << "\n"
             << "  Total Listings: " << Listing::getListingCount() << "\n"
             << "  Sessions      : " << sessionCount << "\n";
    }

    ~MainMenu()
    {
        delete usedCars;
        delete newCars;
        delete usedBikes;
        delete newBikes;
        for (int i = 0; i < listingCount; i++)
            if (listings[i] != nullptr)
            {
                delete listings[i];
                listings[i] = nullptr;
            }
        cout << "✦ " << systemName << " closed.\n";
    }
};
int MainMenu::sessionCount = 0;