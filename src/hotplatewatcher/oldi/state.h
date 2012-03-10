#ifndef _STATE_H_
#define _STATE_H_

enum state_e {WATCHING, GUARDING, BEEPING};

struct state_s {
    char logging; /* 0 if we are not logging to the serial port */
    enum state_e current_state;
    unsigned long current_time; /* current time in seconds */
    unsigned long time_since_guarding; /* time at which GUARDING started */
    unsigned long time_threshold; /* how long we wait before going from
                                     guarding to BEEPING */
    unsigned long unguard_time_threshold; /* if temperature has decreased
                                             how long we wait before
                                             going back to WATCHING */
    double current_temp; /* current temperature in celcius */  
    double temp_threshold; /* temperature threshold before going in GUARDING
                           state */
};

void init_state(struct state_s *state);

#endif

