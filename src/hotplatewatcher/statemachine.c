#include <Arduino.h> // millis()
#include "statemachine.h"

#define TMP_BUFF_LEN 30

char tmp_msg[TMP_BUFF_LEN];


void next_state(struct state_s *state)
{
  if(state->logging) {
    snprintf(tmp_msg, TMP_BUFF_LEN, "\nTemperature: %d\n", state->current_temp);
    hs_writeStr(0, tmp_msg);
    snprintf(tmp_msg, TMP_BUFF_LEN, "current_state: %d\n", state->current_state);
    hs_writeStr(0, tmp_msg);
    snprintf(tmp_msg, TMP_BUFF_LEN, "current_time: %d\n", state->current_time);
    hs_writeStr(0, tmp_msg);
    // problem here:
    snprintf(tmp_msg, TMP_BUFF_LEN, "time_since_guarding: %d\n", state->time_since_guarding);
    hs_writeStr(0, tmp_msg);
    
  }
  
    switch (state->current_state) {
    case WATCHING:
        if(state->current_temp > state->temp_threshold) {
            state->current_state = GUARDING;
            state->time_since_guarding = millis();
        }
        break;

    case GUARDING:
      if(state->current_temp < state->temp_threshold) {
        state->current_state = WATCHING;
      } else if((state->current_time - state->time_since_guarding) > state->time_threshold) {
        state->current_state = BEEPING;
      } 
      break;

    case BEEPING:
        break;

    default:
        break;
    }
}
