// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#include "pwm.h"
#include "timer.h"
#include <avr/io.h>

// Defines for constants
#define ON 1
#define OFF 0

// Clock is 16 MHz
// Using Timer 3 for PWM. May need another timer as well.
void initPWM(){
  // Using Fast PWM OCRnA as TOP for frequency compare
  // WGMn[3:0] = 1111, 15: Fast PWM (OCRnA)   Datasheet 17.9.3
  TCCR3B |= (1 << WGM33 | 1 << WGM32);
  TCCR3A |= (1 << WGM31 | 1 << WGM30);

  // Clear OCnA/OCnB/OCnC on compare match, Basically will NOT invert PWM
  TCCR3A |= (1 << COM3A0); // | 1 << COM3B0 | 1 << COM3C0);
  TCCR3A &= ~(1 << COM3A1); // | 1 << COM3B1 | 1 << COM3C1);

  // Using no prescalar
  // CSn[2:0] = 001, 1: Clk
  TCCR3B &= ~(1 << CS32 | 1 << CS31);
  TCCR3B |= (1 << CS30);

  // Set the pin as output
  // DDE3 (PE3) for OC3A and DDE4 (PE4) for OC3B (Schematic)
  // On the board, we have to use these pins for this as per schematic
  DDRE |= (1 << DDE3);

}

void setAlarmFreq(int inputFreq) {

  // Need to sweep 24kHz to 2kHz in 100ms
  int TOPVAL = 0;
  TOPVAL = (16000000/inputFreq) - 1;

  OCR3AH = TOPVAL >> 8;     // Shifts numTicks 8 bits and
  OCR3AL = (TOPVAL & 255);  // Sets lower 8 bits

}

void toggleAlarm(int num) {
  if (num == ON) {
    // CSn[2:0] = 001, 1: Clk
    TCCR3B &= ~(1 << CS32 | 1 << CS31);
    TCCR3B |= (1 << CS30);
  }
  else if (num == OFF) {
    // CSn[2:0] = 000, 0: Off
    TCCR3B &= ~(1 << CS32 | 1 << CS31 | 1 << CS30);
  }
}

// Roberto's code, pasting as is.
void initLED(){
  DDRL |= (1 << PL3);
}

// Roberto's code, pasting as is.
void toggleLED(int num){
  if (num == ON) {
    PORTL |= (1 << PORTL3);
  }
  else if (num == OFF){
    PORTL &= ~(1 << PORTL3);
  }
}
