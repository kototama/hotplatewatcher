/*
 * hserial.c
 *
 *  Created on: Jul 25, 2009
 *      Author: Orlando Arias
 *     License: GPLv3
 *
 *
 *   Based off: HardwareSerial.cpp
 *
 *   Special thanks to RuggedCircuits for fixing bug on hs_writeChar() function.
 *   		http://www.ruggedcircuits.com/
 *
 */
#include <inttypes.h>
#include <stdio.h>
#include "wiring_private.h"

#include "hserial.h"

// function prototypes
void hs_parseStr(const int port, const char *str);
inline void store_char(unsigned char c, ring_buffer_t *rx_buffer);

// Initialize rx_buffer arrays accordingly.
#if defined(__AVR_ATmega1280__)
	ring_buffer_t rx_buffer[4] = { { { 0 }, 0, 0 },
								 { { 0 }, 0, 0 }
								 { { 0 }, 0, 0 }
								 { { 0 }, 0, 0 } };
#else
	ring_buffer_t rx_buffer[1] =  { { { 0 }, 0, 0 } };
#endif

// serial macros
#if defined(__AVR_ATmega1280__)

SIGNAL(SIG_USART0_RECV)
{
	unsigned char c = UDR0;
  store_char(c, &rx_buffer[0]);
}

SIGNAL(SIG_USART1_RECV)
{
	unsigned char c = UDR1;
  store_char(c, &rx_buffer[1]);
}

SIGNAL(SIG_USART2_RECV)
{
	unsigned char c = UDR2;
  store_char(c, &rx_buffer[2]);
}

SIGNAL(SIG_USART3_RECV)
{
	unsigned char c = UDR3;
  store_char(c, &rx_buffer[3]);
}

#else

#if defined(__AVR_ATmega8__)
SIGNAL(SIG_UART_RECV)
#else
SIGNAL(USART_RX_vect)
#endif
{
#if defined(__AVR_ATmega8__)
	unsigned char c = UDR;
#else
	unsigned char c = UDR0;
#endif
  store_char(c, &rx_buffer[0]);
}
#endif

// Initialize serial objects according to processor type.
void hs_init(){
	#if defined(__AVR_ATmega8__)
		SerialV[0].rx_buffer = &rx_buffer[0];
		SerialV[0].ubrrh = &UBRRH;
		SerialV[0].ubrrl = &UBRRL;
		SerialV[0].ucsra = &UCSRA;
		SerialV[0].ucsrb = &UCSRB;
		SerialV[0].udr = &UDR;
		SerialV[0].rxen = RXEN;
		SerialV[0].txen = TXEN;
		SerialV[0].rxcie = RXCIE;
		SerialV[0].udre = UDRE;
	#else
		SerialV[0].rx_buffer = &rx_buffer[0];
		SerialV[0].ubrrh = &UBRR0H;
		SerialV[0].ubrrl = &UBRR0L;
		SerialV[0].ucsra = &UCSR0A;
		SerialV[0].ucsrb = &UCSR0B;
		SerialV[0].udr = &UDR0;
		SerialV[0].rxen = RXEN0;
		SerialV[0].txen = TXEN0;
		SerialV[0].rxcie = RXCIE0;
		SerialV[0].udre = UDRE0;
	#endif

	#if defined(__AVR_ATmega1280__)
		SerialV[1].rx_buffer = &rx_buffer[1];
		SerialV[1].ubrrh = &UBRR1H;
		SerialV[1].ubrrl = &UBRR1L;
		SerialV[1].ucsra = &UCSR1A;
		SerialV[1].ucsrb = &UCSR1B;
		SerialV[1].udr = &UDR1;
		SerialV[1].rxen = RXEN1;
		SerialV[1].txen = TXEN1;
		SerialV[1].rxcie = RXCIE1;
		SerialV[1].udre = UDRE1;

		SerialV[2].rx_buffer = &rx_buffer[2];
		SerialV[2].ubrrh = &UBRR2H;
		SerialV[2].ubrrl = &UBRR2L;
		SerialV[2].ucsra = &UCSR2A;
		SerialV[2].ucsrb = &UCSR2B;
		SerialV[2].udr = &UDR2;
		SerialV[2].rxen = RXEN2;
		SerialV[2].txen = TXEN2;
		SerialV[2].rxcie = RXCIE2;
		SerialV[2].udre = UDRE2;

		SerialV[3].rx_buffer = &rx_buffer[3];
		SerialV[3].ubrrh = &UBRR3H;
		SerialV[3].ubrrl = &UBRR3L;
		SerialV[3].ucsra = &UCSR3A;
		SerialV[3].ucsrb = &UCSR3B;
		SerialV[3].udr = &UDR3;
		SerialV[3].rxen = RXEN3;
		SerialV[3].txen = TXEN3;
		SerialV[3].rxcie = RXCIE3;
		SerialV[3].udre = UDRE3;
	#endif
}

void hs_start(const int port, unsigned long baud){
	*SerialV[port].ubrrh = ((F_CPU / 16 + baud / 2) / baud - 1) >> 8;
	*SerialV[port].ubrrl = ((F_CPU / 16 + baud / 2) / baud - 1);
	sbi(*SerialV[port].ucsrb, SerialV[port].rxen);
	sbi(*SerialV[port].ucsrb, SerialV[port].txen);
	sbi(*SerialV[port].ucsrb, SerialV[port].rxcie);
}

uint8_t hs_available(const int port){
	return (RX_BUFFER_SIZE + SerialV[port].rx_buffer->head -
			SerialV[port].rx_buffer->tail) % RX_BUFFER_SIZE;
}

int hs_getChar(const int port){
	/*
	 * If the head isn't ahead of the tail,
	 * we don't have any characters
	 */
	if (SerialV[port].rx_buffer->head == SerialV[port].rx_buffer->tail) {
		return -1;
	} else {
		unsigned char c =
			SerialV[port].rx_buffer->buffer[SerialV[port].rx_buffer->tail];
		SerialV[port].rx_buffer->tail =
			(SerialV[port].rx_buffer->tail + 1) % RX_BUFFER_SIZE;
		return c;
	}
}

void hs_flush(const int port){
	SerialV[port].rx_buffer->head =
			SerialV[port].rx_buffer->tail;
}

void hs_writeChar(const int port, uint8_t c){
	while (!((*SerialV[port].ucsra) & (1 << SerialV[port].udre)));
	*(SerialV[port].udr) = c;
}

void hs_writeStr(const int port, const char str[]){
	hs_parseStr(port, str);
}

void hs_parseStr(const int port, const char *str){
	  while (*str)
	    hs_writeChar(port, *str++);
}

inline void store_char(unsigned char c, ring_buffer_t *rx_buffer){
	int i = (rx_buffer->head + 1) % RX_BUFFER_SIZE;
	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != rx_buffer->tail) {
		rx_buffer->buffer[rx_buffer->head] = c;
		rx_buffer->head = i;
	}
}
