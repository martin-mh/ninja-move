#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall
{
public:
    void draw();

    sf::RectangleShape first;
    sf::RectangleShape second;

    Wall(int leftMargin, int top, sf::RenderWindow * window);
    ~Wall();

private:
    sf::RenderWindow * window;

    int thickness = 45;
    int holeSize = 150;
};

#endif // WALL_H
