#pragma once

#include "light.h"
#include "constants.h"
#include "utility.h"
#include "effect_ticker.h"

class GyverLamp
{
  private:
    uint8_t cMode = EFF_WHITE_COLOR;

  public:
    GyverLamp();
    ~GyverLamp();

    void ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it);
};

GyverLamp::GyverLamp()
{
}

GyverLamp::~GyverLamp()
{
  FreeLeds();
}

void GyverLamp::ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it)
{
  InitLeds(p_it->size());

  if (cMode != CurrentMode)
  {
    cMode = CurrentMode;
  }
  currentMode = CurrentMode;
  loadingFlag = true;

  effectsTick();

  for (int i = 0; i < p_it->size(); i++)
  {
    (*p_it)[i] = Color(leds[i].r, leds[i].g, leds[i].b);
  }

  #if defined delay
  delay(1);
  #else
  esphome::delay(1);
  #endif
}

class GyverLamp gyver_lamp;
