#include <Arduino.h>
static const byte READ_PIN = 34;
volatile byte state = LOW;

bool reset_button = false;
unsigned long last_tick_count;
void IRAM_ATTR reset_pressed()
{
  if (((unsigned long)(xTaskGetTickCount() - last_tick_count)) >= 400)
  {
    state = !state;
    last_tick_count = xTaskGetTickCount();
    Serial.println("Button pressed");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(READ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(READ_PIN), reset_pressed, CHANGE);
}
void loop()
{
  digitalWrite(2, state);

  delay(100);
}
