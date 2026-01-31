#include <iostream>
using namespace std;
class Water_Bottle{
    string company;
    string color;
    double capacity_in_liters;
    double capacity_in_ml;
    public:
    void setDetails(string c1, string c2, double cap_ml){
        company = c1;
        color = c2;
        capacity_in_ml = cap_ml;
        capacity_in_liters = cap_ml / 1000;
    }
    string getCompany(){
        return company;
    }
    string getColor(){
        return color;
    }
    double getCapacityInLiters(){
        return capacity_in_liters;
    }
    double getCapacityInML(){
        return capacity_in_ml;
    }
    void drink(double amount_ml){
        if(amount_ml <= capacity_in_ml){
            capacity_in_ml -= amount_ml;
            capacity_in_liters = capacity_in_ml / 1000;
            cout<<"You drank "<<amount_ml<<" ml of water."<<endl;
        }
        else{
            cout<<"Not enough water in the bottle to drink "<<amount_ml<<" ml."<<endl;
        }
        cout<<"Remaining capacity: "<<capacity_in_ml<<" ml ("<<capacity_in_liters<<" liters)"<<endl;
    }
};
int main(){
    Water_Bottle bottle1;
    string c1, c2;
    double cap_ml, drink_amount;
    cout<<"Enter company name: ";
    cin>>c1;
    cout<<"Enter color: ";
    cin>>c2;
    cout<<"Enter capacity in ml: ";
    cin>>cap_ml;
    bottle1.setDetails(c1, c2, cap_ml);
    cout<<"Company: "<<bottle1.getCompany()<<endl;
    cout<<"Color: "<<bottle1.getColor()<<endl;
    cout<<"Capacity: "<<bottle1.getCapacityInML()<<" ml ("<<bottle1.getCapacityInLiters()<<" liters)"<<endl;
    cout<<"Enter amount to drink in ml: ";
    cin>>drink_amount;
    bottle1.drink(drink_amount);
}