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
#include "keyboard.cpp"
#include "entities/ship.cpp"

#define TURN_SPEED 10 //rotation of the ship
#define MAX_SPEED 0.04 //the max speed of the ship (for acceleration)
#define MIN_SPEED 0.01 //the min speed of the ship (for de-acceleration)
#define NEW_WAVE 14000 //the amount of ms it takes for a new round

int wave_round; //the current round of asteroids
int wave_timer = 0; //the current timer set in ms
int score = 0;
int high_score = 0;
bool game_over = true;

Ship* ship;
std::list<Asteroid> asteroids;

void reset_game()
{
  ship = new Ship();
  score = 0;
  wave_round = 1;
  wave_timer = 0;
  asteroids.clear();
  asteroids.push_back(Asteroid(ship));
  game_over = false;
  new_round = false;
  // start_game = false;
}

//true if the objects coordinates are over the border's coordinates
bool hasHitBorder(float x, float y)
{
  float border_width = arena_width - 0.03;
  float border_height = arena_height - 0.03;
  return x > border_width || x < -border_width || y > border_height || y < -border_height;
}

void keys()
{
    if(keystate[0]) { //exit
      return exit(EXIT_SUCCESS);
    }

    if(keystate[1]) { //forward W key
        if(ship->speed < MAX_SPEED) ship->speed += 0.003;
        ship->moveForward();
    } else {
        if(ship->speed >= MIN_SPEED) {
          ship->speed -= 0.005;
          ship->moveForward();
        }
        ship->moving = false;
    }

    if(keystate[2]) { //rotate with A key
        ship->angle += TURN_SPEED;
    } else if(keystate[3]) { //rotate with D key
        ship->angle -= TURN_SPEED;
    }

    if(game_over && new_round) reset_game();

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
  draw_particles(ship);
  draw_ship(ship);
  draw_bullets(ship, 7.0); //ship and bullet size
  draw_text(std::to_string(score), -0.95, 0.9);
  draw_text(std::to_string(wave_timer/1000), 0.9, 0.9);

  if(!start_game) {
    draw_text("Press any key to start...", -0.1, 0);
  } else if (game_over && start_game) {
    draw_text("GAME OVER.", -0.05, 0.01);
    draw_text("Press any key to play again...", -0.1, -0.03);
  }

  for (std::list<Asteroid>::iterator a = asteroids.begin(); a != asteroids.end(); ++a) {
    draw_asteroid(&*a);
  }

  glutSwapBuffers();
}

void timer(int value)
{
  //check keys being pressed & fix ship angle inbetween 0 and 360
  keys();
  while (ship->angle < 0) { ship->angle += 360; }
  while (ship->angle > 360) { ship->angle -= 360; }

  if(hasHitBorder(ship->x, ship->y)) {
    game_over = true;
    new_round = false;
  }

  if(wave_timer % NEW_WAVE == 0) { //wave timer % NEW_WAVE
    for(int i = 0; i < wave_round+1; i++) {
      asteroids.push_back(Asteroid(ship));
    }
    wave_round++;
  }

  float border_bounce;
  for (std::list<Asteroid>::iterator a = asteroids.begin(); a != asteroids.end(); ++a) {
    a->shoot_asteroid();

    if(hasHitBorder(a->x, a->y)) { //check if asteroids hit border
        if(a->passedBorder) a->change_trajectory(); 
    } else if(!a->passedBorder && !hasHitBorder(a->x, a->y)) {
      //erase asteroid if it never goes into the border
      if(!(powf(a->x - 0, 2) + powf(a->y - 0, 2) < powf(2.0, 2))) { 
        asteroids.erase(a);
        break;
      }
      a->passedBorder = true;
    }
  
    if(a->has_collided_with(ship->x, ship->y)) { //check if asteroids collides with ship
      game_over = true;
      new_round = false;
      break;
    }

    for (std::list<Bullet>::iterator b = ship->bullets.begin(); b != ship->bullets.end(); ++b) {   
      if(a->has_collided_with(b->x, b->y)) { //check if the asteroid collides with bullets
        ship->bullets.erase(b);
        if(a->hitPoints > 0) {
          a->hitPoints -= 1;
        } else {
          score += a->points * wave_round;
          std::cout << "\ncurrent score: " << score;
          asteroids.erase(a);
          break;
        }
      } else if (hasHitBorder(b->x, b->y)) { //check if bullets collides with wall
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
  
  glutCreateWindow("Asteroids I3DG A1");
  glutFullScreen();

  glutKeyboardFunc(on_key_press);
  glutKeyboardUpFunc(on_key_up);
  glutMouseFunc(on_mouse_click);

  glutDisplayFunc(on_display);
  glutTimerFunc(100, timer, 0);
  
  glutMainLoop();
  
  return(EXIT_SUCCESS);
}