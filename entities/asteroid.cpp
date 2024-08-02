#ifndef _ASTEROID_CLASS_
#define _ASTEROID_CLASS_

#include <stdlib.h>
#include <cmath>
#include <random>
#include <list>
#include "particle.cpp"

int max_asteroid_speed = 3;
int min_asteroid_speed = 2;

float off_arena_radius = 2.0;

class Asteroid 
{

    public:
    Asteroid();
    Asteroid(Asteroid* asteroid);
    void shoot_asteroid();
    void change_trajectory();
    bool has_collided_with(float x, float y, float radius);
    void generate_particles();
    void shoot_particles();
    void change_particle_size();

    float x, y; //coords
    float r, g, b;
    float speed; //speed
    float radius;
    float trajectory;
    int hitPoints;
    int points;
    int edges;
    bool passedBorder;
    bool split;
    bool hittingWall;
    bool destroyed;
    std::list<Particle> particles;
    float particleSize;

};

Asteroid::Asteroid()
{

    r = 1; g = 1; b = 1;

    speed = rand() % max_asteroid_speed + min_asteroid_speed;
    edges = rand() % 5 + 5; //(5-15 edges)

    int n = rand() % 10 + 5; 
    //a random n decides the radius of the asteroid (between 5-14)
    radius = float(n) / 100;
    hitPoints = n/4;
    points = hitPoints * 100;

    trajectory = rand() % 360;

    x = cos((trajectory-180) * M_PI / 180) * off_arena_radius;
    y = sin((trajectory-180) * M_PI / 180) * off_arena_radius;

    passedBorder = false;
    split = false;
    destroyed = false;
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

    // if(rand() % 2 == 0)  trajectory = asteroid->trajectory + 45;
    // else trajectory = asteroid->trajectory - 45;
    trajectory = rand() % 360;

    x = asteroid->x;
    y = asteroid->y;

    passedBorder = true;
    split = true;
    destroyed = true;
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

//  This command generates a random number of 5-15 particles
//  the particles will start off at a size of 10 and all go in random
//  trajectoryies at random speeds
void Asteroid::generate_particles()
{

    int n = rand() % 10 + 5; //generate n 5-15 particles
    Particle p;

    for(int i = 0; i < n; i++) {
        p.x = x;
        p.y = y;
        p.trajectory = rand() % 360;
        p.speed = (rand() % max_asteroid_speed + min_asteroid_speed)/2;
        p.size = 10;
        particles.push_back(p);
    }

    particleSize = 10;
}

    // This command translates each particle in the
    // particles list of the asteroid by the speed it was given
void Asteroid::shoot_particles()
{
    for (std::list<Particle>::iterator p = particles.begin(); p != particles.end(); ++p) {
        p->x += cos(p->trajectory * M_PI / 180) * p->speed/100;
        p->y += sin(p->trajectory * M_PI / 180) * p->speed/100;
    }
}

    // This command changes the particle size in the particle list of the asteroid
    // by 0.4 until it was erased
void Asteroid::change_particle_size()
{
    particleSize -= 0.4;
    for (std::list<Particle>::iterator p=particles.begin(); p != particles.end(); ++p) {
     p->size -= 0.4;
     if(p->size < 0) p = particles.erase(p);
    }
}
#endif