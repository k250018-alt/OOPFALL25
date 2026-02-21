#pragma once
#include <iostream>
#include "Vehicle.h"
using namespace std;
class Cars_Inventory{
    Car* cars[maxVehicles];
    bool used;
    public:
    Cars_Inventory(Car* cars ,bool isused):used(isused){

        for (int i = 0; i < maxVehicles; i++) {
            this->cars[i] = nullptr;
        }
        for(int i=0 ; i<maxVehicles ; i++){
            if(cars[i].getIsUsed() == isused){
                this->cars[i] = new Car(cars[i]);
            }
        }
    }
    void displayCarsInventory() const{
        for(int i=0 ; i<maxVehicles ; i++){
            if(cars[i] != nullptr){
                cars[i]->display();
                cout<<endl;
            }
        }
    }
    void addCar(const Car& car){
        if(car.getIsUsed() != used){
            return;
        }
        for(int i=0 ; i<maxVehicles ; i++){
                if(cars[i] == nullptr){
                    cars[i] = new Car(car);
                    break;
                }
        }
    }
    void removeCar(int vehicleID){
        for(int i=0 ; i<maxVehicles ; i++){
            if(cars[i] != nullptr && cars[i]->getID() == vehicleID){
                delete cars[i];
                cars[i] = nullptr;
                break;
            }
        }
    }
    ~Cars_Inventory(){
        for(int i=0 ; i<maxVehicles ; i++){
            if(cars[i] != nullptr){
                delete cars[i];
            }
        }
    }

};