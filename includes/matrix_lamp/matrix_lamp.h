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
    bool GetRandomSettings();
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
bool MatrixLamp::GetRandomSettings()
{
  return random_settings;
}

void MatrixLamp::SetRandomSettings(bool b)
{
  if (!b)
  {
    restoreSettings();
  }

  loadingFlag = true;

  random_settings = b;
  selectedSettings = b;
}
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)

void MatrixLamp::ShowFrame(uint8_t CurrentMode, esphome::Color current_color, light::AddressableLight *p_it)
{
  InitLeds(p_it->size());

  if (currentMode != CurrentMode)
  {
    currentMode = CurrentMode;
    loadingFlag = true;
#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    selectedSettings = random_settings;
    if (!random_settings)
#endif // #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
    {
      auto speed = id(fastled_speed).make_call();
      speed.set_value(modes[currentMode].Speed);
      speed.perform();
      auto scale = id(fastled_variant).make_call();
      scale.set_value(modes[currentMode].Scale);
      scale.perform();
    }
  }

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

  if (modes[currentMode].Speed != (int)id(fastled_speed).state)
  {
    modes[currentMode].Speed = (int)id(fastled_speed).state;
    loadingFlag = true; // без перезапуска эффекта ничего и не увидишь
  }
  if (modes[currentMode].Scale != (int)id(fastled_variant).state)
  {
    modes[currentMode].Scale = (int)id(fastled_variant).state;
    loadingFlag = true; // без перезапуска эффекта ничего и не увидишь
  }
}

class MatrixLamp matrix_lamp;
