#pragma once
#include <iostream>
using namespace std;

class Engine
{
    const string fuelType;
    const string cylinderConfiguration;
    const int numberOfCylinders;
    const string ignitionType;
    const double displacement;
    const int horsepower;

public:
    Engine() : fuelType("Unknown"), cylinderConfiguration("Unknown"),
               numberOfCylinders(0), ignitionType("Unknown"),
               displacement(0.0), horsepower(0) {}

    Engine(string fuelType, string cylinderConfig, int numCylinders,
           string ignitionType, double displacement, int horsepower) : fuelType(fuelType), cylinderConfiguration(cylinderConfig),
                                                                       numberOfCylinders(numCylinders), ignitionType(ignitionType),
                                                                       displacement(displacement), horsepower(horsepower) {}

    Engine(const Engine &other) : fuelType(other.fuelType), cylinderConfiguration(other.cylinderConfiguration),
                                  numberOfCylinders(other.numberOfCylinders), ignitionType(other.ignitionType),
                                  displacement(other.displacement), horsepower(other.horsepower) {}

    string getFuelType() const { return fuelType; }
    string getCylinderConfig() const { return cylinderConfiguration; }
    int getNumCylinders() const { return numberOfCylinders; }
    string getIgnitionType() const { return ignitionType; }
    double getDisplacement() const { return displacement; }
    int getHorsepower() const { return horsepower; }

    void display() const
    {
        cout << "  Fuel Type          : " << fuelType << "\n"
             << "  Cylinder Config    : " << cylinderConfiguration << "\n"
             << "  Number of Cylinders: " << numberOfCylinders << "\n"
             << "  Ignition Type      : " << ignitionType << "\n"
             << "  Displacement (L)   : " << displacement << "\n"
             << "  Horsepower         : " << horsepower << " hp\n";
    }

    bool matchesFuelType(const string &type) const
    {
        return fuelType == type;
    }

    bool hasMinHorsepower(int minHP) const
    {
        return horsepower >= minHP;
    }
};