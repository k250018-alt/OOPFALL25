#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture* textureRef;
    sf::Vector2f position;
    float speed;
    float hitBoxSize;
    int health;
    float invulnTimer;
    bool canMove(const TileMap& map, float newX, float newY) const;

public:
    Player(float startX, float startY, sf::Texture& texture);
    void update(float deltaTime, const TileMap& map, sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
    sf::Vector2f getCenterPosition() const;
    void takeDamage(int damage);
    bool isDead() const;
    int getHealth() const;
};