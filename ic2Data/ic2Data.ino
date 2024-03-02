/**
  ******************************************************************************
    @file     ePaper_screen_layout
    @author   Alonzo Ortiz-Sanchez
    @version  V1.0.0
    @made     27-Feburary-2024
    @modified 01-March-2024
    @brief    Has the functions that will obtain I2C data, but also have them tested out if they are available. This is mainly to easily import this existing code, and to simplify my own testing
*/
// Start:
// https://learn.adafruit.com/adafruit-aht20/arduino
#include <Adafruit_AHTX0.h>

// Start:
// https://randomnerdtutorials.com/esp32-with-bmp180-barometric-sensor/
//#include <Wire.h>
#include <Adafruit_BMP085.h>

// Defining global variables
long alt, pres; // Fake test values
double temp, hum; // Fake test values
sensors_event_t tempObject, humObject; // For DHT20 Sensor
Adafruit_AHTX0 aht; // For DHT20 Sensor
Adafruit_BMP085 bmp; // For BMP180 Sensor

void setup() {
  SerialUSB.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool bmpSensor = true;
  if (bmpSensor) {
    testBmp();
  }
  else {
    testDht();
  }
}

// Retrieve contents of BMP180 sensor & include safety
void getBmp(long* altitudeHeight, long* pressure) {
  if (!bmp.begin()) { // Check if we have a BMP sensor detectable or not
    SerialUSB.println("No valid BMP Sensor");
    *altitudeHeight = 0;
    *pressure = 0;
  }
  else {
    *altitudeHeight = bmp.readAltitude(); // Measured in meters
    *pressure = bmp.readPressure(); // Measured in Pascal: pa
  }
}

// Retrieve contents of DHT20 sensor & include safety
void getDht(double* temp, double* humidity) {
  if (!aht.begin()) { // Check if we have a BMP sensor detectable or not
    SerialUSB.println("No valid BMP Sensor");
    *temp = 0;
    *humidity = 0;
  }
  else {
    aht.getEvent(&humObject, &tempObject);
    *temp = tempObject.temperature; // Measured in Celcius (C)
    *humidity = humObject.relative_humidity; // Measured in % rH
  }
}

// For printing the BMP180 sensor
void testBmp() {
  getBmp(&alt, &pres);
  SerialUSB.println(alt);
  SerialUSB.println(pres);
}

// For printing the DHT20 Sensor
void testDht() {
  getDht(&temp, &hum);
  SerialUSB.println(temp);
  SerialUSB.println(hum);
}
