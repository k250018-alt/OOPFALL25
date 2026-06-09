#pragma once
#include <iostream>
using namespace std;

class  Member{
    string name;
    int memberID;

    public:
    Member(string name , int memberID) : name(name), memberID(memberID){};
    
    string getmember(){
        return name;
    }
};