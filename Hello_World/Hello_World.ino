// Local Devices
#include "lcd_display.h"
#include "hc_sr04.h"

void setup() {
    // Inicializar el LCD
    initializeLCD();

    // Inicializar comunicación serial
    Serial.begin(9600);

    inicializar_sensor();
}

void loop() {
    
    float distancia = obtener_distancia();
    displayData("Distance", distancia, "cm");
    delay(500);
}
