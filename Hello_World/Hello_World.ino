// Local Devices
#include "lcd_display.h"

void setup() {
    // Inicializar el LCD
    initializeLCD();

    // Inicializar comunicación serial
    Serial.begin(9600);
}

void loop() {
    // Mostrar mensaje en el LCD
    displayMessage("On-line");
    delay(500);
}
