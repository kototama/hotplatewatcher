#include "sensors.h"
#include "state.h"
#include "ktytemp.h"

unsigned long millis();
int analogRead(uint8_t pin);

void take_time(struct state_s *state)
{
    state->current_time = millis();
}

void take_temp(struct state_s *state)
{
    int pin_val = analogRead(THERMISTOR_PIN);
    state->current_temp = temp(pin_val);
}

