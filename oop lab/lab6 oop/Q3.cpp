#include<iostream>
#include<string>
using namespace std;
 
class Position {
public:
    float x, y, z;
    Position() : x(0), y(0), z(0) {}
    void setPosition(float px, float py, float pz) {
        x = px; y = py; z = pz;
    }
    void displayPosition() {
        cout << "Position -> X: " << x << " Y: " << y << " Z: " << z << endl;
    }
};
 
class Health {
public:
    int health;
    Health() : health(100) {}
    void setHealth(int h) { health = h; }
    void displayHealth() {
        cout << "Health: " << health << endl;
    }
};
 
class Character : public Position, public Health {
public:
    string name;
    Character(string n) : name(n) {}
    void display() {
        cout << "Character: " << name << endl;
        displayPosition();
        displayHealth();
    }
};
 
int main() {
    Character c("Hero");
    c.setPosition(10.5, 20.3, 5.0);
    c.setHealth(85);
    c.display();
    return 0;
}
