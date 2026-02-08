#include"iostream"
#include "WeekDay.h"
using namespace std;

int main(){
    WeekDay w1;
    WeekDay w2(3);
    w2.get_current_Day();
    w2.next_Day();
    w2.previous_Day();
    w2.day_after_N_days(5);
    return 0;
}