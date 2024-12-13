#pragma once

#undef delay

#define FASTLED_INTERNAL // remove annoying pragma messages

#include "FastLED.h"
#include "constants.h"

// --- МАТРИЦА ------------------------------------------------------------------------------------------------------------------------------------------
uint8_t ORIENTATION = 3;                                    // Ориентация матрицы
uint8_t MATRIX_TYPE = 0;                                    // Тип матрицы: 0 - зигзаг, 1 - параллельная

/*
  ORIENTATION 0 :: CONNECTION_ANGLE == 0 :: STRIP_DIRECTION == 0
  ORIENTATION 1 :: CONNECTION_ANGLE == 0 :: STRIP_DIRECTION == 1
  ORIENTATION 2 :: CONNECTION_ANGLE == 1 :: STRIP_DIRECTION == 0
  ORIENTATION 3 :: CONNECTION_ANGLE == 1 :: STRIP_DIRECTION == 3
  ORIENTATION 4 :: CONNECTION_ANGLE == 2 :: STRIP_DIRECTION == 2
  ORIENTATION 5 :: CONNECTION_ANGLE == 2 :: STRIP_DIRECTION == 3
  ORIENTATION 6 :: CONNECTION_ANGLE == 3 :: STRIP_DIRECTION == 2
  ORIENTATION 7 :: CONNECTION_ANGLE == 3 :: STRIP_DIRECTION == 1

  CONNECTION_ANGLE - Угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
  STRIP_DIRECTION  - Направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
                     при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
                     шпаргалка по настройке матрицы здесь! https://alexgyver.ru/matrix_guide/
*/


// --- Common -------------------------------------------------------------------------------------------------------------------------------------------
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


// --- Effects ------------------------------------------------------------------------------------------------------------------------------------------
uint16_t speed = 20; // speed is set dynamically once we've started up
uint16_t scale = 30; // scale is set dynamically once we've started up

CRGBPalette16 currentPalette(PartyColors_p);
