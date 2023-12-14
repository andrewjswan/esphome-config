#pragma once

#include "esphome.h"
#undef delay

#include "FastLED.h"
#include "palettes.h"

CRGB* leds;
CRGBPalette16 randomPalette;

uint32_t randomPaletteChange = 0;

CRGB color_from_palette(int index, esphome::Color current_color, uint8_t brightness);
CRGB color_from_palette(int index, CRGB current_color, uint8_t brightness);

void InitLeds(int size) 
{
  if (leds == NULL) 
  {
    leds = new CRGB[size];
  }
}

CRGB color_from_palette(int index, esphome::Color current_color, uint8_t brightness = 255)
{
  CRGB color = CRGB(current_color.r, current_color.g, current_color.b);
  return color_from_palette(index, color, brightness);
}

CRGB color_from_palette(int index, CRGB current_color, uint8_t brightness = 255)
{
  if ((int)id(fastled_palette).state == 0)                                      // Current led color
  {
    return ColorFromPalette(CRGBPalette16(current_color), index, brightness, LINEARBLEND);
  }

  if ((int)id(fastled_palette).state == 1)                                      // Periodically replace palette with a random one
  {
    if (millis() - randomPaletteChange > 1000 + ((uint32_t)(255 - (int)id(fastled_variant).state)) * 100)
    {
      randomPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)),
                                    CHSV(random8(), 255, random8(128, 255)),
                                    CHSV(random8(), 192, random8(128, 255)),
                                    CHSV(random8(), 255, random8(128, 255)));
      randomPaletteChange = millis();
    }
    return ColorFromPalette(randomPalette, index, brightness, LINEARBLEND);
  }

  if ((int)id(fastled_palette).state == 2)
  {
    #ifdef SOUND_REACTIVE                                                       // SOUND_REACTIVE
    return ColorFromPalette(getAudioPalette(0), index, brightness, LINEARBLEND);
    #else
    return ColorFromPalette(paletteArr[random8((int)id(fastled_palette).traits.get_max_value() - 4)], index, brightness, LINEARBLEND);
    #endif
  }

  if ((int)id(fastled_palette).state == 3)
  {
    #ifdef SOUND_REACTIVE                                                       // SOUND_REACTIVE
    return ColorFromPalette(getAudioPalette(1), index, brightness, LINEARBLEND);
    #else
    return ColorFromPalette(paletteArr[random8((int)id(fastled_palette).traits.get_max_value() - 4)], index, brightness, LINEARBLEND);
    #endif
  }

  return ColorFromPalette(paletteArr[(int)id(fastled_palette).state - 4], index, brightness, LINEARBLEND);
}

#ifdef SOUND_REACTIVE                                                           // SOUND_REACTIVE
CRGBPalette16 getAudioPalette(int pal)
{
  // https://forum.makerforums.info/t/hi-is-it-possible-to-define-a-gradient-palette-at-runtime-the-define-gradient-palette-uses-the/63339

  uint8_t xyz[16];                                                              // Needs to be 4 times however many colors are being used.
                                                                                // 3 colors = 12, 4 colors = 16, etc.

  xyz[0] = 0;                                                                   // Anchor of first color - must be zero
  xyz[1] = 0;
  xyz[2] = 0;
  xyz[3] = 0;

  CRGB rgb = getCRGBForBand(1, pal);
  xyz[4] = 1;                                                                   // Anchor of first color
  xyz[5] = rgb.r;
  xyz[6] = rgb.g;
  xyz[7] = rgb.b;

  rgb = getCRGBForBand(128, pal);
  xyz[8] = 128;
  xyz[9] = rgb.r;
  xyz[10] = rgb.g;
  xyz[11] = rgb.b;
  
  rgb = getCRGBForBand(255, pal);
  xyz[12] = 255;                                                                // Anchor of last color - must be 255
  xyz[13] = rgb.r;
  xyz[14] = rgb.g;
  xyz[15] = rgb.b;

  return CRGBPalette16(xyz);
}

CRGB getCRGBForBand(int x, int pal)
{ 
  extern int fftResult[];                                                       // Summary of bins Array. 16 summary bins.

  CRGB value;
  CHSV hsv;

  if(pal == 0) 
  {
    if(x == 1)
    {
      value = CRGB(uint8_t(fftResult[10] / 2), uint8_t(fftResult[4]/2), uint8_t(fftResult[0] / 2));
    }
    else if(x == 255)
    {
      value = CRGB(uint8_t(fftResult[10] / 2), uint8_t(fftResult[0]/2), uint8_t(fftResult[4] / 2));
    } 
    else
    {
      value = CRGB(uint8_t(fftResult[0] / 2), uint8_t(fftResult[4]/2), uint8_t(fftResult[10] / 2));
    } 
  }
  else if(pal == 1)
  {
    int b = map(x, 1, 255, 0, 8);                                                        // Convert palette position to lower half of freq band
    hsv = CHSV(uint8_t(fftResult[b]), 255, uint8_t(map(fftResult[b], 0, 255, 30, 255))); // Pick hue
    hsv2rgb_rainbow(hsv, value);                                                         // Convert to R,G,B
  }
  return value;
}
#endif                                                                          // SOUND_REACTIVE