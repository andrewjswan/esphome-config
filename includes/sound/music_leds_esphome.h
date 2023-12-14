#include "esphome.h"
using namespace esphome;

#include "VisualEffect.h"
#include "audio_reactive.h"

enum PLAYMODE
{
  MODE_BINMAP,
  MODE_GRAV,
  MODE_GRAVICENTER,
  MODE_GRAVICENTRIC,
  MODE_PIXELS,
  MODE_JUNGLES,
  MODE_MIDNOISE
};

class MusicLeds
{
  private:
    class VisualEffect * effect;

    PLAYMODE CurrentMode = MODE_GRAV;

  public:
    MusicLeds();
    ~MusicLeds();

    void ShowFrame(PLAYMODE CurrentMode, esphome::Color current_color, light::AddressableLight *p_it);
};

MusicLeds::MusicLeds()
{
  disableSoundProcessing = true;           // Just to be safe
  
  i2s_driver_uninstall(I2S_NUM_0);         // Reset I2S peripheral for good measure
  #if defined delay
  delay(100);                              // Give this peripheral time to disable to avoid an indeterminate state.
  #else
  esphome::delay(100);
  #endif

  periph_module_reset(PERIPH_I2S0_MODULE);
  #if defined delay
  delay(100);                              // Give that poor microphone some time to setup.
  #else
  esphome::delay(100);
  #endif

  useInputFilter = 3;                      // Apply 60Hz Low-Cut filter
  
  audioSource = new I2SSource(SAMPLE_RATE, BLOCK_SIZE, 0, 0xFFFFFFFF);
  #if defined delay
  delay(100);
  #else
  esphome::delay(100);
  #endif

  audioSource->initialize();
  #if defined delay
  delay(250);
  #else
  esphome::delay(250);
  #endif

  if(!audioSource->isInitialized())
  {
    ESP_LOGE("ASR", "ML: Failed to initialize sound input driver. Please check input PIN settings.");
  }

  // Define the FFT Task and lock it to core 0
  xTaskCreatePinnedToCore(
        FFTcode,                          // Function to implement the task
        "FFT",                            // Name of the task
        5000,                             // Stack size in words
        NULL,                             // Task input parameter
        1,                                // Priority of the task
        &FFT_Task,                        // Task handle
        1);                               // Core where the task should run

  if(audioSource->isInitialized())
  {
    disableSoundProcessing = false;       // Let it run
  }
}

MusicLeds::~MusicLeds()
{
  disableSoundProcessing = true;           // Just to be safe

  vTaskDelete(FFT_Task);                   // OTA: Avoid crash due to angry watchdog

  i2s_driver_uninstall(I2S_NUM_0);         // Reset I2S peripheral for good measure

  delete effect;
  effect = nullptr;

  FreeLeds();
}

void MusicLeds::ShowFrame(PLAYMODE CurrentMode, esphome::Color current_color, light::AddressableLight *p_it)
{
  if (effect == NULL)
  {
    effect = new VisualEffect(p_it->size());
  }

  InitLeds(p_it->size());

  if (disableSoundProcessing)
  {
    return;
  }

  static unsigned long lastUMRun = millis();          // time of last filter run

  int userloopDelay = int(millis() - lastUMRun);
  if (lastUMRun == 0) userloopDelay=0;                // startup - don't have valid data from last run.

  unsigned long t_now = millis();
  lastUMRun = t_now;
  if (soundAgc > AGC_NUM_PRESETS) soundAgc = 0;  // make sure that AGC preset is valid (to avoid array bounds violation)

  if (userloopDelay < 2) userloopDelay = 0;      // minor glitch, no problem
  if (userloopDelay > 150) userloopDelay = 150;  // limit number of filter re-runs  
  do {
    getSample();                        // Sample the microphone
    agcAvg(t_now - userloopDelay);      // Calculated the PI adjusted value as sampleAvg
    userloopDelay -= 2;                 // advance "simulated time" by 2ms
  } while (userloopDelay > 0);

  myVals[millis() % 32] = sampleAgc;

  // limit dynamics (experimental)
  limitSampleDynamics();

  effect->main_color = CRGB(current_color.r, current_color.g, current_color.b);
  if ((int)id(fastled_palette).state == 0)
  {
    effect->back_color = CRGB(current_color.r / 100 * 5, current_color.g / 100 * 5, current_color.b / 100 * 5); // 5% from main color
  }
  else
  {
    effect->back_color = CRGB::Black;
  }

  switch(CurrentMode)
  {
    case MODE_BINMAP:
      effect->visualize_binmap(leds);
      break;
    case MODE_GRAV:
      effect->visualize_gravfreq(leds);
      break;
    case MODE_GRAVICENTER:
      effect->visualize_gravcenter(leds);
      break;
    case MODE_GRAVICENTRIC:
      effect->visualize_gravcentric(leds);
      break;
    case MODE_PIXELS:
      effect->visualize_pixels(leds);
      break;
    case MODE_JUNGLES:
      effect->visualize_juggles(leds);
      break;
    case MODE_MIDNOISE:
      effect->visualize_midnoise(leds);
      break;
  }

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

class MusicLeds music_leds;
