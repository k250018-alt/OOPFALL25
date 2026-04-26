#include<iostream>
#include<string>
using namespace std;
 
class Device {
public:
    string brand, model;
    Device(string b, string m) : brand(b), model(m) {}
    void display() {
        cout << "Brand: " << brand << ", Model: " << model << endl;
    }
};
 
class Smartphone : virtual public Device {
public:
    int simSlots;
    Smartphone(string b, string m, int s) : Device(b, m), simSlots(s) {}
    void display() {
        Device::display();
        cout << "SIM Slots: " << simSlots << endl;
    }
};
 
class Tablet : virtual public Device {
public:
    bool stylusSupport;
    Tablet(string b, string m, bool st) : Device(b, m), stylusSupport(st) {}
    void display() {
        Device::display();
        cout << "Stylus Support: " << (stylusSupport ? "Yes" : "No") << endl;
    }
};
 
class HybridDevice : public Smartphone, public Tablet {
public:
    HybridDevice(string b, string m, int s, bool st)
        : Device(b, m), Smartphone(b, m, s), Tablet(b, m, st) {}
    void display() {
        Device::display();
        cout << "SIM Slots: " << simSlots << endl;
        cout << "Stylus Support: " << (stylusSupport ? "Yes" : "No") << endl;
    }
};
 
int main() {
    HybridDevice hd("Samsung", "Galaxy Ultra", 2, true);
    hd.display();
    return 0;
}
