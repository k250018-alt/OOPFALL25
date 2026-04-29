#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray vertices;
    sf::Texture tileset;
    std::vector<int> grid;
    sf::Vector2f tileDimensions;
    unsigned int mapWidth;
    unsigned int mapHeight;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool generateProceduralTileset();

public:
    bool load(sf::Vector2f tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height);
    bool isSolid(float x, float y) const;
};