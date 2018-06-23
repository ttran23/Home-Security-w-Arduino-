// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

void initSwitchPB3(){
  DDRB &= ~(1 << DDB3);     // turn into input
  PORTB |= (1 << PORTB3);   // enable pull up register
  PCICR |= (1 << PCIE0);    // enable pin-change interrupts, 15.2.5 on DataSheet
  PCMSK0 |= (1 << PCINT3);  // enable interrupts on PB3, Schematic, PB3 == PCINT3
}
