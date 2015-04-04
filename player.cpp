#include "player.h"

void Player::update()
{
    if(!running)
        return;

    if(direction == 0)
    {
        move(-v_x, v_y);
    }
    else
    {
        move(v_x, v_y);
    }

    v_y += v_grav;


}

void Player::left()
{
    running = true;

    direction = 0;

    v_y = v_saut;
}

void Player::right()
{
    running = true;

    direction = 1;

    v_y = v_saut;
}

Player::Player() : sf::CircleShape(25,4)
{
    running = false;

    setFillColor(sf::Color::Red);
}

Player::~Player()
{

}

