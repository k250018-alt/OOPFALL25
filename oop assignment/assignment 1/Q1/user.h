#pragma once
#include <iostream>
#include "Cars_Inventory.h"
#include "Bike_Inventory.h"
using namespace std;
class User{
    protected:
    string name;
    string email;
    string password;
    public:
    User(string name , string email , string password):name(name) , email(email) , password(password){}
    void seeCarsInventory(const Cars_Inventory& inventory) const{
        inventory.displayCarsInventory();
    }
    void seeBikeInventory(const Bike_Inventory& inventory) const{
        inventory.displayBikeInventory();
    }
};
class Admin : public User{
    public:
    Admin(string name , string email , string password):User(name , email , password){}
    void addCarToInventory(Cars_Inventory& inventory , const Car& car){
        inventory.addCar(car);
    }
    void modifyCarInInventory(Cars_Inventory& inventory , int vehicleID , const Car& newCar){
        inventory.removeCar(vehicleID);
        inventory.addCar(newCar);
    }
    void modifyBikeInInventory(Bike_Inventory& inventory , int vehicleID , const Bike& newBike){
        inventory.removeBike(vehicleID);
        inventory.addBike(newBike);
    }
};
class Seller : public User{
    public:
    Seller(string name , string email , string password):User(name , email , password){}
    void addCarToInventory(Cars_Inventory& inventory , const Car& car){
        inventory.addCar(car);
    }
    void addBikeToInventory(Bike_Inventory& inventory , const Bike& bike){
        inventory.addBike(bike);
    }
};
class Buyer : public User{
    public:
    Buyer(string name , string email , string password):User(name , email , password){}
    void proceedToBuyCar(Cars_Inventory& inventory , int vehicleID){
        inventory.removeCar(vehicleID);
    }
};  