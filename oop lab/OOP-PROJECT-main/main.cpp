#include "GameManager.h"

int main() {
  GameManager *game = GameManager::getInstance();
  game->initialize();
  game->runLoop();
  game->cleanUp();
  return 0;
}