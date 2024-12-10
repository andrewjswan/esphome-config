#pragma once

#include "light.h"
#include "constants.h"
#include "utility.h"
#include "effect_ticker.h"

class MatrixLamp
{
#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
  protected:
    bool random_settings = false;
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)

  public:
    MatrixLamp();
    ~MatrixLamp();

#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    void SetRandomSettings(bool b=false);
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    void ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it);
};

MatrixLamp::MatrixLamp()
{
  memset(matrixValue, 0, sizeof(matrixValue)); // это массив для эффекта Огонь. странно, что его нужно залить нулями
  restoreSettings();
}

MatrixLamp::~MatrixLamp()
{
  FreeLeds();
}

#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
void MatrixLamp::SetRandomSettings(bool b)
{
  random_settings = b;
  selectedSettings = b;
}
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)

void MatrixLamp::ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it)
{
  InitLeds(p_it->size());

  if (currentMode != CurrentMode)
  {
    loadingFlag = true;
#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    selectedSettings = random_settings;
    if (random_settings)
    {
      float br = (float)modes[CurrentMode].Brightness / (float)255;
      id(neopixel_led).turn_on().set_brightness(br).perform();
    }
    else
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    {
      id(fastled_speed).state == modes[CurrentMode].Speed;
      id(fastled_variant).state == modes[CurrentMode].Scale;
    }
  }
  currentMode = CurrentMode;

  effectsTick();

  modes[CurrentMode].Speed = id(fastled_speed).state;
  modes[CurrentMode].Scale = id(fastled_variant).state;

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
