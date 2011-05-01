#ifndef _STATE_H_
#define _STATE_H_

enum state_e {WATCHING, GUARDING, BEEPING};

struct state_s {
    char logging; /* 0 if we are not logging to the serial port */
    enum state_e current_state;
    unsigned long current_time; /* current time in seconds */
    unsigned long time_since_guarding; /* time at which guarding started */
    unsigned long time_threshold; /* how long we wait before going from
                                     guarding to beeping */
    unsigned long unguard_time_threshold; /* if temperature has decreased
                                             how long we wait before
                                             going back to watching */
};

void init_state(struct state_s *state);

#endif

