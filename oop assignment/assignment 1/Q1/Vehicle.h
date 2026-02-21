#pragma once
#include <iostream>
#include "Engine.h"
#include <cstdlib>
#include <ctime>
using namespace std;
const int maxVehicles = 100;

class Vehicle
{
protected:
    string model;
    string color;
    const int vehicleID;
    bool is_used;
    Engine engine;

public:
    Vehicle() : model("NULL"), color("NULL"), vehicleID(0), is_used(rand() % 2 == 0), engine() {}

    Vehicle(string mod, string colour, int vehicle_id, bool isused, const Engine &eng) : 
    model(mod),
    color(colour),
    vehicleID(vehicle_id),
    is_used(isused),
    engine(eng)
    {
    }
    int getID() const;
    virtual void display() const = 0;
    virtual ~Vehicle()
    {
    }
};
int Vehicle::getID() const
{
    return vehicleID;
}

class Car : public Vehicle
{
    static int TotalCars;

public:
    Car() : Vehicle()
    {
        TotalCars++;
    }
    Car(string mod, string colour, int vehicle_id, bool isused, const Engine &eng) : Vehicle(mod, colour, vehicle_id, isused, eng)
    {
        TotalCars++;
    }
    Car(const Car &other)
        : Vehicle(other.model, other.color, other.vehicleID, other.is_used, other.engine)
    {
        TotalCars++;
    }

    void display() const override
    {
        cout << "Car details : " << endl;
        cout << "Model : " << model << endl;
        cout << "Color : " << color << endl;
        cout << "Vehicle ID : " << vehicleID << endl;
        cout << "Is used : " << (is_used ? "Yes" : "No") << endl;
        engine.display();
    }
    static int getTotalCars()
    {
        return TotalCars;
    }
    bool getIsUsed() const
    {
        return is_used;
    }
    ~Car()
    {
        TotalCars--;
    }
};
class Bike : public Vehicle
{
    static int TotalBikes;

public:
    Bike() : Vehicle()
    {
        TotalBikes++;
    }
    Bike(string mod, string colour, int vehicle_id, bool isused, const Engine &eng) : Vehicle(mod, colour, vehicle_id, isused, eng)
    {
        TotalBikes++;
    }
    void display() const override
    {
        cout << "Bike details : " << endl;
        cout << "Model : " << model << endl;
        cout << "Color : " << color << endl;
        cout << "Vehicle ID : " << vehicleID << endl;
        cout << "Is used : " << (is_used ? "Yes" : "No") << endl;
    };
    bool getIsUsed() const
    {
        return is_used;
    }
    ~Bike()
    {
        TotalBikes--;
    }
};