# Tactical Shooter Simulation
> **C++20 | SFML 3.0 | 2D Top-Down Combat System**

## Overview
Tactical Shooter is a high-performance 2D combat simulation built entirely in standard C++20 using the Simple and Fast Multimedia Library (SFML). The project demonstrates real-time interactive mechanics, custom AI pathfinding, and strict Object-Oriented system architecture.

## Technical Architecture
The core engine is driven by a centralized management pattern, interacting with deeply encapsulated entity classes.

* **GameManager (Singleton Pattern):** A centralized orchestrator that strictly controls the game loop, window rendering, memory allocation, and entity lifecycle. It ensures only one instance of the game state exists at any time.
* **A* Pathfinding Algorithm:** The `Enemy` AI utilizes a custom-built A* (A-Star) search algorithm. It dynamically calculates the shortest, non-colliding route to the player using a priority queue and Manhattan distance heuristics, re-evaluating the grid every 0.5 seconds.
* **TileMap Grid System:** A deterministic spatial grid that handles rigid body collisions for both entities and projectiles, allowing for complex level geometries.
* **Memory Management:** The system handles dynamic allocation of combat entities (Enemies, Bullets, Explosions) via raw pointers and standard vectors, with explicit garbage collection routines executed during runtime loop iterations and engine shutdown.

## Build Requirements
This project utilizes a modern CMake build pipeline.

* **C++ Standard:** C++20 (Required)
* **Graphics API:** SFML 3.0.2 (Graphics, Window, System modules)
* **Build Tool:** CMake 3.16+

## Compilation Instructions
```bash
# Generate build files
cmake -S . -B build

# Compile the executable
cmake --build build

# Execute the simulation
./build/TacticalShooter
