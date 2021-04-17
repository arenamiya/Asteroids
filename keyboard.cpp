#ifndef _KEYBOARD_FUNCTIONS_
#define _KEYBOARD_FUNCTIONS_

bool keystate[4];
/**
 * keystate 0 = escape
 * keystate 1 = w / W
 * keystate 2 = a / A
 * keystate 3 = d / D
 * keystate 4 = any other key
 * **/

bool start_game = false;
bool new_round = false;

//keys
void on_key_press(unsigned char key, int x, int y)
{
  if(key == 27) {
    keystate[0] = true;
  } else if(key == 'w' || key == 'W') {
    keystate[1] = true;
  } else if(key == 'a' || key =='A') {
    keystate[2] = true;
  } else if(key == 'd' || key == 'D') {
    keystate[3] = true;
  } 

  start_game = true;
  new_round = true;
  
}

void on_key_up(unsigned char key, int x, int y)
{
  if(key == 'w' || key == 'W') {
    keystate[1] = false;
  } else if(key == 'a' || key =='A') {
    keystate[2] = false;
  } else if(key == 'd' || key == 'D') {
    keystate[3] = false;
  } 
  
}


#endif