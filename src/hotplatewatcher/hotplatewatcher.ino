extern "C" {
#include "hserial.h"
#include "ktytemp.h"
}

#define THERMISTOR_PIN A0
#define TMP_BUFF_LEN 25

int thermistor_value = 0;
int temperature = 42;

char tmp_msg[TMP_BUFF_LEN];

void setup() {
//  delay(3000);

  pinMode(13, OUTPUT);
   /* Serial.begin(9600); */
  hs_init();
  hs_start(0, 9600); // set arduino soft to 19200 to read?!

}

void loop() {

  /* _delay_ms(3000); */
  
  digitalWrite(13, HIGH);
  delay(3000);
  hs_writeStr(0, "hello world");
  /* Serial.println("hello world"); */
  
  // hs_writeStr(0, "xbx");
  // hs_writeChar(0, (uint8_t)64);
  // hs_writeStr(0, "hello\n");
  temp(10);
  /* temperature = analogRead(THERMISTOR_PIN) + 42; */
  /* snprintf(tmp_msg, TMP_BUFF_LEN, "Temperature: %d\n", temperature); */
  // hs_writeStr(0, tmp_msg);

}
