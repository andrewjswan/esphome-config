#pragma once

// ************* НАСТРОЙКА МАТРИЦЫ *****
#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)

#else
!!!!!!!!!!!!!!!!!!!!!!!!!!!   смотрите инструкцию: https://alexgyver.ru/wp-content/uploads/2018/11/scheme3.jpg
!!!!!!!!!!!!!!!!!!!!!!!!!!!   такого сочетания CONNECTION_ANGLE и STRIP_DIRECTION не бывает
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif

// если у вас матрица необычной формы с зазорами/вырезами, либо просто маленькая, тогда вам придётся переписать функцию XY() под себя
// массив для переадресации можно сформировать на этом онлайн-сервисе: https://macetech.github.io/FastLED-XY-Map-Generator/
// или тут по-русски: https://firelamp.pp.ua/matrix_generator/

// ниже пример функции, когда у вас матрица 8х16, а вы хотите, чтобы эффекты рисовались, будто бы матрица 16х16 (рисуем по центру, а по бокам обрезано)
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  Х  Х  -  -  -  - 
//   -  -  -  -  Х  Х  Х  Х  Х  Х  9  8  -  -  -  - 
//   -  -  -  -  0  1  2  3  4  5  6  7  -  -  -  -
/*
uint8_t XY (uint8_t x, uint8_t y) {
  // any out of bounds address maps to the first hidden pixel
  if ( (x >= 16) || (y >= 16) ) {
    return (128); //(LAST_VISIBLE_LED + 1);
  }

  const uint8_t XYTable[] = {
   255, 254, 253, 252, 127, 126, 125, 124, 123, 122, 121, 120, 251, 250, 249, 248,
   240, 241, 242, 243, 112, 113, 114, 115, 116, 117, 118, 119, 244, 245, 246, 247,
   239, 238, 237, 236, 111, 110, 109, 108, 107, 106, 105, 104, 235, 234, 233, 232,
   224, 225, 226, 227,  96,  97,  98,  99, 100, 101, 102, 103, 228, 229, 230, 231,
   223, 222, 221, 220,  95,  94,  93,  92,  91,  90,  89,  88, 219, 218, 217, 216,
   208, 209, 210, 211,  80,  81,  82,  83,  84,  85,  86,  87, 212, 213, 214, 215,
   207, 206, 205, 204,  79,  78,  77,  76,  75,  74,  73,  72, 203, 202, 201, 200,
   192, 193, 194, 195,  64,  65,  66,  67,  68,  69,  70,  71, 196, 197, 198, 199,
   191, 190, 189, 188,  63,  62,  61,  60,  59,  58,  57,  56, 187, 186, 185, 184,
   176, 177, 178, 179,  48,  49,  50,  51,  52,  53,  54,  55, 180, 181, 182, 183,
   175, 174, 173, 172,  47,  46,  45,  44,  43,  42,  41,  40, 171, 170, 169, 168,
   160, 161, 162, 163,  32,  33,  34,  35,  36,  37,  38,  39, 164, 165, 166, 167,
   159, 158, 157, 156,  31,  30,  29,  28,  27,  26,  25,  24, 155, 154, 153, 152,
   144, 145, 146, 147,  16,  17,  18,  19,  20,  21,  22,  23, 148, 149, 150, 151,
   143, 142, 141, 140,  15,  14,  13,  12,  11,  10,   9,   8, 139, 138, 137, 136,
   128, 129, 130, 131,   0,   1,   2,   3,   4,   5,   6,   7, 132, 133, 134, 135
  };

  uint8_t i = (y * 16) + x;
  return XYTable[i];
}
*/

#if CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0
  #define ORIENTATION      (0U)
#endif
#if CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1
  #define ORIENTATION      (1U)
#endif
#if CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0
  #define ORIENTATION      (2U)
#endif
#if CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3
  #define ORIENTATION      (3U)
#endif
#if CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2
  #define ORIENTATION      (4U)
#endif
#if CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3
  #define ORIENTATION      (5U)
#endif
#if CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2
  #define ORIENTATION      (6U)
#endif
#if CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1
  #define ORIENTATION      (7U)
#endif

 
void restoreSettings()
{
  for (uint8_t i = 0; i < MODE_AMOUNT; i++)
  {
    modes[i].Brightness = pgm_read_byte(&defaultSettings[i][0]);
    modes[i].Speed      = pgm_read_byte(&defaultSettings[i][1]);
    modes[i].Scale      = pgm_read_byte(&defaultSettings[i][2]);
  }
}

// =====================================
uint8_t SpeedFactor(uint8_t spd)
{
  uint8_t result = spd * NUM_LEDS / 1024.0;
  return result;
}


// неточный, зато более быстрый квадратный корень
float sqrt3(const float x)
{
  union
  {
    int i;
    float x;
  } u;

  u.x = x;
  u.i = (1<<29) + (u.i >> 1) - (1<<22);
  return u.x;
}

// получить номер пикселя в ленте по координатам
// библиотека FastLED тоже использует эту функцию
uint16_t XY(uint8_t x, uint8_t y)
{
  if (!(THIS_Y & 0x01) || MATRIX_TYPE)               // Even rows run forwards
    return (THIS_Y * _WIDTH + THIS_X);
  else                                                  
    return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);  // Odd rows run backwards
}


// функция отрисовки точки по координатам X Y
#if (WIDTH > 127) || (HEIGHT > 127)
void drawPixelXY(int16_t x, int16_t y, CRGB color)
#else
void drawPixelXY(int8_t x, int8_t y, CRGB color)
#endif
{
  if (x < 0 || x > (WIDTH - 1) || y < 0 || y > (HEIGHT - 1)) return;
  //uint32_t thisPixel = XY((uint8_t)x, (uint8_t)y) * SEGMENTS;
  //for (uint8_t i = 0; i < SEGMENTS; i++)
  //{
  //  leds[thisPixel + i] = color;
  //}
  leds[XY(x, y)] = color;
}


// функция получения цвета пикселя по его номеру
uint32_t getPixColor(uint16_t thisPixel)
{
  if (thisPixel >= NUM_LEDS) return 0;
  return (((uint32_t)leds[thisPixel].r << 16) | ((uint32_t)leds[thisPixel].g << 8 ) | (uint32_t)leds[thisPixel].b); // а почему не просто return (leds[thisPixel])?
}


// функция получения цвета пикселя в матрице по его координатам
uint32_t getPixColorXY(uint8_t x, uint8_t y)
{
  return getPixColor(XY(x, y));
}


// залить все
void fillAll(CRGB color)
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
    leds[i] = color;
}

void ledsClear()
{
  fillAll(CRGB(0,0,0));
}

// стандартные функции библиотеки LEDraw от @Palpalych (для адаптаций его эффектов)
void blurScreen(fract8 blur_amount, CRGB *LEDarray = leds)
{
  blur2d(LEDarray, WIDTH, HEIGHT, blur_amount);
}

void dimAll(uint8_t value, CRGB *LEDarray = leds) {
  nscale8(LEDarray, NUM_LEDS, value);
  // fadeToBlackBy(LEDarray, NUM_LEDS, 255U - value); // эквивалент  
}


// ------------------------------ Дополнительные функции рисования ----------------------
// по мотивам
// https://gist.github.com/sutaburosu/32a203c2efa2bb584f4b846a91066583
void drawPixelXYF(float x, float y, CRGB color) //, uint8_t darklevel = 0U)
{
//  if (x<0 || y<0) return; //не похоже, чтобы отрицательные значения хоть как-нибудь учитывались тут // зато с этой строчкой пропадает нижний ряд
  // extract the fractional parts and derive their inverses
  uint8_t xx = (x - (int)x) * 255, yy = (y - (int)y) * 255, ix = 255 - xx, iy = 255 - yy;
  // calculate the intensities for each affected pixel
  #define WU_WEIGHT(a,b) ((uint8_t) (((a)*(b)+(a)+(b))>>8))
  uint8_t wu[4] = {WU_WEIGHT(ix, iy), WU_WEIGHT(xx, iy),
                   WU_WEIGHT(ix, yy), WU_WEIGHT(xx, yy)};
  // multiply the intensities by the colour, and saturating-add them to the pixels
  for (uint8_t i = 0; i < 4; i++) {
    int16_t xn = x + (i & 1), yn = y + ((i >> 1) & 1);
    CRGB clr = getPixColorXY(xn, yn);
    clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
    clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
    clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
//if (darklevel) drawPixelXY(xn, yn, makeDarker(clr, darklevel));
//else
    drawPixelXY(xn, yn, clr);
  }
}


//---------------------------------------
void DrawLine(int x1, int y1, int x2, int y2, CRGB color)
{
  int deltaX = abs(x2 - x1);
  int deltaY = abs(y2 - y1);
  int signX = x1 < x2 ? 1 : -1;
  int signY = y1 < y2 ? 1 : -1;
  int error = deltaX - deltaY;

  drawPixelXY(x2, y2, color);
  while (x1 != x2 || y1 != y2) {
      drawPixelXY(x1, y1, color);
      int error2 = error * 2;
      if (error2 > -deltaY) {
          error -= deltaY;
          x1 += signX;
      }
      if (error2 < deltaX) {
          error += deltaX;
          y1 += signY;
      }
  }
}


//---------------------------------------
void DrawLineF(float x1, float y1, float x2, float y2, CRGB color)
{
  float deltaX = std::fabs(x2 - x1);
  float deltaY = std::fabs(y2 - y1);
  float error = deltaX - deltaY;

  float signX = x1 < x2 ? 0.5 : -0.5;
  float signY = y1 < y2 ? 0.5 : -0.5;

  while (x1 != x2 || y1 != y2) { // (true) - а я то думаю - "почему функция часто вызывает вылет по вачдогу?" А оно вон оно чё, Михалычь!
      if ((signX > 0 && x1 > x2+signX) || (signX < 0 && x1 < x2+signX)) break;
      if ((signY > 0 && y1 > y2+signY) || (signY < 0 && y1 < y2+signY)) break;
      drawPixelXYF(x1, y1, color); // интересно, почему тут было обычное drawPixelXY() ???
      float error2 = error;
      if (error2 > -deltaY) {
          error -= deltaY;
          x1 += signX;
      }
      if (error2 < deltaX) {
          error += deltaX;
          y1 += signY;
      }
  }
}


//---------------------------------------
/* kostyamat добавил
 функция уменьшения яркости */
CRGB makeDarker( const CRGB& color, fract8 howMuchDarker)
{
  CRGB newcolor = color;
  //newcolor.nscale8( 255 - howMuchDarker);
  newcolor.fadeToBlackBy(howMuchDarker);//эквивалент
  return newcolor;
}


//---------------------------------------
void drawCircleF(float x0, float y0, float radius, CRGB color)
{
  float x = 0, y = radius, error = 0;
  float delta = 1. - 2. * radius;

  while (y >= 0) {
//    drawPixelXYF(x0 + x, y0 + y, color);
//    drawPixelXYF(x0 + x, y0 - y, color);
//    drawPixelXYF(x0 - x, y0 + y, color);
//    drawPixelXYF(x0 - x, y0 - y, color);
    drawPixelXYF(fmod(x0 + x +WIDTH,WIDTH), y0 + y, color); // сделал, чтобы круги были бесшовными по оси х
    drawPixelXYF(fmod(x0 + x +WIDTH,WIDTH), y0 - y, color);
    drawPixelXYF(fmod(x0 - x +WIDTH,WIDTH), y0 + y, color);
    drawPixelXYF(fmod(x0 - x +WIDTH,WIDTH), y0 - y, color);
    error = 2. * (delta + y) - 1.;
    if (delta < 0 && error <= 0) {
      ++x;
      delta += 2. * x + 1.;
      continue;
    }
    error = 2. * (delta - x) - 1.;
    if (delta > 0 && error > 0) {
      --y;
      delta += 1. - 2. * y;
      continue;
    }
    ++x;
    delta += 2. * (x - y);
    --y;
  }
}


//---------------------------------------
uint8_t wrapX(int8_t x){
  return (x + WIDTH)%WIDTH;
}
uint8_t wrapY(int8_t y){
  return (y + HEIGHT)%HEIGHT;
}


//---------------------------------------
void drawRec(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint32_t color) {
  for (uint8_t y = startY; y < endY; y++) {
    for (uint8_t x = startX; x < endX; x++) {
      drawPixelXY(x, y, color);
    }
  }
}

//---------------------------------------
void drawRecCHSV(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, CHSV color) {
  for (uint8_t y = startY; y < endY; y++) {
    for (uint8_t x = startX; x < endX; x++) {
      drawPixelXY(x, y, color);
    }
  }
}

//--------------------------------------
uint8_t validMinMax(float val, uint8_t minV, uint32_t maxV) {
  uint8_t result;
  if (val <= minV) {
    result = minV;
  } else if (val >= maxV) {
    result = maxV;
  } else {
    result = ceil(val);
  }
  //  LOG.printf_P(PSTR( "result: %f | val: %f \n\r"), result, val);
  return result;
}


//--------------------------------------
// альтернативный градиент для ламп собраных из лент с вертикальной компоновкой
// gradientHorizontal | gradientVertical менее производительный но работает на всех видах ламп
void gradientHorizontal(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t start_color, uint8_t end_color, uint8_t start_br, uint8_t end_br, uint8_t saturate) {
  float step_color = 0;
  float step_br = 0;
  if (startX == endX) {
    endX++;
  }
  if (startY == endY) {
    endY++;
  }
  step_color = (end_color - start_color) / abs(startX - endX);
  if (start_color >  end_color) {
    step_color -= 1.2;
  } else {
    step_color += 1.2;
  }

  step_br = (end_br - start_br) / abs(startX - endX);
  if (start_br >  end_color) {
    step_br -= 1.2;
  } else {
    step_br += 1.2;
  }

  // LOG.printf_P(PSTR( "\n step_color: %f | step_br: %f \n\n\r"), step_color, step_br);
  for (uint8_t x = startX; x < endX; x++) {
    for (uint8_t y = startY; y < endY; y++) {
      CHSV thisColor = CHSV((uint8_t) validMinMax((start_color + (x - startX) * step_color), 1, 254), saturate,
                            (uint8_t) validMinMax((start_br + (x - startX) * step_br), 0, 255) );
      drawPixelXY(x, y, thisColor);
    }
  }
}


//--------------------------------------
void gradientVertical(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t start_color, uint8_t end_color, uint8_t start_br, uint8_t end_br, uint8_t saturate) {
  float step_color = 0;
  float step_br = 0;
  if (startX == endX) {
    endX++;
  }
  if (startY == endY) {
    endY++;
  }
  step_color = (end_color - start_color) / abs(startY - endY);

  if (start_color >  end_color) {
    step_color -= 1.2;
  } else {
    step_color += 1.2;
  }

  step_br = (end_br - start_br) / abs(startY - endY);
  if (start_br >  end_color) {
    step_br -= 1.2;
  } else {
    step_br += 1.2;
  }
  for (uint8_t y = startY; y < endY; y++) {
    CHSV thisColor = CHSV( (uint8_t) validMinMax((start_color + (y - startY) * step_color), 0, 255), saturate,
                           (uint8_t) validMinMax((start_br + (y - startY) * step_br), 0, 255) );
    for (uint8_t x = startX; x < endX; x++) {
      drawPixelXY(x, y, thisColor);
    }
  }
}


//---------------------------------------
// gradientDownTop • более плавный градиент в отличие от gradientVertical
// но может некоректно работать на лампах собранных на ленточных светодиодах
//---------------------------------------
void gradientDownTop( uint8_t bottom, CHSV bottom_color, uint8_t top, CHSV top_color ) {
  //  FORWARD_HUES: hue always goes clockwise
  //  BACKWARD_HUES: hue always goes counter-clockwise
  //  SHORTEST_HUES: hue goes whichever way is shortest
  //  LONGEST_HUES: hue goes whichever way is longest
  if (ORIENTATION < 3 || ORIENTATION == 7) {    // if (STRIP_DIRECTION < 2) {
    // STRIP_DIRECTION to UP ========
    fill_gradient(leds, top * WIDTH, top_color, bottom * WIDTH, bottom_color, SHORTEST_HUES);
  } else {
    // STRIP_DIRECTION to DOWN ======
    fill_gradient(leds, NUM_LEDS - bottom * WIDTH - 1, bottom_color, NUM_LEDS - top * WIDTH, top_color, SHORTEST_HUES);
  }
}


//---------------------------------------
void fadePixel(uint8_t i, uint8_t j, uint8_t step)          // новый фейдер
{
  int32_t pixelNum = XY(i, j);
  if (getPixColor(pixelNum) == 0U) return;

  if (leds[pixelNum].r >= 30U ||
      leds[pixelNum].g >= 30U ||
      leds[pixelNum].b >= 30U)
  {
    leds[pixelNum].fadeToBlackBy(step);
  }
  else
  {
    leds[pixelNum] = 0U;
  }
}
