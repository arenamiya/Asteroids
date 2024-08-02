
#ifndef _BULLET_CLASS_
#define _BULLET_CLASS_

#include <cmath>

class Bullet
{
    public:
    Bullet(float x, float y, float angle, float speed);
    void shootForward();

    float angle;
    float x, y;
    float speed;

};


Bullet::Bullet(float x, float y, float angle, float speed)
{
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->speed = speed;
}

void Bullet::shootForward()
{
    x += cos(angle * M_PI / 180) * speed;
    y += sin(angle * M_PI / 180) * speed;
}



#endif