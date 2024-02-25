#include <SPI.h>
#include "epd1in54_V2.h"
#include "image.h"
#include "epdpaint.h"
#include <stdio.h>

// Orientation 0 is starts away from the very fragile ribbon and ends towards the fragile ribbon

Epd epd;
unsigned char image[512]; // Set buffer 1024 for that many bytes of reserved ram. This declares how much of a canvas we can have at once
Paint paint(image, 0, 0); // Use buffer

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1
#define origen      0

void setup()
{
  delay(2000);
  Serial.begin(9600);
  digitalWrite(PWR_PIN, 1);
  epd.LDirInit(); // Unsure why this is executed first
  epd.Clear();
  drawScreen(0);
  delay(2000);
  drawScreen(1);
  delay(2000);
  drawScreen(2);
  delay(2000);
  drawScreen(3);
  delay(2000);
  drawScreen(4);
  delay(2000);
  drawScreen(5);
  delay(2000);
  deviceScreenClear();
}

void loop()
{

}

void drawScreen(uint8_t test){
  Serial.println(F("Preparing variables & Clearing Screen"));

  //Conditionals declared
  bool dustSensor = true;
  bool internet = false; // False is index 0, true is index 1
  bool tempWarnInside = 0; // 0 represents no extreme icon, 1 for extreme icon
  bool tempWarnOutside = 0; // 0 represents no extreme icon, 1 for extreme icon
  bool tempNegInside = 0; // For indicating positive or negative degrees
  bool tempNegOutside = 0;
  bool dustTrend = 0; // 0 is no change
  bool dustRising = 0;
  bool aqiTrend = 0; // 1 is change. Where we need to consider direction. No rotate means rising, 180 degree rotate means dropping
  bool aqiRising = 0; // Only activates if above is valid
  bool pressureTrend = 0;
  bool pressureRising = 0;
  uint8_t batIndex = 0; // We assume normal @ 0: 4 for critical, 3 for low, 0 for full. 5 for recharge
  uint8_t humIndex = 1; // We assume normal @ 1: 0 for low, 2 for high
  uint8_t cloudIndex = 2; // We assume normal @ 2: 0 for dry & sunny, 3 for raining. 4 is snowing
  uint8_t tempInsideIndex = 1; // We assume normal @ 1: 0 for cold, 2 for heat. When extreme <1 is cold, >0 is heat
  uint8_t tempOutsideIndex = 1; // We assume normal @ 1: 0 for cold, 2 for heat. When extreme <1 is cold, >0 is heat
  uint8_t aqiIndex = 0; // We assume normal @ 0: 1 for moderate, 2 for high
  tImage tempInsideDecided = Temperature;
  tImage tempOutsideDecided = Temperature;
  
  // Stats
  uint8_t aqipm = 0; // Whole number
  uint8_t aqiozone = 0; // Whole number
  char aqiRating[] = "Green!"; // Non heap for now. Other values: "Green!", "Yellow", "Orange", "Red!!!", "Purple", "Maroon"
  float battery = 3.2;
  float humidity = 0;
  float insideTemperature = 0;
  float outsideTemperature = 0;
  float dust = 0;
  float barometerPresure = 1.00;
  float barometerAltitude = 0; // We assume we have a sea pressure of 10132 pascals
  float pressureAverage[] = {0,0,0,0,0}; // Non heap
  float dustAverage[] = {0,0,0,0,0}; // Non heap
  float aqiAverage[] = {0,0,0,0,0}; // Non heap; Tracks max(apipm, aqiozone)

  // Failed replacement stats
  char dummyInt[] = "--";
  char dummyFloat[] = "--.--";

  Serial.println(F("Drawing borders"));
  // Drawing in the area boxes
  paint.SetRotate(ROTATE_0);
  //constrainedFillDrawRectangle(95,200-0,5,200); // Draw me a rectangle at cords (95,0) on the screen. Have the buffer set for an area 5x200 that draws a width of 5 and a height of 200
  constrainedFillDrawRectangle(0,200-47,200,3); // Worked?
  constrainedFillDrawRectangle(0,200-124,94,3);
  constrainedFillDrawRectangle(100,200-97,99,3);
  constrainedFillDrawRectangle(100,200-148,99,3);
  //constrainedFillDrawRectangle(47,200-127,2,72); WHY DOES VERTICLE LINES NOT WORK?

  Serial.println(F("Getting data"));
  // Celcius, ug/m^3, pressure unit, AQI units, etc

  // Gather data

  /*/ Declare what picture to demonstrated
  if (internetCheck) {
    internet = true;
    aqiDust = getAQI();
    
  }
  battery = getBattery();
  
  baro = getBaroResults();
  humidity = getHumidity();
  temp = getTemp();
  dust = getDust();
  */

  if (test != 0){
    if (test == 1){
      dustSensor = false;
      internet = true;
      tempWarnInside = 0;
      tempWarnOutside = false;
      tempNegInside = 1;
      tempNegOutside = 1;
      dustTrend = 0;
      dustRising = 1; // Checking if this conditional does not activate
      aqiTrend = 0;
      aqiRising = 1;
      pressureTrend = 0;
      pressureRising = 1;
      batIndex = 1;
      humIndex = 1;
      cloudIndex = 2;
      tempInsideIndex = 1;
      tempOutsideIndex = 1;
    }
    else if (test == 2){
      dustSensor = false;
      internet = true;
      tempWarnInside = 0;
      tempWarnOutside = false;
      dustTrend = 1;
      dustRising = 0; // Checking if this conditional does not activate
      aqiTrend = 1;
      aqiRising = 0;
      pressureTrend = 1;
      pressureRising = 0;
      batIndex = 2;
      humIndex = 2;
      cloudIndex = 3;
      tempInsideIndex = 2;
      tempOutsideIndex = 2;

      aqipm = 160; // Whole number
      aqiozone = 160; // Whole number
      humidity = 60.87;
      insideTemperature = 62.15;
      outsideTemperature = 62.16;
      dust = 303.241878;
      barometerPresure = 30.02;
      barometerAltitude = 10000; // We assume we have a sea pressure of 10132 pascals
    }
    else if (test == 3){
      dustSensor = true;
      internet = true;
      tempWarnInside = 0;
      tempWarnOutside = false;
      dustTrend = 1;
      dustRising = 1; // Checking if this conditional does not activate
      aqiTrend = 1;
      aqiRising = 1;
      pressureTrend = 1;
      pressureRising = 1;
      batIndex = 3;
      humIndex = 0;
      cloudIndex = 4;
      tempInsideIndex = 0;
      tempOutsideIndex = 0;

      aqipm = 60; // Whole number
      aqiozone = 60; // Whole number
      humidity = 40.87;
      insideTemperature = 52.15;
      outsideTemperature = 52.16;
      dust = 303.241878;
      barometerPresure = 16894.02;
      barometerAltitude = 30000; // We assume we have a sea pressure of 10132 pascals
    }
    else if (test == 4){
      dustSensor = true;
      internet = true;
      tempWarnInside = 1;
      tempWarnOutside = true;
      dustTrend = 1;
      dustRising = 0; // Checking if this conditional does not activate
      aqiTrend = 1;
      aqiRising = 0;
      pressureTrend = 1;
      pressureRising = 0;
      batIndex = 4;
      cloudIndex = 0;
      tempInsideIndex = 0;
      tempOutsideIndex = 0;

      aqipm = 30; // Whole number
      aqiozone = 30; // Whole number
      humidity = 30.87;
      insideTemperature = 52.15;
      outsideTemperature = 52.16;
      dust = 303.241878;
      barometerPresure = 15894.02;
      barometerAltitude = 20000; // We assume we have a sea pressure of 10132 pascals
    }
    else if (test == 5){
      dustSensor = true;
      internet = false;
      tempWarnInside = 1;
      tempWarnOutside = true;
      batIndex = 5;
      cloudIndex = 1;
      tempInsideIndex = 1;
      tempOutsideIndex = 1;

      aqipm = 10; // Whole number
      aqiozone = 10; // Whole number
      humidity = 10.87;
      insideTemperature = 32.15;
      outsideTemperature = 32.16;
      dust = 3.241878;
      barometerPresure = 12894.02;
      barometerAltitude = 10000; // We assume we have a sea pressure of 10132 pascals
    }
  }

  Serial.println(F("Consulting internet"));
  // Insert internet component

  Serial.println(F("Plastering images"));
  /*
   *  Checking which images to use in general
   */

  // Check inside image
  epd.HDirInit();
  if (tempWarnInside){
    if (tempInsideIndex > 0) {
      tempInsideDecided = TemperatureWarn;
      tempInsideIndex = 1; // In case it wasn't already 1
      tempNegInside = 0;
    }
    else {
      tempInsideDecided = TemperatureWarn;
      tempInsideIndex = 0; // In case it wasn't already 1
      tempNegInside = 1;
    }
  }
  // Check outside image
  if (tempWarnOutside){
    if (tempOutsideIndex > 0) {
      tempOutsideDecided = TemperatureWarn;
      tempOutsideIndex = 1; // In case it wasn't already 1
      tempNegInside = 0;
    }
    else {
      tempOutsideDecided = TemperatureWarn;
      tempOutsideIndex = 0; // In case it wasn't already 1
      tempNegInside = 1;
    }
  }

  // Checking if dust sensor is active, otherwise we have dummy input
  if (not dustSensor) {
    dustTrend = 0;
    dustRising = 0;
    drawStringConstrained(103, 200-122, dummyFloat, &Font12, COLORED);
  }

  // Same deal for the internet component as well
  if (not internet) {
    aqiTrend = 0;
    aqiRising = 0;
    tempWarnOutside = 0;
    tempNegOutside = 0;
    tempOutsideIndex = 1;
    tempOutsideDecided = Temperature;
    drawStringConstrained(35, 200-22, dummyFloat, &Font12, COLORED); // Maximum of 5 characters & Can "fail"
    drawStringConstrained(2, 200-149, "------", &Font12, COLORED); //Maximum of 6 characters & Can "fail"
    drawStringConstrained(154, 200-165, dummyInt, &Font12, COLORED); // Maximum of 2 characters & Can "fail"
    drawStringConstrained(154, 200-183, dummyInt, &Font12, COLORED);
  }

  /*
   *  Code for checking which sky image to use
   */

  // Show AQI symbol, Weather symbol, Connectivity symbol, Battery symbol, etc. ALL IMAGES ADD IN ~6322 bytes of data
  drawImage(2, 200-13, &tempOutsideDecided, tempOutsideIndex); // Drawing temperature of outside
  drawImage(44, 200-12, &TempSign, tempNegOutside);
  drawImage(102, 200-13, &tempInsideDecided, tempInsideIndex); // Drawing temperature of inside
  drawImage(140, 200-12, &TempSign, tempNegInside);
  drawImage(2, 200-52, &Sky, cloudIndex); // Drawing outside local predictions
  drawImage(176, 200-2, &Battery, batIndex); // Drawing current battery status
  drawImage(176, 200-17, &Internet, internet); // Drawing if we are connected or not
  if (pressureTrend and not pressureRising) { paint.SetRotate(ROTATE_180); } // Drawing arrow trends for 3 metrics we are keeping an average tracked
  drawImage(191, 200-60, &Trend, pressureTrend);
  paint.SetRotate(ROTATE_0);
  if (dustTrend and not dustRising) { paint.SetRotate(ROTATE_180); }
  drawImage(191, 200-112, &Trend, dustTrend);
  paint.SetRotate(ROTATE_0);
  if (aqiTrend and not aqiRising) { paint.SetRotate(ROTATE_180); }
  drawImage(191, 200-168, &Trend, aqiTrend);
  paint.SetRotate(ROTATE_0);
  drawImage(50, 200-159, &Humidity, humIndex); // Drawing humidity icons
  drawImage(7, 200-164, &Aqi, aqiIndex); // Drawing AQI bar for summary

  Serial.println("Setting up titles & numbers to display");
  // Titles
  drawStringConstrained(9, 3, "Outside Climate", &Font8, COLORED);
  drawStringConstrained(101, 3, "Indoor Climate", &Font8, COLORED);
  drawStringConstrained(103, 53, "Barometer", &Font12, COLORED);
  drawStringConstrained(103, 102, "DustSensor", &Font12, COLORED);
  drawStringConstrained(102, 153, "Portland OR AQF Now", &Font8, COLORED); // Will show Ozone & PM2.5. AQF=Air Quality Forecast
  drawStringConstrained(51, 129, "Humidity", &Font8, COLORED);
  drawStringConstrained(3, 129, "Portland", &Font8, COLORED);
  drawStringConstrained(3, 139, "AQI Avg;", &Font8, COLORED);
  paint.SetRotate(ROTATE_90);
  drawStringConstrained(178, 54, "Trend", &Font12, COLORED);
  drawStringConstrained(178, 106, "Trend", &Font12, COLORED);
  drawStringConstrained(178, 162, "Trend", &Font12, COLORED);
  paint.SetRotate(ROTATE_0);
  // Units
  constrainedDrawCircle(70, 22, 2, 5, 5, 2, 2); // Draw a circle @ the screen's location (70,22) with a radius of 2 in the 5x5 grid @ (2,2) local coordinance
  drawStringConstrained(75, 22, "C", &Font12, COLORED);
  drawStringConstrained(40, 35, "Celsius", &Font8, COLORED);
  constrainedDrawCircle(169, 22, 2, 4, 4, 2, 2); // Maybe change later
  drawStringConstrained(136, 35, "Celsius", &Font8, COLORED);
  drawStringConstrained(103, 82, "Alt", &Font12, COLORED);
  drawStringConstrained(162, 82, "m", &Font12, COLORED);
  drawStringConstrained(103, 66, "Prs", &Font12, COLORED);
  drawStringConstrained(162, 66, "Pa", &Font12, COLORED);
  drawStringConstrained(141, 122, "ug/m", &Font12, COLORED);
  drawStringConstrained(169, 122, "3", &Font8, COLORED);
  drawStringConstrained(102, 165, "pm2.5:", &Font12, COLORED);
  drawStringConstrained(102, 183, "Ozone:", &Font12, COLORED);

  // Numbers & Values that change
  drawFloatConstrained(134, 22, insideTemperature, &Font12, COLORED); // Maximum of 5 characters
  drawFloatConstrained(127, 66, barometerPresure, &Font12, COLORED); // Maximum of 5 characters
  drawIntConstrained(127, 82, barometerAltitude, &Font12, COLORED); // Maximum of 5 characters, and it's in meters
  if (dustSensor) {
      char text[5]; // I messed up and forgot to consider reading values above 100
      snprintf(text, 5, "%.1f", dust);
      drawStringConstrained(103, 122, text, &Font12, COLORED);
  } // Maximum of 5 characters, and it's in meters & Can "fail" if dust sensor is not active
  if (internet) {drawStringConstrained(2, 149, aqiRating, &Font12, COLORED);} //Maximum of 6 characters & Can "fail"
  if (internet) {drawFloatConstrained(35, 22, outsideTemperature, &Font12, COLORED);} // Maximum of 5 characters & Can "fail"
  if (internet) {drawIntConstrained(154, 165, aqipm, &Font12, COLORED);} // Maximum of 2 characters & Can "fail"
  if (internet) {drawIntConstrained(154, 183, aqiozone, &Font12, COLORED);} // Maximum of 2 characters & Can "fail"

  Serial.println(F("Sleeping after drawing"));
  epd.DisplayFrame(); // Show final picture
  sleepDevice();
}

/*
 *  Basic functions
 */
void deviceScreenClear(){ //Serves as a way to wake up the device & clears it
  Serial.println(F("Waking device"));
  epd.HDirInit(); // Wake up device
  epd.Clear();  // Clear anything on it since it will be drawn ontop of it
}

void sleepDevice(){ //Serves as a way to sleep the device, based on pin
  epd.HDirInit();
  epd.Clear(); // For testing
  epd.Sleep(); // Already has built in delay
  digitalWrite(PWR_PIN, 0); // When executed, it will drop current below detectable signs of mA usage (possibly even uM).
  Serial.println(F("Asleep"));
}

/*/ 
 *  Increasing redability
 */
void setScreenCanvas(uint8_t x, uint8_t y){
  paint.SetWidth(x); // Change frame size for below
  paint.SetHeight(y);
}

// I need to limit how much the character buffer I use, otherwise I would set it to (200,200) and just draw from their. Too much ram sadly required (max; 100x100)
void constrainedFillDrawRectangle(uint8_t cordX, uint8_t cordY, uint8_t screenX, uint8_t screenY){
  setScreenCanvas(screenX, screenY);
  paint.Clear(COLORED); // Essentially all of it becomes a COLORED shade in the given canvas's size
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight()); // Save progress @ x,y location of memory. Assume to go to 199x199. Where we start at 0x0
}

void constrainedDrawCircle(uint8_t cordX, uint8_t cordY, uint8_t radius, uint8_t screenX, uint8_t screenY, uint8_t circleOrigenX, uint8_t circleOrigenY){
  setScreenCanvas(screenX, screenY);
  paint.Clear(UNCOLORED); // To clear the buffer
  paint.DrawCircle(circleOrigenX, circleOrigenY, radius, COLORED);
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight()); // Save progress @ x,y location of memory. Assume to go to 199x199. Where we start at 0x0
}

void drawImage(uint8_t cordX, uint8_t cordY, tImage* pic, uint8_t tableIndex){
  setScreenCanvas(pic->width, pic->height);
  paint.Clear(UNCOLORED); // To clear the buffer
  /*/ 
   Borrowed/Modifed from DrawCharAt();
   */
  int i, j;
  unsigned int char_offset = tableIndex * (pic->width / 8 + (pic->width % 8 ? 1 : 0)) * pic->height; //Modifed to: index of array * length of bytes per row * height of bytes per column
  const unsigned char* ptr = &pic->table[char_offset];

  for (j = 0; j < pic->height; j++) {
      for (i = 0; i < pic->width; i++) {
          if (pgm_read_byte(ptr) & (0x80 >> (i % 8))) { // Already accounts for PROGMEM
              paint.DrawPixel(i, j, COLORED); //Removed cordX & cordY from here since we want to draw at the origen
          }
          if (i % 8 == 7) {
              ptr++;
          }
      }
      if (pic->width % 8 != 0) {
          ptr++;
      }
  }
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight());
}

void drawStringConstrained(uint8_t cordX, uint8_t cordY, const char* text, sFONT* font, int colored){
  setScreenCanvas(font->Width*strlen(text), font->Height);
  paint.Clear(UNCOLORED); // To clear the buffer
  paint.DrawStringAt(origen, origen, text, font, colored);
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight());
}

void drawStringConstrainedRotated(uint8_t cordX, uint8_t cordY, const char* text, sFONT* font, int colored){
  setScreenCanvas(font->Height, font->Width*strlen(text));
  paint.Clear(UNCOLORED); // To clear the buffer
  paint.DrawStringAt(origen, origen, text, font, colored);
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight());
}

void drawFloatConstrained(uint8_t cordX, uint8_t cordY, float num, sFONT* font, int colored){
  // Convert float to const char*
  char text[5];
  snprintf(text, 5, "%.2f", num);
  setScreenCanvas(font->Width*strlen(text), font->Height);
  paint.Clear(UNCOLORED); // To clear the buffer
  paint.DrawStringAt(origen, origen, text, font, colored);
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight());
}

void drawIntConstrained(uint8_t cordX, uint8_t cordY, float num, sFONT* font, int colored){
  // Convert float to const char*
  char text[5];
  snprintf(text, 5, "%d", num);
  setScreenCanvas(font->Width*strlen(text), font->Height);
  paint.Clear(UNCOLORED); // To clear the buffer
  paint.DrawStringAt(origen, origen, text, font, colored);
  epd.SetFrameMemory(paint.GetImage(), cordX, cordY, paint.GetWidth(), paint.GetHeight());
}
