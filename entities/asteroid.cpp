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
    bool has_hit_player(Ship* ship);

    float x, y; //coords
    float speed; //speed
    float radius;
    float trajectory;
    int edges;
    bool destroyed;
    bool passedBorder;
};

Asteroid::Asteroid(Ship* ship)
{


    //asteroids spawn randomly outside of the border, lol fix this
    // if (rand() % 2 != 0)  x = -x;

    // if (rand() % 2 != 0)  y = -y;

    

    speed = rand() % max_speed;
    edges = rand() % 5 + 5; //(5-10 edges)
    radius = float(rand() % 10 + 3) / 100;
    destroyed = false;
    trajectory = rand() % 360;


    x = cos((trajectory-180) * M_PI / 180) * off_arena_radius;
    y = sin((trajectory-180) * M_PI / 180) * off_arena_radius;

    std::cout << " \n spawn: " << x << "," << y;
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
    std::cout << " changed trajectory \n";
}

bool Asteroid::has_hit_player(Ship* ship)
{
    return ship->x > x + radius && ship->y > y + radius && ship->x < x - radius && ship->y < y - radius;
}

#endif