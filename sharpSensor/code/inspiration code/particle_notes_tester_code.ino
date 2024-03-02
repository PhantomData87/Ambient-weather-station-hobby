clear
a//Info: GP2Y1010AU0F Dust sensor
//The dust sensor reaches the maximum output pulse 0.28 ms after the LED was turned on
//This sensor is based on voltage measurement
//Sharp GP2Y1010AU0F datasheet: https://pdf1.alldatasheet.com/datasheet-pdf/view/412700/SHARP/GP2Y1010AU0F.html
 
//Dust sensor
int dustmeasurePin = 18; //The output of the dust sensor is connected to A6 (AD converter pin)
int dustLEDPin = 13; //The IR pin inside the dust sensor is connected to D2 (digital output pin)
float outBits = 0; //AD-converter raw output
float dustDensity = 0; //dust density, based on the formula (see later)
 
//String for storing the formatted output data
String outputData;
 
void setup()
{
    Serial.begin(9600); //Start serial
 
    Serial.println("*Dust and VOC sensor"); //Print message. I use '*' to tell the receives software that this is not a measurement data
/* 
    if(!ccs.begin()) //if we are not able to start the VOC sensor, print the following message
    {
        Serial.println("* Failed to start sensor! Please check your wiring.");
        while(1); //And hold the code here
    }
   
    while(!ccs.available());
 
    float temp = ccs.calculateTemperature(); //calculate the temperature
    ccs.setTempOffset(temp - 25.0); //set the offset using the
*/ 
    pinMode(dustLEDPin,OUTPUT); //the pin for the dust sensor's LED is set as an output
}
 
 
void loop()
{
    if (Serial.available() > 0) //if there's something on the serial
    {
    char commandCharacter = Serial.read(); //we use characters (letters) for controlling the switch-case
 
        switch (commandCharacter)
        {
          case 'S': //S: start
 
          while(Serial.read() != 'N') //while we don't send N through the serial, the following functions are looping:
          {
             measureDust();
             delay(1000);
             printFormattedData();        
          }
          break;
 
          default:
              //
          break;    
        }    
  }
}
 
void measureDust()
{
  digitalWrite(dustLEDPin,LOW); //turn ON the LED
 
  delayMicroseconds(280); // wait 0.28 ms = 280 us
 
  outBits = analogRead(dustmeasurePin); //measure the peak of the output pulse  
 
  digitalWrite(dustLEDPin,HIGH); //turn OFF the LED    
 
  /*
  If you want to get the converted data on the Arduino terminal,
  //uncomment this part and replace the outbits to dustDensity in printFormattedData()
 
  dustDensity = 1000* ( 0.17 * ((5.0 / 1024) * outBits) - 0.1); //dust density: Since we are given a equation to consider mg/m^3, 
  than simply by 1000 we obtain 1000 ug/m^3.

  voltage = (outBits * (0.0049)) = outBits = (5.0 / 1024)
  dustDensity = (170 * Voltage - 0.1) // This is a simplification of the equation given of y=0.172 * x - 0.0999
  Why the 0.17? It's from equation, thats why.

  Learned: pm2.5 = 65.4 ug/m^3. pm10 = 254 ug/m^3
  pmx = it has a diameter of x
  pph = pp1 * 10^2 = pp1 * hundred
  ppm = pp1 * 10^6 = pp1 * million
  ppb = pp1 * 10^9 = pp1 * billion

  1 ug/m^3 = 35.314 ug/f^3
  0.0283 ug/m^3 = 1 ug/f^3

  Finally; The sensor detects up to 580 ug/m^3

  ppm = (V-0.0356)*120000 or (V-0.0256)*120000. Where the "0.0356" is a offset of the voltage from the sensor when at baseline clean air. 
  For mg/m^3 to ppm requires knowing as well atmosphere and current temperature. Default of 25C and 1 atmopshere pressure.
  
  The 0.0356 offset comes from blind intuition to make the graph lower when measuring in pph. I need to obtain this value as well.
  How PPM works:
  https://www.breeze-technologies.de/blog/air-pollution-how-to-convert-between-mgm3-%C2%B5gm3-ppm-ppb/
  https://earthscience.stackexchange.com/questions/25579/why-and-how-is-particulate-matter-measured-in-mass-per-volume

  Site to calculate ppm:
  http://niosh.dnacih.com/nioshdbs/calc.htm
  https://sciencing.com/calculate-ppm-vapor-pressure-6457861.html
  The number 24.45 comes from assuming the temperature is 25 and it's one atmosphere of pressure currently. This is what can be changed.
  Moles are such an important unifying factor for all of this. Read what AQI uses to measure and stop focusing on this 120000 number and make my own.

  Exploring the Temperature Coefficient:
  https://forum.digikey.com/t/temperature-coefficient-and-ppm-explanation/20698
  https://www.allaboutcircuits.com/technical-articles/understanding-the-temperature-coefficient-of-a-voltage-reference/

  Essentially. When temperature changes, voltage output can also change. Thus, I need to make a custom equation that offsets this ppm value by 1, whenever voltage drops from the norm.
  It's also not something linear.

  Finally, make the calculations average over time & Calculate voltage offset.

  Sensor is meant for 2.5. With a max of 1300 ug/m^3 +- 4 ug for detection:
  https://www.aivc.org/sites/default/files/2_C15.pdf
  https://www.mdpi.com/2076-3417/9/16/3435

  Can detect at most 0.3-2.5um. Finally, learned that it cannot be used to precisely estimate AQI, but can be used to estimate IAQ (Indoor Air Quality)
  */  
}

void printFormattedData() //Formatting the output so the receiver software can process it
{  
  //output:    Dust
  outputData = (String)outBits; //for the output
  Serial.println(outputData);
 
  /* outBits can be replaced to dustDensity to print the converted data instead of the raw data.
  Proper code:
  https://github.com/PaulZC/GP2Y1010AU0F_Dust_Sensor/blob/master/Dust_Sensor/Dust_Sensor.ino
  http://www.socle-tech.com/doc/IC%20Channel%20Product/sharp%20products.pdf

  Chart:
  https://greenecon.net/3-metrics-to-guide-air-quality-health-safety

  Recommended to use: delayMicroseconds() instead of delay()
  */
}
