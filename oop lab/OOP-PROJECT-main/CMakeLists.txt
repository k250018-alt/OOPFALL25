cmake_minimum_required(VERSION 3.16)
project(TacticalShooter CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-3.0.2/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(TacticalShooter main.cpp GameManager.cpp TileMap.cpp Player.cpp Bullet.cpp Explosion.cpp Enemy.cpp)

target_include_directories(TacticalShooter PRIVATE "C:/SFML-3.0.2/include")

target_link_libraries(TacticalShooter PRIVATE SFML::Graphics SFML::Window SFML::System)