#include "state.h"

void init_state(struct state_s *state)
{
    state->logging = 1;
    state->temp_index = -1;
    state->current_temp = -1;
    state->current_time = 0;
    state->current_state = WATCHING;
    state->time_since_guarding = 0;
    state->time_threshold = 60000; /* in milliseconds */
    state->temp_threshold = 25.0;
}

