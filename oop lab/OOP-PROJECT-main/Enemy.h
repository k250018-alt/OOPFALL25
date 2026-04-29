#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"

class Enemy
{
private:
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    float hitBoxSize;
    int health;
    std::vector<sf::Vector2f> path;
    float pathTimer;
    bool canMove(const TileMap& map, float newX, float newY) const;
    void calculatePath(const TileMap& map, sf::Vector2f targetPos);

public:
    Enemy(float startX, float startY, sf::Texture& texture);
    void update(float deltaTime, const TileMap& map, sf::Vector2f playerPos);
    void render(sf::RenderTarget& target);
    sf::Vector2f getCenterPosition() const;
    void takeDamage(int damage);
    bool isDead() const;
};