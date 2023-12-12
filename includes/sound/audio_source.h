#pragma once

#include <driver/i2s.h>

// Microphone, connecting to GPIO
constexpr int I2S_SD_PIN  = 32;
constexpr int I2S_WS_PIN  = 15;
constexpr int I2S_SCK_PIN = 14;

constexpr i2s_port_t I2S_PORT = I2S_NUM_0;

// data type requested from the I2S driver - currently we always use 32bit
//#define I2S_USE_16BIT_SAMPLES    // (experimental) define this to request 16bit - more efficient but possibly less compatible

// if you have problems to get your microphone work on the left channel, uncomment the following line
//#define I2S_USE_RIGHT_CHANNEL    // (experimental) define this to use right channel (digital mics only)

// Uncomment the line below to utilize ADC1 _exclusively_ for I2S sound input.
// benefit: analog mic inputs will be sampled contiously -> better response times and less "glitches"
// WARNING: this option WILL lock-up your device in case that any other analogRead() operation is performed; 
//          for example if you want to read "analog buttons"
//#define I2S_GRAB_ADC1_COMPLETELY // (experimental) continously sample analog ADC microphone. WARNING will cause analogRead() lock-up 

#ifdef I2S_USE_16BIT_SAMPLES
  #define I2S_SAMPLE_RESOLUTION I2S_BITS_PER_SAMPLE_16BIT
  #define I2S_datatype int16_t
  #define I2S_unsigned_datatype uint16_t
  #undef  I2S_SAMPLE_DOWNSCALE_TO_16BIT
#else
  #define I2S_SAMPLE_RESOLUTION I2S_BITS_PER_SAMPLE_32BIT
  #define I2S_datatype int32_t
  #define I2S_unsigned_datatype uint32_t
  #define I2S_SAMPLE_DOWNSCALE_TO_16BIT
#endif

#define I2S_USE_RIGHT_CHANNEL

#ifdef I2S_USE_RIGHT_CHANNEL
  #define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_RIGHT
  #define I2S_MIC_CHANNEL_TEXT "Right channel only."
#else
  #define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT
  #define I2S_MIC_CHANNEL_TEXT "Left channel only."
#endif

/* 
  Interface class
  AudioSource serves as base class for all microphone types
  This enables accessing all microphones with one single interface
  which simplifies the caller code
*/

class AudioSource {
public:
    /*
      All public methods are virtual, so they can be overridden
      Everything but the destructor is also removed, to make sure each mic
      Implementation provides its version of this function
    */
    virtual ~AudioSource() {};

    /*
      Initialize
      This function needs to take care of anything that needs to be done
      before samples can be obtained from the microphone.
    */
    virtual void initialize() = 0;

    /*
      Deinitialize
      Release all resources and deactivate any functionality that is used
      by this microphone
    */
    virtual void deinitialize() = 0;

    /*
      getSamples
      Read num_samples from the microphone, and store them in the provided
      buffer
    */
    virtual void getSamples(float *buffer, uint16_t num_samples) = 0;

    /* Get an up-to-date sample without DC offset */
    virtual int getSampleWithoutDCOffset() = 0;

    /* check if the audio source driver was initialized successfully */
    virtual bool isInitialized(void) {return(_initialized);}

protected:
    // Private constructor, to make sure it is not callable except from derived classes
    AudioSource(int sampleRate, int blockSize, int16_t lshift, uint32_t mask, float sampleScale) : 
        _sampleRate(sampleRate), _blockSize(blockSize), _sampleNoDCOffset(0), _dcOffset(0.0f), 
        _shift(lshift), _mask(mask), _sampleScale(sampleScale), 
        _initialized(false), _myADCchannel(0x0F), _lastADCsample(0), _broken_samples_counter(0) 
    {};

    int _sampleRate;                /* Microphone sampling rate (from uint16_t to int to suppress warning)*/ 
    int _blockSize;                 /* I2S block size */
    volatile int _sampleNoDCOffset; /* Up-to-date sample without DCOffset */
    float _dcOffset;                /* Rolling average DC offset */
    int16_t _shift;                 /* Shift obtained samples to the right (positive) or left(negative) by this amount */
    uint32_t _mask;                 /* Bitmask for sample data after shifting. Bitmask 0X0FFF means that we need to convert 12bit ADC samples from unsigned to signed*/
    float _sampleScale;             /* pre-scaling factor for I2S samples */
    bool _initialized;              /* Gets set to true if initialization is successful */
    int8_t _myADCchannel;           /* current ADC channel, in case of analog input. 0x0F if undefined */
    I2S_datatype _lastADCsample;    /* last sample from ADC */
    I2S_datatype decodeADCsample(I2S_unsigned_datatype rawData); /* function to handle ADC samples */
    unsigned int _broken_samples_counter; /* counts number of broken (and fixed) ADC samples */
};

/*
   Basic I2S microphone source
   All functions are marked virtual, so derived classes can replace them
*/
class I2SSource : public AudioSource {
public:
    I2SSource(int sampleRate, int blockSize, int16_t lshift, uint32_t mask, float sampleScale = 1.0f) :
        AudioSource(sampleRate, blockSize, lshift, mask, sampleScale) {
        _config = {
            .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
            .sample_rate = _sampleRate,                       // "narrowing conversion" warning can be ignored here - our _sampleRate is never bigger that INT32_MAX
            .bits_per_sample = I2S_SAMPLE_RESOLUTION,
            .channel_format = I2S_MIC_CHANNEL,
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)
            .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
#else
            .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
#endif
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 8,
            .dma_buf_len = _blockSize
        };

        _pinConfig = {
            #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)
            .mck_io_num = I2S_PIN_NO_CHANGE, // needed, otherwise i2s_set_pin() will fail in IDF >=4.4.x
            #endif
            .bck_io_num = I2S_SCK_PIN,
            .ws_io_num = I2S_WS_PIN,
            .data_out_num = I2S_PIN_NO_CHANGE,
            .data_in_num = I2S_SD_PIN
        };
    };

    virtual void initialize() {

        #if defined(ARDUINO_ARCH_ESP32) && !defined(CONFIG_IDF_TARGET_ESP32S3) && !defined(CONFIG_IDF_TARGET_ESP32S2) && !defined(CONFIG_IDF_TARGET_ESP32C3)
        if (ESP.getChipRevision() == 0) _config.use_apll = false; // APLL is broken on ESP32 revision 0, so we disable it on rev0 chips
        #endif

        esp_err_t err = i2s_driver_install(I2S_NUM_0, &_config, 0, nullptr);
        if (err != ESP_OK) 
        {
          ESP_LOGE("ASR", "AS: Failed to install i2s driver: %d", err);
          return;
        }

        err = i2s_set_pin(I2S_NUM_0, &_pinConfig);
        if (err != ESP_OK) 
        {
          ESP_LOGE("ASR", "AS: Failed to set i2s pin config: %d", err);
          return;
        }

        _initialized = true;
    }

    virtual void deinitialize() {
        if (_initialized) {
            _initialized = false;
            esp_err_t err = i2s_driver_uninstall(I2S_NUM_0);
            if (err != ESP_OK) 
            {
              ESP_LOGE("ASR", "AS: Failed to uninstall i2s driver: %d", err);
              return;
            }
        }
    }

    virtual void getSamples(float *buffer, uint16_t num_samples) {
        if(_initialized) {
            esp_err_t err;
            size_t bytes_read = 0;        /* Counter variable to check if we actually got enough data */
            I2S_datatype newSamples[num_samples]; /* Intermediary sample storage */
           
            _dcOffset = 0.0f;              // Reset dc offset
            _broken_samples_counter = 0;   // Reset ADC broken samples counter

            // get fresh samples
            err = i2s_read(I2S_NUM_0, (void *)newSamples, sizeof(newSamples), &bytes_read, portMAX_DELAY);
            if ((err != ESP_OK)) {
                ESP_LOGE("ASR", "AS: Failed to get samples: %d", err);
                return;
            }

            // For correct operation, we need to read exactly sizeof(samples) bytes from i2s
            if(bytes_read != sizeof(newSamples)) {
                ESP_LOGE("ASR", "AS: Failed to get enough samples: wanted: %d read: %d", sizeof(newSamples), bytes_read);
                return;
            }

            // Store samples in sample buffer and update DC offset
            for (int i = 0; i < num_samples; i++) {
                if (_mask == 0x0FFF) // mask = 0x0FFF means we are in I2SAdcSource
                {  
                    I2S_unsigned_datatype rawData = * reinterpret_cast<I2S_unsigned_datatype *> (newSamples + i); // C++ acrobatics to get sample as "unsigned"
                    I2S_datatype sampleNoFilter = decodeADCsample(rawData);
                    if (_broken_samples_counter >= num_samples-1) // kill-switch: ADC sample correction off when all samples in a batch were "broken"
                    {             
                        _myADCchannel = 0x0F;
                        ESP_LOGE("ASR", "AS: Too many broken audio samples from ADC - sample correction switched off.");
                    }
                    newSamples[i] = (3 * sampleNoFilter + _lastADCsample) / 4;  // apply low-pass filter (2-tap FIR)
                    //newSamples[i] = (sampleNoFilter + lastADCsample) / 2;      // apply stronger low-pass filter (2-tap FIR)
                    _lastADCsample = sampleNoFilter;                            // update ADC last sample
                }

                // pre-shift samples down to 16bit
#ifdef I2S_SAMPLE_DOWNSCALE_TO_16BIT
                if (_shift != 0)
                    newSamples[i] >>= 16;
#endif
                float currSample = 0.0;
                if(_shift > 0)
                  currSample = (float) (newSamples[i] >> _shift);
                else {
                  if(_shift < 0)
                    currSample = (float) (newSamples[i] << (- _shift)); // need to "pump up" 12bit ADC to full 16bit as delivered by other digital mics
                  else
#ifdef I2S_SAMPLE_DOWNSCALE_TO_16BIT
                    currSample = (float) newSamples[i] / 65536.0f;        // _shift == 0 -> use the chance to keep lower 16bits
#else
                    currSample = (float) newSamples[i];
#endif
                }
                buffer[i] = currSample;                                   // store sample
                buffer[i] *= _sampleScale;                                // scale sample
                _dcOffset = ((_dcOffset * 31) + currSample) / 32;
            }

            // Update no-DC sample
            _sampleNoDCOffset = buffer[num_samples - 1] - _dcOffset;
        }
    }

    // function to handle ADC samples
    I2S_datatype decodeADCsample(I2S_unsigned_datatype rawData) {
#ifndef I2S_USE_16BIT_SAMPLES
        rawData = (rawData >> 16) & 0xFFFF;                        // scale input down from 32bit -> 16bit
        I2S_datatype lastGoodSample = _lastADCsample / 16384 ;     // 26bit-> 12bit with correct sign handling
#else
        rawData = rawData & 0xFFFF;                                // input is already in 16bit, just mask off possible junk
        I2S_datatype lastGoodSample = _lastADCsample * 4;          // 10bit-> 12bit
#endif
        // decode ADC sample
        uint16_t the_channel = (rawData >> 12) & 0x000F;           // upper 4 bit = ADC channel
        uint16_t the_sample  =  rawData & 0x0FFF;                  // lower 12bit -> ADC sample (unsigned)
        I2S_datatype finalSample = (int(the_sample) - 2048);       // convert to signed (centered at 0);

        // fix bad samples
        if ((the_channel != _myADCchannel) && (_myADCchannel != 0x0F)) { // 0x0F means "don't know what my channel is" 
            finalSample = lastGoodSample;                         // replace with the last good ADC sample
            _broken_samples_counter ++;
            //Serial.print("\n!ADC rogue sample 0x"); Serial.print(rawData, HEX); Serial.print("\tchannel:");Serial.println(the_channel);
        }
#ifndef I2S_USE_16BIT_SAMPLES
        finalSample = finalSample << 16;    // scale up from 16bit -> 32bit;
#endif
        finalSample = finalSample / 4;      // mimic old analog driver behaviour (12bit -> 10bit)
        return(finalSample);
    }

    virtual int getSampleWithoutDCOffset() {
        return _sampleNoDCOffset;
    }

protected:
    i2s_config_t _config;
    i2s_pin_config_t _pinConfig;
};
