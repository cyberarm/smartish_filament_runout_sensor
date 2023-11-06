#pragma once
#include <Arduino.h>

/// LED ///
/* Indictator LED */
#define LED_RED_PIN 0
#define LED_GREEN_PIN 4
#define LED_BLUE_PIN 3

#define MAX_LED_RED 255
#define MAX_LED_GREEN 100
#define MAX_LED_BLUE 120

/// LED FUNCTIONS ///
void set_led_color(uint8_t red, uint8_t green, uint8_t blue)
{
  analogWrite(LED_RED_PIN, (255 - red) % 256);
  analogWrite(LED_GREEN_PIN, (255 - green) % 256);
  // analogWrite(LED_BLUE_PIN, (255 - blue) % 256);
  digitalWrite(LED_BLUE_PIN, blue > 0 ? LOW : HIGH); // Meh. Blue is binary.
}
