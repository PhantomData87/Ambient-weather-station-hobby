/**
  ******************************************************************************
    @file     ePaper_screen_layout
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     16-Feburary-2024
    @modified 24-Feburary-2024
    @brief    This is me testing the layout of my GUI by using my own library
    @note     Feel free to modify. I don't expect my crummy pixel art to be used and do not mind finding it elsewhere
    @mention  If you have questions on why things are defined the way they are. Feel free to read "README.md" to obtain some answers.
    @stats    At the time of writing. This program when initialized takes up 617 bytes of memory, and 19764 bytes in "program storage space" (my max is 28672). A lot of the bytes come from the images/icons loaded in
*/
#include "epdConf.h"
#include "icon.h"
epd epd;

void setup() {
  // Turn on the screen
  SerialUSB.begin(9600);
  epd.turnOn();

  // Ensure we have a fresh screen & Start the testing
  epd.clearScreen();

  // Minor testing
  printScreen(1);
  delay(2000);
  epd.turnOff();
}

void loop() {
  // Include battery safety detection (Check if we go below 15% charge) & Must also detect charging
  //https://electronics.stackexchange.com/questions/110104/calculating-battery-percentage-using-an-arduino
  //https://forum.makecode.com/t/any-way-to-get-or-estimate-the-battery-percentage/18239/2
  /*
  Where I tested rounding & type rounding. Until it produced the number I wanted
  SerialUSB.println("Normal numbers");
  SerialUSB.println(98.3845);
  SerialUSB.println(736.9498);
  SerialUSB.println(7264.9824);
  SerialUSB.println(1000289);
  SerialUSB.println(-212784390);
  SerialUSB.println(72);
  SerialUSB.println("Absolute");
  SerialUSB.println(abs(98.3845));
  SerialUSB.println(abs(736.9498));
  SerialUSB.println(abs(7264.9824));
  SerialUSB.println(abs(1000289));
  SerialUSB.println(abs(-212784390));
  SerialUSB.println(abs(72));
  SerialUSB.println("Rounding 1");
  SerialUSB.println((int)98.3845 % 101);
  SerialUSB.println((int)736.9498 % 1000);
  SerialUSB.println((int)7264.9824 % 100000);
  SerialUSB.println(1000289 % 10000000);
  SerialUSB.println(212784390 % 2000000000);
  SerialUSB.println(72 % 101);
  SerialUSB.println("Rounding 2");
  SerialUSB.println((98.3845 * 100));
  SerialUSB.println((long)(98.3845 * 100));
  SerialUSB.println((long)(98.3845 * 100) % 100);
  SerialUSB.println((736.9498 * 100));
  SerialUSB.println((long)(736.9498 * 100));
  SerialUSB.println((long)(736.9498 * 100) % 100);
  SerialUSB.println((7264.9824 * 100));
  SerialUSB.println((long)(7264.9824 * 100));
  SerialUSB.println((long)(7264.9824 * 100) % 100);
  delay(10000);
  */
}

// More global variables meant for longterm
float previousAveragePressure = 0.0;
float previousAverageHumidity = 0.0;
float previousAverageTemperature = 0.0;
float previousAverageDust = 0.0;

float pressureAverage[] = {0, 0, 0, 0, 0}; // Non heap
float dustAverage[] = {0, 0, 0, 0, 0}; // Non heap
float tempAverage[] = {0, 0, 0, 0, 0}; // Non heap
float humAverage[] = {0, 0, 0, 0, 0}; // Non heap

bool batCharge = false;
bool batSafety = true; // Must be detected
int battery = 0; // To ensure we know the proper battery across the program

void printScreen(unsigned int test) {
  // Text expected ot be in font 12 (Would use const, but compiler complains)
  unsigned char* pressureT = (unsigned char *)"Pressure:"; // 9 char out of 10 max
  unsigned char* humidityT = (unsigned char *)"Humidity:"; // 9 char out of 10 max
  unsigned char* dustT = (unsigned char *)"Dust PM2.5"; // 10 char out of 10 max
  unsigned char* barometerTOne = (unsigned char *)"Barometer"; // 9 char out of 12 max
  unsigned char* barometerTTwo = (unsigned char *)"forecast"; // 8 char out of 12 max
  unsigned char* altitudeT = (unsigned char *)"Altitude (m)"; // 12 char out of 12 max
  unsigned char* temperatureT = (unsigned char *)"Temp (C):"; // 9 char out of 10 max

  //Conditionals declared detecting which image to use
  bool tempNeg = false; // For indicating positive or negative degrees
  bool tempTrend = false;
  bool tempRising = false;
  bool dustTrend = false;
  bool dustRising = false;
  bool humidityTrend = false;
  bool humidityRising = false;
  bool pressureTrend = false;
  bool pressureRising = false;
  bool altNeg = false; // For barometer altitude readings
  unsigned int batIndex = 0;
  unsigned int barometerIndex = 0;

  // Stats
  double humidity = 0;
  double temperature = 0;
  double long dust = 0;
  long barometerPressure = 0;
  long barometerAltitude = 0; // We assume we have a sea pressure of 10132 pascals

  // Gather data
  /*
    battery = getBattery();
    barometerAltitude = getAltitude();
    barometerPressure = getPressure(); // Don't forget to conver this to Pa instead of hPA
    dust = getDust();
    humidity = getHumidity();
    temp = getTemp();
  */

  // Screen test values (Feel free to delete this)
  if (test == 1) {
    humidity = 98.3845;
    temperature = 736.9498;
    dust = 72640.9824;
    barometerPressure = 1000289;
    barometerAltitude = -212784390;
    battery = 72;
  }

  // Calculate averages & move values along (Doing "for loop unrolling" instead of 4 different for loops)
  int presMean;
  int dustMean;
  int humMean;
  int tempMean;
  for (int i = 0; i < 4; i++) { // Discarding the oldest value
    pressureAverage[i] = pressureAverage[i + 1];
    dustAverage[i] = dustAverage[i + 1];
    tempAverage[i] = tempAverage[i + 1];
    humAverage[i] = humAverage[i + 1];
    presMean += pressureAverage[i];
    dustMean += dustAverage[i];
    humMean += humAverage[i];
    tempMean += tempAverage[i];
  } // Doing the last row with new numbers obtained
  pressureAverage[4] = barometerPressure;
  dustAverage[4] = dust;
  tempAverage[4] = temperature;
  humAverage[4] = humidity;
  presMean += pressureAverage[4];
  dustMean += dustAverage[4];
  humMean += humAverage[4];
  tempMean += tempAverage[4];
  presMean /= 5;
  dustMean /= 5;
  humMean /= 5;
  tempMean /= 5;

  // Calculating if a "trend" exists with a certain "tolerance"
  if (previousAveragePressure - 7 <= presMean and presMean <= previousAveragePressure + 7) { // Based on https://www.thoughtco.com/how-to-read-a-barometer-3444043
    pressureTrend = false;
  }
  else {
    pressureTrend = true;
    if (previousAveragePressure < presMean) {
      pressureRising = true;
    }
  }
  previousAveragePressure = presMean;

  if (previousAverageHumidity - 1 <= humMean and humMean <= previousAverageHumidity + 1) {
    humidityTrend = false;
  }
  else {
    humidityTrend = true;
    if (previousAverageHumidity < humMean) {
      humidityRising = true;
    }
  }
  previousAverageHumidity = humMean;

  if (previousAverageDust - 50 <= dustMean and dustMean <= previousAverageDust + 50) {
    dustTrend = false;
  }
  else {
    dustTrend = true;
    if (previousAverageDust < dustMean) {
      dustRising = true;
    }
  }
  previousAverageDust = dustMean;

  if (previousAverageTemperature - 2 <= tempMean and tempMean <= previousAverageTemperature + 2) {
    tempTrend = false;
  }
  else {
    tempTrend = true;
    if (previousAverageTemperature < tempMean) {
      tempRising = true;
    }
  }
  previousAverageTemperature = tempMean;

  // Determine if temperature is negative or positive
  if (temperature < 0) {
    tempNeg = true;
  }

  // Determine if altitude is negative or positive
  if (barometerAltitude < 0) {
    altNeg = true;
  }

  // If we have integer overflow, it should be relatively obvious to spot. Thus we assume we never receive a negative number, or it has already been considered
  temperature = abs(temperature);
  humidity = abs(humidity);
  dust = abs(dust);
  battery = abs(battery);
  barometerAltitude = abs(barometerAltitude);
  barometerPressure = abs(barometerPressure);

  // Determine which image to show for battery
  if (batCharge) { // We are re-charging, this takes precedence
    batIndex = 4;
  }
  else if (battery >= 95) { // Essentially full
    batIndex = 0;
  }
  else if (battery >= 70) { // Near full
    batIndex = 1;
  }

  else if (battery >= 45) { // We are definetely higher than half
    batIndex = 2;
  }
  else if (battery >= 20) { // We are reaching the limit of "safety"
    batIndex = 3;
  }
  else { // This will only display if we choosen to go below 20%. Since below 20% it would technically turn off
    batIndex = 5;
  }

  // Determine which image to show for barometer's prediction
  if (barometerPressure >= 102269) { // Check if it's "high" based on https://www.thoughtco.com/how-to-read-a-barometer-3444043
    if (pressureTrend and pressureRising) { // We have "moved" and it has been rising last checked
      unsigned int barometerIndex = 0;
    }
    else if (pressureTrend) { // We have "moved" however, it has been falling
      unsigned int barometerIndex = 1;
    }
    else { // We have not "moved"
      unsigned int barometerIndex = 0;
    }
  }
  else if (barometerPressure <= 100914) { // Check if it's "low"
    if (pressureTrend and pressureRising) { // We have "moved" and it has been rising last checked
      unsigned int barometerIndex = 0;
    }
    else if (pressureTrend) { // We have "moved" however, it has been falling
      unsigned int barometerIndex = 2;
    }
    else { // We have not "moved"
      unsigned int barometerIndex = 1;
    }
  }
  else { // Were in that sweet middle range
    if (pressureTrend and pressureRising) { // We have "moved" and it has been rising last checked
      unsigned int barometerIndex = 1;
    }
    else if (pressureTrend) { // We have "moved" however, it has been falling
      unsigned int barometerIndex = 2;
    }
    else { // We have not "moved"
      unsigned int barometerIndex = 2;
    }
  }

  // Insert values as a char (First we do simple, than noticing my board does not support "float format string" operations. I will have to "manually" do it
  // Since I am unable to properely use unsigned buffers. I will use normal char buffs, sometimes I wonder if sticking to "unsigned char" was such a good idea
  char batChar[5]; // Max of 3 + "%" symbol, so 4 chracters residing in 8 bytes & we will be considering the "null terminator"
  char presChar[8]; // Maximum of 7
  char altiChar[11]; // Maximum of 10 characters. Since the max is 2 billion before integer overflow
  char humChar[7]; // Max of 6
  char tempChar[7]; // Max of 6
  char dustChar[9]; // Maximum of 8 characters
  int decimal;
  snprintf(batChar, 5, "%03d%%", battery % 101);  // We will not accept values higher than 100. Also we do "%%" to represent "%"
  snprintf(presChar, 8, "%07ld", barometerPressure % 10000000); // We will not accept values higher than 9999999
  snprintf(altiChar, 11, "%010ld", barometerAltitude); // We will not accept values higher than the literal "long" limit

  decimal = ((long)(humidity * 100) % 100); // Obtaining the two decimal places from our float. We also do "long" instead of "int" conversion to prevent overflow edge case
  snprintf(humChar, 7, "%03d.%02d", (int)humidity % 101, decimal); // We will not accept values higher than 100

  decimal = (long)(temperature * 100) % 100; // Obtaining the two decimal places from our float
  snprintf(tempChar, 7, "%03d.%02d", (int)temperature % 1000, decimal); // We will not accept values higher than 999

  decimal = ((long)(dust * 100) % 100); // Obtaining the two decimal places from our float
  snprintf(dustChar, 9, "%05ld.%02d", (long)dust % 100000, decimal); // We will not accept values higher than 99999

  // Begin drawing more; Indicating the word "trend"
  epd.drawImage(80, 0, &iconTrendWord);
  epd.drawImage(80, 41, &iconTrendWord);
  epd.drawImage(80, 81, &iconTrendWord);
  epd.drawImage(80, 121, &iconTrendWord);

  // Determining the sign for temperature & altitude
  if (tempNeg) {
    epd.drawCharArray(8, 21, (unsigned char*)"-", 1, &Font12);
  }
  else {
    epd.drawCharArray(8, 21, (unsigned char*)"+", 1, &Font12);
  }
  if (altNeg) {
    epd.drawCharArray(0, 183, (unsigned char*)"-", 1, &Font12);
  }
  else {
    epd.drawCharArray(0, 183, (unsigned char*)"+", 1, &Font12);
  }

  // Drawing current "trend" for data points
  if (tempTrend and not tempRising) {
    epd.switchYRotation();
  }
  epd.drawImage(88, 5, &iconTrend, tempTrend);
  if (tempTrend and not tempRising) {
    epd.switchYRotation();
  }

  if (humidityTrend and not humidityRising) {
    epd.switchYRotation();
  }
  epd.drawImage(88, 45, &iconTrend, humidityTrend);
  if (humidityTrend and not humidityRising) {
    epd.switchYRotation();
  }

  if (dustTrend and not dustRising) {
    epd.switchYRotation();
  }
  epd.drawImage(88, 85, &iconTrend, dustTrend);
  if (dustTrend and not dustRising) {
    epd.switchYRotation();
  }

  if (pressureTrend and not pressureRising) {
    epd.switchYRotation();
  }
  epd.drawImage(88, 125, &iconTrend, pressureTrend);
  if (pressureTrend and not pressureRising) {
    epd.switchYRotation();
  }

  // Draw last pictures
  epd.drawImage(108, 166, &iconBattery, batIndex);
  epd.drawImage(109, 41, &iconBarometer, barometerIndex);
  epd.drawImage(72, 108, &iconPower); // For dust sensor

  // Draw titles
  epd.drawCharArray(116, 5, barometerTOne, 9, &Font12);
  epd.drawCharArray(120, 21, barometerTTwo, 8, &Font12);
  epd.drawCharArray(4, 5, temperatureT, 9, &Font12);
  epd.drawCharArray(4, 46, humidityT, 9, &Font12);
  epd.drawCharArray(0, 86, dustT, 10, &Font12);
  epd.drawCharArray(4, 126, pressureT, 9, &Font12);
  epd.drawCharArray(0, 166, altitudeT, 12, &Font12);

  // Draw units
  epd.drawCharArray(64, 99, (unsigned char*)"ug", 2, &Font8); // For Dust sensor
  epd.drawCharArray(64, 109, (unsigned char*)"m", 1, &Font8); // For Dust sensor
  epd.drawCharArray(88, 183, (unsigned char*)"m", 1, &Font12);  // For altitude
  epd.drawCharArray(64, 141, (unsigned char*)"Pa", 2, &Font12); // For pressure
  epd.drawCharArray(64, 61, (unsigned char*)"%", 1, &Font12); // For humidity
  epd.drawCharArray(64, 21, (unsigned char*)"C", 1, &Font12); // For temperature
  epd.drawCircle(72, 21, 1); // For temperature celcius "o" symbol

  // Draw results
  epd.drawCharArray(16, 21, (unsigned char *)tempChar, 6, &Font12);
  epd.drawCharArray(16, 61, (unsigned char *)humChar, 6, &Font12);
  epd.drawCharArray(0, 101, (unsigned char *)dustChar, 8, &Font12);
  epd.drawCharArray(4, 141, (unsigned char *)presChar, 7, &Font12);
  epd.drawCharArray(8, 183, (unsigned char *)altiChar, 10, &Font12);
  epd.drawCharArray(132, 172, (unsigned char *)batChar, 4, &Font20);

  // Draw edges to divide data
  epd.switchFilled();
  epd.drawRectangleArea(97, 0, 6, 200); // Main edge that divides the screen
  epd.drawRectangleArea(0, 38, 103, 3);
  epd.drawRectangleArea(0, 78, 103, 3);
  epd.drawRectangleArea(0, 118, 103, 3);
  epd.drawRectangleArea(0, 158, 200, 3);
  epd.drawRectangleArea(64, 106, 16, 1); // For unit symbol division
  epd.switchFilled();

  // Display screen
  epd.displayFrame();
  epd.sleepScreen();
}

// Helper function from: https://forum.arduino.cc/t/count-digits-of-a-number/936102/5
unsigned int countDigits(int num)
{
  return (  1 + log10( num )  ) ;
}
