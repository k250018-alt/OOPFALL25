#pragma once
#include <iostream>
using namespace std;
class Player{
    private:
        string name;
        int jersey_Number;
        int average_Score;
    public:
        Player(string n, int j, int a){
            name = n;
            jersey_Number = j;
            average_Score = a;
        }
        void improve_Score(int increment){
            average_Score += increment;
        }
        void display_player_stats(){
            cout << "Player Name: " << name << endl;
            cout << "Jersey Number: " << jersey_Number << endl;
            cout << "Average Score: " << average_Score << endl;
        }
        void play_Match(int runs_Scored){
            cout << name << " is playing a match and scored " << runs_Scored << " runs." << endl;
            improve_Score(runs_Scored); }
            
};
