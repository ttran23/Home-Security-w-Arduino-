// Author:         Team 219
// Net ID:         qsz, ttran23 <your IDs here>
// Date:           14 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#include "serial.h"
#include <avr/io.h>

#define FOSC 16000000 // Clk Frequency
#define BAUD 9600 // BAUD Rate

void initSerial(){
  // Enable receiver and transmitter
  UCSR1B = (1 << TXEN1);
  // UCSR2B = (1 << RXEN2);
  // Calculate UBRR
  unsigned char ubrr = 0;
  ubrr = FOSC/16/BAUD - 1;
  // Assign baud rate
  UBRR1H = (unsigned char)(ubrr >> 8);
  UBRR1L = (unsigned char)(ubrr);
  // UBRR2H = (unsigned char)(ubrr >> 8);
  // UBRR2L = (unsigned char)(ubrr);
  // Set frame format: 8data, 2stop bit
  UCSR1C = (1 << USBS1 | 1 << UCSZ11 | 1 << UCSZ10);
  // UCSR2C = (1 << USBS2 | 1 << UCSZ21 | 1 << UCSZ20);
}

void transmitData( unsigned char data ) {
  // Wait for empty buffer
  while (!(UCSR1A & (1 << UDRE1)));
  // Put data in
  UDR1 = data;
}

// unsigned char receiveData( void ) {
//   // Wait for data
//   while (!(UCSR2A & (1 << RXC2)));
//   // Return data
//   return UDR2;
// }
