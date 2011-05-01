#include "state.h"

void init_state(struct state_s *state)
{
    state->logging = 1;
    state->current_state = WATCHING;
    state->time_threshold = 1000; /* 1 minute */
    state->temp_threshold = 25;
}
