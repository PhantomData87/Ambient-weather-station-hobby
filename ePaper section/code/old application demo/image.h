/**
  ******************************************************************************
  * @file    image.h
  * @author  Alonzo Ortiz-Sanchez
  * @version V1.0.0
  * @date    03-January-2024
  * @brief   Header for image.c
  * @note    Feel free to modify. I don't expect my crummy pixel art to be used and do not mind so
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IMAGE_H
#define __IMAGE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

typedef struct {
     const uint8_t *table;
     uint8_t width;
     uint8_t height;
} tImage;

extern tImage Aqi; // 3 Images &  Assumes we have already defined it
extern tImage Battery; // 6 Images
extern tImage Internet; // 2 Images
extern tImage Humidity; // 3 Images
extern tImage Sky; // 5 Images
extern tImage Temperature; // 3 Images
extern tImage TempSign; // 2 Images
extern tImage TemperatureWarn; // 2 Images
extern tImage Trend; // 2 Images

#ifdef __cplusplus
}
#endif
  
#endif /* __IMAGE_H */
