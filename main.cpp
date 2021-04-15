#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <vector>

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

#include <iostream>
#include "render.cpp"
#include "entities/ship.cpp"

const int turn_speed = 8;

Ship* ship;
std::vector<Asteroid*> asteroids;
int num_of_asteroids = 0;

void reset_game()
{
  ship = new Ship();
  
  num_of_asteroids = rand() % 3 + 2; //2-5 asteroids when starting game

  for(int i = 0; i < num_of_asteroids; i++)
  {
    asteroids.push_back(new Asteroid(ship));
  }
}

//keys
void on_key_press(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      ship->moveForward();
      break;
    case 'a':
      ship->angle += turn_speed;
      break;
    case 'd':
      ship->angle -= turn_speed;
      break;
    case 'W':
      ship->moveForward();
      break;
    case 'A':
      ship->angle += turn_speed;
      break;
    case 'D':
      ship->angle -= turn_speed;
      break;
    default:
      break;
  }

  // angle = 360 degrees only
  while (ship->angle < 0) { ship->angle += 360; }
  while (ship->angle > 360) { ship->angle -= 360; }

  float border = 0.98;
  if(ship->x > border || ship->y > border || 
  ship->x < -border || ship->y < -border) 
    reset_game(); 
}

//display func
void on_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  draw_arena(ship->x, ship->y);
  draw_ship(ship);
  
  for(int i = 0; i < num_of_asteroids; i++)
  {
    draw_asteroid(asteroids.at(i));
  }

  glutSwapBuffers();
}

void timer(int value)
{
  for(int i = 0; i < num_of_asteroids; i++)
  {
    asteroids.at(i)->shoot_asteroid();
  }

  on_display();
  glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv) 
{

  reset_game();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  
  glutCreateWindow("Asteroids Game");
  glutFullScreen();


  glutKeyboardFunc(on_key_press);
  glutDisplayFunc(on_display);
  glutTimerFunc(100, timer, 0);
  
  glutMainLoop();
  
  return(EXIT_SUCCESS);
}
