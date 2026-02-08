#pragma once
#include <iostream>
using namespace std;

class WeekDay{
    private:
        string *day;
        int current_Day;
    public:
        WeekDay(){
            day = new string[7]{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            current_Day = 0;
        }
        WeekDay(int d){
            day = new string[7]{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            current_Day = d % 7;
        }
        void get_current_Day(){
            cout << "Current day: " << day[current_Day] << endl;
        }
        void next_Day(){
            int next_Day = (current_Day + 1) % 7;
            cout << "Next day: " << day[next_Day] << endl;
        }
        void previous_Day(){
            int previous_Day = (current_Day - 1 + 7) % 7;
            cout << "Previous day: " << day[previous_Day] << endl;
        }
        void day_after_N_days(int n){
            int new_Day = (current_Day + n) % 7;
            cout << "Day after " << n << " days: " << day[new_Day] << endl;
        }
    
};