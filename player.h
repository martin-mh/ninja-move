#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::CircleShape
{
public:
    void left();
    void right();
    void update();

    bool running;

    Player();
    ~Player();

private:
    int direction; //0 -> left 1 -> right

    double v_grav = 0.28;
    double v_saut = -7.5;
    double v_x = 1.7;
    double v_y = v_saut;

};

#endif // PLAYER_H
