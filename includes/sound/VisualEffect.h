#pragma once

#define FASTLED_INTERNAL // remove annoying pragma messages

#include <FastLED.h>

#include "light.h"
#include "audio_reactive.h"

class VisualEffect
{
  private:
    uint16_t _leds_num;

    int topLED = 0;
    int gravityCounter = 0;

  public:
    CRGB main_color; // SEGCOLOR(0) - First Color in WLED
    CRGB back_color; // SEGCOLOR(1) - Second Color in WLED (Background)

    VisualEffect(uint16_t leds_num);

    void visualize_gravfreq(CRGB * physic_leds);
    void visualize_gravcenter(CRGB * physic_leds);
    void visualize_gravcentric(CRGB * physic_leds);
    void visualize_binmap(CRGB * physic_leds);
    void visualize_pixels(CRGB * physic_leds);
    void visualize_juggles(CRGB * physic_leds);
    void visualize_midnoise(CRGB * physic_leds);

    ~VisualEffect();
};

VisualEffect::VisualEffect(uint16_t leds_num)
{
  CRGB main_color = CRGB::White;
  CRGB back_color = CRGB::Black;

  _leds_num = leds_num;
}

VisualEffect::~VisualEffect()
{
}

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_gravfreq(CRGB * physic_leds)                       // Gravfreq. By Andrew Tuline.
{
  fade_out(physic_leds, _leds_num, 240, back_color);
  
  float tmpSound = (soundAgc) ? sampleAgc : sampleAvg;
  float segmentSampleAvg = tmpSound * (float)id(fastled_variant).state / 255.0;
  segmentSampleAvg *= 0.125; // divide by 8,  to compensate for later "sensitivty" upscaling

  float mySampleAvg = mapf(segmentSampleAvg * 2.0, 0, 32, 0, (float)_leds_num / 2.0); // Map to pixels availeable in current segment
  int tempsamp = constrain(mySampleAvg , 0, _leds_num / 2);                            // Keep the sample from overflowing.
  uint8_t gravity = 8 - (int)id(fastled_speed).state / 32;

  for (int i = 0; i < tempsamp; i++)
  {
    int index = (log10f(FFT_MajorPeak) - (3.71 - 1.78)) * 255;
    if (index < 0) index = 0;
    index = scale8(index, 240); // Cut off blend at palette "end"
    
    physic_leds[i + _leds_num / 2] = color_from_palette(index, main_color);
    physic_leds[_leds_num / 2 - i - 1] = color_from_palette(index, main_color);
  }

  if (tempsamp >= topLED)
  {
    topLED = tempsamp - 1;
  }
  else if (gravityCounter % gravity == 0)
  {
    topLED--;
  }

  if (topLED >= 0)
  {
    physic_leds[topLED + _leds_num / 2]     = CRGB::Gray;
    physic_leds[_leds_num / 2 - 1 - topLED] = CRGB::Gray;
  }
  gravityCounter = (gravityCounter + 1) % gravity;
} // visualize_gravfreq

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_gravcenter(CRGB * physic_leds)                     // Gravcenter. By Andrew Tuline.
{
  fade_out(physic_leds, _leds_num, 240, back_color);

  float tmpSound = (soundAgc) ? sampleAgc : sampleAvg;
  float segmentSampleAvg = tmpSound * (float)id(fastled_variant).state / 255.0;
  segmentSampleAvg *= 0.125;                                                           // divide by 8, to compensate for later "sensitivty" upscaling

  float mySampleAvg = mapd(segmentSampleAvg * 2.0, 0, 32, 0, (float)_leds_num / 2.0);  // map to pixels availeable in current segment
  int tempsamp = constrain(mySampleAvg, 0, _leds_num / 2);                             // Keep the sample from overflowing.
  uint8_t gravity = 8 - id(fastled_speed).state / 32;

  for (int i=0; i<tempsamp; i++)
  {
    uint8_t index = inoise8(i * segmentSampleAvg + millis(), 5000 + i * segmentSampleAvg);
    physic_leds[i + _leds_num / 2] = color_blend(back_color, color_from_palette(index, main_color), segmentSampleAvg * 8);
    physic_leds[_leds_num / 2 - i - 1] = color_blend(back_color, color_from_palette(index, main_color), segmentSampleAvg * 8);
  }

  if (tempsamp >= topLED)
    topLED = tempsamp - 1;
  else if (gravityCounter % gravity == 0)
    topLED--;

  if (topLED >= 0)
  {
    physic_leds[topLED + _leds_num / 2]     = color_from_palette(millis(), main_color);
    physic_leds[_leds_num / 2 - 1 - topLED] = color_from_palette(millis(), main_color);
  }
  gravityCounter = (gravityCounter + 1) % gravity;
} // visualize_gravcenter()

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_gravcentric(CRGB * physic_leds)                    // Gravcentric. By Andrew Tuline.
{
  fade_out(physic_leds, _leds_num, 226, back_color);

  float tmpSound = (soundAgc) ? sampleAgc : sampleAvg;
  float segmentSampleAvg = tmpSound * (float)id(fastled_variant).state / 255.0;
  segmentSampleAvg *= 0.125;                                                          // divide by 8, to compensate for later "sensitivty" upscaling

  float mySampleAvg = mapd(segmentSampleAvg * 2.0, 0, 32, 0, (float)_leds_num / 2.0); // map to pixels availeable in current segment
  int tempsamp = constrain(mySampleAvg, 0, _leds_num / 2);                            // Keep the sample from overflowing.
  uint8_t gravity = 8 - id(fastled_speed).state / 32;

  for (int i = 0; i < tempsamp; i++)
  {
    uint8_t index = segmentSampleAvg*24 + millis() / 200;
    physic_leds[i + _leds_num/2]       = color_from_palette(index, main_color);
    physic_leds[_leds_num / 2 - 1 - i] = color_from_palette(index, main_color);
  }

  if (tempsamp >= topLED)
    topLED = tempsamp-1;
  else if (gravityCounter % gravity == 0)
    topLED--;

  if (topLED >= 0)
  {
    physic_leds[topLED + _leds_num / 2]     = CRGB::Gray;
    physic_leds[_leds_num / 2 - 1 - topLED] = CRGB::Gray;
  }
  gravityCounter = (gravityCounter + 1) % gravity;
} // visualize_gravcentric

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_binmap(CRGB * physic_leds)                         // Binmap. Scale raw fftBin[] values to SEGLEN. Shows just how noisy those bins are.
{
  #define FIRSTBIN 3                            // The first 3 bins are garbage.
  #define LASTBIN 255                           // Don't use the highest bins, as they're (almost) a mirror of the first 256.

  float maxVal = 512;                           // Kind of a guess as to the maximum output value per combined logarithmic bins.

  float binScale = (((float)sampleGain / 40.0) + 1.0/16) * ((float)id(fastled_variant).state / 128.0);  // non-AGC gain multiplier
  if (soundAgc) binScale = multAgc;                                                                     // AGC gain
  if (sampleAvg < 1) binScale = 0.001;                                                                  // silentium!

  for (int i = 0; i < _leds_num; i++)
  {
    uint16_t startBin = FIRSTBIN + i * (LASTBIN - FIRSTBIN) / _leds_num;        // This is the START bin for this particular pixel.
    uint16_t   endBin = FIRSTBIN + (i + 1) * (LASTBIN - FIRSTBIN) / _leds_num;  // This is the END bin for this particular pixel.
    if (endBin > startBin) endBin --;                                           // avoid overlapping

    float sumBin = 0;

    for (int j = startBin; j <= endBin; j++)
    {
      sumBin += (fftBin[j] < soundSquelch * 1.75) ? 0 : fftBin[j];  // We need some sound temporary squelch for fftBin, because we didn't do it for the raw bins in audio_reactive.h
    }

    sumBin = sumBin / (endBin - startBin + 1);            // Normalize it.
    sumBin = sumBin * (i + 5) / (endBin - startBin + 5);  // Disgusting frequency adjustment calculation. Lows were too bright. Am open to quick 'n dirty alternatives.

    sumBin = sumBin * 8;                                  // Need to use the 'log' version for this. Why " * 8" ??
    sumBin *= binScale;                                   // apply gain

    if (sumBin > maxVal) sumBin = maxVal;                 // Make sure our bin isn't higher than the max . . which we capped earlier.

    uint8_t bright = constrain(mapf(sumBin, 0, maxVal, 0, 255), 0, 255);                                    // Map the brightness in relation to maxVal and crunch to 8 bits.
    physic_leds[i] = color_blend(back_color, color_from_palette(i * 8 + millis() / 50, main_color), bright); // 'i' is just an index in the palette. The FFT value, bright, is the intensity.
  } // for i
} // visualize_binmap

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_pixels(CRGB * physic_leds)                         // Pixels. By Andrew Tuline.
{
  fade_out(physic_leds, _leds_num, (int)id(fastled_speed).state, back_color);

  for (int i = 0; i < (int)id(fastled_variant).state / 16; i++)
  {
    uint16_t segLoc = random(_leds_num); // 16 bit for larger strands of LED's.
    physic_leds[segLoc] = color_blend(back_color, color_from_palette(myVals[i % 32] + i * 4, main_color), sampleAgc);
  }
} // visualize_pixels()

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_juggles(CRGB * physic_leds)                        // Juggles. By Andrew Tuline.
{
  fade_out(physic_leds, _leds_num, 224, back_color);

  int my_sampleAgc = fmax(fmin(sampleAgc, 255.0), 0);

  for (int i = 0; i < (int)id(fastled_variant).state / 32 + 1; i++)
  {
    physic_leds[beatsin16((int)id(fastled_speed).state / 4 + i * 2, 0, _leds_num - 1)] = color_blend(back_color, color_from_palette(millis() / 4 + i * 2, main_color), my_sampleAgc);
  }
} // visualize_juggles()

// *****************************************************************************************************************************************************************
void VisualEffect::visualize_midnoise(CRGB * physic_leds)                       // Midnoise. By Andrew Tuline.
{
  static int x = 0;
  static int y = 0;

  fade_out(physic_leds, _leds_num, (int)id(fastled_speed).state * (int)id(fastled_speed).state / 255, back_color); // Same as two fade-out runs

  float tmpSound = (soundAgc) ? sampleAgc : sampleAvg;
  float tmpSound2 = tmpSound * (float)id(fastled_variant).state / 256.0;        // Too sensitive.
  tmpSound2 *= (float)id(fastled_variant).state / 128.0;                        // Reduce sensitity/length.

  int maxLen = mapd(tmpSound2, 0, 127, 0, _leds_num / 2);
  if (maxLen > _leds_num / 2) maxLen = _leds_num / 2;

  for (int i = (_leds_num / 2 - maxLen); i < (_leds_num / 2 + maxLen); i++)
  {
    uint8_t index = inoise8(i * tmpSound + x, y + i * tmpSound);  // Get a value from the noise function. I'm using both x and y axis.
    physic_leds[i] = color_from_palette(index, main_color);
  }

  x = x + beatsin8(5,0,10);
  y = y + beatsin8(4,0,10);
} // visualize_midnoise()
