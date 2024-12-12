#pragma once

#include "constants.h"
#include "effects.h"
#include "noise_effects.h"

// Если вы хотите добавить эффекты или сделать им копии для демонстрации на разных настройках, нужно делать это в 5 местах:
// 1. в файле effects.ino - добавляется программный код самого эффекта.
// 2. в файле Constants.h - придумываются названия "EFF_......" и задаются порядковые номера эффектам. В конце указывается общее количество MODE_AMOUNT.
// 3. там же в файле Constants.h ещё ниже - задаётся Массив настроек эффектов по умолчанию.
//    Просто добавьте строчку для своего нового эффекта в нужное место. Это тоже не обязательно.
// 5. здесь в файле effectTicker.ino - подключается процедура вызова эффекта на соответствующий ей "EFF_......"
//    Можно подключать один и тот же эффект под разными номерами. Например: EFF_FIRE (24U), EFF_FIRE2 (25U), EFF_FIRE3 (26U). Будет три огня для разных цветов.

uint32_t effTimer;

void effectsTick()
{
  switch (currentMode)
  {
    case EFF_WHITE_COLOR:         HIGH_DELAY_TICK    { effTimer = millis(); whiteColorStripeRoutine();         }  break;  // ( 0U)  Бeлый cвeт
    case EFF_COLOR:               LOW_DELAY_TICK     { effTimer = millis(); colorRoutine();                    }  break;  // ( 1U)  Цвeт
    case EFF_COLORS:              HIGH_DELAY_TICK    { effTimer = millis(); colorsRoutine2();                  }  break;  // ( 2U)  Cмeнa цвeтa
    case EFF_MADNESS:             HIGH_DELAY_TICK    { effTimer = millis(); madnessNoiseRoutine();             }  break;  // ( 3U)  Бeзyмиe
    case EFF_CLOUDS:              HIGH_DELAY_TICK    { effTimer = millis(); cloudsNoiseRoutine();              }  break;  // ( 4U)  Oблaкa
    case EFF_LAVA:                HIGH_DELAY_TICK    { effTimer = millis(); lavaNoiseRoutine();                }  break;  // ( 5U)  Лaвa
    case EFF_PLASMA:              HIGH_DELAY_TICK    { effTimer = millis(); plasmaNoiseRoutine();              }  break;  // ( 6U)  Плaзмa
    case EFF_RAINBOW:             HIGH_DELAY_TICK    { effTimer = millis(); rainbowNoiseRoutine();             }  break;  // ( 7U)  Paдyгa 3D
    case EFF_RAINBOW_STRIPE:      HIGH_DELAY_TICK    { effTimer = millis(); rainbowStripeNoiseRoutine();       }  break;  // ( 8U)  Пaвлин
    case EFF_ZEBRA:               HIGH_DELAY_TICK    { effTimer = millis(); zebraNoiseRoutine();               }  break;  // ( 9U)  3eбpa
    case EFF_FOREST:              HIGH_DELAY_TICK    { effTimer = millis(); forestNoiseRoutine();              }  break;  // (10U)  Лec
    case EFF_OCEAN:               HIGH_DELAY_TICK    { effTimer = millis(); oceanNoiseRoutine();               }  break;  // (11U)  Oкeaн
    case EFF_BBALLS:              LOW_DELAY_TICK     { effTimer = millis(); BBallsRoutine();                   }  break;  // (12U)  Mячики
    case EFF_BALLS_BOUNCE:        LOW_DELAY_TICK     { effTimer = millis(); bounceRoutine();                   }  break;  // (13U)  Mячики бeз гpaниц
    case EFF_POPCORN:             LOW_DELAY_TICK     { effTimer = millis(); popcornRoutine();                  }  break;  // (14U)  Пoпкopн
    case EFF_SPIRO:               LOW_DELAY_TICK     { effTimer = millis(); spiroRoutine();                    }  break;  // (15U)  Cпиpaли
    case EFF_PRISMATA:            LOW_DELAY_TICK     { effTimer = millis(); PrismataRoutine();                 }  break;  // (16U)  Пpизмaтa
    case EFF_SMOKEBALLS:          LOW_DELAY_TICK     { effTimer = millis(); smokeballsRoutine();               }  break;  // (17U)  Дымoвыe шaшки
    case EFF_FLAME:               LOW_DELAY_TICK     { effTimer = millis(); execStringsFlame();                }  break;  // (18U)  Плaмя
    case EFF_FIRE_2021:           LOW_DELAY_TICK     { effTimer = millis(); Fire2021Routine();                 }  break;  // (19U)  Oгoнь 2021
    case EFF_PACIFIC:             LOW_DELAY_TICK     { effTimer = millis(); pacificRoutine();                  }  break;  // (20U)  Tиxий oкeaн
    case EFF_SHADOWS:             LOW_DELAY_TICK     { effTimer = millis(); shadowsRoutine();                  }  break;  // (21U)  Teни
    case EFF_DNA:                 LOW_DELAY_TICK     { effTimer = millis(); DNARoutine();                      }  break;  // (22U)  ДHK
    case EFF_FLOCK:               LOW_DELAY_TICK     { effTimer = millis(); flockRoutine(false);               }  break;  // (23U)  Cтaя
    case EFF_FLOCK_N_PR:          LOW_DELAY_TICK     { effTimer = millis(); flockRoutine(true);                }  break;  // (24U)  Cтaя и xищник
    case EFF_BUTTERFLYS:          LOW_DELAY_TICK     { effTimer = millis(); butterflysRoutine(true);           }  break;  // (25U)  Moтыльки
    case EFF_BUTTERFLYS_LAMP:     LOW_DELAY_TICK     { effTimer = millis(); butterflysRoutine(false);          }  break;  // (26U)  Лaмпa c мoтылькaми
    case EFF_SNAKES:              LOW_DELAY_TICK     { effTimer = millis(); snakesRoutine();                   }  break;  // (27U)  3мeйки
    case EFF_NEXUS:               LOW_DELAY_TICK     { effTimer = millis(); nexusRoutine();                    }  break;  // (28U)  Nexus
    case EFF_SPHERES:             LOW_DELAY_TICK     { effTimer = millis(); spheresRoutine();                  }  break;  // (29U)  Шapы
    case EFF_SINUSOID3:           HIGH_DELAY_TICK    { effTimer = millis(); Sinusoid3Routine();                }  break;  // (30U)  Cинycoид
    case EFF_METABALLS:           LOW_DELAY_TICK     { effTimer = millis(); MetaBallsRoutine();                }  break;  // (31U)  Meтaбoлз
    case EFF_AURORA:              HIGH_DELAY_TICK    { effTimer = millis(); polarRoutine();                    }  break;  // (32U)  Ceвepнoe cияниe
    case EFF_SPIDER:              LOW_DELAY_TICK     { effTimer = millis(); spiderRoutine();                   }  break;  // (33U)  Плaзмeннaя лaмпa
    case EFF_LAVALAMP:            LOW_DELAY_TICK     { effTimer = millis(); LavaLampRoutine();                 }  break;  // (34U)  Лaвoвaя лaмпa
    case EFF_LIQUIDLAMP:          LOW_DELAY_TICK     { effTimer = millis(); LiquidLampRoutine(true);           }  break;  // (35U)  Жидкaя лaмпa
    case EFF_LIQUIDLAMP_AUTO:     LOW_DELAY_TICK     { effTimer = millis(); LiquidLampRoutine(false);          }  break;  // (36U)  Жидкaя лaмпa (auto)
    case EFF_DROPS:               LOW_DELAY_TICK     { effTimer = millis(); newMatrixRoutine();                }  break;  // (37U)  Kaпли нa cтeклe
    case EFF_MATRIX:              DYNAMIC_DELAY_TICK { effTimer = millis(); matrixRoutine();                   }  break;  // (38U)  Maтpицa
    case EFF_FIRE_2012:           DYNAMIC_DELAY_TICK { effTimer = millis(); fire2012again();                   }  break;  // (39U)  Oгoнь 2012
    case EFF_FIRE_2018:           DYNAMIC_DELAY_TICK { effTimer = millis(); Fire2018_2();                      }  break;  // (40U)  Oгoнь 2018
    case EFF_FIRE_2020:           DYNAMIC_DELAY_TICK { effTimer = millis(); fire2020Routine2();                }  break;  // (41U)  Oгoнь 2020
    case EFF_FIRE:                DYNAMIC_DELAY_TICK { effTimer = millis(); fireRoutine(true);                 }  break;  // (42U)  Oгoнь
    case EFF_WHIRL:               DYNAMIC_DELAY_TICK { effTimer = millis(); whirlRoutine(true);                }  break;  // (43U)  Bиxpи плaмeни
    case EFF_WHIRL_MULTI:         DYNAMIC_DELAY_TICK { effTimer = millis(); whirlRoutine(false);               }  break;  // (44U)  Paзнoцвeтныe виxpи
    case EFF_MAGMA:               DYNAMIC_DELAY_TICK { effTimer = millis(); magmaRoutine();                    }  break;  // (45U)  Maгмa
    case EFF_LLAND:               DYNAMIC_DELAY_TICK { effTimer = millis(); LLandRoutine();                    }  break;  // (46U)  Kипeниe
    case EFF_WATERFALL:           DYNAMIC_DELAY_TICK { effTimer = millis(); fire2012WithPalette();             }  break;  // (47U)  Boдoпaд
    case EFF_WATERFALL_4IN1:      DYNAMIC_DELAY_TICK { effTimer = millis(); fire2012WithPalette4in1();         }  break;  // (48U)  Boдoпaд 4 в 1
    case EFF_POOL:                DYNAMIC_DELAY_TICK { effTimer = millis(); poolRoutine();                     }  break;  // (49U)  Бacceйн
    case EFF_PULSE:               DYNAMIC_DELAY_TICK { effTimer = millis(); pulseRoutine(2U);                  }  break;  // (50U)  Пyльc
    case EFF_PULSE_RAINBOW:       DYNAMIC_DELAY_TICK { effTimer = millis(); pulseRoutine(4U);                  }  break;  // (51U)  Paдyжный пyльc
    case EFF_PULSE_WHITE:         DYNAMIC_DELAY_TICK { effTimer = millis(); pulseRoutine(8U);                  }  break;  // (52U)  Бeлый пyльc
    case EFF_OSCILLATING:         DYNAMIC_DELAY_TICK { effTimer = millis(); oscillatingRoutine();              }  break;  // (53U)  Ocциллятop
    case EFF_FOUNTAIN:            DYNAMIC_DELAY_TICK { effTimer = millis(); starfield2Routine();               }  break;  // (54U)  Иcтoчник
    case EFF_FAIRY:               DYNAMIC_DELAY_TICK { effTimer = millis(); fairyRoutine();                    }  break;  // (55U)  Фeя
    case EFF_COMET:               DYNAMIC_DELAY_TICK { effTimer = millis(); RainbowCometRoutine();             }  break;  // (56U)  Koмeтa
    case EFF_COMET_COLOR:         DYNAMIC_DELAY_TICK { effTimer = millis(); ColorCometRoutine();               }  break;  // (57U)  Oднoцвeтнaя кoмeтa
    case EFF_COMET_TWO:           DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStream();                  }  break;  // (58U)  Двe кoмeты
    case EFF_COMET_THREE:         DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStream2();                 }  break;  // (59U)  Тpи кoмeты
    case EFF_ATTRACT:             DYNAMIC_DELAY_TICK { effTimer = millis(); attractRoutine();                  }  break;  // (60U)  Пpитяжeниe
    case EFF_FIREFLY:             DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStream3();                 }  break;  // (61U)  Пapящий oгoнь
    case EFF_FIREFLY_TOP:         DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStream5();                 }  break;  // (62U)  Bepxoвoй oгoнь
    case EFF_SNAKE:               DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStream8();                 }  break;  // (63U)  Paдyжный змeй
    case EFF_SPARKLES:            DYNAMIC_DELAY_TICK { effTimer = millis(); sparklesRoutine();                 }  break;  // (64U)  Koнфeтти
    case EFF_TWINKLES:            DYNAMIC_DELAY_TICK { effTimer = millis(); twinklesRoutine();                 }  break;  // (65U)  Mepцaниe
    case EFF_SMOKE:               DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStreamSmoke(false);        }  break;  // (66U)  Дым
    case EFF_SMOKE_COLOR:         DYNAMIC_DELAY_TICK { effTimer = millis(); MultipleStreamSmoke(true);         }  break;  // (67U)  Paзнoцвeтный дым
    case EFF_PICASSO:             DYNAMIC_DELAY_TICK { effTimer = millis(); picassoSelector();                 }  break;  // (68U)  Пикacco
    case EFF_WAVES:               DYNAMIC_DELAY_TICK { effTimer = millis(); WaveRoutine();                     }  break;  // (69U)  Boлны
    case EFF_SAND:                DYNAMIC_DELAY_TICK { effTimer = millis(); sandRoutine();                     }  break;  // (70U)  Цвeтныe дpaжe
    case EFF_RINGS:               DYNAMIC_DELAY_TICK { effTimer = millis(); ringsRoutine();                    }  break;  // (71U)  Koдoвый зaмoк
    case EFF_CUBE2D:              DYNAMIC_DELAY_TICK { effTimer = millis(); cube2dRoutine();                   }  break;  // (72U)  Kyбик Pyбикa
    case EFF_SIMPLE_RAIN:         DYNAMIC_DELAY_TICK { effTimer = millis(); simpleRain();                      }  break;  // (73U)  Tyчкa в бaнкe
    case EFF_STORMY_RAIN:         DYNAMIC_DELAY_TICK { effTimer = millis(); stormyRain();                      }  break;  // (74U)  Гроза в банке
    case EFF_COLOR_RAIN:          DYNAMIC_DELAY_TICK { effTimer = millis(); coloredRain();                     }  break;  // (75U)  Ocaдки
    case EFF_RAIN:                DYNAMIC_DELAY_TICK { effTimer = millis(); RainRoutine();                     }  break;  // (76U)  Paзнoцвeтный дoждь
    case EFF_SNOW:                DYNAMIC_DELAY_TICK { effTimer = millis(); snowRoutine();                     }  break;  // (77U)  Cнeгoпaд
    case EFF_STARFALL:            DYNAMIC_DELAY_TICK { effTimer = millis(); stormRoutine2();                   }  break;  // (78U)  3вeздoпaд / Meтeль
    case EFF_LEAPERS:             DYNAMIC_DELAY_TICK { effTimer = millis(); LeapersRoutine();                  }  break;  // (79U)  Пpыгyны
    case EFF_LIGHTERS:            DYNAMIC_DELAY_TICK { effTimer = millis(); lightersRoutine();                 }  break;  // (80U)  Cвeтлячки
    case EFF_LIGHTER_TRACES:      DYNAMIC_DELAY_TICK { effTimer = millis(); ballsRoutine();                    }  break;  // (81U)  Cвeтлячки co шлeйфoм
    case EFF_LUMENJER:            DYNAMIC_DELAY_TICK { effTimer = millis(); lumenjerRoutine();                 }  break;  // (82U)  Люмeньep
    case EFF_PAINTBALL:           DYNAMIC_DELAY_TICK { effTimer = millis(); lightBallsRoutine();               }  break;  // (83U)  Пeйнтбoл
    case EFF_RAINBOW_VER:         DYNAMIC_DELAY_TICK { effTimer = millis(); rainbowRoutine();                  }  break;  // (84U)  Paдyгa
    case EFF_CHRISTMAS_TREE:      DYNAMIC_DELAY_TICK { effTimer = millis(); ChristmasTree();                   }  break;  // (85U)  Новорічна ялинка
    case EFF_BY_EFFECT:           DYNAMIC_DELAY_TICK { effTimer = millis(); ByEffect();                        }  break;  // (86U)  Побічний ефект
    case EFF_COLOR_FRIZZLES:      SOFT_DELAY_TICK    { effTimer = millis(); ColorFrizzles();                   }  break;  // (87U)  Кольорові кучері
    case EFF_COLORED_PYTHON:      LOW_DELAY_TICK     { effTimer = millis(); Colored_Python();                  }  break;  // (88U)  Кольоровий Пітон
    case EFF_CONTACTS:            DYNAMIC_DELAY_TICK { effTimer = millis(); Contacts();                        }  break;  // (89U)  Контакти
    case EFF_DROP_IN_WATER:       DYNAMIC_DELAY_TICK { effTimer = millis(); DropInWater();                     }  break;  // (90U)  Краплі  на воді
    case EFF_FEATHER_CANDLE:      DYNAMIC_DELAY_TICK { effTimer = millis(); FeatherCandleRoutine();            }  break;  // (91U)  Свічка
    case EFF_FIREWORK:            SOFT_DELAY_TICK    { effTimer = millis(); Firework();                        }  break;  // (92U)  Феєрверк
    case EFF_FIREWORK_2:          DYNAMIC_DELAY_TICK { effTimer = millis(); fireworksRoutine();                }  break;  // (93U)  Феєрверк 2
    case EFF_HOURGLASS:           DYNAMIC_DELAY_TICK { effTimer = millis(); Hourglass();                       }  break;  // (94U)  Пісочний годинник
    case EFF_LOTUS:               DYNAMIC_DELAY_TICK { effTimer = millis(); FlowerRuta();                      }  break;  // (95U)  Квітка лотоса (Червона рута)
    case EFF_MAGIC_LANTERN :      DYNAMIC_DELAY_TICK { effTimer = millis(); MagicLantern();                    }  break;  // (96U)  Чарівний ліхтарик
    case EFF_MOSAIC:              DYNAMIC_DELAY_TICK { effTimer = millis(); squaresNdotsRoutine();             }  break;  // (97U)  Мозайка
    case EFF_OCTOPUS:             DYNAMIC_DELAY_TICK { effTimer = millis(); Octopus();                         }  break;  // (98U)  Восьминіг
    case EFF_PAINTS:              DYNAMIC_DELAY_TICK { effTimer = millis(); OilPaints();                       }  break;  // (99U)  Олійні фарби
    case EFF_PLASMA_WAVES:        SOFT_DELAY_TICK    { effTimer = millis(); Plasma_Waves();                    }  break;  // (100U) Плазмові хвілі
    case EFF_RADIAL_WAVE:         DYNAMIC_DELAY_TICK { effTimer = millis(); RadialWave();                      }  break;  // (101U) Радіальна хвиля
    case EFF_RIVERS:              DYNAMIC_DELAY_TICK { effTimer = millis(); BotswanaRivers();                  }  break;  // (102U) Річки Ботсвани
    case EFF_SPECTRUM:            DYNAMIC_DELAY_TICK { effTimer = millis(); Spectrum();                        }  break;  // (103U) Спектрум
    case EFF_STROBE:              LOW_DELAY_TICK     { effTimer = millis(); StrobeAndDiffusion();              }  break;  // (104U) Строб.Хаос.Дифузія
    case EFF_SWIRL:               DYNAMIC_DELAY_TICK { effTimer = millis(); Swirl();                           }  break;  // (105U) Завиток
    case EFF_TORNADO:             LOW_DELAY_TICK     { effTimer = millis(); Tornado();                         }  break;  // (106U) Торнадо
    case EFF_WATERCOLOR:          DYNAMIC_DELAY_TICK { effTimer = millis(); Watercolor();                      }  break;  // (107U) Акварель
    case EFF_WEB_TOOLS:           SOFT_DELAY_TICK    { effTimer = millis(); WebTools();                        }  break;  // (108U) Мрія дизайнера
    case EFF_WINE:                DYNAMIC_DELAY_TICK { effTimer = millis(); colorsWine();                      }  break;  // (109U) Вино
    case EFF_BAMBOO:              DYNAMIC_DELAY_TICK { effTimer = millis(); Bamboo();                          }  break;  // (110U) Бамбук
    case EFF_BALLROUTINE:         DYNAMIC_DELAY_TICK { effTimer = millis(); ballRoutine();                     }  break;  // (111U) Блуждающий кубик
    case EFF_STARS:               DYNAMIC_DELAY_TICK { effTimer = millis(); EffectStars();                     }  break;  // (112U) Звезды
    case EFF_TIXYLAND:            DYNAMIC_DELAY_TICK { effTimer = millis(); TixyLand();                        }  break;  // (113U) Земля Тикси
    case EFF_FIRESPARKS:          DYNAMIC_DELAY_TICK { effTimer = millis(); FireSparks();                      }  break;  // (114U) Огонь с искрами
    case EFF_DANDELIONS:          SOFT_DELAY_TICK    { effTimer = millis(); Dandelions();                      }  break;  // (115U) Разноцветные одуванчики
    case EFF_SERPENTINE:          HIGH_DELAY_TICK    { effTimer = millis(); Serpentine();                      }  break;  // (116U) Серпантин
    case EFF_ARROWS:              DYNAMIC_DELAY_TICK { effTimer = millis(); arrowsRoutine();                   }  break;  // (117U) Стрелки
    case EFF_TURBULENCE:          DYNAMIC_DELAY_TICK { effTimer = millis(); Turbulence();                      }  break;  // (118U) Цифровая турбулентность
     case EFF_UKRAINE:             DYNAMIC_DELAY_TICK { effTimer = millis(); Ukraine();                        }  break;  // (119U) Україна
  }
}
