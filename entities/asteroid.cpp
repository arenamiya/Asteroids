#ifndef _ASTEROID_CLASS_
#define _ASTEROID_CLASS_

#include <stdlib.h>
#include <cmath>
#include <random>
#include <iostream>

int max_asteroid_speed = 5;
int min_asteroid_speed = 1;

float off_arena_radius = 2.0;

class Asteroid 
{

    public:
    Asteroid();
    Asteroid(Asteroid* asteroid);
    void shoot_asteroid();
    void change_trajectory();
    bool has_collided_with(float x, float y, float radius);

    float x, y; //coords
    float r, g, b;
    float speed; //speed
    float radius;
    float trajectory;
    int hitPoints;
    int points;
    int edges;
    bool destroyed;
    bool passedBorder;
    bool split;
    bool justSplit;
    bool hittingWall;
};

Asteroid::Asteroid()
{

    r = 1; g = 1; b = 1;

    speed = rand() % max_asteroid_speed + 1;
    edges = rand() % 5 + 5; //(5-15 edges)

    int n = rand() % 10 + 5; 
    //a random n decides radius, HP and the score points of the asteroid
    radius = float(n) / 100;
    hitPoints = n/4;
    points = hitPoints * 100;

    destroyed = false;
    trajectory = rand() % 360;

    x = cos((trajectory-180) * M_PI / 180) * off_arena_radius;
    y = sin((trajectory-180) * M_PI / 180) * off_arena_radius;

    passedBorder = false;
    split = false;
    justSplit = false;
    hittingWall = false;

}

Asteroid::Asteroid(Asteroid* asteroid)
{
    r = 1; g = 1; b = 1;

    speed = asteroid->speed;
    edges = rand() % 5 + 5;

    radius = asteroid->radius / 2;
    hitPoints = asteroid->hitPoints / 4;
    points = hitPoints * 100;

    destroyed = false;
    trajectory = rand() % 360;

    x = asteroid->x;
    y = asteroid->y;

    passedBorder = true;
    split = true;
    justSplit = true;
    hittingWall = false;

}


void Asteroid::shoot_asteroid()
{
    x += cos(trajectory * M_PI / 180) * speed/100;
    y += sin(trajectory * M_PI / 180) * speed/100;
}

void Asteroid::change_trajectory()
{
    float old_trajectory = trajectory;
    float new_trajectory = rand() % 90 + 90; //90-180 deg
    trajectory += new_trajectory;
}

//check if an asteroid has collided an object that has x,y coordinates and specific radius
bool Asteroid::has_collided_with(float x, float y, float radius)
{
    return powf(x - this->x, 2) + powf(y - this->y, 2) <= powf(radius + this->radius, 2); 
}



#endif