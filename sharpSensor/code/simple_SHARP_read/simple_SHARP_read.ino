/*
  ******************************************************************************
    @file     simple_SHARP_read
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     02-January-2024
    @modified 01-March-2024
    @brief    A way to test the dust system, and see where the function for it is retrieved
    @note;
  This sensor is based on voltage measurement that specifically reports particles of various types encountered in the air of pm2.5 size
  Sharp GP2Y1010AU0F datasheet: https://pdf1.alldatasheet.com/datasheet-pdf/view/412700/SHARP/GP2Y1010AU0F.html
  Github database link:

  // My board's consumption: ~0.0325A, with an estimation of 1mAh per 3-7 minutes. @ 5.1V.
  On 5V line of board, I receive an estimation of 0.9-0.79mA (approaching 0.8mA) when capacitors are charged. When not charged, it becomes ~1.75mA
  Default read in house is ~150 ug/m^3

  // To prevent unexpected overflow from affecting results. I will be removing the average calculated every 255 times.
  Essentially, we intentionally wait for a overflow to occur, before resetting the average.
*/
#include "sharpSensor.h"

void setup() {
  Serial.begin(9600);
  pinMode(dustLEDPin, OUTPUT);
  // No need yet to interrupt the analog reading, can still use other means
}

// Testing loop
void loop() {
  // Data points
  double dustDensity = 0; // A datapoint to consider

  // Control for verbosity
  bool verboose = true;
  // Start of loop, we begin with LED ON
  digitalWrite(dustLEDPin, LOW); // power on the LED by setting this to LOW voltage
  delayMicroseconds(280); // Wait for absolute peak (0.28ms). The numbers are based on manufacturer specifications

  /*/ Sampling Based on a linear equation derived from; http://www.howmuchsnow.com/arduino/airquality/ Chris Nafis (c) 2012
    // Raw Calculation format: ((x * Milligram/meters^3_To_Microgram/meters^3(inputAnalog * (voltage / arduinoAnalogRange)) - c)
    // Simplified equation: (0.17 * 1000 (inputAnalog * (5.0 / 1024.0)) - 0.1)
    // Optimized equation is simply combining like terms
    // Note: x & c are derived from the linear equation. Where x is our linear factor, and c is a constant. However, these can be calibrated /*/
  dustDensity = (analogRead(dustMeasurePin) * 0.830078125) - 0.1;
  delayMicroseconds(40); // Finishing specifications of a pulse of every 0.32ms by adding the remaining 0.04ms. Before abruptly turning off (0.04 ms)
  digitalWrite(dustLEDPin, HIGH); // power off the LED by setting this to HIGH voltage

  // Printing
  if (verboose) {
    Serial.println(F("Dust Current Density"));
    Serial.print(F("\t"));
    Serial.print(dustDensity); // In future, this will be changed
    Serial.println(F(" ug/m^3\t\t"));
  }
  delayMicroseconds(9680); // Sleep until 10 ms cycle has concluded (9.68 ms)
  delay(990); // But I instead decided to go with 1 second cycle instead of 10ms
}
