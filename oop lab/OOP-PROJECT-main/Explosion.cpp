#include "Explosion.h"
#include <cstdint>

Explosion::Explosion(sf::Vector2f position)
{
    maxLifetime = 0.15f;
    lifetime = maxLifetime;
    shape.setRadius(2.0f);
    shape.setFillColor(sf::Color(255, 150, 0, 255));
    shape.setOrigin({2.0f, 2.0f});
    shape.setPosition(position);
}

void Explosion::update(float deltaTime)
{
    lifetime -= deltaTime;
    if (lifetime > 0.0f)
    {
        float progress = 1.0f - (lifetime / maxLifetime);
        shape.setRadius(2.0f + (progress * 10.0f));
        shape.setOrigin({shape.getRadius(), shape.getRadius()});
        sf::Color color = shape.getFillColor();
        color.a = static_cast<std::uint8_t>(255.0f * (lifetime / maxLifetime));
        shape.setFillColor(color);
    }
}

void Explosion::render(sf::RenderTarget& target)
{
    target.draw(shape);
}

bool Explosion::isFinished() const
{
    return lifetime <= 0.0f;
}