#ifndef _SHIP_CLASS_
#define _SHIP_CLASS_

#include <cmath>

class Ship 
{
    public:
    Ship();
    ~Ship();
    void moveForward();

    float angle; // angle
    float x, y; // coordinates
    float r, g, b; // colors
    float speed; // speed

};

Ship::Ship()
{
    //default starting ship
    angle = 45;
    x = -0.5; y = -0.5;
    r = 0.0; g = 1.0; b = 0.0;
    speed = 0.05;
}

void Ship::moveForward() 
{
    x += cos(angle * M_PI / 180) * speed;
    y += sin(angle * M_PI / 180) * speed;
}

#endif