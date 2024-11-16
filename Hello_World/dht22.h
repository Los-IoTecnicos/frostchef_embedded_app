#ifndef DHT22_H
#define DHT22_H

#include <DHT.h>
#include <Arduino.h>

extern DHT dht;

void initDht();

float getTemperature();

float getHumidity();

#endif