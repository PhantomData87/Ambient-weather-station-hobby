/**
  ******************************************************************************
  * @file     image.h
  * @author   Alonzo Ortiz-Sanchez
  * @version  V1.0.0
  * @made     19-Feburary-2024
  * @modified 19-Feburary-2024
  * @brief    Header of icon.c
  * @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere
  */

#ifndef __ICON_H
#define __ICON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "fonts.h"

extern info iconBarometer; // 5 Images
extern info iconBattery; // 6 Images
extern info iconTrend; // 2 Images
extern info iconTrendWord; // 1 Image
extern info iconPower; // 1 Image

#ifdef __cplusplus
}
#endif

#endif /* __ICON_H */
