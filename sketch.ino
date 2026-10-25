#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "NSE0RPDBQC9XN3LD";
String studentID = "12324278";

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  Serial.println("Student ID: " + studentID);
  Serial.println("Temp: " + String(temp) + " C | Humidity: " + String(hum) + " %");

  HTTPClient http;
  String url = "http://api.thingspeak.com/update?api_key=" + apiKey + 
               "&field1=" + String(temp) + 
               "&field2=" + String(hum);

  http.begin(url);
  int httpCode = http.GET();
  Serial.println("Response code: " + String(httpCode));
  http.end();

  delay(20000);
}