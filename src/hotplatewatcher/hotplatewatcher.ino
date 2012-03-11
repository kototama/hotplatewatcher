extern "C" {
#include "hserial.h"
#include "ktytemp.h"
#include "pin.h"
#include "sensors.h"
#include "statemachine.h"
}


struct state_s state;

void setup() {
  init_state(&state);
  
  pinMode(13, OUTPUT);

  if(state.logging) {
    hs_init();
    hs_start(0, 9600); // set arduino soft to 19200 to read?!
  }
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  delay(3000);
  digitalWrite(LED_PIN, HIGH);

  take_time(&state);
  take_temp(&state);
  next_state(&state);
  
}
