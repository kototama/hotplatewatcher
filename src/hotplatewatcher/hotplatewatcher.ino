extern "C" {
#include "hserial.h"
#include "ktytemp.h"
}

#define THERMISTOR_PIN A0
#define TMP_BUFF_LEN 25

#define LED_PIN 13

int thermistor_value = 0;
int temperature = 42;

char tmp_msg[TMP_BUFF_LEN];

void setup() {
  pinMode(13, OUTPUT);
  hs_init();
  hs_start(0, 9600); // set arduino soft to 19200 to read?!
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  delay(3000);
  digitalWrite(LED_PIN, HIGH);
  temperature = temp(analogRead(THERMISTOR_PIN));
  snprintf(tmp_msg, TMP_BUFF_LEN, "Temperature: %d\n", temperature);
  hs_writeStr(0, tmp_msg);
}
