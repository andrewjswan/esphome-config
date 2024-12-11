#pragma once

#define FASTLED_INTERNAL // remove annoying pragma messages

#include "FastLED.h"

#define STARS

#ifdef ESP8266
  #define MAX_NUM_SEGMENTS     16
  #define MAX_SEGMENT_DATA   5120

  #define STARBURST_MAX_FRAG    8 // 52 bytes / star
#else
  #define MAX_NUM_SEGMENTS     32
  #define MAX_SEGMENT_DATA  32767

  #define STARBURST_MAX_FRAG   10 // 60 bytes / star
#endif

/* 
  How much data bytes each segment should max allocate to leave enough space for other segments,
  assuming each segment uses the same amount of data. 256 for ESP8266, 640 for ESP32.
*/
#define FAIR_DATA_PER_SEG (MAX_SEGMENT_DATA / MAX_NUM_SEGMENTS)

typedef struct particle {
  CRGB     color;
  uint32_t birth  = 0;
  uint32_t last   = 0;
  float    vel    = 0;
  uint16_t pos    = -1;
  float    fragment[STARBURST_MAX_FRAG];
} star;

star* stars;

int InitStars(int size)
{
  uint16_t maxStars = FAIR_DATA_PER_SEG * 4 / sizeof(star); // ESP8266: max. 4/9/19 stars/seg, ESP32: max. 10/21/42 stars/seg
  uint8_t  numStars = 1 + (size >> 3);
  if (numStars > maxStars)
  {
    numStars = maxStars;
  }

  if (stars == NULL) 
  {
    stars = new star[numStars];
  }
  return numStars;
}

// *****************************************************************************************************************************************************************
void FreeStars()
{
  delete [] stars;
  stars = nullptr;
}
