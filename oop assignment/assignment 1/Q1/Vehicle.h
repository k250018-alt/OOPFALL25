#pragma once
#include <iostream>
#include <string>
#include "Engine.h"
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
    double price;
    int year;

public:
    Vehicle() : model("Unknown"), color("Unknown"), vehicleID(0),
                is_used(false), engine(), price(0.0), year(2000) {}

    Vehicle(string mod, string col, int vid, bool used,
            const Engine &eng, double price, int year) : model(mod), color(col), vehicleID(vid), is_used(used),
                                                         engine(eng), price(price), year(year) {}

    Vehicle(const Vehicle &other) : model(other.model), color(other.color), vehicleID(other.vehicleID),
                                    is_used(other.is_used), engine(other.engine),
                                    price(other.price), year(other.year) {}

    int getID() const { return vehicleID; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    bool getIsUsed() const { return is_used; }
    double getPrice() const { return price; }
    int getYear() const { return year; }
    Engine getEngine() const { return engine; }

    void setModel(const string &m) { model = m; }
    void setColor(const string &c) { color = c; }
    void setPrice(double p) { price = p; }

    virtual void display() const = 0;

    bool matchesModel(const string &m) const { return model == m; }
    bool matchesColor(const string &c) const { return color == c; }
    bool isInPriceRange(double lo, double hi) const { return price >= lo && price <= hi; }
    bool isInYearRange(int lo, int hi) const { return year >= lo && year <= hi; }

    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
    string brand;
    int mileage;
    int numDoors;
    string transmission;

    static int totalCars;

public:
    Car() : Vehicle(), brand("Unknown"), mileage(0),
            numDoors(4), transmission("Manual") { totalCars++; }

    Car(string mod, string col, int vid, bool used, const Engine &eng,
        double price, int year, string brand, int mileage,
        int doors, string trans) : Vehicle(mod, col, vid, used, eng, price, year),
                                   brand(brand), mileage(mileage), numDoors(doors), transmission(trans)
    {
        totalCars++;
    }

    Car(const Car &other) : Vehicle(other), brand(other.brand), mileage(other.mileage),
                            numDoors(other.numDoors), transmission(other.transmission)
    {
        totalCars++;
    }

    ~Car() { totalCars--; }

    string getBrand() const { return brand; }
    int getMileage() const { return mileage; }
    int getNumDoors() const { return numDoors; }
    string getTransmission() const { return transmission; }

    void setBrand(const string &b) { brand = b; }
    void setMileage(int m) { mileage = m; }
    void setTransmission(const string &t) { transmission = t; }

    static int getTotalCars() { return totalCars; }

    bool matchesBrand(const string &b) const { return brand == b; }
    bool isInMileageRange(int lo, int hi) const { return mileage >= lo && mileage <= hi; }

    void display() const override
    {
        cout << "╔══ CAR LISTING ══════════════════════════╗\n"
             << "  ID          : " << vehicleID << "\n"
             << "  Brand       : " << brand << "\n"
             << "  Model       : " << model << "\n"
             << "  Color       : " << color << "\n"
             << "  Year        : " << year << "\n"
             << "  Price       : $" << price << "\n"
             << "  Mileage     : " << mileage << " km\n"
             << "  Doors       : " << numDoors << "\n"
             << "  Transmission: " << transmission << "\n"
             << "  Condition   : " << (is_used ? "Used" : "New") << "\n"
             << "  ── Engine ──\n";
        engine.display();
        cout << "╚═════════════════════════════════════════╝\n";
    }
};
int Car::totalCars = 0;

class Bike : public Vehicle
{
    string brand;
    int mileage;
    string bikeType;
    bool hasSidecar;

    static int totalBikes;

public:
    Bike() : Vehicle(), brand("Unknown"), mileage(0),
             bikeType("Sport"), hasSidecar(false) { totalBikes++; }

    Bike(string mod, string col, int vid, bool used, const Engine &eng,
         double price, int year, string brand, int mileage,
         string type, bool sidecar) : Vehicle(mod, col, vid, used, eng, price, year),
                                      brand(brand), mileage(mileage), bikeType(type), hasSidecar(sidecar)
    {
        totalBikes++;
    }

    Bike(const Bike &other) : Vehicle(other), brand(other.brand), mileage(other.mileage),
                              bikeType(other.bikeType), hasSidecar(other.hasSidecar)
    {
        totalBikes++;
    }

    ~Bike() { totalBikes--; }

    string getBrand() const { return brand; }
    int getMileage() const { return mileage; }
    string getBikeType() const { return bikeType; }
    bool getSidecar() const { return hasSidecar; }

    void setBrand(const string &b) { brand = b; }
    void setMileage(int m) { mileage = m; }
    void setBikeType(const string &t) { bikeType = t; }

    static int getTotalBikes() { return totalBikes; }

    bool matchesBrand(const string &b) const { return brand == b; }

    void display() const override
    {
        cout << "╔══ BIKE LISTING ══════════════════════════╗\n"
             << "  ID       : " << vehicleID << "\n"
             << "  Brand    : " << brand << "\n"
             << "  Model    : " << model << "\n"
             << "  Color    : " << color << "\n"
             << "  Year     : " << year << "\n"
             << "  Price    : $" << price << "\n"
             << "  Mileage  : " << mileage << " km\n"
             << "  Type     : " << bikeType << "\n"
             << "  Sidecar  : " << (hasSidecar ? "Yes" : "No") << "\n"
             << "  Condition: " << (is_used ? "Used" : "New") << "\n"
             << "  ── Engine ──\n";
        engine.display();
        cout << "╚══════════════════════════════════════════╝\n";
    }
};
int Bike::totalBikes = 0;