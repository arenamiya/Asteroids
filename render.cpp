#include <OpenGL/gl.h>
#include <stdlib.h>
#include "entities/ship.cpp"
#include "entities/asteroid.cpp"

#include <iostream>

float warning_distance = 0.7;

float max_outside_radius = 1.5;

void draw_arena(float ship_x, float ship_y)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    //left border
    glBegin(GL_LINES); 
    if(ship_x > -warning_distance) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(-0.99, 0.99);
    glVertex2f(-0.99, -0.99);
    glEnd();

    //right border
    glBegin(GL_LINES); 
    if(ship_x < 0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(0.99, -0.99);
    glVertex2f(0.99, 0.99);
    glEnd();

    // top border
    glBegin(GL_LINES); 
    if(ship_y < 0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(-0.99, 0.99);
    glVertex2f(0.99, 0.99);
    glEnd();

    // bottom border
    glBegin(GL_LINES); 
    if(ship_y > -0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(-0.99, -0.99);
    glVertex2f(0.99, -0.99);
    glEnd();

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

    glPopMatrix();

}

void draw_asteroid(Asteroid* asteroid)
{
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
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
        b->shootForward();
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

    glColor3f(1.0, 1.0, 1.0);

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