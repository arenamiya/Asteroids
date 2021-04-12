#include <OpenGL/gl.h>
#include "ship.h"

void Ship::render() {

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glVertex3f(0.f, -0.2f, -0.5f);
    glVertex3f(0.f, 0.6f, -0.5f);

    glVertex3f(0.6f, -0.4f, 0.f);
    glVertex3f(0.f, -0.2f, -0.5f);
    glVertex3f(0.f, 0.6f, -0.5f);

    glEnd();
    
}