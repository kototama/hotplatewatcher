#include <pins_arduino.h>

#include "ktytemp.h"

#include "util/delay.h"
#include "hserial.h"

#define PIN_THERMISTOR A0
#define TMP_BUFF_LEN 25

int thermistor_value = 0;
int temperature = 0;

char tmp_msg[TMP_BUFF_LEN];


void setup();
void loop();

void setup() {
//  delay(3000);

  pinMode(13, OUTPUT);
  hs_init();
  hs_start(0, 9600);

}

void loop() {

  _delay_ms(3000);
  digitalWrite(13, HIGH);
  
  hs_writeChar(0, (uint8_t)'a');
  hs_writeChar(0, (uint8_t)64);
  hs_writeStr(0, "hello\n");
  snprintf(tmp_msg, TMP_BUFF_LEN, "Hello %d\n", 1042);
  hs_writeStr(0, tmp_msg);
//  delay(3000);
}

int main()
{
	setup();
	while(1)
		loop();

	return 0;
}

