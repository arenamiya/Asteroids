#include <OpenGL/gl.h>


void draw_arena(float ship_x, float ship_y)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    

    glBegin(GL_LINES); //left border

    if(ship_x > -0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(-0.99, 0.99);
    glVertex2f(-0.99, -0.99);

    glEnd();

    glBegin(GL_LINES); //right border

    if(ship_x < 0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(0.99, -0.99);
    glVertex2f(0.99, 0.99);

    glEnd();

    glBegin(GL_LINES); // top border

    if(ship_y < 0.7) {
        glColor3f(0.0, 1.0, 0.0); //green
    } else { 
        glColor3f(1.0, 0.0, 0.0); //red
    }
    glVertex2f(-0.99, 0.99);
    glVertex2f(0.99, 0.99);

    glEnd();

    glBegin(GL_LINES); // bottom border

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
