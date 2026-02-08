#pragma once
#include <iostream>
using namespace std;
class Football_Player{
    private:
        string *name;
        string *position;
        int *goals_Scored;
    public:
        Football_Player(string n, string p, int g){
            name = new string(n);
            position = new string(p);
            goals_Scored = new int(g);
        }
        Football_Player(){
            name = new string("Unknown");
            position = new string("Unknown");
            goals_Scored = new int(0);
        }

        Football_Player(string n){
            name = new string(n);
            position = new string("Unknown");
            goals_Scored = new int(0);
        }
        Football_Player(Football_Player &other){
            name = new string(*other.name);
            position = new string(*other.position);
            goals_Scored = new int(*other.goals_Scored);
        }
        ~Football_Player(){
            delete name;
            delete position;
            delete goals_Scored;
        }
};