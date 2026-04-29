#include "Player.h"
#include <cmath>

Player::Player(float startX, float startY, sf::Texture& texture)
    : sprite(texture)
{
    position = sf::Vector2f(startX, startY);
    textureRef = &texture;
    hitBoxSize = 60.0f;
    speed = 250.0f;
    health = 5;
    invulnTimer = 0.0f;

    sf::Vector2u texSize = textureRef->getSize();
    sprite.setOrigin({static_cast<float>(texSize.x) / 2.0f, static_cast<float>(texSize.y) / 2.0f});

    float scale = hitBoxSize / static_cast<float>(texSize.x);
    sprite.setScale({scale * 1.5f, scale * 1.5f});
    
    sprite.setPosition({position.x + (hitBoxSize / 2.0f), position.y + (hitBoxSize / 2.0f)});
}

bool Player::canMove(const TileMap& map, float newX, float newY) const
{
    if (map.isSolid(newX, newY))
    {
        return false;
    }
    if (map.isSolid(newX + hitBoxSize, newY))
    {
        return false;
    }
    if (map.isSolid(newX, newY + hitBoxSize))
    {
        return false;
    }
    if (map.isSolid(newX + hitBoxSize, newY + hitBoxSize))
    {
        return false;
    }
    return true;
}

void Player::update(float deltaTime, const TileMap& map, sf::Vector2f mousePos)
{
    if (invulnTimer > 0.0f)
    {
        invulnTimer -= deltaTime;
    }

    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        deltaY -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        deltaY += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        deltaX -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        deltaX += speed * deltaTime;
    }

    if (deltaX != 0.0f)
    {
        if (canMove(map, position.x + deltaX, position.y))
        {
            position.x += deltaX;
        }
    }

    if (deltaY != 0.0f)
    {
        if (canMove(map, position.x, position.y + deltaY))
        {
            position.y += deltaY;
        }
    }

    sf::Vector2f center = getCenterPosition();
    float dx = mousePos.x - center.x;
    float dy = mousePos.y - center.y;
    float angle = std::atan2(dy, dx) * 180.0f / 3.14159265f;
    
    sprite.setRotation(sf::degrees(angle));
    sprite.setPosition(center);
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}

sf::Vector2f Player::getCenterPosition() const
{
    return sf::Vector2f(position.x + (hitBoxSize / 2.0f), position.y + (hitBoxSize / 2.0f));
}

void Player::takeDamage(int damage)
{
    if (invulnTimer <= 0.0f)
    {
        health -= damage;
        invulnTimer = 1.0f;
    }
}

bool Player::isDead() const
{
    return health <= 0;
}

int Player::getHealth() const
{
    return health;
}