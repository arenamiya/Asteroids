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

#include "game.cpp"

int g_screen_width = 0;
int g_screen_height = 0;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void on_key_press(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      glutPostRedisplay();
      break;
    case 'a':
      ship.angle += 14;
      glutPostRedisplay();
      break;
    case 'd':
      ship.angle -= 14;
      glutPostRedisplay();
      break;
    case 'W':
      glutPostRedisplay();
      break;
    case 'A':
      ship.angle += 14;
      glutPostRedisplay();
      break;
    case 'D':
      ship.angle -= 14;
      glutPostRedisplay();
      break;
    default:
      break;
  }
}

void render_game()
{
  drawShip(ship.angle);
}

void on_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  render_game();
  
  int err;
  while ((err = glGetError()) != GL_NO_ERROR)
    printf("error: %s\n", gluErrorString(err));

  glutSwapBuffers();
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
