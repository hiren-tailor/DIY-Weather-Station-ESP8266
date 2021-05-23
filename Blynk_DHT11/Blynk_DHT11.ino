#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "ihE0NCnxE5-bnZvELYTXNk1cUbiZI5WB";
char ssid[] = "Hiren";
char pass[] = "123456789";

#define DHTPIN 5          // GPIO 5 (pin D1 of ESP8266)
#define DHTTYPE DHT11     // DHT 11 (use DHT22 for DHT22 sensor)
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

int mq135 = A0;           //AQI sensor is connected with the analog pin A0
int data = 0;

void sendSensor()
{
  data = analogRead(mq135);           //read A0 pin of NodeMCU
  Blynk.virtualWrite(V4, data);       //virtual pin V4 for AQI

  float h = dht.readHumidity();
  float t = dht.readTemperature();    // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V2, h);          //virtual pin V2 for humidity
  Blynk.virtualWrite(V3, t);          //virtual pin V3 for temperature
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "188.166.206.43", 80); //PING blynk-cloud.com
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
