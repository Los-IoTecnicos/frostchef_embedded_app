// Local Devices
#include "lcd_display.h"
#include "hc_sr04.h"

void setup() {
    // Inicializar el LCD
    initializeLCD();

    // Inicializar comunicación serial
    Serial.begin(9600);

    initializeSensor();
}

void loop() {
    
    float distance = getDistance();
    displayData("Dist: ", distance, "cm");
    delay(500);
}
