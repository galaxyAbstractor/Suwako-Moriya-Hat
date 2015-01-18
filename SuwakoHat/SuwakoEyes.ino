uint8_t _eyes[3][8] PROGMEM = {
                        {
                          B00000000, // Regular eye
                          B00000000,
                          B00011000,
                          B00111100,
                          B00111100,
                          B00011000,
                          B00000000,
                          B00000000
                        },
                        {
                          B00000011, // < eye (arrow)
                          B00001100,
                          B00110000,
                          B11000000,
                          B11000000,
                          B00110000,
                          B00001100,
                          B00000011
                        },
                        {
                          B00000000, // < shut eye
                          B00000000,
                          B00000000,
                          B11111111,
                          B11111111,
                          B00000000,
                          B00000000,
                          B00000000
                        }
}; 
                
Adafruit_NeoMatrix* _leftEye; 
Adafruit_NeoMatrix* _rightEye; 

int _offsetX = 0;
int _offsetY = 0;
int _eye;
int _colorMode;
uint16_t _color;

void SuwakoEyes(int leftEyePin, int rightEyePin) {
  _leftEye = new Adafruit_NeoMatrix(8, 8, leftEyePin,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);
    
  _rightEye = new Adafruit_NeoMatrix(8, 8, rightEyePin,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);
  

  _leftEye->begin();
  _leftEye->setBrightness(8); // pls no hurt my eyes while testing ;_;
  _leftEye->show();
  _rightEye->begin();
  _rightEye->setBrightness(8); // pls no hurt my eyes while testing ;_;
  _rightEye->show(); 
}

void clearEyes() {
  _leftEye->clear();
  _rightEye->clear();
}

void drawEye(Adafruit_NeoMatrix* ledMatrix, bool inverted) {
  ledMatrix->clear();
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      byte buffer = pgm_read_byte(&(_eyes[_eye][y]));
      if (inverted) {
        if ((buffer >> 7-x)&1) {
          ledMatrix->drawPixel(y + _offsetY, x + _offsetX, _color);
          ledMatrix->show();
        }
      } else {
        if ((buffer >> x)&1) { 
          ledMatrix->drawPixel((y + _offsetY), (x + _offsetX), _color);
          ledMatrix->show();
        }
      }
    }
  }
}

void animateLookAround() {
  int offsetX = -2 + (rand() % 5);
  int offsetY = -2 + (rand() % 5);
  
  while (_offsetX != offsetX && _offsetY != offsetY) {
    int x = offsetX == _offsetX ? 0 : offsetX < _offsetX ? -1 : 1;
    int y = offsetY == _offsetY ? 0 : offsetY < _offsetY ? -1 : 1;
    
    drawEye(_leftEye, true);
    drawEye(_rightEye, false);

    _offsetX += x;
    _offsetY += y;

    delay(150);
  }
}

void setEye(int eye) {
  _eye = eye;
}

void setColorMode(int mode) {
  _colorMode = mode;
}

void tick() {
  animateLookAround();
}

void setColor(int r, int g, int b) {
  _color = ((uint16_t)(r & 0xF8) << 8) |
         ((uint16_t)(g & 0xFC) << 3) |
                    (b         >> 3);
}
