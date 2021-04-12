#include <OpenGL/gl.h>

struct Ship {
    float angle;
    float x;
    float y;
} ship;

void drawShip(float angle)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
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