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

int wave_round; //the current round of asteroids
float border = 0.98; //border set to 0.98
int new_wave = 8000; //new wave happens every 8000 ms
int wave_timer = 0; //the current timer set in ms


void reset_game()
{
  ship = new Ship();

  wave_round = 1;
  wave_timer = 0;

  asteroids.clear();

  asteroids.push_back(new Asteroid(ship));

}

//true if the objects coordinates are over the border's coordinates
bool hasHitBorder(float x, float y, float border)
{
  return x > border || x < -border || y > border || y < -border;
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

  if(hasHitBorder(ship->x, ship->y, border)) 
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
  
  for(int i = 0; i < asteroids.size(); i++)
  {
    draw_asteroid(asteroids.at(i));
  }

  glutSwapBuffers();
}

void timer(int value)
{

  if(wave_timer % new_wave == 0) { //wave timer % new_wave
    for(int i = 0; i < wave_round+1; i++) {
      asteroids.push_back(new Asteroid(ship));
    }
    wave_round++;
  }

  float border_bounce;
  for(int i = 0; i < asteroids.size(); i++)
  {
    Asteroid* a = asteroids.at(i);
    a->shoot_asteroid();

    border_bounce = border - a->radius - 0.02;

    if(hasHitBorder(a->x, a->y, border_bounce)) {
        if(a->passedBorder) {
          a->change_trajectory(); 
        }
    } else if(!a->passedBorder && !hasHitBorder(a->x, a->y, border_bounce)) {
      a->passedBorder = true;
    }

    if(a->has_collided_with(ship->x, ship->y, ship->speed)) {
      reset_game();
    }

  }

  wave_timer += 100; //add 1 ms to wave timer

  on_display();
  glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv) 
{

  srand(time(NULL));
  reset_game();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutCreateWindow("Asteroids");
  glutFullScreen();

  glutKeyboardFunc(on_key_press);
  glutDisplayFunc(on_display);
  glutTimerFunc(100, timer, 0);
  
  glutMainLoop();
  
  return(EXIT_SUCCESS);
}
