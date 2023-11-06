#pragma once
#include <Arduino.h>

/// SIGNAL ///
/* Signal back to controller */
#define SIGNAL_PIN 2

/// SIGNAL FUNCTIONS ///
bool signal_status = HIGH;
volatile bool signal_pin_state = false;
volatile bool signal_pin_state_changed = false;

void signal_okay()
{
  signal_status = HIGH;
  digitalWrite(SIGNAL_PIN, signal_status);
}

void signal_triggered()
{
  signal_status = LOW;
  digitalWrite(SIGNAL_PIN, signal_status);
}

void signal_issue()
{
  // Send "PWM" to host?
}
