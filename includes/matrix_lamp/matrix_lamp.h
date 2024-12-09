#pragma once

#include "light.h"
#include "constants.h"
#include "utility.h"
#include "effect_ticker.h"

class MatrixLamp
{
  public:
    MatrixLamp();
    ~MatrixLamp();

    void ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it);
};

MatrixLamp::MatrixLamp()
{
  memset(matrixValue, 0, sizeof(matrixValue)); // это массив для эффекта Огонь. странно, что его нужно залить нулями
}

MatrixLamp::~MatrixLamp()
{
  FreeLeds();
}

void MatrixLamp::ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it)
{
  InitLeds(p_it->size());

  if (currentMode != CurrentMode)
  {
    loadingFlag = true;
    selectedSettings = 1U;
  }
  currentMode = CurrentMode;

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

class MatrixLamp matrix_lamp;
