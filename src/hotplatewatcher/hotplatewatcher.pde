extern "C" {
  #include "state.h"
  #include "sensors.h"
  #include "statemachine.h"
}

struct state_s state;

void setup() {
  delay(5000);
  init_state(&state);
  Serial.begin(9600);
}

void loop() {
  
  take_temp(&state);
  take_time(&state);
  next_state(&state);
  
  if(state.logging) {
    
      Serial.println("\n=============");
      Serial.print("time = ");
      Serial.println(state.current_time);
      Serial.print("temp = ");
      Serial.println(state.current_temp);
      Serial.print("state = ");
        switch (state.current_state) {
        case WATCHING:
            Serial.println("WATCHING");
            break;
    
        case GUARDING:
            Serial.println("GUARDING");
            break;
    
        case BEEPING:
            Serial.println("BEEPING");
            break;
    
        default:
            break;
        }
  }
    
  delay(2000);
}
