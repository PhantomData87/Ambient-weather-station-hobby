/**
  ******************************************************************************
  * @file     image.h
  * @author   Alonzo Ortiz-Sanchez
  * @version  V1.0.0
  * @made     03-January-2024
  * @modified 16-Feburary-2024
  * @brief    Header of image.c
  * @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere
  */

#ifndef __IMAGE_H
#define __IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "fonts.h"

extern info Battery; // 6 Images & Assumes we have already defined it
extern info Humidity; // 3 Images
extern info Sky; // 5 Images
extern info Temperature; // 3 Images
extern info TempSign; // 2 Images
extern info TemperatureWarn; // 2 Images
extern info Trend; // 2 Images

#ifdef __cplusplus
}
#endif

#endif /* __IMAGE_H */
