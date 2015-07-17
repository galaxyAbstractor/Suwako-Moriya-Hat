const uint8_t _eyes[3][6] PROGMEM = {
                        {
                          B00000000, // Regular eye
                          B00001100,
                          B00011110,
                          B00011110,
                          B00001100,
                          B00000000
                        },
                        {
                          B00000011, // < eye (arrow)
                          B00001100,
                          B00110000,
                          B00110000,
                          B00001100,
                          B00000011
                        },
                        {
                          B00000000, // < shut eye
                          B00000000,
                          B11111111,
                          B11111111,
                          B00000000,
                          B00000000
                        }
}; 

Adafruit_NeoMatrix* _leftEye; 
Adafruit_NeoMatrix* _rightEye; 

int8_t _offsetX = 0;
int8_t _offsetY = 0;
uint8_t _leftEyeIndex;
uint8_t _rightEyeIndex;
uint8_t _colorMode;
uint32_t _color;
boolean _randomEyes = false;
boolean _initial = false;

void SuwakoEyes(uint8_t leftEyePin, uint8_t rightEyePin) {
  _leftEye = new Adafruit_NeoMatrix(6, 6, leftEyePin,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);
    
  _rightEye = new Adafruit_NeoMatrix(6, 6, rightEyePin,
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

void drawEye(Adafruit_NeoMatrix* ledMatrix, bool inverted, uint8_t eye) {
  ledMatrix->clear();
  for (uint8_t y = 0; y < 6; y++) {
    byte buffer = pgm_read_byte(&(_eyes[eye][y]));
    for (uint8_t x = 0; x < 6; x++) {
      if (inverted) {
        if ((buffer >> 5-x)&1) {
          ledMatrix->drawPixel(y + _offsetY, x + _offsetX, _color);
        }
      } else {
        if ((buffer >> x)&1) { 
          ledMatrix->drawPixel((y + _offsetY), (x + _offsetX), _color);
        }
      }
    }
  }
  ledMatrix->show();
}

void animateLookAround() {
  int8_t offsetX = -1 + (rand() % 3);
  int8_t offsetY = -1 + (rand() % 3);
  
  while (_offsetX != offsetX && _offsetY != offsetY) {
    int8_t x = offsetX == _offsetX ? 0 : offsetX < _offsetX ? -1 : 1;
    int8_t y = offsetY == _offsetY ? 0 : offsetY < _offsetY ? -1 : 1;
    
    drawEye(_leftEye, true, _leftEyeIndex);
    drawEye(_rightEye, false, _rightEyeIndex);

    _offsetX += x;
    _offsetY += y;

    delay(150);
  }
}

void setEyes(uint8_t eye) {
  setOffsetX(0);
  setOffsetY(0);
  _leftEyeIndex = eye;
  _rightEyeIndex = eye;
}

void setLeftEyeIndex(uint8_t leftEyeIndex) {
  setOffsetX(0);
  setOffsetY(0);
  _leftEyeIndex = leftEyeIndex;
}

void setRightEyeIndex(uint8_t rightEyeIndex) {
  setOffsetX(0);
  setOffsetY(0);
  _rightEyeIndex = rightEyeIndex;
}

void setOffsetX(int8_t offsetX) {
  _offsetX = offsetX;
}

void setOffsetY(int8_t offsetY) {
  _offsetY = offsetY;
}

/*
* 0 = static
* 1 = fade
*/
void setColorMode(uint8_t mode) {
  _colorMode = mode;
}

void setRandomEyes(boolean randomEyes) {
  _randomEyes = randomEyes;
}

unsigned long nextTime = 0L;
unsigned long nextLookaroundTime = 0L;
void doRandom() {
  if ((rand() % 100) >= 95 && millis() > nextTime) {
    uint8_t eye = rand() % 3;
    
    setEyes(eye);
    
    setOffsetX(0);
    setOffsetY(0);
    
    nextTime = millis() + 60000;
  } else { 
    if (_leftEyeIndex == 0 && _rightEyeIndex == 0) {
      if ((rand() % 100) >= 25 && millis() > nextLookaroundTime) {
        animateLookAround();
        nextLookaroundTime = millis() + 5000;
      }
    }
  }
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  _color = _leftEye->Color(r, g, b);
}

void Wheel(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setColor(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    setColor(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    setColor(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

uint8_t _step = 0;
void doFadeColor() {
  Wheel(_step);
  _step += 3;
  if (_step > 256) _step = 0;
}

void tick() {
  if (_randomEyes) {
    doRandom();
  }
  
  if (_colorMode == 1) {
    doFadeColor();
  }
  
  if (!_randomEyes && _leftEyeIndex == 0 _rightEyeIndex == 0) {
    animateLookAround();
  }
  
  drawEye(_leftEye, true, _leftEyeIndex);
  drawEye(_rightEye, false, _rightEyeIndex);
 
}
