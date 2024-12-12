#pragma once

// --- МАТРИЦА -------------------------
#define CURRENT_LIMIT         (1000U)                       // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define WIDTH                 (16U)                         // ширина матрицы
#define HEIGHT                (16U)                         // высота матрицы

#define NUM_LEDS              (uint16_t)(WIDTH * HEIGHT)

#define COLOR_ORDER           (GRB)                         // порядок цветов на ленте. Если цвет отображается некорректно - меняйте. Начать можно с RGB

#define MATRIX_TYPE           (0U)                          // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE      (1U)                          // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION       (3U)                          // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
                                                            // при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
                                                            // шпаргалка по настройке матрицы здесь! https://alexgyver.ru/matrix_guide/

// --- ЭФФЕКТЫ -------------------------
#define RANDOM_SETTINGS_IN_CYCLE_MODE     (1U)              // с этой строчкой в режиме Цикл эффекты будут включаться на случайных (но удачных) настройках Скорости и Масштаба
                                                            // настройки подбирались для лампы с матрицей 16х16 со стеклянным плафоном и калькой под ним. на других - не гарантируется
                                                            // этот режим можно включать/выключать секретной командой. чтобы после первой загрузки прошивки в плату он был выключен, поменяйте (1U) на (0U).

#define DYNAMIC                (0U)                         // динамическая задержка для кадров ( будет использоваться бегунок Скорость )
#define SOFT_DELAY             (1U)                         // задержка для смены кадров FPSdelay задается програмно прямо в теле эффекта
#define LOW_DELAY             (15U)                         // низкая фиксированная задержка для смены кадров
#define HIGH_DELAY            (50U)                         // высокая фиксированная задержка для смены кадров
#define DYNAMIC_DELAY_TICK    if (millis() - effTimer >= (256U - modes[currentMode].Speed))
#define HIGH_DELAY_TICK       if (millis() - effTimer >= 50)
#define LOW_DELAY_TICK        if (millis() - effTimer >= 15)
#define MICRO_DELAY_TICK      if (millis() - effTimer >= 2)
#define SOFT_DELAY_TICK       if (millis() - effTimer >= FPSdelay)

// --- ЭФФЕКТЫ -------------------------
// == названия и номера эффектов ниже в списке используются на вкладке effectTricker ==
// == если меняете, меняйте и там, и ещё здесь ниже в РЕЕСТРЕ ДОСТУПНЫХ ЭФФЕКТОВ ==
#define EFF_WHITE_COLOR         ( 0U)    // Бeлый cвeт
#define EFF_COLOR               ( 1U)    // Цвeт
#define EFF_COLORS              ( 2U)    // Cмeнa цвeтa
#define EFF_MADNESS             ( 3U)    // Бeзyмиe
#define EFF_CLOUDS              ( 4U)    // Oблaкa
#define EFF_LAVA                ( 5U)    // Лaвa
#define EFF_PLASMA              ( 6U)    // Плaзмa
#define EFF_RAINBOW             ( 7U)    // Paдyгa 3D
#define EFF_RAINBOW_STRIPE      ( 8U)    // Пaвлин
#define EFF_ZEBRA               ( 9U)    // 3eбpa
#define EFF_FOREST              (10U)    // Лec
#define EFF_OCEAN               (11U)    // Oкeaн
#define EFF_BBALLS              (12U)    // Mячики
#define EFF_BALLS_BOUNCE        (13U)    // Mячики бeз гpaниц
#define EFF_POPCORN             (14U)    // Пoпкopн
#define EFF_SPIRO               (15U)    // Cпиpaли
#define EFF_PRISMATA            (16U)    // Пpизмaтa
#define EFF_SMOKEBALLS          (17U)    // Дымoвыe шaшки
#define EFF_FLAME               (18U)    // Плaмя
#define EFF_FIRE_2021           (19U)    // Oгoнь 2021
#define EFF_PACIFIC             (20U)    // Tиxий oкeaн
#define EFF_SHADOWS             (21U)    // Teни
#define EFF_DNA                 (22U)    // ДHK
#define EFF_FLOCK               (23U)    // Cтaя
#define EFF_FLOCK_N_PR          (24U)    // Cтaя и xищник
#define EFF_BUTTERFLYS          (25U)    // Moтыльки
#define EFF_BUTTERFLYS_LAMP     (26U)    // Лaмпa c мoтылькaми
#define EFF_SNAKES              (27U)    // 3мeйки
#define EFF_NEXUS               (28U)    // Nexus
#define EFF_SPHERES             (29U)    // Шapы
#define EFF_SINUSOID3           (30U)    // Cинycoид
#define EFF_METABALLS           (31U)    // Meтaбoлз
#define EFF_AURORA              (32U)    // Ceвepнoe cияниe
#define EFF_SPIDER              (33U)    // Плaзмeннaя лaмпa
#define EFF_LAVALAMP            (34U)    // Лaвoвaя лaмпa
#define EFF_LIQUIDLAMP          (35U)    // Жидкaя лaмпa
#define EFF_LIQUIDLAMP_AUTO     (36U)    // Жидкaя лaмпa (auto)
#define EFF_DROPS               (37U)    // Kaпли нa cтeклe
#define EFF_MATRIX              (38U)    // Maтpицa
#define EFF_FIRE_2012           (39U)    // Oгoнь 2012
#define EFF_FIRE_2018           (40U)    // Oгoнь 2018
#define EFF_FIRE_2020           (41U)    // Oгoнь 2020
#define EFF_FIRE                (42U)    // Oгoнь
#define EFF_WHIRL               (43U)    // Bиxpи плaмeни
#define EFF_WHIRL_MULTI         (44U)    // Paзнoцвeтныe виxpи
#define EFF_MAGMA               (45U)    // Maгмa
#define EFF_LLAND               (46U)    // Kипeниe
#define EFF_WATERFALL           (47U)    // Boдoпaд
#define EFF_WATERFALL_4IN1      (48U)    // Boдoпaд 4 в 1
#define EFF_POOL                (49U)    // Бacceйн
#define EFF_PULSE               (50U)    // Пyльc
#define EFF_PULSE_RAINBOW       (51U)    // Paдyжный пyльc
#define EFF_PULSE_WHITE         (52U)    // Бeлый пyльc
#define EFF_OSCILLATING         (53U)    // Ocциллятop
#define EFF_FOUNTAIN            (54U)    // Иcтoчник
#define EFF_FAIRY               (55U)    // Фeя
#define EFF_COMET               (56U)    // Koмeтa
#define EFF_COMET_COLOR         (57U)    // Oднoцвeтнaя кoмeтa
#define EFF_COMET_TWO           (58U)    // Двe кoмeты
#define EFF_COMET_THREE         (59U)    // Тpи кoмeты
#define EFF_ATTRACT             (60U)    // Пpитяжeниe
#define EFF_FIREFLY             (61U)    // Пapящий oгoнь
#define EFF_FIREFLY_TOP         (62U)    // Bepxoвoй oгoнь
#define EFF_SNAKE               (63U)    // Paдyжный змeй
#define EFF_SPARKLES            (64U)    // Koнфeтти
#define EFF_TWINKLES            (65U)    // Mepцaниe
#define EFF_SMOKE               (66U)    // Дым
#define EFF_SMOKE_COLOR         (67U)    // Paзнoцвeтный дым
#define EFF_PICASSO             (68U)    // Пикacco
#define EFF_WAVES               (69U)    // Boлны
#define EFF_SAND                (70U)    // Цвeтныe дpaжe
#define EFF_RINGS               (71U)    // Koдoвый зaмoк
#define EFF_CUBE2D              (72U)    // Kyбик Pyбикa
#define EFF_SIMPLE_RAIN         (73U)    // Tyчкa в бaнкe
#define EFF_STORMY_RAIN         (74U)    // Гроза в банке
#define EFF_COLOR_RAIN          (75U)    // Ocaдки
#define EFF_RAIN                (76U)    // Paзнoцвeтный дoждь
#define EFF_SNOW                (77U)    // Cнeгoпaд
#define EFF_STARFALL            (78U)    // 3вeздoпaд / Meтeль
#define EFF_LEAPERS             (79U)    // Пpыгyны
#define EFF_LIGHTERS            (80U)    // Cвeтлячки
#define EFF_LIGHTER_TRACES      (81U)    // Cвeтлячки co шлeйфoм
#define EFF_LUMENJER            (82U)    // Люмeньep
#define EFF_PAINTBALL           (83U)    // Пeйнтбoл
#define EFF_RAINBOW_VER         (84U)    // Paдyгa
#define EFF_CHRISTMAS_TREE      (85U)    // Новорічна ялинка
#define EFF_BY_EFFECT           (86U)    // Побічний ефект
#define EFF_COLOR_FRIZZLES      (87U)    // Кольорові кучері
#define EFF_COLORED_PYTHON      (88U)    // Кольоровий Пітон
#define EFF_CONTACTS            (89U)    // Контакти
#define EFF_DROP_IN_WATER       (90U)    // Краплі на воді
#define EFF_FEATHER_CANDLE      (91U)    // Свічка
#define EFF_FIREWORK            (92U)    // Феєрверк
#define EFF_FIREWORK_2          (93U)    // Феєрверк 2
#define EFF_HOURGLASS           (94U)    // Пісочний годинник
#define EFF_LOTUS               (95U)    // Квітка лотоса
#define EFF_MAGIC_LANTERN       (96U)    // Чарівний ліхтарик
#define EFF_MOSAIC              (97U)    // Мозайка
#define EFF_OCTOPUS             (98U)    // Восьминіг
#define EFF_PAINTS              (99U)    // Олійні фарби
#define EFF_PLASMA_WAVES        (100U)   // Плазмові хвілі
#define EFF_RADIAL_WAVE         (101U)   // Радіальна хвиля
#define EFF_RIVERS              (102U)   // Річки Ботсвани
#define EFF_SPECTRUM            (103U)   // Спектрум
#define EFF_STROBE              (104U)   // Строб.Хаос.Дифузія
#define EFF_SWIRL               (105U)   // Завиток
#define EFF_TORNADO             (106U)   // Торнадо
#define EFF_WATERCOLOR          (107U)   // Акварель
#define EFF_WEB_TOOLS           (108U)   // Мрія дизайнера
#define EFF_WINE                (109U)   // Вино

// https://github.com/SlingMaster/WiFiLampJavelin/blob/main/Firmware/effectTicker.ino
// https://github.com/terrorsl/FieryLedLamp/blob/main/FieryLedLamp_New_WEB/FieryLedLamp2/src/Constants.h

#define EFF_FLOWERRUTA          (110U)    // Червона Рута
#define EFF_BAMBOO              (111U)    // Бамбук
#define EFF_BALLROUTINE         (112U)    // Блуждающий кубик
#define EFF_STARS               (113U)    // Звезды
#define EFF_TIXYLAND            (114U)    // Земля Тикси
#define EFF_FIRESPARKS          (115U)    // Огонь с искрами
#define EFF_PLANETEARTH         (116U)    // Планета Земля
#define EFF_DANDELIONS          (117U)    // Разноцветные одуванчики
#define EFF_SERPENTINE          (118U)    // Серпантин
#define EFF_ARROWS              (119U)    // Стрелки
#define EFF_TURBULENCE          (120U)    // Цифровая турбулентность

#define EFF_UKRAINE             (121U)   // Україна

#define MODE_AMOUNT             (122U)   // количество режимов

// ============= МАССИВ НАСТРОЕК ЭФФЕКТОВ ПО УМОЛЧАНИЮ ===================
// формат записи:
//{ Яркость, Скорость, Масштаб},
static const uint8_t defaultSettings[][3] PROGMEM = {
  {   9, 207,  26}, // Бeлый cвeт
  {   9, 180,  99}, // Цвeт
  {  10, 252,  32}, // Cмeнa цвeтa
  {  11,  33,  58}, // Бeзyмиe
  {   8,   4,  34}, // Oблaкa
  {   8,   9,  24}, // Лaвa
  {  11,  19,  59}, // Плaзмa
  {  11,  13,  60}, // Paдyгa 3D
  {  11,   5,  12}, // Пaвлин
  {   7,   8,  21}, // 3eбpa
  {   7,   8,  95}, // Лec
  {   7,   6,  12}, // Oкeaн
  {  24, 255,  26}, // Mячики
  {  18,  11,  70}, // Mячики бeз гpaниц
  {  19,  32,  16}, // Пoпкopн
  {   9,  46,   3}, // Cпиpaли
  {  17, 100,   2}, // Пpизмaтa
  {  12,  44,  17}, // Дымoвыe шaшки
  {  22,  53,   3}, // Плaмя
  {   9,  51,  11}, // Oгoнь 2021
  {  55, 127, 100}, // Tиxий oкeaн
  {  39,  77,   1}, // Teни
  {  15,  77,  95}, // ДHK
  {  15, 136,   4}, // Cтaя
  {  15, 128,  80}, // Cтaя и xищник
  {  11,  53,  87}, // Moтыльки
  {   7, 118,  57}, // Лaмпa c мoтылькaми
  {   9,  96,  31}, // 3мeйки
  {  19,  60,  20}, // Nexus
  {   9,  85,  85}, // Шapы
  {   7,  89,  83}, // Cинycoид
  {   7,  85,   3}, // Meтaбoлз
  {  12,  73,  38}, // Ceвepнoe cияниe
  {   8,  59,  18}, // Плaзмeннaя лaмпa
  {  23, 203,   1}, // Лaвoвaя лaмпa
  {  11,  63,   1}, // Жидкaя лaмпa
  {  11, 124,  39}, // Жидкaя лaмпa (auto)
  {  23,  71,  59}, // Kaпли нa cтeклe
  {  27, 186,  23}, // Maтpицa
  {   9, 225,  59}, // Oгoнь 2012
  {  57, 225,  15}, // Oгoнь 2018
  {   9, 220,  20}, // Oгoнь 2020
  {  22, 225,   1}, // Oгoнь
  {   9, 240,   1}, // Bиxpи плaмeни
  {   9, 240,  86}, // Paзнoцвeтныe виxpи
  {   9, 198,  20}, // Maгмa
  {   7, 240,  18}, // Kипeниe
  {   5, 212,  54}, // Boдoпaд
  {   7, 197,  22}, // Boдoпaд 4 в 1
  {   8, 222,  63}, // Бacceйн
  {  12, 185,   6}, // Пyльc
  {  11, 185,  31}, // Paдyжный пyльc
  {   9, 179,  11}, // Бeлый пyльc
  {   8, 208, 100}, // Ocциллятop
  {  15, 233,  77}, // Иcтoчник
  {  19, 212,  44}, // Фeя
  {  16, 220,  28}, // Koмeтa
  {  14, 212,  69}, // Oднoцвeтнaя кoмeтa
  {  27, 186,  19}, // Двe кoмeты
  {  24, 186,   9}, // Тpи кoмeты
  {  21, 203,  65}, // Пpитяжeниe
  {  26, 206,  15}, // Пapящий oгoнь
  {  26, 190,  15}, // Bepxoвoй oгoнь
  {  12, 178,   1}, // Paдyжный змeй
  {  16, 142,  63}, // Koнфeтти
  {  25, 236,   4}, // Mepцaниe
  {   9, 157, 100}, // Дым
  {   9, 157,  30}, // Paзнoцвeтный дым
  {   9, 189,  43}, // Пикacco
  {   9, 236,  80}, // Boлны
  {   9, 195,  80}, // Цвeтныe дpaжe
  {  10, 222,  92}, // Koдoвый зaмoк
  {  10, 231,  89}, // Kyбик Pyбикa
  {  30, 233,   2}, // Tyчкa в бaнкe
  {  20, 236,  25}, // Гроза в банке
  {  15, 198,  99}, // Ocaдки
  {  15, 225,   1}, // Paзнoцвeтный дoждь
  {   9, 180,  90}, // Cнeгoпaд
  {  20, 199,  54}, // 3вeздoпaд / Meтeль
  {  24, 203,   5}, // Пpыгyны
  {  15, 157,  23}, // Cвeтлячки
  {  21, 198,  93}, // Cвeтлячки co шлeйфoм
  {  14, 223,  40}, // Люмeньep
  {  11, 236,   7}, // Пeйнтбoл
  {   8, 196,  56}, // Paдyгa
  {  50,  90,  50}, // Новорічна ялинка
  {  45, 150,  30}, // Побічний ефект
  {  20, 128,  25}, // Кольорові кучері
  {  15, 127,  92}, // Кольоровий Пітон
  {  10, 200,  60}, // Контакти
  {  15, 200,  55}, // Краплі на воді
  {  50, 220,   5}, // Свічка
  {  80,  50,   0}, // Феєрверк
  {  40, 240,  75}, // Феєрверк 2
  {  30, 250, 100}, // Пісочний годинник
  {  20, 210,  33}, // Квітка лотоса
  {  20, 200,  96}, // Чарівний ліхтарик
  {  10, 220,  50}, // Мозайка
  {  15, 230,  51}, // Восьминіг
  {  25, 195,  50}, // Олійні фарби
  {  15, 150,  50}, // Плазмові хвілі
  {  10, 205,  50}, // Радіальна хвиля
  {  15,  50,  50}, // Річки Ботсвани
  {  11, 255,   1}, // Спектрум
  {  25,  70,  51}, // Строб.Хаос.Дифузія
  {  30, 230,  50}, // Завиток
  {  15, 127,  50}, // Торнадо
  {  25, 240,  65}, // Акварель
  {  15, 128,  50}, // Мрія дизайнера
  {  50, 230,  63}, // Вино
  
  {  20, 215,  60}, // Червона Рута
  {  20, 215,  90}, // Бамбук
  {  20, 150,  50}, // Блуждающий кубик
  {  25, 215,  99}, // Звезды
  {  20, 212,  76}, // Земля Тикси
  {  30,  80,  64}, // Огонь с искрами
  {  25, 128,  75}, // Планета Земля
  {  20,  50,  90}, // Разноцветные одуванчики
  {  15,  75,  50}, // Серпантин
  {  75, 165,  40}, // Стрелки
  {  15, 215,  35}, // Цифровая турбулентность
  
  {  15, 240,  50}  // Україна
}; //             ^-- проверьте, чтобы у предыдущей строки не было запятой после скобки

// ============= КОНЕЦ МАССИВА =====
