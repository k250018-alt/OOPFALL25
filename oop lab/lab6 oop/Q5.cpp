#include<iostream>
#include<string>
using namespace std;
 
class Vehicle {
public:
    string make, model;
    int year;
    Vehicle(string mk, string mo, int y) : make(mk), model(mo), year(y) {}
    void display() {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    }
};
 
class Car : public Vehicle {
public:
    int doors;
    float fuelEfficiency;
    Car(string mk, string mo, int y, int d, float fe)
        : Vehicle(mk, mo, y), doors(d), fuelEfficiency(fe) {}
    void display() {
        Vehicle::display();
        cout << "Doors: " << doors << ", Fuel Efficiency: " << fuelEfficiency << " km/L" << endl;
    }
};
 
class ElectricCar : public Car {
public:
    float batteryLife;
    ElectricCar(string mk, string mo, int y, int d, float fe, float bl)
        : Car(mk, mo, y, d, fe), batteryLife(bl) {}
    void display() {
        Car::display();
        cout << "Battery Life: " << batteryLife << " kWh" << endl;
    }
};
 
int main() {
    ElectricCar ec("Tesla", "Model 3", 2024, 4, 0, 75.0);
    ec.display();
    return 0;
}
