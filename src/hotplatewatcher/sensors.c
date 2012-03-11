#include "sensors.h"
#include "state.h"
#include "ktytemp.h"
#include "pin.h"
#include "hserial.h"

/*
  We take the average of 10 measures to increase
  fiability and avoid problems with the threashold
 */
int temp_avg(int temperature, struct state_s *state)
{
  if(state->temp_index == -1) {
    for(int i = 0; i < NB_TEMPERATURES; i++) {
      state->temperatures[i] = temperature;
    }
    state->temp_index = 0;
    
    return temperature;
    }
  if(state->temp_index == NB_TEMPERATURES - 1) {
    state->temp_index = 0;
    state->temperatures[0] = temperature;
  } else {
    state->temp_index++;
    state->temperatures[state->temp_index] = temperature;
  }

  int sum = 0;
  for(int i = 0; i < NB_TEMPERATURES; i++) {
    sum += state->temperatures[i];
  }

  return (int)(sum / NB_TEMPERATURES);
}

void take_time(struct state_s *state)
{
    state->current_time = millis();
}

void take_temp(struct state_s *state)
{
  int pin_val = analogRead(THERMISTOR_PIN);
  int temperature = (int)temp(pin_val);
  state->current_temp = temp_avg(temperature, state);
}

