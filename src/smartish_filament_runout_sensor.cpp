#include <Arduino.h>
#include <util/delay.h>

#include "signal.h"
#include "sensor.h"
#include "led.h"
#include "led_animation.h"

#define DELAY_MS 8

/// SETUP ///
void setup()
{
  pinMode(SIGNAL_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

/// MAIN LOOP ///
void loop()
{
  bool v = read_sensor();
  sensor_history[sensor_history_index] = v;
  sensor_history_index++;
  sensor_history_index %= SENSOR_HISTORY_SIZE;

  if (signal_pin_state != v)
  {
    signal_pin_state_changed = true;

    signal_pin_state = v;
  }

  int old_led_animation;
  old_led_animation = led_animation;

  if (is_sensor_pin_stable(DELAY_MS))
  {
    if (signal_pin_state)
    {
      led_animation = LED_ANIMATION_OKAY;
      signal_okay();
    }
    else
    {
      led_animation = LED_ANIMATION_TRIGGERED;
      signal_triggered();
    }
  }
  else
  {
    led_animation = LED_ANIMATION_ISSUE;
    signal_issue();
  }

  if (led_animation != old_led_animation)
  {
    led_animation_frame = 0;
    last_led_frame_time = 0;
  }

  switch (led_animation)
  {
  case LED_ANIMATION_OKAY:
    led_animation_okay();
    break;
  case LED_ANIMATION_TRIGGERED:
    led_animation_triggered();
    break;
  case LED_ANIMATION_ISSUE:
    led_animation_issue();
    break;
  }

  delay(DELAY_MS); // ~125 ticks per second
  last_led_frame_time += DELAY_MS;
}
