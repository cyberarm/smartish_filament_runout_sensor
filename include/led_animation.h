#pragma once

#define LED_ANIMATION_OKAY 0
#define LED_ANIMATION_TRIGGERED 1
#define LED_ANIMATION_ISSUE 2

// typedef struct LedAnimation
// {
//   int frames[8][3];    // max of 8 frames, with RGB values.
//   int frame_count = 0; // number of frames to "animate"
//   int frame_index = 0;
//   int delay = 250; // ms
// } LedAnimation;

uint8_t led_animation = LED_ANIMATION_OKAY;
uint8_t led_animation_frame = 0;
uint16_t led_animation_delay = 0;
unsigned long last_led_frame_time = 0;

void led_animation_okay()
{
  set_led_color(0, 0, 0);
}

void led_animation_triggered()
{
  unsigned long frame_interval = 500;

  if (led_animation_frame >= 7)
  {
    led_animation_frame = 0;
  }

  switch (led_animation_frame)
  {
  case 0:
  case 2:
  case 4:
    set_led_color(MAX_LED_RED, 0, 0);
    break;
  default:
    set_led_color(0, 0, 0);
    break;
  }

  if (last_led_frame_time >= frame_interval)
  {
    led_animation_frame++;
    last_led_frame_time = 0;
  }
}

void led_animation_issue()
{
  unsigned long frame_interval = 250;

  if (led_animation_frame >= 4)
  {
    led_animation_frame = 0;
  }

  switch (led_animation_frame)
  {
  case 0:
    set_led_color(MAX_LED_RED, MAX_LED_GREEN, 0);
    break;
  case 2:
    set_led_color(MAX_LED_RED, 0, MAX_LED_BLUE);
    break;
  default:
    set_led_color(0, 0, 0);
    break;
  }

  if (last_led_frame_time >= frame_interval)
  {
    led_animation_frame++;
    last_led_frame_time = 0;
  }
}
