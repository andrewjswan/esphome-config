#pragma once

#undef delay

#define FASTLED_INTERNAL // remove annoying pragma messages

#include "FastLED.h"
#include "constants.h"

uint8_t FPSdelay = DYNAMIC;

uint8_t currentMode = 0;
bool loadingFlag = true;

struct ModeType
{
  uint8_t Brightness = 50U;
  uint8_t Speed = 225U;
  uint8_t Scale = 40U;
};

ModeType modes[MODE_AMOUNT];

#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
uint8_t selectedSettings = 0U;
#endif //#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)

// --- For effects ----------------------------------------

uint16_t speed = 20; // speed is set dynamically once we've started up
uint16_t scale = 30; // scale is set dynamically once we've started up

CRGBPalette16 currentPalette(PartyColors_p);