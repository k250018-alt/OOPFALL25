#include "Enemy.h"
#include <cmath>
#include <queue>
#include <map>
#include <algorithm>

struct Node
{
    sf::Vector2i position;
    int gCost;
    int hCost;
    
    int fCost() const
    {
        return gCost + hCost;
    }
};

struct CompareNode
{
    bool operator()(const Node& a, const Node& b) const
    {
        return a.fCost() > b.fCost();
    }
};

Enemy::Enemy(float startX, float startY, sf::Texture& texture)
    : sprite(texture)
{
    position = sf::Vector2f(startX, startY);
    hitBoxSize = 60.0f;
    speed = 150.0f;
    health = 3;
    pathTimer = 0.0f;

    sf::Vector2u texSize = texture.getSize();
    sprite.setOrigin({static_cast<float>(texSize.x) / 2.0f, static_cast<float>(texSize.y) / 2.0f});

    float scale = hitBoxSize / static_cast<float>(texSize.x);
    sprite.setScale({scale * 1.5f, scale * 1.5f});
    sprite.setPosition({position.x + (hitBoxSize / 2.0f), position.y + (hitBoxSize / 2.0f)});
}

bool Enemy::canMove(const TileMap& map, float newX, float newY) const
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

void Enemy::calculatePath(const TileMap& map, sf::Vector2f targetPos)
{
    path.clear();
    
    sf::Vector2i startGrid(static_cast<int>((position.x + (hitBoxSize / 2.0f)) / 80.0f), static_cast<int>((position.y + (hitBoxSize / 2.0f)) / 80.0f));
    sf::Vector2i targetGrid(static_cast<int>(targetPos.x / 80.0f), static_cast<int>(targetPos.y / 80.0f));

    if (startGrid.x == targetGrid.x && startGrid.y == targetGrid.y)
    {
        return;
    }

    std::priority_queue<Node, std::vector<Node>, CompareNode> openSet;
    std::map<int, sf::Vector2i> cameFrom;
    std::map<int, int> gCosts;

    int startHash = startGrid.y * 1000 + startGrid.x;
    openSet.push({startGrid, 0, std::abs(startGrid.x - targetGrid.x) + std::abs(startGrid.y - targetGrid.y)});
    gCosts[startHash] = 0;

    sf::Vector2i directions[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        int currentHash = current.position.y * 1000 + current.position.x;

        if (current.position.x == targetGrid.x && current.position.y == targetGrid.y)
        {
            sf::Vector2i curr = targetGrid;
            while (curr.x != startGrid.x || curr.y != startGrid.y)
            {
                path.push_back(sf::Vector2f((curr.x * 80.0f) + 40.0f, (curr.y * 80.0f) + 40.0f));
                int hash = curr.y * 1000 + curr.x;
                curr = cameFrom[hash];
            }
            std::reverse(path.begin(), path.end());
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            sf::Vector2i neighbor(current.position.x + directions[i].x, current.position.y + directions[i].y);
            
            float testX = static_cast<float>(neighbor.x * 80);
            float testY = static_cast<float>(neighbor.y * 80);

            if (map.isSolid(testX + 40.0f, testY + 40.0f))
            {
                continue;
            }

            int neighborHash = neighbor.y * 1000 + neighbor.x;
            int tentativeGCost = gCosts[currentHash] + 10;

            if (gCosts.find(neighborHash) == gCosts.end() || tentativeGCost < gCosts[neighborHash])
            {
                cameFrom[neighborHash] = current.position;
                gCosts[neighborHash] = tentativeGCost;
                int hCost = (std::abs(neighbor.x - targetGrid.x) + std::abs(neighbor.y - targetGrid.y)) * 10;
                openSet.push({neighbor, tentativeGCost, hCost});
            }
        }
    }
}

void Enemy::update(float deltaTime, const TileMap& map, sf::Vector2f playerPos)
{
    pathTimer += deltaTime;
    if (pathTimer >= 0.5f)
    {
        calculatePath(map, playerPos);
        pathTimer = 0.0f;
    }

    if (!path.empty())
    {
        sf::Vector2f targetWaypoint = path[0];
        sf::Vector2f center = getCenterPosition();
        float dx = targetWaypoint.x - center.x;
        float dy = targetWaypoint.y - center.y;
        float distance = std::sqrt((dx * dx) + (dy * dy));

        if (distance < 10.0f)
        {
            path.erase(path.begin());
        }
        else
        {
            float moveX = (dx / distance) * speed * deltaTime;
            float moveY = (dy / distance) * speed * deltaTime;

            if (canMove(map, position.x + moveX, position.y))
            {
                position.x += moveX;
            }
            
            if (canMove(map, position.x, position.y + moveY))
            {
                position.y += moveY;
            }
        }
    }

    sf::Vector2f center = getCenterPosition();
    float dxRot = playerPos.x - center.x;
    float dyRot = playerPos.y - center.y;
    float angle = std::atan2(dyRot, dxRot) * 180.0f / 3.14159265f;
    
    sprite.setRotation(sf::degrees(angle));
    sprite.setPosition({position.x + (hitBoxSize / 2.0f), position.y + (hitBoxSize / 2.0f)});
}

void Enemy::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}

sf::Vector2f Enemy::getCenterPosition() const
{
    return sf::Vector2f(position.x + (hitBoxSize / 2.0f), position.y + (hitBoxSize / 2.0f));
}

void Enemy::takeDamage(int damage)
{
    health -= damage;
}

bool Enemy::isDead() const
{
    return health <= 0;
}