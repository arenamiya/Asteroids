#ifndef _ASTEROID_CLASS_
#define _ASTEROID_CLASS_

#include <stdlib.h>
#include <cmath>
#include <random>
#include <iostream>

int max_speed = 5;

float off_arena_radius = 2.0;

class Asteroid 
{

    public:
    Asteroid(Ship* ship);
    ~Asteroid();
    void shoot_asteroid();
    void change_trajectory();
    bool has_collided_with(float x, float y, float radius);

    float x, y; //coords
    float speed; //speed
    float radius;
    float trajectory;
    int hitPoints;
    int edges;
    bool destroyed;
    bool passedBorder;
};

Asteroid::Asteroid(Ship* ship)
{

    speed = rand() % max_speed;
    edges = rand() % 5 + 5; //(5-10 edges)
    int n = rand() % 10 + 3;
    radius = float(n) / 100;
    hitPoints = n/3;
    destroyed = false;
    trajectory = rand() % 360;

    x = cos((trajectory-180) * M_PI / 180) * off_arena_radius;
    y = sin((trajectory-180) * M_PI / 180) * off_arena_radius;

    passedBorder = false;

}

Asteroid::~Asteroid()
{

}

void Asteroid::shoot_asteroid()
{
    x += cos(trajectory * M_PI / 180) * speed/100;
    y += sin(trajectory * M_PI / 180) * speed/100;
}

void Asteroid::change_trajectory()
{
    float old_trajectory = trajectory;
    float new_trajectory = rand() % 70 + 100; //100-170
    
    trajectory += new_trajectory;
}

//check if an asteroid has collided with an object that has x,y coordinates and specific radius
bool Asteroid::has_collided_with(float x, float y, float radius)
{
    return powf(x - this->x, 2) + powf(y - this->y, 2) < powf(this->radius, 2);
}

#endif