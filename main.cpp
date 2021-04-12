#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include "ship.h"

#define KEY_ESC 27
int g_screen_width = 0;
int g_screen_height = 0;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


void on_key_press(unsigned char key, int x, int y)
{
  fprintf(stderr, "on_key_press()\n");
  switch (key) {
    case KEY_ESC:
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      //move up
      break;
    case 'a':
      //move left
      break;
    case 's':
      //move right
      break;
    case 'd':
      //move down
      break;
    case 'W':
      //move up
      break;
    case 'A':
      //move left
      break;
    case 'S':
      //move right
      break;
    case 'D':
      //move down
      break;
    default:
      break;
  }
}

void render_ship()
{
    Ship* ship = new Ship();
    ship->render();
}

void on_display()
{
  fprintf(stderr, "on_display()\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  render_ship();
  
  int err;
  while ((err = glGetError()) != GL_NO_ERROR)
    printf("error: %s\n", gluErrorString(err));

  glutSwapBuffers();
}

void on_idle()
{
  glutPostRedisplay();
}

void init_app(int *argcp, char **argv)
{
  glutInit(argcp, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutCreateWindow("Asteroids Game");
  glutFullScreen();
  glutKeyboardFunc(on_key_press);

  glutDisplayFunc(on_display);
  

}

int main(int argc, char **argv) 
{
  init_app(&argc, argv);
  glutMainLoop();
  
  return(EXIT_SUCCESS);
}
