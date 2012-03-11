#include "sensors.h"
#include "state.h"
#include "ktytemp.h"
#include "pin.h"
#include "hserial.h"

void take_time(struct state_s *state)
{
    state->current_time = millis();
}

void take_temp(struct state_s *state)
{
  char tmp_msg[25];
  
  int pin_val = analogRead(THERMISTOR_PIN);
  state->current_temp = (int)temp(pin_val);
}

