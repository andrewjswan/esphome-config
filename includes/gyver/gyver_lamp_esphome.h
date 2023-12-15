#pragma once

class GyverLamp
{
  private:
    uint8_t CurrentMode = EFF_LAVALAMP;

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
