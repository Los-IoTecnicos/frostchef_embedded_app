#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal_I2C.h>

// Declarar el objeto LCD
extern LiquidCrystal_I2C lcd;

// Funciones relacionadas con el LCD
void initializeLCD();
void displayMessage(const char* message);
void displayData(const char* message, float data, const char* measure);
void changeRow(int row);
void clearDisplay();
#endif
