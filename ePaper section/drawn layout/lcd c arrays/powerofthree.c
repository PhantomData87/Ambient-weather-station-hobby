
/*******************************************************************************
* generated by lcd-image-converter rev.4d43872 from 2022-06-23 22:11:57 +0500
* image
* filename: /home/void/Documents/Wiring/Information for ePaper/pixelated icons (second attempt)/powerofthree.xml
* name: powerofthree
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

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_powerofthree[5] = {/*
    ███∙
    ∙∙∙█
    ∙██∙
    ∙∙∙█
    ███∙*/
    0xe0,
    0x10, 
    0x60,
    0x10,
    0xe0
};
const tImage powerofthree = { image_data_powerofthree, 4, 5,
    8 };