// Local Devices
#include "lcd_display.h"
#include "hc_sr04.h"
#include "dht22.h"

void setup() {
    // Inicializar el LCD
    initializeLCD();

    // Inicializar comunicación serial
    Serial.begin(9600);

    initProximity();
}

void loop() {
    
    float temperature = getTemperature();
    float humidity = getHumidity();

    clearDisplay();
    
    changeRow(0);
    if (temperature != -999) {
        displayData("Temp: ", temperature, "C");
    } else {
        displayData("Temp: ", 0, "ERR");
    }

    changeRow(1);
    if (humidity != -999) {
        displayData("Hum: ", humidity, "%");
    } else {
        displayData("Hum: ", 0, "ERR");
    }

    delay(2000); // Tiempo suficiente para evitar lecturas consecutivas rápidas
}
