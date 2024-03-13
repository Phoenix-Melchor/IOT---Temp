#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

const char *ssid = "Melchor";
const char *password = "Jamz240414";
const char *thingSpeakApiKey = "7EMD730Q2G1FS6JV";

const int pinDHT = 32;  // Pin digital para el sensor DHT11
DHT dht(pinDHT, DHT11);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  ThingSpeak.begin(client);
  delay(2000);
  dht.begin();
  delay(2000);
}

void loop() {
  int tiempo = millis() / 1000;

  // Lee la temperatura del sensor DHT11
  float temperaturaCelsius = dht.readTemperature();

  Serial.print("Tiempo: ");
  Serial.print(tiempo);
  Serial.print(" - Temperatura: ");
  Serial.println(temperaturaCelsius);

  // Enviar datos a ThingSpeak
  ThingSpeak.writeField(2439854, 3, temperaturaCelsius, thingSpeakApiKey);

  delay(15000);
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

