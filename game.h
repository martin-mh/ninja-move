#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "wall.h"
#include "player.h"

class Game
{
public:
    void start();
    void init();

    Game();
    ~Game();

private:
    void gameLoop();

    void computeGameLogic();
    void draw();

    void pollEvents();
    void computeCollisions();

    void checkPlayerPos();
    void checkLastWall();
    void updateBackground();

    void drawWalls();

    sf::RenderWindow window;
    sf::RectangleShape background;

    sf::View view;

    std::vector<Wall> walls;
    Player player;

    const int windowWidth = 500;
    const int windowHeight = 800;
    const int spaceBetweenWalls = 400;
};

#endif // GAME_H
