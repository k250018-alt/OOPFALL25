#include<iostream>
using namespace std;
int main(){
    int units;
    float bill=0;
    cin>>units;
    if(units<=50)
        bill=units*0.50;
    else if(units<=150)
        bill=50*0.50+(units-50)*0.75;
    else if(units<=250)
        bill=50*0.50+100*0.75+(units-150)*1.20;
    else
        bill=units*1.50;
    bill=bill+(bill*0.20);
    cout<<bill;
}
