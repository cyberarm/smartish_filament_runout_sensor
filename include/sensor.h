#pragma once
#include <Arduino.h>
#include "sensor.h"

/// SENSOR ///
/* Signal from sensor to mcu */
#define SENSOR_PIN 1
#define SENSOR_PIN_INVERT true // Whether to invert the value of the pin

#define SENSOR_HISTORY_SIZE 128
#define SENSOR_UNSTABLE_COUNT 1
#define SENSOR_JITTER_MS 1500

bool sensor_history[SENSOR_HISTORY_SIZE] = {false};
int sensor_history_index = 0;
int sensor_unstable_time = 0;

bool read_sensor()
{
  bool value = digitalRead(SENSOR_PIN);

  if (SENSOR_PIN_INVERT)
  {
    return !value;
  }
  else
  {
    return value;
  }
}

void handle_sensor()
{
  read_sensor() ? signal_okay() : signal_triggered();
}

bool is_sensor_pin_stable(int tick_delay)
{
  int high_count = 0;
  int low_count = 0;

  for (bool v : sensor_history)
  {
    if (v)
      high_count++;
    if (!v)
      low_count++;
  }

  // SENSOR_UNSTABLE_COUNT events in history count as floating pin.
  bool stable = (SENSOR_HISTORY_SIZE - abs(high_count - low_count) < SENSOR_UNSTABLE_COUNT);

  if (!stable) {
    sensor_unstable_time += tick_delay;
    if (sensor_unstable_time > SENSOR_JITTER_MS)
      sensor_unstable_time = SENSOR_JITTER_MS;
  } else {
    sensor_unstable_time -= tick_delay;
    if (sensor_unstable_time < 0)
      sensor_unstable_time = 0;
  }

  return sensor_unstable_time < SENSOR_JITTER_MS;
}
