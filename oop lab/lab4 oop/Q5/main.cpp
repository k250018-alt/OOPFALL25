#include"Football_player.h"
#include"iostream"
using namespace std;
int main(){
    Football_Player player1("John", "Forward", 5);
    Football_Player player2(player1);
    Football_Player player3;
    Football_Player player4("Alice");
    return 0;
}