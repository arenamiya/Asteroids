#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

# define GL_SILENCE_DEPRECATION

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

#include "entities/ship.cpp"
#include "system/game.cpp"

const int turn_speed = 8;

//keys
void on_key_press(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      moveForward();
      glutPostRedisplay();
      break;
    case 'a':
      ship.angle += turn_speed;
      glutPostRedisplay();
      break;
    case 'd':
      ship.angle -= turn_speed;
      glutPostRedisplay();
      break;
    case 'W':
      moveForward();
      glutPostRedisplay();
      break;
    case 'A':
      ship.angle += turn_speed;
      glutPostRedisplay();
      break;
    case 'D':
      ship.angle -= turn_speed;
      glutPostRedisplay();
      break;
    default:
      break;
  }

  // angle = 360 degrees only
  while (ship.angle < 0) { ship.angle += 360; }
  while (ship.angle > 360) { ship.angle -= 360; }
}

//display func
void on_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  draw_arena(ship.x, ship.y);
  draw_ship();
  
  glutSwapBuffers();
}

//initialise
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
