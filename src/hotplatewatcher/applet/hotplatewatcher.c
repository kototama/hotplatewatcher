#include "util/delay.h"
#include "hserial.h"

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
  
//  delay(3000);
}

int main()
{
	setup();
	while(1)
		loop();

	return 0;
}

