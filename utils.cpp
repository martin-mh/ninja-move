#include "utils.hpp"

bool Collision(const sf::FloatRect &box1, const sf::FloatRect &box2)
{
    if(    (box2.left >= box1.left + box1.width)
       ||  (box2.left + box2.width <= box1.left)
       ||  (box2.top >= box1.top + box1.height)
       ||  (box2.top + box2.height <= box1.top))
        return false;

    return true;
}


int randomValue(const int min, const int max)
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(min, max);

    return distr(generator);
}


sf::FloatRect getRectFromView(const sf::View &view)
{
    sf::FloatRect rect;
    rect.width = view.getSize().x;
    rect.height = view.getSize().y;
    rect.left = view.getCenter().x - view.getSize().x / 2;
    rect.top = view.getCenter().y - view.getSize().y / 2;

    return rect;
}
