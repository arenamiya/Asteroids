#include <OpenGL/gl.h>

struct Ship {
    float angle; //angle
    float x = -0.5, y = -0.5; //coordinates
    float r = 1.0, g = 1.0, b = 1.0; //colors
} ship;

void drawShip()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glColor3f(ship.r, ship.g, ship.b);
    //glRotatef(ship.angle, ship.x, ship.y, 1.0);
    glTranslatef(ship.x, ship.y, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.05);
    glVertex2f(0.04, -0.05);
    glVertex2f(0.0, -0.025);
    glVertex2f(-0.04, -0.05);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.05);
    glVertex2f(0.04, -0.05);
    glVertex2f(0.0, -0.025);
    glVertex2f(-0.04, -0.05);
    glEnd();
    glPopMatrix();
}

void moveForward()
{

}