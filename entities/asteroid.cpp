#ifndef _ASTEROID_CLASS_
#define _ASTEROID_CLASS_

#include <stdlib.h>
#include <cmath>
#include <random>
#include <iostream>

int max_speed = 30;

class Asteroid 
{

    public:
    Asteroid(Ship* ship);
    ~Asteroid();
    void shoot_asteroid();
    void change_trajectory();

    float x, y; //coords
    float speed; //speed
    float radius;
    float trajectory;
    int edges;
    bool destroyed;
};

Asteroid::Asteroid(Ship* ship)
{

    float spawn_min = 0, spawn_max = 0.8;

    float x_spawn = (float)(rand()) / ((float)(RAND_MAX/(spawn_min - spawn_max)));
    float y_spawn = (float)(rand()) / ((float)(RAND_MAX/(spawn_min - spawn_max)));

    //asteroids spawn randomly outside of the border, lol fix this
    if (rand() % 2 != 0) {
        x = -(1 + x_spawn);
    } else {
        x = 1 + x_spawn;
    } 

    if (rand() % 2 != 0) {
        y = -(1 + y_spawn);
    } else {
        y = 1 + y_spawn;
    }

    speed = rand() % max_speed;
    edges = rand() % 5 + 5; //(5-10 edges)
    radius = float(rand() % 10 + 1) / 100;
    destroyed = false;

    trajectory = rand() % 360;


}

Asteroid::~Asteroid()
{

}

void Asteroid::shoot_asteroid()
{
    
    x += cos(trajectory * M_PI / 180) * speed/100 + 0.01;
    y += sin(trajectory * M_PI / 180) * speed/100 + 0.01;
    std::cout << trajectory << " : " << speed/100 << std::endl;
}

void Asteroid::change_trajectory()
{
    
}


#endif