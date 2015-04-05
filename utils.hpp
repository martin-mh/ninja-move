#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <random>

#include <SFML/Graphics.hpp>

#include <iostream>

extern bool Collision(const sf::FloatRect &box1, const sf::FloatRect &box2);
extern int randomValue(const int min, const int max);
extern sf::FloatRect getRectFromView(const sf::View &view);

#endif // COLLISION_HPP

