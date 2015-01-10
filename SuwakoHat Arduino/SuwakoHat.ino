#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>


/*
* @copyright (c) 2014, Victor Nagy (galaxyAbstractor)
* @license BSD - $root/license
*/


                
void setup()
{
  SuwakoEyes(5, 6);
  setEye(0);
  setColor(255, 0, 0);
}

void loop()
{
  tick();
  
  delay(500);
}


