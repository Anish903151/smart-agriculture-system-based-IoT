#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Soil Monitor"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ==== Sensor Pins ====
#define DHTPIN 15
#define DHTTYPE DHT22      // Or DHT11
#define SOIL_PIN 34        // Analog pin
#define BUZZER_PIN 25      // Optional buzzer

DHT dht(DHTPIN, DHTTYPE);

// ==== Virtual Pins ====
#define VPIN_TEMP     V0
#define VPIN_HUMIDITY V1
#define VPIN_SOIL     V2

// ==== WiFi Credentials ====
char ssid[] = "Your_WiFi_Name";
char pass[] = "Your_WiFi_Password";

// ==== Setup ====
void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
}

// ==== Main Loop ====
void loop() {
  Blynk.run();

  // Read temperature and humidity
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read soil moisture
  int soilRaw = analogRead(SOIL_PIN); // 0–4095
  int soilPercent = map(soilRaw, 3000, 1000, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  // Debug output
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C, Humidity: "); Serial.print(humidity);
  Serial.print(" %, Soil Moisture: "); Serial.print(soilPercent); Serial.println("%");

  // Send to Blynk app
  Blynk.virtualWrite(VPIN_TEMP, temp);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity);
  Blynk.virtualWrite(VPIN_SOIL, soilPercent);

  // Local buzzer alert
  if (soilPercent < 30) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(5000);  // Wait 5 seconds
}
