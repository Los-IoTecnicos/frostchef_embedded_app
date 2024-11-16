/*
*	Hello_World.ino
*
*	Author: Frank Häfele
*	Date:	01.12.2023
*
*	Object: Print Hello World on LCD Display
*/

#include <LCD-I2C.h>
#include <Wire.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

void setup() {
    // If you are using more I2C devices using the Wire library use lcd.begin(false)
    // this stop the library(LCD-I2C) from calling Wire.begin()
    Wire.begin();
    lcd.begin(&Wire);
    lcd.display();
    lcd.backlight();
}

void loop()
{   
    lcd.clear();
    lcd.print("Agradecido"); // You can make spaces using well... spaces
    delay(500);

    
    
}
