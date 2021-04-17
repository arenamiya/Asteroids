#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <list>

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

const int turn_speed = 18;
const float max_speed = 0.1;
const float min_speed = 0.02;

Ship* ship;
std::list<Asteroid> asteroids;

int wave_round; //the current round of asteroids
float border = 0.98; //border set to 0.98
int new_wave = 8000; //new wave happens every 8000 ms
int wave_timer = 0; //the current timer set in ms
int score = 0;

void reset_game()
{
  ship = new Ship();

  wave_round = 1;
  wave_timer = 0;

  asteroids.clear();
  asteroids.push_back(Asteroid(ship));
}

//true if the objects coordinates are over the border's coordinates
bool hasHitBorder(float x, float y, float border)
{
  return x > border || x < -border || y > border || y < -border;
}


//keys
void on_key_press(unsigned char key, int x, int y)
{
  if(key == 27) {
    exit(EXIT_SUCCESS);
  } else if(key == 'w' || key == 'W') {
    if(ship->speed < max_speed) ship->speed += 0.005;
    ship->moveForward();
    ship->moving = true;
  } else if(key == 'a' || key =='A') {
    ship->angle += turn_speed;
  } else if(key == 'd' || key == 'D') {
    ship->angle -= turn_speed;
  } 
  // angle = 360 degrees only
  while (ship->angle < 0) { ship->angle += 360; }
  while (ship->angle > 360) { ship->angle -= 360; }

  if(hasHitBorder(ship->x, ship->y, border)) 
    reset_game(); 
}

void on_key_up(unsigned char key, int x, int y)
{
  if(key == 'w' || key == 'W') {
    if(ship->speed >= min_speed) {
      ship->speed -= 0.005;
      ship->moveForward();
    }
    ship->moving = false;
  }
}

void on_mouse_click(int button, int state, int x, int y)
{
  switch(button) {
    case GLUT_LEFT_BUTTON:
      ship->shootBullet();
      break;
  }
}

//display func
void on_display()
{
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  draw_arena(ship->x, ship->y);
  draw_ship(ship);
  draw_bullets(ship, 8.0); //ship and bullet size
  draw_particles(ship);
  
  for (std::list<Asteroid>::iterator a = asteroids.begin(); a != asteroids.end(); ++a) {
    draw_asteroid(&*a);
  }

  glutSwapBuffers();
}

void timer(int value)
{
  if(wave_timer % new_wave == 0) { //wave timer % new_wave
    for(int i = 0; i < wave_round+1; i++) {
      asteroids.push_back(Asteroid(ship));
    }
    wave_round++;
  }

  float border_bounce;
  for (std::list<Asteroid>::iterator a = asteroids.begin(); a != asteroids.end(); ++a) {
    a->shoot_asteroid();

    border_bounce = border - a->radius - 0.02;

    if(hasHitBorder(a->x, a->y, border_bounce)) { //if asteroid hits the border
        if(a->passedBorder) a->change_trajectory(); 
    } else if(!a->passedBorder && !hasHitBorder(a->x, a->y, border_bounce)) {
      a->passedBorder = true;
    }

  
    if(a->has_collided_with(ship->x, ship->y)) {
      std::cout << "\ntotal amount scored: " << score;
      reset_game();
      break;
    }

    for (std::list<Bullet>::iterator b = ship->bullets.begin(); b != ship->bullets.end(); ++b) {   
      if(a->has_collided_with(b->x, b->y)) {
        ship->bullets.erase(b);
        if(a->hitPoints > 0) {
          a->hitPoints -= 1;
        } else {
          score += a->points;
          std::cout << "\ncurrent score: " << score;
          asteroids.erase(a);
          break;
        }
      } else if (hasHitBorder(b->x, b->y, border)) {
        ship->bullets.erase(b);
      }
    }
  }

  

  //change particle size every 500 ms
  if(wave_timer % 500) ship->changeParticleSize();
  //remove particles if the ship isn't moving
  if(!ship->moving && ship->particles.size() > 0) ship->particles.pop_front();

  wave_timer += 100; //add 1 ms to wave timer

  glutTimerFunc(100, timer, 0);
  on_display();
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
  glutKeyboardUpFunc(on_key_up);
  glutMouseFunc(on_mouse_click);

  glutDisplayFunc(on_display);
  glutTimerFunc(100, timer, 0);
  
  glutMainLoop();
  
  return(EXIT_SUCCESS);
}
