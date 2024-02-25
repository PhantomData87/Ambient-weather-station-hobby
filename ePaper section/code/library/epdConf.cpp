/**
  ******************************************************************************
    @file     epdConf.cpp
    @author   Alonzo Ortiz-Sanchez
    @version  V1.1.0
    @made     02-January-2024
    @modified 24-Feburary-2024
    @brief    The combination and interlinkedness of "epd1in54_V2", "epdif", and "epdpaint"
    @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere.
    @warning  Any comments left over that "seem" meaningless are left since I encountered odd cases from neglecting them.
*/

#include "epdConf.h"
#include <SPI.h>
/*

     Waveform's special arrays

*/

// waveform full refresh registrar arrays
unsigned char WF_Full_1IN54[159] =
{
  0x80, 0x48, 0x40, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x40, 0x48, 0x80, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x80, 0x48, 0x40, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x40, 0x48, 0x80, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0xA,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x8,  0x1,  0x0,  0x8,  0x1,  0x0,  0x2,
  0xA,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0,  0x0,  0x0,
  0x22, 0x17, 0x41, 0x0,  0x32, 0x20
};

// waveform partial refresh(fast) registrar arrays
unsigned char WF_PARTIAL_1IN54_0[159] =
{
  0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
  0x02, 0x17, 0x41, 0xB0, 0x32, 0x28,
};

/*

   Preparation for the main class

*/

// Here we are setting values based on what has been pre-defined & declared.
epd::epd(bool xRot, bool yRot) {
  this->screenWidth = EPD_WIDTH;
  this->screenHeight = EPD_HEIGHT;
  this->reset_pin = RST_PIN;
  this->dc_pin = DC_PIN;
  this->cs_pin = CS_PIN;
  this->busy_pin = BUSY_PIN;
  this->pwr_pin = PWR_PIN;
  this->xRotation = xRot;
  this->yRotation = yRot;
};

// A destructor, just in case
epd::~epd() {
  this->turnOff();
};

/*

   High level functions to draw on the screen. Also can be recognized as "main functions"

*/

// This function will take a Unsigned Integer array & translate it to pixels on the screen. Has built in inversing, rotation, and basic error preventing.
void epd::drawCharArray(unsigned int xStart, unsigned int yStart, unsigned char* string, unsigned int arraySize, info* font) {
  // Ensuring you are using the "correct" rotation. Feel free to change "channelHigh" to something else
  if (this->channelHigh == true) {
    this->channelHigh = false;
    this->wireChannel();
  }

  // Count the number of characters & start preparing. We are measuing bytes here
  unsigned int widthOfChar = (font->Width / 8) + ((font->Width % 8 == 0) ? 0 : 1); // For readability, and has become a multiple of 8
  unsigned int bitOffset = xStart % 8; // When we are unable to obtain a precisely placed multiple of 8
  unsigned int width = widthOfChar * arraySize;
  unsigned int height = font->Height;
  this->drawPrep(xStart, yStart, (8 * width), height);

  // Safety for drawing. I assume no one would be dumb enough to pick a initial position in the negatives.
  if (this->canvasWidthEnd == this->screenWidth - 1) {
    for (int i = xStart + (8 * width) - 1; i > this->screenWidth; i -= 8) {
      width -= 1;
    }
  }
  if (this->canvasHeightEnd == this->screenHeight - 1) {
    for (int i = yStart + height - 1; i > this->screenHeight; i -= 1) {
      height -= 1;
    }
  }

  // Get ready for things. Now we consider rotation
  int xCounter = 1;
  int xBegin = 0;
  if (this->xRotation) {
    xCounter = -1;
    xBegin = width - 1; // Since it's inversed. We want it to begin at the very end
  }

  int yCounter = 1;
  int yBegin = 0;
  if (this->yRotation) {
    yCounter = -1;
    yBegin = height - 1; // Since it's inversed. We want it to begin at the very end
  }

  // First. We use the height of the characters to easily manipulate the bytes to be sent. We define "which bit" on the "screen's byte" we starting. And setting up which character we are indexing
  // Do recall: This is a abtract for sending a stream of bytes to the screen.
  for (int j = yBegin; (j < height and not this->yRotation) || (j >= 0 and this->yRotation); j += yCounter) {
    int widthCounter = this->xRotation ? widthOfChar - 1 : 0; // Setting this to unsigned int makes it be registered as 65535 instead of just 0.
    unsigned int charCounter = this->xRotation ? arraySize - 1 : 0;
    byte charLeft = 0x00;
    byte charRight = 0x00;
    // Second. We are counting in bytes, but we may require to manipulate the individual bits to account for any non-multiple of 8 starting position; On the x-axis.
    // It should be noted, we need to count both the "character's width" and the "string's width"
    for (int i = xBegin; (i < width and not this->xRotation) || (i >= 0 and this->xRotation); i += xCounter) {
      // Obtain character from FLASH. By using pgm_read_byte
      int charOffset = ((string[charCounter] - ' ') * height * widthOfChar); // Map the char to the font table provided
      byte charRetrieved = pgm_read_byte(&(font->table[charOffset + widthOfChar * j + widthCounter])); // It appears the fonts are the opposite of what they should be

      // Consider xRotation
      if (this->xRotation) {
        charRetrieved = this->reverseBits(charRetrieved); // Flip the bits around
      }

      // Do pixel adjustments
      charLeft = charRight + (charRetrieved >> bitOffset); // Shift by how much of an offset it is, and lose that many bits to the right. Then fill in the extra bits with 1 or 0
      charRight = (charRetrieved << (8 - bitOffset)); // Shift by how much of an offset it is, and lose that many bits to the left. Then fill in the extra bits with 1 or 0

      // Consider inverse. When printing it should be black text and white background when it's normal. Otherwise it's left inverted
      charLeft = charLeft ^ (this->invertColor ? 0x00 : 0xFF);

      // Sending byte
      this->spiData(charLeft);

      // Detect the edge of the individual letter
      widthCounter += xCounter;
      if (((widthCounter == widthOfChar) and not this->xRotation) or ((widthCounter < 0) and this->xRotation)) { // Considers x rotation
        widthCounter = this->xRotation ? widthOfChar - 1 : 0;
        charCounter += xCounter;
      }
    }
    // For our left/right most byte to be sent last. Unless we neved used that byte in which case we ignore
    if (bitOffset > 0 ) {
      charRight = charRight ^ (this->invertColor ? 0x00 : 0xFF); // Consider a inverse
      this->spiData(charRight); // Do 0x02 to test if it's drawing a line at the very end
    }
  }
  this->wait();
}

// This function will draw a rectangle of any size specified. We are measuing here more in bits than bytes. Has basic error protection, and inverse support
void epd::drawRectangleArea(unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height) {
  // Ensuring you are using the "correct" rotation. Feel free to change "channelHigh" to something else
  if (this->channelHigh == true) {
    this->channelHigh = false; // I assume an image wants 8 bits of data, right?
    this->wireChannel(); // Wouldn't want to keep calling this unless I need too
  }

  // Get ready
  this->drawPrep(xStart, yStart, width + (xStart % 8), height);
  bool northSouthSide = false; // Used to differentiate when we are drawing a straight line, and when we are drawing a border
  bool color = false; // For readability it's left as a variable.

  // Safety for drawing. I assume no one would be dumb enough to pick a initial position in the negatives.
  if (this->canvasWidthEnd == this->screenWidth - 1) {
    for (int i = xStart + width; i > this->screenWidth; i -= 1) {
      width -= 1;
    }
  }
  if (this->canvasHeightEnd == this->screenHeight - 1) {
    for (int i = yStart + height - 1; i > this->screenHeight; i -= 1) {
      height -= 1;
    }
  }

  // First we use a similar abtract like drawing a string. However this time we are just simply sending a stream of bits that are converted to bytes.
  // We heavily rely on "singleByte" and "widthCounter" to ensure that we can modify the screen & correctly adjust for non-multiple of 8 starting values in the x-axis.
  for (int j = 0; j < height; j += 1) {
    unsigned int singleByte = 0xFF;
    unsigned int widthCounter = xStart % 8;
    northSouthSide = (j == 0 or j == height - 1) ? true : false;
    for (int i = 0; i < width; i += 1) {
      // Detect the next color of the bit
      color = (this->filledShapes or northSouthSide or i == 0 or i == width - 1) ? true : false;
      singleByte = this->bitDeclare(singleByte, widthCounter, color); // Where inversing can occur

      // Consider if we have reached the end of a "byte" length
      widthCounter = ((widthCounter + 1) % 8);
      if ((xStart + i + 1) % 8 == 0) {
        this->spiData(singleByte);
        singleByte = 0xFF; // Representing white on everything
      }
    }
    // Send the remaining data, unless it's already empty since we never adjusted for x-axis positioning
    if (widthCounter > 0) {
      this->spiData(singleByte);
    }
  }
  this->wait();
}

// Since we lack an array. We will not use a efficient algorithm for drawing a circle. Since drawing on this screen requires acknolwedging every bit. Since we canot keeping track we will use a more bruteforce approach
// We are measuing in bits that are converted to bytes. Their is basic protection for errors in positioning, and has inversing support.
void epd::drawCircle(unsigned int x, unsigned int y, unsigned int radius, unsigned int additionalThickness) {
  // No need to consider Rotation
  if (this->channelHigh == true) {
    this->channelHigh = false; // I assume an image wants 8 bits of data, right?
    this->wireChannel(); // Wouldn't want to keep calling this unless I need too
  }

  // Get ready
  int realRadius = radius + additionalThickness;
  int circumference = (realRadius * 2) + 1;
  this->drawPrep(x, y, circumference, circumference); // Drawing a perfect circle

  // Safety for drawing. I assume no one would be dumb enough to pick a initial position in the negatives.
  int xOffset = 0;
  int yOffset = 0;
  bool sendLast = true;
  if (this->canvasWidthEnd == this->screenWidth - 1) {
    for (int i = x + circumference; i > this->screenWidth; i -= 1) {
      xOffset -= 1;
    }
    sendLast = false;
  }
  if (this->canvasHeightEnd == this->screenHeight - 1) {
    for (int i = y + circumference; i > this->screenHeight; i -= 1) {
      yOffset -= 1;
    }
  }

  // Proper circle drawing inspiration
  // Inspired initially from: https://stackoverflow.com/questions/38843226/how-to-draw-a-circle-with-stars-in-c
  // Proper circle drawing for filling & interior https://stackoverflow.com/questions/70722545/draw-circle-in-console-using-python
  for (int j = 0 - realRadius; j <= realRadius + yOffset; j += 1) {
    byte singleByte = 0xFF;
    int widthCounter = x % 8;
    int counter = 0; // Since our nested loop is not from the range of 0-n. We will rely on a different variable to serve that purpose
    bool color = false;
    for (int i = 0 - realRadius; i <= realRadius + xOffset; i += 1) {
      // Find the color
      color = (((this->filledShapes ? 0 : radius - 1) <= this->distance(i, j)) and (this->distance(i, j) <= realRadius)) ? true : false; // Do we include the inside of the circle <= answer <= is answer smaller or equal to "radius+additionalThickness"
      singleByte = this->bitDeclare(singleByte, widthCounter, color); // Where inversing can occur

      // Updating our counters & sending our byte if we can
      widthCounter = ((widthCounter + 1) % 8);
      if ((x + counter + 1) % 8 == 0) {
        this->spiData(singleByte);
        singleByte = 0xFF; // Representing white on everything
      }
      counter += 1;
    }
    // Send the remaining data. Unless we have less x-axis space than stated earlier
    if (sendLast) {
      this->spiData(singleByte);
    }
  }
  this->wait();
}

// Here we take an image that has been pre-made and stored in FLASH. We will account for x-axis positioning
void epd::drawImage(unsigned int xStart, unsigned int yStart, info* info, unsigned int offsetImage) {
  if (this->channelHigh == true) {
    this->channelHigh = false; // I assume an image wants 9 bits of data, right?
    this->wireChannel(); // Wouldn't want to keep calling this unless I need too
  }

  // Defined for redability
  int realWidth = (info->Width / 8) + ((info->Width % 8 == 0) ? 0 : 1);
  int width = (info->Width / 8) + ((info->Width % 8 == 0) ? 0 : 1);
  int height = info->Height;
  int bitOffset = xStart % 8; // When we are unable to obtain a precisely placed multiple of 8
  unsigned int offsetArea = offsetImage * width * height;

  // Get ready
  this->drawPrep(xStart, yStart, info->Width, height);

  // Safety for drawing. I assume no one would be dumb enough to pick a initial position in the negatives.
  if (this->canvasWidthEnd == this->screenWidth - 1) {
    for (int i = xStart + (width * 8) - 1; i > this->screenWidth; i -= 8) {
      width -= 1;
    }
  }
  if (this->canvasHeightEnd == this->screenHeight - 1) {
    for (int i = yStart + height - 1; i > this->screenHeight; i -= 1) {
      height -= 1;
    }
  }

  // Get ready for things. Now we consider rotation
  int xCounter = 1;
  int xBegin = 0;
  if (this->xRotation) {
    xCounter = -1;
    xBegin = width - 1; // Since it's inversed. We want it to begin at the end. We multiple by the array's size since we are concern here with characters
  }

  int yCounter = 1;
  int yBegin = 0;
  if (this->yRotation) {
    yCounter = -1;
    yBegin = height - 1; // Since it's inversed. We want it to begin at the very end
  }

  // Start with an abstract of the height. Where the height is in bits.
  for (int j = yBegin; (j < height and not this->yRotation) || (j >= 0 and this->yRotation); j += yCounter) {      
    byte charLeft = 0x00;
    byte charRight = 0x00;
    // Then obtain the character from FLASH storage by abstracting this as bytes.
    for (int i = xBegin; (i < width and not this->xRotation) || (i >= 0 and this->xRotation); i += xCounter) {    
      // Obtaining character from FLASH
      byte charRetrieved = pgm_read_byte(&(info->table[offsetArea + realWidth * j + i])); // Byte obtain goes against what the screen recognizes as a "black" or "white"

      // Consider xRotation:
      if (this->xRotation) {
        charRetrieved = this->reverseBits(charRetrieved); // Flip the bits around
      }

      // Do pixel adjustments
      charLeft = charRight + (charRetrieved >> bitOffset); // Shift by how much of an offset it is, and lose that many bits to the right. Then fill in the extra bits with 1 or 0
      charRight = (charRetrieved << (8 - bitOffset)); // Shift by how much of an offset it is, and lose that many bits to the left. Then fill in the extra bits with 1 or 0

      // Consider inverse. In my humble opinion, it should be considered normal black text and a white background. Otherwise it's left inverted if we wanted inverted text
      charLeft = charLeft ^ (this->invertColor ? 0x00 : 0xFF);

      // Sending byte
      this->spiData(charLeft);
    }
    // For our left/right most byte to be sent last. Unless we neved used that byte in which case we ignore
    if (bitOffset > 0) {
      charRight = charRight ^ (this->invertColor ? 0x00 : 0xFF); // Consider a inverse
      this->spiData(charRight); // Do 0x02 to test if it's drawing a line at the very end
    }
  }
  this->wait();
}

// A simple function that will round up a number to a multiple of 8, before dividing it by 8. So we can get the multiple of 8.
unsigned int epd::numToIndex(unsigned int num) {
  // Check if it's already a multiple of 8
  if (num == num & 0xF8) {
    return num / 8;
  }
  return (num / 8) + 1; // Otherwise, pressume it's close to being another multiple (Round up)
}

// Here we are deciding whether the byte we received needs a bit to be declared as "colored" or "non-colored".
unsigned int epd::bitDeclare(unsigned int num, unsigned int iter, bool color) {
  // We will flip based on the `color` bool. If it's true; we flip the bit to "0" for "colored-pixel". Otherwise we flip it to "1" to mark it as "non-colored" pixel.
  byte flipAssingment = 0x80 >> iter; // 0x80 = 10000000 in binary, we right logical shift it by our "iter" or essentially; we move that 1 to a specific position
  if ((color and not this->invertColor) or (not color and this->invertColor)) { // My version of exclusive OR
    num &= ~flipAssingment; // Enforce only one bit becomes a "0"
  }
  else {
    num |= flipAssingment; // We simply do a bitwise OR to enforce one bit to be a "1"
  }
  return num;
}

// Here we are simply reversing the order of bits in a byte. Used mainly for x-axis rotation
uint8_t epd::reverseBits(uint8_t bits) {
  uint8_t newBit = 0x00;
  // Will rotate the bits found in "bits"
  newBit = newBit | (bits << 7);
  newBit = newBit | ((bits & 0x02) << 5);
  newBit = newBit | ((bits & 0x04) << 3);
  newBit = newBit | ((bits & 0x08) << 1);
  newBit = newBit | ((bits & 0x10) >> 1);
  newBit = newBit | ((bits & 0x20) >> 3);
  newBit = newBit | ((bits & 0x40) >> 5);
  newBit = newBit | (bits >> 7);
  return newBit;
}

// Simple distance formula
float epd::distance(unsigned int x, unsigned int y) {
  return sqrt((x * x) + (y * y));
}
/*

   General utilities for our screen, and does some low level communication

*/

// Turns on the screen by declaring what each pin does. Followed by turning on the "pwr_pin". Initialize SPI, and start "wireChanne" so it's ready for communication
// This should not be confused with "awakeScreen()"
void epd::turnOn() {
  pinMode(this->cs_pin, OUTPUT);
  pinMode(this->reset_pin, OUTPUT);
  pinMode(this->dc_pin, OUTPUT);
  pinMode(this->busy_pin, INPUT);

  pinMode(this->pwr_pin, OUTPUT);
  digitalWrite(this->pwr_pin, 1);
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  this->channelHigh = false; // Begin in 4 wire mode. Can be changed if 3 wire mode is prefered.
  this->wireChannel();
}

// The manufacturor's "wait" function
void epd::wait() {
  while (digitalRead(this->busy_pin) == 1) {     //LOW: idle, HIGH: busy
    delay(100);
  }
  delay(200);
}

// We turn off the screen by simply awakening it, clearing it, and then sleeping it before cutting power
void epd::turnOff() {
  this->awakeScreen(); // In case it was already in "deep-sleep"
  this->clearScreen();
  delayMicroseconds(2); // Give time for this to fully occur
  this->sleepScreen();
  delayMicroseconds(2); // Give time for this to fully occur
  digitalWrite(this->pwr_pin, 0);
}

// Shows what has been stored in ram, and it's decided between either full or partial refresh.
void epd::displayFrame() { // Calls for most recent memory to display. Perfectly identifical to "DisplayPartFrame", except for c7 & cF. Uses command 0xcF for partial instead of 0xc7 for full refresh
  //DISPLAY REFRESH
  this->spiCommand(0x22); // Display update control 2
  this->spiData(this->refreshFull ? 0xc7 : 0xcF); // Binary; 11000111 vs 11001111. This disables INITIAL DISPLAY. Difference in A3
  this->spiCommand(0x20); // Master activation
  this->wait();
}

// This is similar in the act of tunring off the screen, but this one keeps the image & it's mainly used for conserving power.
// Requires "awakeScreen" from below to "undo" "sleeping" a screen.
void epd::sleepScreen() {
  this->spiCommand(0x10); //enter deep sleep
  this->spiData(0x01); // This declares deep sleep mode, and not normal mode [POR]
  delay(200);

  digitalWrite(this->reset_pin, LOW);
}

// This comes from Edp::reset(), used to wake device. Now this is used to "undo" sleepScreen()
void epd::awakeScreen() {
  delay(20);
  digitalWrite(this->reset_pin, HIGH); // Initialize wake up sequence
  delay(20);
  digitalWrite(this->reset_pin, LOW); //module reset
  delay(5);
  digitalWrite(this->reset_pin, HIGH);
  delay(20);
}

// Clears the screen back to a certain background, uses RAM command 0x24 for BW (Black,White) & RAM command 0x26 for RW (Red,White)
void epd::clearScreen() {
  // Make this more readable
  unsigned int side1, side2, area;
  side1 = this->numToIndex(this->screenWidth); // Needs to be in multiple of 8
  side2 = this->screenHeight; // Can be from 0-n
  area = side1 * side2; // For my 1.54 inch 200x200 screen, this should say 25x200 = 5000

  // Make the screen initialize once again. So it's ready to receive as many bits it can
  this->wireChannel();
  this->wait();

  // Send in "0xFF" to paint every byte as "white"
  this->spiCommand(0x24);
  for (int i = 0; i < area; i++) {
    this->spiData(0xff);
  }

  this->spiCommand(0x26);
  for (int i = 0; i < area; i++) {
    this->spiData(0xff); //
  }

  // Display what has been sent
  this->displayFrame();
}

/*

    Simple functions to invert our boolean values

*/

// Switches and alternatives betwene alternating pixel colors
void epd::invertColorSelection() {
  this->invertColor = this->invertColor ? false : true; // Flip flop
}

// Will alternate between full & partial refresh automatically by a simple bool value switched
void epd::changeRefreshType() {
  this->refreshFull = this->refreshFull ? false : true;
}

// Switches the bool value related to X-axis rotation
void epd::switchXRotation() {
  this->xRotation = this->xRotation ? false : true;
}

// Switches the bool value related to Y-axis rotation
void epd::switchYRotation() {
  this->yRotation = this->yRotation ? false : true;
}

// Switches the bool value related to filling up a custom shape
void epd::switchFilled() {
  this->filledShapes = this->filledShapes ? false : true;
}

/*

    A protected function that easily retrieves the current boolean value

*/

// Obtain the boolean values. Can be used for debugging
bool epd::getXRotation() {
  return this->xRotation;
}
bool epd::getYRotation() {
  return this->yRotation;
}
bool epd::getFilled() {
  return this->filledShapes;
}
bool epd::getRefreshFull() {
  return this->refreshFull;
}
bool epd::getChannelHigh() {
  return this->channelHigh;
}
bool epd::getInversedColor() {
  return this->invertColor;
}

/*

    A much more low level functions that do all the heavy lifting. They follow a specific order and communicate to the device on their own sometimes

*/

// The function that permits for anything to happen for all. A lot of comments will be here for understanding the chaos that is below
// This function accounts for "LDirInit()" & "HDirInit". However, with some tinkering and reading of the official documentation. One can modify & simplify this to suit their own needs.
// This function declares the "LUT" values, how to read bytes sent, proper initialization of the screen based on documentaion & manufacturor code, and finally highlighting "mysterious" code.
void epd::wireChannel() { // channelHigh = 0 = low, otherwise it's high
  // Wires are already turned on

  // Request the EPD hardware to awaken
  this->awakeScreen();

  // Start by SWRESET
  this->spiCommand(0x12);  // SWRESET
  this->wait(); // Wait until it has been processed

  // Declare Driver output control (THIS CHANGES BASED ON channelHigh)
  this->spiCommand(0x01); // Driver output control
  this->spiData(0xC7);
  this->spiData(0x00);
  this->spiData(this->channelHigh ? 0x01 : 0x00); // High : Low, 9bit or 8bit channel? 3 line or 4 line? It also declares some "Gate Settings". This 1 mode indicates to read from G299-G0, instead of the opposite.

  // Declare how to read data from our spi data sent (THIS CHANGES BEASED ON channelHigh)
  this->spiCommand(0x11); //data entry mode
  this->spiData(this->channelHigh ? 0x01 : 0x03); // This declares how to treat Y & X. Essentially how to update counter. Here we update from Y decrement, X increment.

  // Declare how, where, start, end, and size of X & Y ram arrays. (THIS CHANGES BEASED ON channelHigh)
  this->setMemoryArea(0, this->channelHigh ? 0xC7 : 0, /*this->channelHigh ? 0x18 :*/ 199, this->channelHigh ? 0 : 199); /* Unsure why this is changed, since it would be more reasonable to have them all start and end from 0 to 199 on both X & Y.
                x_start,                      y_start,                              x_end,                       y_end
    0xc7 = 199, 0x18 = 24, and why not use 199 instead of 24? What were the manufacturer on?
*/

  // Declare the "Borderwaveform, and the next one enables the GS1 Entry
  this->spiCommand(0x3C); //BorderWavefrom
  this->spiData(0x01); // I think this is to enable GS1 entry

  // Unknown
  this->spiCommand(0x18); // Undocumented
  this->spiData(0x80);

  // Temperature and waveform setting loading
  this->spiCommand(0x22); // Load Temperature and waveform setting.
  this->spiData(0XB1); // This declares what parts of the screen should it initialize & some of its behavior
  this->spiCommand(0x20); // Master activation; Display update sequence

  // Declare X & Y pointers
  this->setMemoryPointer(0, 0xC7); // Very important, it's how the internal ram keeps track of it's pointer

  // Finally, update registers to what we want
  this->setLut(WF_Full_1IN54);
}

// This is by far the second most important function. It defines "how" large of an area of "bytes" we are changing, the type of "refresh" from the screen, error correction,
// translating the x-axis as multiples of 8, declaring the screen's internal pointer and finally declaring to the screen that "we are ready to send bytes".
void epd::drawPrep(int x, int y, int width, int height) {
  //module reset & setup
  digitalWrite(this->reset_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->reset_pin, HIGH);
  delayMicroseconds(2);

  // Additional commands sent if we are partial-refreshing
  if (this->refreshFull == false) {
    this->setLut(WF_PARTIAL_1IN54_0);
    this->spiCommand(0x37); // Unknown undocumented command
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x40);
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x00);
    this->spiData(0x00);
  }
  this->spiCommand(0x3c); // Borderwaveform control since we set it to high the reset_pin.
  this->spiData(0x80); // Only A7 is changed on documentation

  // Additional commands sent if we are partial-refreshing
  if (this->refreshFull == false) {
    this->spiCommand(0x22); // Display update control 2, this is pre-required for command 20
    this->spiData(0xc0);
    this->spiCommand(0x20); // Activates display update sequence
  }
  this->wait();

  // Detect if we surpass the screen's width or height
  this->canvasWidthEnd = x + width - 1; // Add current cord & remove overcounted pixel
  if (this->canvasWidthEnd >= this->screenWidth) {
    this->canvasWidthEnd = this->screenWidth - 1;
  }
  this->canvasHeightEnd = y + height - 1;
  if (this->canvasHeightEnd >= this->screenHeight) {
    this->canvasHeightEnd = this->screenHeight - 1;
  }

  // Set our screen ready by declaring screen's pointer, screen's area to change, and sending "0x24" command
  this->setMemoryArea(x, y, this->canvasWidthEnd, this->canvasHeightEnd); // The "x" and "this->canvasWidthEnd" will become multiples of 8
  this->setMemoryPointer(x, y);
  this->spiCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
}

// Declares what regions of the internal ePaper screen's memory will be READ/WRITE.
// From my understanding. Only the x-axis is multiple's of 8 since we are sending bytes.
// Some of what is sent is left as a "tribute" to the original authors of this code
void epd::setMemoryArea(int x_start, int y_start, int x_end, int y_end) {
  // Multiple of 8, and rounding by Right Arithmatic Shift by removing the last 3 bits.
  this->spiCommand(0x44);
  this->spiData((x_start >> 3) & 0xFF); // Converting it to a multiplicity of 8. Since we only accept a valid range of 25 that is between 0-24. Essentially 200/25 = 8.
  this->spiData((x_end >> 3) & 0xFF); // Converting it to a multiplicity of 8, should be rounded up
  // Normal declaration of height with range of 0 - screen's height
  this->spiCommand(0x45);
  this->spiData(y_start & 0xFF);
  this->spiData((y_start >> 8) & 0xFF); // Evaluates to 0 in 8 bits. Required as 0 per the documentation. Left like this as a tribute to the original author
  this->spiData(y_end & 0xFF);
  this->spiData((y_end >> 8) & 0xFF); // Evaluates to 0 in 8 bits
  this->wait();
}

// Points where in the internal ePaper screen's memory to begin at
void epd::setMemoryPointer(int x, int y) {
  // Multiple of 8 Section
  this->spiCommand(0x4e);
  this->spiData((x >> 3) & 0xFF);
  // Non-multiple of 8 section
  this->spiCommand(0x4F);
  this->spiData(y & 0xFF); // A num
  this->spiData((y >> 8) & 0xFF);
  this->wait();
}

/*

   These functions directly communicate to our device, and it's their only purpose

*/

// Will send the current char given
void epd::spiTransfer(unsigned char let) {
  digitalWrite(this->cs_pin, LOW);
  SPI.transfer(let);
  digitalWrite(this->cs_pin, HIGH);
}

// Sends a specific SPI command
void epd::spiCommand(unsigned char command) {
  digitalWrite(this->dc_pin, LOW);
  this->spiTransfer(command);
}

// After SPI command was used we now send some data.
void epd::spiData(unsigned char dataGiven) {
  digitalWrite(this->dc_pin, HIGH);
  this->spiTransfer(dataGiven);
}

// Used for registrar stuff in the ePaper display, and it's important during initialization of the screen
void epd::lut(unsigned char* lut) {
  this->spiCommand(0x32); // Write to LUT registers
  for (unsigned char i = 0; i < 153; i++) { // Ensure why 153 times, but it's what it is
    this->spiData(lut[i]);
  }
  this->wait();
}
void epd::setLut(unsigned char* lut) {
  this->lut(lut);

  this->spiCommand(0x3f); // Undocumented
  this->spiData(lut[153]);

  this->spiCommand(0x03); // Gate Driving voltage control
  this->spiData(lut[154]);

  this->spiCommand(0x04); // Source Driving voltage control
  this->spiData(lut[155]);
  this->spiData(lut[156]);
  this->spiData(lut[157]);

  this->spiCommand(0x2c); // Messes with a VCOM register to be written on
  this->spiData(lut[158]); // Sent from lut array the 159'th byte
}
