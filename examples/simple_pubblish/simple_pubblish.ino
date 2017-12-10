/*
 *  This sketch is a basic example to send data on emoncms.org due to the
 *  Arduino_EmonCMS library.
 *
 *  at the moment the data published are random value,
 *  substitute the data1 and data2 with your measure
 *  written by Giacomo Leonzi
 */

#include <ArduinoEmoncms.h>
#include <ESP8266WiFi.h>

#define APIKEY        "<xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx>"                  // replace your emoncms apikeywrite here
#define HTTPPORT 80          // change this value to point at a local
#define HOST "80.243.190.58" //installation of the platform emoncms.org

const char* ssid     = "<name>";  // SSID name
const char* password = "<pswd>";   // SSID password

// set up net client info:
const unsigned long postingInterval = 6000;  //delay between updates to emoncms.com
unsigned long lastRequest = 0;      // when you last made a request


ArduinoEmoncms emoncms(HOST, HTTPPORT, APIKEY);  //Initialize the object

void setup() {

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
    emoncms.addValue("data1", data1);
    emoncms.addValue("data2", data2);
    Serial.println(emoncms.publish());  //open the connection and publish
    lastRequest = now;
  }
  delay(10);
}