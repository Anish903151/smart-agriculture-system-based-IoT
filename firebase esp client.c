#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <DHT.h>

// Firebase config
#define DATABASE_URL "https://your-project.firebaseio.com/"  // Replace with your DB URL
#define API_KEY "Your_Web_API_Key"  // From Firebase project settings
#define USER_EMAIL "test@example.com"  // Can be dummy
#define USER_PASSWORD "12345678"

// Sensor pins
#define DHTPIN 15
#define DHTTYPE DHT22
#define SOIL_PIN 34

DHT dht(DHTPIN, DHTTYPE);

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
