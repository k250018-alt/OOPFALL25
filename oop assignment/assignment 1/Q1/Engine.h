#pragma once
#include<iostream>
using namespace std;

class Engine{
    const string fuelType;
    const string cylinderConfiguration;
    const int numberOfCylinders;
    const string ignitionType;
    public:
        Engine():
        fuelType("NULL"),
        cylinderConfiguration("NULL"),
        numberOfCylinders(0),
        ignitionType("NULL"){}

        Engine(string fuetype , string cylinder_config , int no_of_cylinders ,string ignition_type ):
        fuelType(fuetype),
        cylinderConfiguration(cylinder_config),
        numberOfCylinders(no_of_cylinders),
        ignitionType(ignition_type){

        }
        void display() const;
};

    void Engine::display() const{
        cout<<"Fuel type : " << fuelType ;
        cout << "Cylinder configuration : " << cylinderConfiguration;
        cout << "Number of Cylinders : " << numberOfCylinders;
        cout << "Ignition type : " << ignitionType;
    }