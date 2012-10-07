#include "effector.h"
#include "pin.h"
#include <Arduino.h>

void apply_state(struct state_s *state)
{
    if(state->current_state == WATCHING
       || (state->current_state == GUARDING && state->previous_state == WATCHING) ) {
        digitalWrite(LED_PIN, HIGH);
    }

    delay(1000);

    if(state->current_state == WATCHING) {
        digitalWrite(LED_PIN, LOW);
    }

    delay(1000);
 
    state->previous_state = state->current_state;
}
