#ifndef _SHIP_CLASS_
#define _SHIP_CLASS_

#include "bullet.cpp"
#include <cmath>
#include <list>

struct Particle
{
    float x;
    float y;
    float size;
};

class Ship 
{
    public:
    Ship();
    ~Ship();
    void moveForward();
    void changeParticleSize();
    void shootBullet();

    float angle; // angle
    float x, y; // coordinates
    float r, g, b; // colors
    float speed; // speed
    bool moving;

    float firingRate;
    int maxBullets;

    std::list<Particle> particles;
    std::list<Bullet> bullets;

};

Ship::Ship()
{
    //default starting ship
    angle = 45;
    x = -0.5; y = -0.5;
    r = 0.0; g = 1.0; b = 0.0;
    speed = 0.08;
    moving = false;
    firingRate = 0.1;
    maxBullets = 10;
}

/** moves x y coordinates & 
 * adds previous position into the particles list,
 * then deletes the last position from the particles list
**/
void Ship::moveForward() 
{

    Particle p;
    p.x = x;
    p.y = y;
    p.size = 10.0;
    particles.push_back(p);
    if(particles.size() > 10) 
        particles.pop_front();

    x += cos(angle * M_PI / 180) * speed;
    y += sin(angle * M_PI / 180) * speed;
    moving = true;
    
}

void Ship::changeParticleSize()
{
    for (std::list<Particle>::iterator p=particles.begin(); p != particles.end(); ++p)
    {
        p->size -= 1.0;
    }
}

void Ship::shootBullet()
{
    if(bullets.size() < maxBullets) {
        Bullet b = Bullet(x, y, angle, 0.1);
        bullets.push_front(b);
    }
}

#endif