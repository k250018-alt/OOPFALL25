#pragma once
#include <iostream>
#include "Vehicle.h"
using namespace std;
class Bike_Inventory{
    Bike* bikes[maxVehicles];
    bool used;
    public:
    Bike_Inventory(Bike* bikes ,bool isused):used(isused){
        for (int i = 0; i < maxVehicles; i++) {
            this->bikes[i] = nullptr;
        }
        for(int i=0 ; i<maxVehicles ; i++){
            if(bikes[i].getIsUsed() == isused){
                this->bikes[i] = new Bike(bikes[i]);
            }
        }
    }
    void displayBikeInventory() const{
        for(int i=0 ; i<maxVehicles ; i++){
            if(bikes[i] != nullptr){
                bikes[i]->display();
                cout<<endl;
            }
        }
    }
    void addBike(const Bike& bike){
        for(int i=0 ; i<maxVehicles ; i++){
            if(bike.getIsUsed() == used){
                if(bikes[i] == nullptr){
                    bikes[i] = new Bike(bike);
                    break;
                }
            }
        }
    }
    void removeBike(int vehicleID){
        for(int i=0 ; i<maxVehicles ; i++){
            if(bikes[i] != nullptr && bikes[i]->getID() == vehicleID){
                delete bikes[i];
                bikes[i] = nullptr;
                break;
            }
        }
    }
    ~Bike_Inventory(){
        for(int i=0 ; i<maxVehicles ; i++){
            if(bikes[i] != nullptr){
                delete bikes[i];
            }
        }
    }

};