#pragma once
#include <iostream>
#include "User.h"
#include "Cars_Inventory.h"
#include "Bike_Inventory.h"

using namespace std;

class MainMenu {
private:
    Car* cars;
    Bike* bikes;

    Cars_Inventory* usedcars;
    Cars_Inventory* newcars;
    Bike_Inventory* usedbikes;
    Bike_Inventory* newbikes;
    Admin admin;
    Seller seller;
    Buyer buyer;

public:
    MainMenu(Admin admin, Seller seller, Buyer buyer)
        : admin(admin), seller(seller), buyer(buyer)
    {
        cars = new Car[maxVehicles];
        bikes = new Bike[maxVehicles];
        usedcars = new Cars_Inventory(cars, true);
        newcars  = new Cars_Inventory(cars, false);
        usedbikes = new Bike_Inventory(bikes, true);
        newbikes  = new Bike_Inventory(bikes, false);
    }

    }
    ~MainMenu() {
        delete usedcars;
        delete newcars;
        delete usedbikes;
        delete newbikes;
        delete[] cars;
        delete[] bikes;
    }
};