#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Bullet(sf::Vector2f startPosition, sf::Vector2f targetDirection, float speed);
    void update(float deltaTime);
    void render(sf::RenderTarget& target);
    sf::Vector2f getPosition() const;
};