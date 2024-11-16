#include "lcd_display.h"

// Inicializar el objeto LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Función para inicializar el LCD
void initializeLCD() {
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();
    lcd.print("System Start");
    delay(1000);
}

// Función para mostrar un mensaje en el LCD
void displayMessage(const char* message) {
    lcd.clear();
    lcd.print(message);
}
