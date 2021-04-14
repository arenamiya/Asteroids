#include <OpenGL/gl.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Ship {
    float angle = 315; //angle
    float x = -0.5, y = -0.5; //coordinates
    float r = 0.0, g = 1.0, b = 0.0; //colors
    float speed = 0.03;
} ship;

void drawShip()
{
    glPushMatrix();
    glColor3f(ship.r, ship.g, ship.b);
    glTranslatef(ship.x, ship.y, 1.0);
    glRotatef(ship.angle - 90, 0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.025);
    glVertex2f(0.02, -0.025);
    glVertex2f(0.0, -0.0125);
    glVertex2f(-0.02, -0.025);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.025);
    glVertex2f(0.02, -0.025);
    glVertex2f(0.0, -0.0125);
    glVertex2f(-0.02, -0.025);

    glEnd();
    glPopMatrix();

}

void moveForward() {
    ship.x += cos(ship.angle * M_PI / 180) * ship.speed;
    ship.y += sin(ship.angle * M_PI / 180) * ship.speed;
}