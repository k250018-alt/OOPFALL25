#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Enemy.h"

class GameManager
{
private:
    static GameManager* instance;
    sf::RenderWindow gameWindow;
    sf::View cameraView;
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Font uiFont;
    sf::Text* uiText;
    bool isRunning;
    bool isGameOver;
    TileMap levelMap;
    Player* mainPlayer;
    std::vector<Bullet*> activeBullets;
    std::vector<Explosion*> activeExplosions;
    std::vector<Enemy*> activeEnemies;
    GameManager();

public:
    static GameManager* getInstance();
    void initialize();
    void runLoop();
    void cleanUp();
};