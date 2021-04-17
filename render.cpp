#ifndef _RENDER_FUNCTIONS_
#define _RENDER_FUNCTIONS_

#include <OpenGL/gl.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "entities/ship.cpp"
#include "entities/asteroid.cpp"

//this file is where all the rendering and drawing goes

float warning_distance = 0.7;
float max_outside_radius = 1.5;

float arena_width = 0.99; //arena width set to 0.99
float arena_height = 0.99; //arena height set to 0.99

void draw_wall(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void draw_arena(float ship_x, float ship_y)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    //left border
    if(ship_x > -warning_distance) glColor3f(0.0, 1.0, 0.0); //green
    else glColor3f(1.0, 0.0, 0.0); //red
    draw_wall(-arena_width, arena_height, -arena_width, -arena_height);

    //right border 
    if(ship_x < warning_distance) glColor3f(0.0, 1.0, 0.0); //green
    else glColor3f(1.0, 0.0, 0.0); //red
    draw_wall(arena_width, -arena_height, arena_width, arena_height);

    // top border
    if(ship_y < warning_distance) glColor3f(0.0, 1.0, 0.0); //green
    else glColor3f(1.0, 0.0, 0.0); //red
    draw_wall(-arena_width, arena_height, arena_width, arena_height);

    // bottom border
    if(ship_y > -warning_distance) glColor3f(0.0, 1.0, 0.0); //green
    else glColor3f(1.0, 0.0, 0.0); //red
    draw_wall(-arena_width, -arena_height, arena_width, -arena_height);

    glPopMatrix();

}

void draw_ship(Ship* ship)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //color, translate, rotate
    glColor3f(ship->r, ship->g, ship->b);
    glTranslatef(ship->x, ship->y, 1.0);
    glRotatef(ship->angle - 90, 0.0, 0.0, 1.0);

    //lines
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.025);
    glVertex2f(0.02, -0.025);
    glVertex2f(0.0, -0.0125);
    glVertex2f(-0.02, -0.025);
    glEnd();

    glColor3f(ship->r2, ship->g2, ship->b2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.025);
    glVertex2f(0.02, -0.025);
    glVertex2f(0.0, -0.0125);
    glVertex2f(-0.02, -0.025);
    glEnd();

    glPopMatrix();

}

void draw_asteroid(Asteroid* asteroid)
{
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(asteroid->r, asteroid->g, asteroid->b);
    glTranslatef(asteroid->x, asteroid->y, 1.0);

    glBegin(GL_LINE_LOOP);

    int angle = 0;
    float x, y;
    for(int i = 0; i < asteroid->edges || angle < 270; i++)
    {
        angle += rand() % 45 + 30;
        x = cos(angle * M_PI / 180) * asteroid->radius;
        y = sin(angle * M_PI / 180) * asteroid->radius;
        glVertex2f(x, y);
    }
    
    glEnd();
    glPopMatrix();
}

void draw_bullets(Ship* ship, float bulletSize)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);

    glPointSize(bulletSize);
    glBegin(GL_POINTS);
    
    for (std::list<Bullet>::iterator b = ship->bullets.begin(); b != ship->bullets.end(); ++b) {   
        b->shootForward(); //bullets move at a forward trajectory
        glVertex2f(b->x, b->y); 
    }
    glEnd();
    glPopMatrix();

}

//int moving defines how many particles are being drawn
void draw_particles(Ship* ship)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(0.3, 0.3, 0.3);

    //loop
    int i = 0;
    for (std::list<Particle>::iterator p = ship->particles.begin(); p != ship->particles.end(); ++p) {
        glPointSize(p->size);
        glBegin(GL_POINTS);
        glVertex2f(p->x, p->y);
        glEnd();
    }

    glPopMatrix();

}

void draw_text(std::string string, float start_x, float y) {

    glRasterPos2f(start_x, y);
    for (int i = 0; i < string.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }

}

#endif