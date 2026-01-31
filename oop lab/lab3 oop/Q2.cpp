#include"iostream"
using namespace std;
class Circle{
    double radius;
    double pi = 3.14159;
    public:
    void setRadius(double r){
        radius = r;
    }
    double getRadius(){
        return radius;
    }
    double area(){
        return pi * radius * radius;
    }
    double circumference(){
        return 2 * pi * radius;
    }
    double diameter(){
        return 2 * radius;
    }
};
int main(){
    Circle circle1;
    double r;
    cout<<"Enter the radius of the circle: ";
    cin>>r;
    circle1.setRadius(r);
    cout<<"Radius: "<<circle1.getRadius()<<endl;
    cout<<"Area: "<<circle1.area()<<endl; 
    cout<<"Circumference: "<<circle1.circumference()<<endl;
    cout<<"Diameter: "<<circle1.diameter()<<endl;
    return 0;
}