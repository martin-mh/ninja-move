#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

#include "utils.hpp"

#include <iostream>

class Wall
{
public:
    void draw();

    int id;
    static int counter;

    sf::RectangleShape first;
    sf::RectangleShape second;

    sf::RectangleShape underBlock;
    sf::RectangleShape overBlock;

    Wall(int leftMargin, int top, sf::RenderWindow * window);
    ~Wall();

private:
    sf::RenderWindow * window;

    int thickness = 45;
    int holeSize = 150;
};

#endif // WALL_H
