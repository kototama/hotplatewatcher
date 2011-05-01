extern "C" {
  #include "state.h"
  #include "sensors.h"
}

struct state_s state;

void setup() {
  delay(5000);
  init_state(&state);
  Serial.begin(9600);
}

void loop() {
  Serial.println("hello world");
  
  take_time(&state);
  
  if(state.logging) {
      Serial.print("time = ");
      Serial.println(state.current_time);
  }
    
  delay(2000);
}
