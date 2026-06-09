#include"iostream"
#include"libary.h"
int main(){
    Member m1("Talha shaid", 101);
    Member m2("Mr.Talha Shaid",102);
    Libary libary("FAST NUCES");
    libary.addmember(&m1);
    libary.addmember(&m2);   
    libary.addBook("PF","1087");
    libary.addBook("CALC","1086");
    libary.displayDetails();

    cout<<endl<<"Member distance in main : "<<m1.getmember()<<endl;
}
