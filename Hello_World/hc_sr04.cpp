#include "hc_sr04.h"

// Definir los pines para el sensor ultrasónico
#define TRIGGER 26
#define ECHO 25

// Velocidad del sonido en cm/us
#define VELOCIDAD_SONIDO 0.034  

// Función para inicializar el sensor ultrasónico
void initProximity() {
  pinMode(TRIGGER, OUTPUT); 
  pinMode(ECHO, INPUT); 
}

// Función para obtener la distancia usando el sensor ultrasónico
float getDistance() {
  // Inicializar el TRIGGER en bajo
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Enviar la señal de pulsos de 10 microsegundos
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  // Calcular y devolver la distancia en centímetros
  return (pulseIn(ECHO, HIGH) * VELOCIDAD_SONIDO / 2);
}
