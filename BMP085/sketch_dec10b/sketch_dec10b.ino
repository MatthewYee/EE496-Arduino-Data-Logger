#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

const int chipSelect =4;

void setup(void) 
{
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  pinMode(10,OUTPUT);
  if (!SD.begin(chipSelect)) {
     Serial.println(" ");
     Serial.println("Card has failed, or isn't present!");
     return;
  }
  Serial.println("Card has been initialized...");
  
  Serial.println("Pressure Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
  
  /* Variables */
  float temperature;
  
  // make a string for assembling data to log
  String dataString = "";
  String dataString2 = "";
  
  /* Get Curren Temperature */
  bmp.getTemperature(&temperature);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressure in hPa */
    /*Serial.print("Pressure: "); Serial.print(event.pressure); Serial.println(" hPa");*/
    Serial.println("Printing stuff into dataString");
    dataString += event.pressure;
    dataString2 += temperature;
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(250);
  
  File dataFile = SD.open("log.txt", FILE_WRITE);
  File dataFile2 = SD.open("log2.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening log 1");
  }
  
  if (dataFile2) {
    dataFile2.println(dataString2);
    dataFile2.close();
    Serial.println(dataString2);
  }
  else {
    Serial.println("error opening log 2");
  }
}
