#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f startPosition, sf::Vector2f targetDirection, float speed)
{
    shape.setRadius(4.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPosition);
    float magnitude = std::sqrt((targetDirection.x * targetDirection.x) + (targetDirection.y * targetDirection.y));
    if (magnitude != 0.0f) velocity = (targetDirection / magnitude) * speed;
}

void Bullet::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Bullet::render(sf::RenderTarget& target)
{
    target.draw(shape);
}

sf::Vector2f Bullet::getPosition() const
{
    return shape.getPosition();
}