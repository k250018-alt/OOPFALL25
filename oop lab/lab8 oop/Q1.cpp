#include<iostream>
using namespace std;
class Speed;
class Time;
int claculatedistance(Speed& s, Time& t);
class Speed
{
    private:
    int speed;
    public:
    Speed(int s):speed(s){}
    friend int claculatedistance(Speed& s, Time& t);
};
class Time
{
    private:
    int time;
    public:
    Time(int t):time(t){}
    friend int claculatedistance(Speed& s, Time& t);
};
int claculatedistance(Speed& s, Time& t)
{
    return s.speed * t.time;
}
int main()
{
    Speed s(60);
    Time t(2);
    cout<<"Distance: "<<claculatedistance(s,t);
    return 0;
}