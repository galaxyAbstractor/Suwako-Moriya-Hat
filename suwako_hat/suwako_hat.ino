/*
* @copyright (c) 2014, Victor Nagy (galaxyAbstractor)
* @license BSD - $root/license
*/
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 6,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);

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
                    
uint32_t magenta = matrix.Color(255, 0, 255);
 
void setup()
{
  matrix.begin();
  matrix.setBrightness(8); // pls no hurt my eyes while testing ;_;
  matrix.show(); // Initialize all pixels to 'off'
}

boolean first_run = true;
int prev_offset_x = 0;
int prev_offset_y = 0;
void draw_eyes(int eye[8][8], int offset_x, int offset_y) {
  if (first_run || (offset_x != prev_offset_x) || offset_y != prev_offset_y) {
    matrix.clear();
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (eye[x][y] == 1) {
          matrix.drawPixel(x + offset_x, y + offset_y, magenta);
          matrix.show();
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
  int select_eye = 0;
  
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


