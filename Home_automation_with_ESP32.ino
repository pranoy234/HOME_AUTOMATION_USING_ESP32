 #define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"


char auth[] = "b6chf97tYrCfbhAUin_EFXyK4ZV9gmi6";
char ssid[] = "realme 6 Pro";
char pass[] = "hellopumpkin";
//<---------DHT SENSOR SECTION------------------->
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
float h, t;
void DhtSensor() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V5, t);
}
BlynkTimer timer;

//<-------dht sensor part upto above-------------->


//<-------RELAY SWITCHES---------->
BLYNK_WRITE(V1) {
  digitalWrite(25, param.asInt());
}
BLYNK_WRITE(V2) {
  digitalWrite(26, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(27, param.asInt());
}
//<---------------UPTO THIS---------->

void setup() {
  Serial.begin(9600);
//<---------relay switches types------------>
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
//<---------upto above----------------------> 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
   delay(2000);
  timer.setInterval(1000L, DhtSensor);
  dht.begin();
}

void loop() {
  //Run the Blynk library
  Blynk.run();
  timer.run();
  Serial.println(t);
  Serial.println(h);
}
