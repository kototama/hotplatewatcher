extern "C" {
#include "hserial.h"
#include "ktytemp.h"
#include "pin.h"
#include "sensors.h"
}

#define TMP_BUFF_LEN 25

char tmp_msg[TMP_BUFF_LEN];

struct state_s state;

void setup() {
  init_state(&state);
  
  pinMode(13, OUTPUT);
  hs_init();
  hs_start(0, 9600); // set arduino soft to 19200 to read?!
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  delay(3000);
  digitalWrite(LED_PIN, HIGH);

  take_temp(&state);
  snprintf(tmp_msg, TMP_BUFF_LEN, "Temperature: %d\n", state.current_temp);
  hs_writeStr(0, tmp_msg);
}
