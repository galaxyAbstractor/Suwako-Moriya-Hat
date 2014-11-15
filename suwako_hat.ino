/*
* @copyright (c) 2014, Victor Nagy (galaxyAbstractor)
* @license BSD - $root/license
*/

#include "LedControl.h" //  need the library
LedControl lc=LedControl(1,13,12,1); 

int eyes[3][8][8] = {
                      {
                        {0, 0, 0, 0, 0, 0, 0, 0}, // Regular eye
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}
                      },
                      {
                        {0, 0, 0, 0, 0, 0, 1, 1}, // < eye (arrow)
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 1, 1, 0, 0, 0, 0},
                        {1, 1, 0, 0, 0, 0, 0, 0},
                        {1, 1, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0, 1, 1}
                      },
                      {
                        {0, 0, 0, 0, 0, 0, 0, 0}, // < shut eye
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}
                      }
                    };
 
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

boolean first_run = true;
int prev_offset_x = 0;
int prev_offset_y = 0;
void draw_eyes(int eye[8][8], int offset_x, int offset_y) {
  if (first_run || (offset_x != prev_offset_x) || offset_y != prev_offset_y) {
    lc.clearDisplay(0);
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (eye[x][y] == 1) {
          lc.setLed(0, x + offset_x, y + offset_y, true);
        }
      }
    }
    prev_offset_x = offset_x;
    prev_offset_y = offset_y;
  }
  first_run = false;
}

void regular_eye(int eye[8][8]) {
  int offset_y = -2 + (rand() % 5);
  int offset_x = -2 + (rand() % 5);
  
  while (prev_offset_x != offset_x && prev_offset_y != offset_y) {
    int x = offset_x == prev_offset_x ? 0 : offset_x < prev_offset_x ? -1 : 1;
    int y = offset_y == prev_offset_y ? 0 : offset_y < prev_offset_y ? -1 : 1;
    
    draw_eyes(eye, prev_offset_x + x, prev_offset_y + y);
    delay(150);
  }
}

void arrow_eye(int eye[8][8]) {
  draw_eyes(eye, 0, 0);
}

void loop()
{
  int select_eye = 1;
  
  switch (select_eye) {
    case 0:
      regular_eye(eyes[0]);
      break;
     case 1:
       draw_eyes(eyes[1], 0, 0);
       break;
     case 2:
        draw_eyes(eyes[2], 0, 0);
       break;
  }
  
  delay(500);
}


