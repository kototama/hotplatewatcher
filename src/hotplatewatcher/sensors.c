#include "state.h"

void take_time(struct state_s *state)
{
    state->current_time = millis();
}

