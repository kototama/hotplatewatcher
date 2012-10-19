#include "effector.h"
#include "pin.h"
#include <Arduino.h>

void fadding()
{
    // taken from the Arduino examples:
    // fade in from min to max in increments of 5 points:
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
        // sets the value (range from 0 to 255):
        analogWrite(SPEAKER_PIN, fadeValue);         
        // wait for 30 milliseconds to see the dimming effect    
        delay(30);                            
    } 

    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
        // sets the value (range from 0 to 255):
        analogWrite(SPEAKER_PIN, fadeValue);         
        // wait for 30 milliseconds to see the dimming effect    
        delay(30);                            
    } 
}

void apply_state(struct state_s *state)
{
    if(state->current_state == BEEPING) {
        while(1) {
            fadding();
            // we beep and do nothing more
        } 
    }
    
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
