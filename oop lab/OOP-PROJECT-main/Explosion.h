#pragma once
#include <SFML/Graphics.hpp>

class Explosion
{
private:
    sf::CircleShape shape;
    float lifetime;
    float maxLifetime;

public:
    Explosion(sf::Vector2f position);
    void update(float deltaTime);
    void render(sf::RenderTarget& target);
    bool isFinished() const;
};