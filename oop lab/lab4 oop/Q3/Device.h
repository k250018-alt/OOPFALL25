#pragma once
#include <iostream>
using namespace std;
class Device{
    private:
        string name;
        string type;
        bool is_on;
    public:
        Device(string n, string t, bool on){
            name = n;
            type = t;
            is_on = on;
        }
        ~Device(){
            cout << "Device " << name << " is being destroyed." << endl;
        
        }
};