
/*******************************************************************************
* generated by lcd-image-converter rev.4d43872 from 2022-06-23 22:11:57 +0500
* image
* filename: /home/void/Documents/Wiring/Information for ePaper/pixelated icons/Temp Sign *.xml
* name: Temperature Sign
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Diffuse Dither 0
* split to rows: yes
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: yes
*******************************************************************************/

 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
#include <stdint.h>

static const uint8_t image_data_TemperatureSign_Positive[36] = {/*
    ∙∙∙███∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙
    ∙∙∙███∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙
    ∙∙∙███∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙
    █████████∙∙∙∙███∙∙█∙█∙█∙█∙█
    █████████∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙
    █████████∙∙███∙∙∙∙█∙█∙█∙█∙█
    ∙∙∙███∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    ∙∙∙███∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    ∙∙∙███∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙*/
    0x1c, 0x00, 0xc0, 0x00,
    0x1c, 0x01, 0xc0, 0x00, 
    0x1c, 0x03, 0x80, 0x00,
    0xff, 0x87, 0x2a, 0xa0, 
    0xff, 0x8e, 0x00, 0x00,
    0xff, 0x9c, 0x2a, 0xa0, 
    0x1c, 0x38, 0x00, 0x00,
    0x1c, 0x70, 0x00, 0x00, 
    0x1c, 0x60, 0x00, 0x00
};
const tImage TemperatureSign_Positive = { image_data_TemperatureSign_Positive, 27, 9,
    8 };

static const uint8_t image_data_TemperatureSign_Negative[36] = {/*
    ∙∙∙█∙█∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙∙
    ∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙
    ∙∙∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙
    █∙∙█∙█∙∙█∙∙∙∙███∙∙█████████
    ∙∙∙∙∙∙∙∙∙∙∙∙███∙∙∙█████████
    █∙∙█∙█∙∙█∙∙███∙∙∙∙█████████
    ∙∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    ∙∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙
    ∙∙∙█∙█∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙*/
    0x14, 0x00, 0xc0, 0x00,
    0x00, 0x01, 0xc0, 0x00, 
    0x00, 0x03, 0x80, 0x00,
    0x94, 0x87, 0x3f, 0xe0, 
    0x00, 0x0e, 0x3f, 0xe0,
    0x94, 0x9c, 0x3f, 0xe0, 
    0x00, 0x38, 0x00, 0x00,
    0x00, 0x70, 0x00, 0x00, 
    0x14, 0x60, 0x00, 0x00
};
const tImage TemperatureSign_Negative = { image_data_TemperatureSign_Negative, 27, 9,
    8 };