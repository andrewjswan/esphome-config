#pragma once

#define FASTLED_INTERNAL // remove annoying pragma messages
#define USE_GET_MILLISECOND_TIMER
#define FASTLED_OVERCLOCK 1.2

#include "esphome.h"
#undef delay

#include "FastLED.h"

// *****************************************************************************************************************************************************************
CRGB* leds;

// *****************************************************************************************************************************************************************
void InitLeds(int size)
{
  if (leds == NULL) 
  {
    leds = new CRGB[size];
  }
}

// *****************************************************************************************************************************************************************
void FreeLeds()
{
  delete [] leds;
  leds = nullptr;
}
