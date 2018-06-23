// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#include "sensor.h"
#include "math.h"
#include <avr/io.h>
#include <Arduino.h>

// Defines for constants
#define ON 1
#define OFF 0

extern volatile unsigned int irAdcVal;
unsigned int adcTemp = 0;

void initADC(){
  // Set AVCC as positive reference
  ADMUX |= (1 << REFS0);
  // Disabled pins 0 for digital input.
  DIDR0 |= (1 << ADC0D);
  // Setting ADC0 as input
  ADMUX &= ~(1 << MUX1 | 1 << MUX0);
  // Turns on the interrupt
  ADCSRA |= (1 << ADIE);
}

// My toggle is a simple enable/disable ADC
void toggleIrAdc(int num) {
  if (num == ON) {
    // Enable ADC
    ADCSRA |= (1 << ADEN);
  }
  else if (num == OFF) {
    // Disable ADC
    ADCSRA &= ~(1 << ADEN);
  }
}

// My toggle for the pin, using Roberto's init
void togglePirPin(int num) {
  if (num == ON) {
    // Set as input
    DDRA &= ~(1 << PA1);
    PINA &= ~(1 << PA1);
  }
  else if (num == OFF) {
    // Set as output
    DDRA |= (1 << PA1);
  }
}

// My sampling will just start conversion, and then after it completes,
// the external variable is updated.
void getIrSample() {
  // Start conversion
  ADCSRA |= (1 << ADSC);
  // Wait for conversion
  while((ADCSRA & (1 << ADSC)));
  adcTemp = ADCL;
  adcTemp = adcTemp + (ADCH << 8);
  irAdcVal = adcTemp;
}
