#include<iostream>
using namespace std;
class Trafficcontrol{
    int carsonroad;
    int delaytime;
    public:
    Trafficcontrol(int c, int d):carsonroad(c), delaytime(d){}
    Trafficcontrol():carsonroad(0), delaytime(0){}
    Trafficcontrol operator+(const Trafficcontrol& t)
    {
        return Trafficcontrol(carsonroad + t.carsonroad, delaytime + t.delaytime);
    }
    Trafficcontrol operator-(const Trafficcontrol& t)
    {
        return Trafficcontrol(carsonroad - t.carsonroad, delaytime - t.delaytime);
    }
    Trafficcontrol operator*(int num_of_traffic_faliures)
    {
        return Trafficcontrol(carsonroad, delaytime * num_of_traffic_faliures* 2);
    }
    void operator==(const Trafficcontrol& t)
    {
        if(carsonroad == t.carsonroad){
            cout <<" gridlock";
        }
    }
};
int main()
{
    Trafficcontrol t1(10, 5);
    Trafficcontrol t2(20, 10);
    Trafficcontrol t3 = t1 + t2;
    
}