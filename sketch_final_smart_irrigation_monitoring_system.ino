#define BLYNK_TEMPLATE_ID "TMPL3ASFx7S3i"
#define BLYNK_TEMPLATE_NAME "Soil Mositure and Temperature Monitoring System"
#define BLYNK_AUTH_TOKEN "wZgykJmWemoiwmCKi3rpP-VSaQtB6uDn"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = ""; // WiFi name
char pass[] = ""; // WiFi password

BlynkTimer timer;
#define DHTPIN 4
#define SOIL_MOISTURE_PIN 34
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
int soilmoisture = analogRead(SOIL_MOISTURE_PIN);
int soilmoisturepercentage = map(soilmoisture, 3500, 4095, 100, 0);
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

Blynk.virtualWrite(V0, soilmoisturepercentage);
Blynk.virtualWrite(V1, t);
Blynk.virtualWrite(V2, h); 

Serial.print("Soil Moisture : ");
Serial.print(soilmoisturepercentage);
Serial.print(" Temperature : ");
Serial.print(t);
Serial.print(" Humidity : ");
Serial.println(h);
}

void setup()
{
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
dht.begin();
timer.setInterval(100L, sendSensor);
}

void loop()
{
Blynk.run();
timer.run();
}