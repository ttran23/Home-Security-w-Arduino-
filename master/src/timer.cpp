// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#include "timer.h"

void initTimer1(){
  // Set to CTC mode for the delay functions
  TCCR1A &= ~(1 << WGM11 | 1 << WGM10);   /// Sets bottom two bits to "xx00"
  TCCR1B |= (1 << WGM12);   /// Sets bits to "0100"
  TCCR1B &= ~(1 << WGM13);  /// Sets bits to "0x00"
}

void delayMs(unsigned int delay){
  unsigned int numTicks = 250 * delay;
  /// Datasheet 17.5 pg139
  /// Clear Timer Count, Turn to zero before starting the count
  TCNT1H = 0;
  TCNT1L = 0;
  /// Calculate the TOP value and assign it to OCR1A
  /// Using OCRnA because CTC mode we chose uses TOP reg OCRnA
  /// OCRnA 17.11.17 pg159, just uses bits.
  OCR1AH = numTicks >> 8;     // Shifts numTicks 8 bits and
  OCR1AL = (numTicks & 255);  // Sets lower 8 bits
  /// 16 MHz clock, 1milli sec = 16000 ticks/us
  /// Turning on, prescalar Clk/64
  TCCR1B |= (1 << CS10 | 1 << CS11);
  TCCR1B &= ~(1 << CS12);
  // Do nothing while the OCF1A flag is not up
  // OCF1A flag is up when timer_counter = OCR1A
  while(!(TIFR1 & (1 << OCF1A)));
  // Clear the OCF1A flag
  TIFR1 |= (1 << OCF1A);
  // Turn off the timer
  TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12);
}

void delayUs(unsigned int delay){
  unsigned int numTicks = 2 * delay;
  /// Datasheet 17.5 pg139
  /// Clear Timer Count, Turn to zero before starting the count
  TCNT1H = 0;
  TCNT1L = 0;
  /// Calculate the TOP value and assign it to OCR1A
  /// Using OCRnA because CTC mode we chose uses TOP reg OCRnA
  /// OCRnA 17.11.17 pg159, just uses bits.
  OCR1AH = numTicks >> 8;     // Shifts numTicks 8 bits and
  OCR1AL = (numTicks & 255);  // Sets lower 8 bits
  /// 16 MHz clock, 1micro sec = 16 ticks/us
  /// Turning on, prescalar Clk/8
  TCCR1B &= ~(1 << CS12 | 1 << CS10);
  TCCR1B |= (1 << CS11);
  // Do nothing while the OCF1A flag is not up
  /// OCF1A flag is up when timer_counter = OCR1A
  while(!(TIFR1 & (1 << OCF1A)));
  // Clear the OCF1A flag
  TIFR1 |= (1 << OCF1A);
  // Turn off the timer
  TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12);
}
