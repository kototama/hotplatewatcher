#include "statemachine.h"

#include "WProgram.h"

void next_state(struct state_s *state)
{
    switch (state->current_state) {
    case WATCHING:
        if(state->current_temp > state->temp_threshold) {
            state->current_state = GUARDING;
            state->time_since_guarding = millis();
        }
        break;

    case GUARDING:
        break;

    case BEEPING:
        break;

    default:
        break;
    }
}
