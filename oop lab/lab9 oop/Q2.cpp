#include<iostream>
using namespace std;
class SmartDevice{
protected:
    bool isOn;
public:
    SmartDevice(bool isOn):isOn(isOn){};
    virtual void turnon(double function) = 0;
    virtual void turnoff() = 0;
    virtual void status() = 0;
};
class lightbulb:public SmartDevice{
    double brightness;
public:
    lightbulb(bool isOn , double brightness):brightness(brightness),SmartDevice(isOn){};
    void turnon(double function){
        isOn =1;
        brightness =function;
    }
    void turnoff(){
        isOn =0;
        brightness = 0.0;
    }
    void status(){
        cout<<"\n Status \n power : "<< isOn <<"\n brightness : "<< brightness<<endl;
    }
};
class Thermostate:public SmartDevice{
    double temperature;
public:
    Thermostate(bool isOn , double temperature):temperature(temperature),SmartDevice(isOn){};
    void turnon(double function){
        isOn =1;
        temperature =function;
    }
    void turnoff(){
        isOn =0;
        temperature= 0.0;
    }
    void status(){
        cout<<"\n Status \n power : "<< isOn <<"\n temperature : "<< temperature<<endl;
    }
};
int main(){
    SmartDevice *s[2];
    s[0] = new lightbulb(0 , 0);
    s[1] = new Thermostate(0 , 0);
    s[0]->turnon(20);
    s[0]->status();
    s[0]->turnoff();
    s[1]->turnon(30);
    s[1]->status();
    s[1]->turnoff();
}