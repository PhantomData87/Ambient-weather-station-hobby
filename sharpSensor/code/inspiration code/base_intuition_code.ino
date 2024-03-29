/*
Refrains : https://create.arduino.cc/projecthub/mircemk/diy-air-quality-monitor-with-sharp-gp2y1010au0f-sensor-7b0262

 Standalone Sketch to use with a Arduino UNO and a
 Sharp Optical Dust Sensor GP2Y1010AU0F
*/

int measurePin = 18; //Connect dust sensor to Adafruit A0 pin
int ledPower = 13;   //Connect led driver pins of dust sensor to Adafruit D13

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  
}

void loop(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);// Waiting for maximum voltage pulse

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;

  // Simple wiring: https://github.com/PaulZC/GP2Y1010AU0F_Dust_Sensor/blob/master/Sharp_GP2Y1010AU0F_Optical_Dust_Sensor_Hook-Up_Guide.pdf
  
  Serial.println(dustDensity); // unit: ug/m3
  Serial.println(calcVoltage);
  Serial.println("___");

  delay(1000);
}
