#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::CircleShape
{
public:
    void left();
    void right();
    void update();

    Player();
    ~Player();

private:
    bool running;
    int direction; //0 -> left 1 -> right

    double v_grav = 0.18;
    double v_saut = -6;
    double v_x = 1.5;
    double v_y = v_saut;

};

#endif // PLAYER_H
