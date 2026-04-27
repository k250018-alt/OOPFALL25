#include<iostream>
using namespace std;
class Vehicle{
protected:
    string model;
    double rate;
public:
    Vehicle(string model ,double rate ): model(model), rate(rate){};
    virtual double getDailyRate() = 0;
    virtual void displayDetails() = 0;
};
class Car:public Vehicle{
    double Dailyrate;
    public:
    Car(string model ,double rate , double Dailyrate):Dailyrate(Dailyrate),Vehicle(model,rate){};
    double getDailyRate ()override{
        return Dailyrate;
    }
    void displayDetails()override{
        cout <<"\n CAR \n Daily Rate : "<< Dailyrate <<"\n model : "<<model <<"\n rate : "<<rate<<endl;
    }
};
class Bike:public Vehicle{
    double Dailyrate;
    public:
    Bike(string model ,double rate , double Dailyrate):Dailyrate(Dailyrate),Vehicle(model,rate){};
    double getDailyRate()override{
        return Dailyrate;
    }
    void displayDetails()override{
        cout <<"\n Bike \n Daily Rate : "<< Dailyrate <<"\n model : "<<model <<"\n rate : "<<rate<<endl;
    }
};
int main(){
    Vehicle *v;
    Car c1("ferrari" , 23.0 , 43.0);
    v= &c1;
    v->displayDetails();
    cout << v->getDailyRate();
}