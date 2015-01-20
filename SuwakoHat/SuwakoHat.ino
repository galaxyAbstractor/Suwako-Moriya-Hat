#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BLE_UART.h>
#include <SPI.h>
#include <avr/pgmspace.h>

/*
* @copyright (c) 2014, Victor Nagy (galaxyAbstractor)
* @license BSD - $root/license
*/

unsigned long prevFrameTime = 0L;

void setup() {
  SuwakoEyes(5, 6);
  setEyes(1);
  setColor(255, 0, 0);
  Bluetooth();
  Serial.begin(9600);
}

void loop() {
  unsigned long t = bluetoothLoop();

  if((t - prevFrameTime) >= (1000L)) {
    tick();
    prevFrameTime = millis();
  }

}


