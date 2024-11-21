#include "dht22.h"
// DHT22 Sensor Setup
#define DHTPIN 4  // DHT sensor connected to GPIO 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void initDht(){
  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();
}

float getTemperature() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("Error: No se pudo leer la temperatura");
        return -999; // Valor especial para indicar error
    }
    return temperature;
}

float getHumidity() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Error: No se pudo leer la humedad");
        return -999; // Valor especial para indicar error
    }
    return humidity;
}
 