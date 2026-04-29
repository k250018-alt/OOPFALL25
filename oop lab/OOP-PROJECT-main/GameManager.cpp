#include "GameManager.h"
#include <optional>
#include <cmath>
#include <string>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    mainPlayer = nullptr;
    uiText = nullptr;
}

GameManager* GameManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }
    return instance;
}

void GameManager::initialize()
{
    gameWindow.create(sf::VideoMode({1280, 960}), "Tactical Shooter");
    isRunning = true;
    isGameOver = false;

    cameraView.setSize({1280.0f, 960.0f});

    if (!playerTexture.loadFromFile("player.png"))
    {
        isRunning = false;
    }

    if (!enemyTexture.loadFromFile("enemy.png"))
    {
        isRunning = false;
    }

    if (!uiFont.openFromFile("arial.ttf"))
    {
        isRunning = false;
    }

    uiText = new sf::Text(uiFont, "HEALTH: 5", 36);
    uiText->setFillColor(sf::Color::Green);

    std::vector<int> levelData = 
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
        1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    levelMap.load(sf::Vector2f(80.f, 80.f), levelData, 20, 12);
    mainPlayer = new Player(90.0f, 90.0f, playerTexture);
    
    activeEnemies.push_back(new Enemy(1130.0f, 90.0f, enemyTexture));
    activeEnemies.push_back(new Enemy(490.0f, 650.0f, enemyTexture));
    activeEnemies.push_back(new Enemy(650.0f, 810.0f, enemyTexture));
    activeEnemies.push_back(new Enemy(1210.0f, 570.0f, enemyTexture));
}

void GameManager::runLoop()
{
    sf::Clock deltaClock;
    while (isRunning && gameWindow.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();
        
        while (const std::optional event = gameWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                isRunning = false;
                gameWindow.close();
            }
            else if (!isGameOver && event->getIf<sf::Event::MouseButtonPressed>())
            {
                const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pixelPos(mouseClick->position.x, mouseClick->position.y);
                    sf::Vector2f targetPos = gameWindow.mapPixelToCoords(pixelPos, cameraView);
                    sf::Vector2f startPos = mainPlayer->getCenterPosition();
                    sf::Vector2f direction = targetPos - startPos;
                    activeBullets.push_back(new Bullet(startPos, direction, 1200.0f));
                }
            }
        }

        if (!isGameOver)
        {
            cameraView.setCenter(mainPlayer->getCenterPosition());
            gameWindow.setView(cameraView);

            sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
            sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos, cameraView);
            mainPlayer->update(deltaTime, levelMap, worldPos);

            for (Enemy* enemy : activeEnemies)
            {
                enemy->update(deltaTime, levelMap, mainPlayer->getCenterPosition());
                
                sf::Vector2f pCenter = mainPlayer->getCenterPosition();
                sf::Vector2f eCenter = enemy->getCenterPosition();
                float dx = pCenter.x - eCenter.x;
                float dy = pCenter.y - eCenter.y;
                if ((dx * dx) + (dy * dy) < (50.0f * 50.0f))
                {
                    mainPlayer->takeDamage(1);
                }
            }

            for (auto bIt = activeBullets.begin(); bIt != activeBullets.end(); )
            {
                (*bIt)->update(deltaTime);
                bool bulletDestroyed = false;
                sf::Vector2f bPos = (*bIt)->getPosition();

                if (levelMap.isSolid(bPos.x, bPos.y))
                {
                    activeExplosions.push_back(new Explosion(bPos));
                    delete *bIt;
                    bIt = activeBullets.erase(bIt);
                    bulletDestroyed = true;
                }
                
                if (!bulletDestroyed)
                {
                    for (auto eIt = activeEnemies.begin(); eIt != activeEnemies.end(); )
                    {
                        sf::Vector2f ePos = (*eIt)->getCenterPosition();
                        float dx = bPos.x - ePos.x;
                        float dy = bPos.y - ePos.y;
                        
                        if ((dx * dx) + (dy * dy) < (30.0f * 30.0f))
                        {
                            activeExplosions.push_back(new Explosion(ePos));
                            (*eIt)->takeDamage(1);
                            
                            if ((*eIt)->isDead())
                            {
                                delete *eIt;
                                activeEnemies.erase(eIt);
                            }
                            
                            delete *bIt;
                            bIt = activeBullets.erase(bIt);
                            bulletDestroyed = true;
                            break;
                        }
                        else
                        {
                            ++eIt;
                        }
                    }
                }
                
                if (!bulletDestroyed)
                {
                    ++bIt;
                }
            }

            for (auto it = activeExplosions.begin(); it != activeExplosions.end(); )
            {
                (*it)->update(deltaTime);
                if ((*it)->isFinished())
                {
                    delete *it;
                    it = activeExplosions.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            if (mainPlayer->isDead())
            {
                isGameOver = true;
                uiText->setString("GAME OVER");
                uiText->setCharacterSize(72);
                uiText->setFillColor(sf::Color::Red);
                uiText->setPosition({420.0f, 400.0f});
            }
            else
            {
                uiText->setString("HEALTH: " + std::to_string(mainPlayer->getHealth()));
                uiText->setPosition({20.0f, 20.0f});
            }
        }

        gameWindow.clear(sf::Color::Black);
        
        if (!isGameOver)
        {
            gameWindow.setView(cameraView);
            gameWindow.draw(levelMap);
            mainPlayer->render(gameWindow);
            for (Enemy* enemy : activeEnemies) enemy->render(gameWindow);
            for (Bullet* b : activeBullets) b->render(gameWindow);
            for (Explosion* e : activeExplosions) e->render(gameWindow);
        }

        gameWindow.setView(gameWindow.getDefaultView());
        gameWindow.draw(*uiText);
        
        gameWindow.display();
    }
}

void GameManager::cleanUp()
{
    for (Bullet* b : activeBullets) delete b;
    for (Explosion* e : activeExplosions) delete e;
    for (Enemy* enemy : activeEnemies) delete enemy;
    if (mainPlayer) delete mainPlayer;
    if (uiText) delete uiText;
    if (instance) delete instance;
}