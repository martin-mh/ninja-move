#include "wall.h"

int Wall::counter = 0;

void Wall::draw()
{
    window->draw(first);
    window->draw(second);
    window->draw(underBlock);
    window->draw(overBlock);
}

Wall::Wall(int leftMargin, int top, sf::RenderWindow *window)
{
    ++counter;
    id = counter;

    this->window = window;

    first.setFillColor(sf::Color::Blue);
    second.setFillColor(sf::Color::Blue);
    underBlock.setFillColor(sf::Color::Blue);
    overBlock.setFillColor(sf::Color::Blue);

    sf::Vector2u windowSize = window->getSize();

    first.setSize(sf::Vector2f(leftMargin, thickness));
    second.setSize(sf::Vector2f(windowSize.x - leftMargin - holeSize, thickness));

    first.setPosition(0, top);
    second.setPosition(leftMargin + holeSize, top);

    underBlock.setSize(sf::Vector2f(40, 40));
    overBlock.setSize(sf::Vector2f(40, 40));

    int min = leftMargin - 49;
    int max = leftMargin + holeSize + 49;

    underBlock.setPosition(randomValue(min, max), top + 130);
    overBlock.setPosition(randomValue(min, max), top - 130);
}

Wall::~Wall()
{

}

