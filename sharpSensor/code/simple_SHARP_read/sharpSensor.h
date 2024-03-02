/*
  ******************************************************************************
    @file     sharpSensor.h
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     02-January-2024
    @modified 01-March-2024
    @brief    A way to test the dust system, and see where the function for it is retrieved
    @note; This is for my project I am currently doing. Where it's simplified to a function
*/

// Setup ItsyBitsy 32u4 pins
int dustMeasurePin = 18; //The output of the dust sensor we can detect in analog.
int dustLEDPin = 13; //The Infrared LED pin inside the dust sensor we can control in digital signals.

// Function to be used in main program
void getDust(double long* dust) {
  // Start of loop, we begin with LED ON
  digitalWrite(dustLEDPin, LOW); // power on the LED by setting this to LOW voltage
  delayMicroseconds(280); // Wait for absolute peak (0.28ms). The numbers are based on manufacturer specifications
  *dust = (analogRead(dustMeasurePin) * 0.830078125) - 0.1;

  // Ensuring the cycle correctly ends incase this is used more often
  delayMicroseconds(40); // Finishing specifications of a pulse of every 0.32ms by adding the remaining 0.04ms. Before abruptly turning off (0.04 ms)
  digitalWrite(dustLEDPin, HIGH); // power off the LED by setting this to HIGH voltage
  delayMicroseconds(9680); // Sleep until 10 ms cycle has concluded (9.68 ms)
}
