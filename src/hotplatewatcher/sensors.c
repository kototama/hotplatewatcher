#include "state.h"

void take_time(struct state_s *state)
{
    state->current_time = millis();
}

int current_temp = 19;

void take_temp(struct state_s *state)
{
    state->current_temp = current_temp++;
}

