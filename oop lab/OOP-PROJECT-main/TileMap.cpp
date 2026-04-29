#include "TileMap.h"

bool TileMap::generateProceduralTileset()
{
    sf::Image img;
    img.resize({160, 80});

    for (unsigned int x = 0; x < 80; ++x)
    {
        for (unsigned int y = 0; y < 80; ++y)
        {
            if (x % 20 == 0 || y % 20 == 0)
            {
                img.setPixel({x, y}, sf::Color(40, 40, 40));
            }
            else
            {
                img.setPixel({x, y}, sf::Color(60, 60, 60));
            }
        }
    }

    for (unsigned int x = 80; x < 160; ++x)
    {
        for (unsigned int y = 0; y < 80; ++y)
        {
            if (x % 40 == 0 || y % 20 == 0)
            {
                img.setPixel({x, y}, sf::Color(50, 50, 50));
            }
            else
            {
                img.setPixel({x, y}, sf::Color(150, 50, 50));
            }
        }
    }

    return tileset.loadFromImage(img);
}

bool TileMap::load(sf::Vector2f tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height)
{
    if (!generateProceduralTileset())
    {
        return false;
    }

    tileDimensions = tileSize;
    grid = tiles;
    mapWidth = width;
    mapHeight = height;
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];
            int tu = tileNumber % (tileset.getSize().x / static_cast<unsigned int>(tileSize.x));
            int tv = tileNumber / (tileset.getSize().x / static_cast<unsigned int>(tileSize.x));

            sf::Vertex* quad = &vertices[(i + j * width) * 6];

            quad[0].position = {i * tileSize.x, j * tileSize.y};
            quad[1].position = {(i + 1) * tileSize.x, j * tileSize.y};
            quad[2].position = {i * tileSize.x, (j + 1) * tileSize.y};
            quad[3].position = {i * tileSize.x, (j + 1) * tileSize.y};
            quad[4].position = {(i + 1) * tileSize.x, j * tileSize.y};
            quad[5].position = {(i + 1) * tileSize.x, (j + 1) * tileSize.y};

            quad[0].texCoords = {static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y)};
            quad[1].texCoords = {static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y)};
            quad[2].texCoords = {static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y)};
            quad[3].texCoords = {static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y)};
            quad[4].texCoords = {static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y)};
            quad[5].texCoords = {static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y)};
        }
    }
    return true;
}

bool TileMap::isSolid(float x, float y) const
{
    if (x < 0.0f || y < 0.0f || x >= mapWidth * tileDimensions.x || y >= mapHeight * tileDimensions.y)
    {
        return true;
    }
    unsigned int gridX = static_cast<unsigned int>(x / tileDimensions.x);
    unsigned int gridY = static_cast<unsigned int>(y / tileDimensions.y);
    return grid[gridX + gridY * mapWidth] == 1;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}