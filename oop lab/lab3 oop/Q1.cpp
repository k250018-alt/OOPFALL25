#include <iostream>
using namespace std;
class BoardMarker{
    string company;
    string color;
    bool refillable;
    bool inkstatus;//1 for full, 0 for empty
    public:
    void setDetails(string c1, string c2, bool r, bool i){
        company = c1;
        color = c2;
        refillable = r;
        inkstatus = i;
    }
    string getCompany(){
        return company;
    }
    string getColor(){
        return color;
    }
    bool isRefillable(){
        return refillable;
    }
    bool getInkStatus(){
        return inkstatus;
    }
    void write(){
        if(inkstatus){
            cout<<"Writing on board with "<<color<<" color marker of "<<company<<" company."<<endl;
        }
        else{
            cout<<"Cannot write, the marker is out of ink."<<endl;
            inkstatus = 0;
        }
    }
    void refill(){
        if(refillable){
            inkstatus = 1;
            cout<<"The marker has been refilled."<<endl;
        }
        else{
            cout<<"This marker is not refillable."<<endl;
        }
    }
};
int main(){
    BoardMarker mark1[3];
    for(int i=0;i<3;i++){
        string c1, c2;
        bool r, j;
        cout<<"Enter company name: ";
        cin>>c1;
        cout<<"Enter color: ";
        cin>>c2;
        cout<<"Is it refillable (1 for yes, 0 for no): ";
        cin>>r;
        cout<<"Is it full of ink (1 for full, 0 for epty): ";
        cin>>j;
        mark1[i].setDetails(c1, c2, r, j);
    }
    for(int i=0;i<3;i++){
        mark1[i].write();
        mark1[i].refill();
        mark1[i].write();
    }
}