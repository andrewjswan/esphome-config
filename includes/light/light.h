#include "esphome.h"
#undef delay
#include "FastLED.h"

CRGB* leds;

void InitLeds(int size) 
{
  if (leds == NULL) 
  {
    leds = new CRGB[size];
  }
}