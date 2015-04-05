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
    bool init();

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
    void updateScoreText();

    void drawWalls();

    void lost();

    sf::RenderWindow window;
    sf::RectangleShape background;

    sf::View view;

    std::vector<Wall> walls;
    Player player;

    sf::Font font;
    sf::Text scoreText;

    unsigned int score;
    int scoredWall; //Id of the scored wall. If 0 -> no scored

    const static int windowWidth = 500;
    const static int windowHeight = 800;
    const static int spaceBetweenWalls = 420;
};

#endif // GAME_H
