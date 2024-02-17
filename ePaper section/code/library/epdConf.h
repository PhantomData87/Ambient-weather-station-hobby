/**
  ******************************************************************************
    @file     epdConf.h
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     02-January-2024
    @modified 16-Feburary-2024
    @brief    Custom combination & Simplification of all of the manufacturor's exisitng code
    @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere
*/

#ifndef epdConf_h
#define epdConf_h
#include <Arduino.h>
#include "fonts.h"
#include "image.h" // I do not mind if you remove this and replace it with a different class

/*

   Parameters to Change

*/

// Pin definition (Change them at will)
#define RST_PIN         9 // 7 // (Schematic reference)
#define DC_PIN          12 // 8
#define CS_PIN          11 // 6
#define BUSY_PIN        10 // 4
#define PWR_PIN         7 // 9 // To easily power off the screen without anything physical

// Display resolution
#define EPD_WIDTH       200
#define EPD_HEIGHT      200

/*

   Class epd. Where most of this is inspired from the original

*/

class epd {
  public:
    // Practical c++ setup
    epd(bool xRot = false, bool yRot = false);
    ~epd();

    // Main functions
    void drawCharArray(unsigned int xStart, unsigned int yStart, unsigned char* string, unsigned int arraySize, info* font);
    void drawRectangleArea(unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height);
    void drawCircle(unsigned int xStart, unsigned int yStart, unsigned int radius, unsigned int additionalThickness = 0);
    void drawImage(unsigned int xStart, unsigned int yStart, info* info, int offsetImage = 0);

    // Helper functions
    unsigned int numToIndex(unsigned int num);
    unsigned int bitDeclare(unsigned int num, unsigned int iter, bool color); // We will flip a bit, and it will be flip it to a 1 if non-color, 0 if it's colored
    uint8_t reverseBits(uint8_t bits);
    float distance(unsigned int x, unsigned int y);

    // General utilities
    void turnOn();
    void wait();
    void turnOff();
    void displayFrame(); // Calls for most recent memory area changed to display, than it switches to the next area. Perfectly identifical to "DisplayPartFrame", except for c7 & cF. Uses command 0xcF for partial instead of 0xc7 for full
    void sleepScreen(); // To conserve power, this is not just a delay()
    void awakeScreen(); // This comes from edp::reset(), used to wake device
    void clearScreen(); // Clears the screen, uses 0x24 & 0x26

    // Functions to invert boolean values
    void invertColorSelection(); // Switches and alternatives between alternating pixel colors
    void changeRefreshType(); // Will alternate between full & partial refresh automatically
    void switchXRotation(); // Switches and alternatives between axis X rotation
    void switchYRotation(); // Switches and alternatives between axis Y rotation
    void switchFilled(); // Switches and alternatives between if we want our shapes filled or not

  protected:
    // Retrieve boolean values
    bool getXRotation(); // See if we have x rotation or not
    bool getYRotation(); // See if we have y rotation or not
    bool getFilled(); // See if we are requesting shapes to be filled or not
    bool getRefreshFull(); // Are we doing full refresh or not?
    bool getChannelHigh(); // Are we using high or low channel?
    bool getInversedColor(); // Are we inverting colors?

  private:
    // Low level functions to handle the combinations of data that must be sent in a specific order (per documentation & guidelines)
    void wireChannel(); // From EDP::LDirInit() & EDP::HDirInit() and make it more easier to read. Since Init is really misleading

    void drawPrep(int x, int y, int width, int height);
    void setMemoryArea(int x_start, int y_start, int x_end, int y_end);
    void setMemoryPointer(int x, int y);

    // Directly communicating with the device
    void spiTransfer(unsigned char let);
    void spiCommand(unsigned char command); // Sends a specific SPI command
    void spiData(unsigned char dataGiven); // After SPI command was used, may be improved upon
    void lut(unsigned char* lut);
    void setLut(unsigned char* lut);

    // Pins
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
    unsigned int pwr_pin;

    // Private values
    unsigned int screenWidth; // Also known as the physical limitations our screen has
    unsigned int screenHeight; // Also known as the physical limitations our screen has
    unsigned int canvasWidthEnd; // In the arduino I am unable to return more than one variable.
    unsigned int canvasHeightEnd; // In the arduino I am unable to return more than one variable.
    bool xRotation = false; // This is going to be painful
    bool yRotation = false;
    bool invertColor = false; // This determines the color of the screen. False is black pixel, true is opposite which would be white
    bool filledShapes = false; // When painting a custom shape, have it declared if it's filled or not
    bool channelHigh = false; // Controlled mainly by our drawing functions and not necesarelly for the user to control outside of the class
    bool refreshFull = true;
};

/*/ Other notes;
 * Why combined LDirInit() & HDirInit()
  For why it's called "wireChannel()" instead of "xDirInit()". Well I do have the following theory when seeing the original code:
  int LDirInit(); This refers that it will use MOSI & MISO. Also known as 4 line. Also known for making BS1 to LOW. This one dictates that the top of the wires are near origen. Where as closer to the ribbon is near max. Finally, it's left to right for the x-axis number line
  int HDirInit(); This refers that it will use MOSI. Also known as 3 line. Also, it uses 9 bit SPI? Also known for making BS1 to HIGH
  Thus isolate the changes that declare 8 or 9 bit SPI reading/writing, and boom, a single function.

  * Why use "this->" so much in the code? For readability of when something came from the class, and when something came from another class/function that I hadn't made.
*/
#endif
