#include"Player.h"
#include"iostream"
using namespace std;
int main()
{
    Player p1("Alice", 10, 25);
    Player p2("Bob", 7, 30);
    
    p1.display_player_stats();
    p2.display_player_stats();
    
    p1.play_Match(15);
    p2.play_Match(20);
    
    p1.display_player_stats();
    p2.display_player_stats();
    
    return 0;
}