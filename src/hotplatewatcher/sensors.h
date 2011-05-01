#ifndef _SENSORS_H
#define _SENSORS_H

#include "state.h"

#include "WProgram.h"

#define THERMISTOR_PIN 0

void take_time(struct state_s *state);
void take_temp(struct state_s *state);

#endif

