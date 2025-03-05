#include <SimpleDHT.h>
#include <Wire.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h> 
#include "ESP_Wahaj.h"
#define REPORTING_PERIOD_MS     1000
uint32_t delayMS;
 int te=0;

// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN - D0

 

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = D0;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
  start("Project","12345678");
  pinMode(D5,OUTPUT);
  digitalWrite(D5,LOW);
 ThingSpeak.begin(client);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  te=temperature;
  if(te>33)
  {
    digitalWrite(D5,HIGH);
    }
    else{
    digitalWrite(D5,LOW);   
      }
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  ThingSpeak.setField(5, te);
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(565129,"3J6LJDI7PCAU2IVL");
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
