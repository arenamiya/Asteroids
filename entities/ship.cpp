#ifndef _SHIP_CLASS_
#define _SHIP_CLASS_

#include "bullet.cpp"
#include "particle.cpp"
#include <cmath>
#include <list>

class Ship 
{
    public:
    Ship();
    void move_forward();
    void change_particle_size();
    void shoot_bullet();

    float angle; // angle
    float x, y; // coordinates
    float r, g, b; // fill colors
    float r2, g2, b2; //outline colors
    float speed; // speed
    bool moving;

    float firingRate;
    int maxBullets;

    std::list<Particle> particles;
    std::list<Bullet> bullets;

};

Ship::Ship()
{
    angle = 45;
    x = -0.5; y = -0.5; 
    r = 0.0; g = 1.0; b = 0.0; //player fill color
    r2 = 0; g2 = 1; b2 = 0; //player outline color
    speed = 0.02;
    moving = false;
    firingRate = 0.1;
    maxBullets = 6;
}

/** moves x y coordinates & 
 * adds previous position into the particles list,
 * then deletes the last position from the particles list
**/
void Ship::move_forward() 
{

    Particle p;
    p.x = x;
    p.y = y;
    p.size = 10.0;
    particles.push_back(p);
    if(particles.size() > 5) 
        particles.pop_front();

    x += cos(angle * M_PI / 180) * speed;
    y += sin(angle * M_PI / 180) * speed;
    moving = true;
    
}

void Ship::change_particle_size()
{
    for (std::list<Particle>::iterator p=particles.begin(); p != particles.end(); ++p)
     p->size -= 0.4;
}

void Ship::shoot_bullet()
{
    if(bullets.size() < maxBullets) {
        Bullet b = Bullet(x, y, angle, 0.1);
        bullets.push_front(b);
    }
}

#endif