#include "Arduino.h"
#include "DHT.h"
#include <ArduinoJson.h>

#define DPIN 4        //Pin to connect DHT sensor (GPIO number) D2
#define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type

DHT dht(DPIN,DTYPE);

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(5000);
  
  float tc = dht.readTemperature(false);  //Read temperature in C
  // float tf = dht.readTemperature(true);   //Read Temperature in F
  float hu = dht.readHumidity();          //Read Humidity
  int mst = analogRead(A0);

  // Create a JSON object
  StaticJsonDocument<200> doc;
  doc["temperature"] = tc;
  doc["air_humidity"] = hu;
  doc["soil_humidity"] = mst;

  // Serialize JSON to a string
  char jsonStr[200];
  serializeJson(doc, jsonStr);

  // Send JSON string over Serial
  Serial.println(jsonStr);
}