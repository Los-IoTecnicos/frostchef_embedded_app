// Local Devices
#include "lcd_display.h"
#include "hc_sr04.h"
#include "dht22.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "iot-sensor";
const char* password = "diegosanchez";

// Server URLs
const char* checkUrl = "https://frostchef-edge-api-production.up.railway.app/api/read/sensors/check";
const char* registerUrl = "https://frostchef-edge-api-production.up.railway.app/api/write/sensors/register";
const char* updateUrl = "https://frostchef-edge-api-production.up.railway.app/api/write/sensors/update";

// Thresholds for Temperature and Humidity
const float tempThreshold = 20.0;   // Temperature threshold
const float humThreshold = 40.0;    // Humidity threshold

// Variables
String macAddress;
int proximity = 0;
int gasMethane = 0;
float temperature = 0;
float humidity = 0;

// Flag para verificar si el dispositivo está registrado
bool isRegistered = false;

void checkRegistration() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(String(checkUrl) + "?macAddress=" + macAddress);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      Serial.println("Device is already registered.");
      isRegistered = true;
    } else {
      Serial.print("Device is not registered. HTTP Response code: ");
      Serial.println(httpResponseCode);
      isRegistered = false;
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

// Función para registrar el dispositivo
void registerSensor() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    return;
  }

  HTTPClient http;
  http.begin(registerUrl);
  http.addHeader("Content-Type", "application/json");

  // Crear JSON para el registro
  StaticJsonDocument<200> doc;
  doc["macAddress"] = macAddress;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["proximity"] = proximity;
  doc["gasMethane"] = gasMethane;

  String payload;
  serializeJson(doc, payload);

  Serial.println("Registering device...");
  Serial.print("Payload: ");
  Serial.println(payload);

  // Establecer un timeout más largo
  http.setTimeout(10000);  // 10 segundos de timeout

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200 || httpResponseCode == 201) {
      Serial.println("Device registered successfully!");
      isRegistered = true;
    } else {
      // Mostrar el contenido completo de la respuesta del servidor
      String response = http.getString();
      Serial.println("Error response: ");
      Serial.println(response);
      Serial.print("Failed to register device. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
  } else {
    // Mostrar el contenido completo de la respuesta en caso de error
    String response = http.getString();
    Serial.println("Error response: ");
    Serial.println(response);
    Serial.print("HTTP request failed, error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

// Función para actualizar los datos del sensor
void updateSensorData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(updateUrl);
    http.addHeader("Content-Type", "application/json");

    // Crear JSON para la actualización
    StaticJsonDocument<200> doc;
    doc["macAddress"] = macAddress;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["proximity"] = proximity;
    doc["gasMethane"] = gasMethane;

    String payload;
    serializeJson(doc, payload);

    Serial.println("Updating sensor data...");
    Serial.print("Payload: ");
    Serial.println(payload);

    int httpResponseCode = http.PUT(payload);

    if (httpResponseCode == 200) {
      Serial.println("Sensor data updated successfully!");
    } else {
      Serial.print("Failed to update sensor data. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    lcd.setCursor(0, 1);
    lcd.print(".");
  }
  macAddress = WiFi.macAddress();
  Serial.print("MAC Address: ");
  Serial.println(macAddress);
  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);
  checkRegistration();
  Serial.print("WiFi Status: ");
  Serial.println(WiFi.status());
}

void setup() {
    // Inicializar el LCD
    initializeLCD();

    // Inicializar comunicación serial
    Serial.begin(9600);
    // Connect to WiFi
    connectToWiFi();
    initProximity();
}

void loop() {
    temperature = getTemperature();
    humidity = getHumidity();

    clearDisplay();
    
    changeRow(0);
    if (temperature != -999) {
        displayData("Temp: ", temperature, "C");
    } else {
        displayData("Temp: ", 0, "ERR");
    }

    changeRow(1);
    if (humidity != -999) {
        displayData("Hum: ", humidity / 10, "%");
    } else {
        displayData("Hum: ", 0, "ERR");
    }

    if (humidity != -999 && temperature != -999) {
      if (isRegistered) {
        // Actualizar datos si está registrado
        updateSensorData();
      } else {
        // Intentar registrar si no está registrado
        registerSensor();
        // Verificar registro nuevamente
        checkRegistration();
      }
    }

    delay(6000); // Tiempo suficiente para evitar lecturas consecutivas rápidas
}
