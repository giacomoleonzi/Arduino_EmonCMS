/*
 *  This sketch is a basic example to send data on emoncms.org due to the
 *  Arduino_EmonCMS library.
 *
 *  at the moment the data published are random value,
 *  substitute the data1 and data2 with your measure
 *  written by Giacomo Leonzi
 */

// Define DHT Sensor Libraries
#include "DHT.h"
#define DHTTYPE     DHT21                   // Define the temperature sensor type 
#define DHTPIN      14
DHT dht(DHTPIN, DHTTYPE, 30);

#include <Emoncms.h>
// Include framework code and libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define APIKEY        "xxxxx"  // replace your emoncms apikeywrite here
#define HTTPPORT 80            // change this value to point at a local
#define HOST "emoncms.org"     //installation of the platform emoncms.org

const char* ssid     = "xxx";  // SSID name
const char* password = "xxx";  // SSID password

// set up net client info:
const unsigned long postingInterval = 10000;  //delay between updates to emoncms.com
unsigned long lastRequest = 0;      // when you last made a request

// Temperature and humidity
float h=0,t=0;
WiFiClient client;
Emoncms emoncms;  //Initialize the object

void setup() {
 emoncms.begin(HOST, HTTPPORT, APIKEY,client);
  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  int data1 = int(random(0, 30));     //replace this value with your
  int data2 = int(random(50, 100));   //measure
  long now = millis();
  if (now - lastRequest >= postingInterval) {
    // Reading temperature or humidity takes about 250 milliseconds!
    h = dht.readHumidity();
    t = dht.readTemperature();

    emoncms.addValue("h", h);
    emoncms.addValue("t", t);
    Serial.println(emoncms.publish());  //open the connection and publish
    lastRequest = now;
  }
  delay(10);
}
