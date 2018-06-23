// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//
// Description: This file contains a programmatic overall description of the
// program. It houses the state machine and controls the transitions.
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "serial.h"
// #include "timer.h"
#include "switch.h"
#include "pwm.h"

// Defines for constants
#define ON 1
#define OFF 0
#define SYSON 11
#define SYSOFF 10

// State types
typedef enum systemType_enum {
  systemTurnOn, systemOn, //nothingOn,
  systemTurnOff, systemOff//, nothingOff
} systemType;

// Global variables
volatile systemType systemState = systemOff;
unsigned char data = 'm'; // m for master
unsigned char alarmStatus = OFF;
unsigned int alarmFreq = 24000;

int main() {
  // Debugging w/ Serial.println()
  Serial.begin(9600);
  // Global interrupt
  sei();
  // Initialization
  initSerial();
  initSwitchPB3();
  initPWM();
  // initTimer1();

  while(1) {
    switch (systemState) {
      case systemTurnOff:
        Serial.println("Turning OFF Master/Slave.");
        // Reset/Turn off alarm (LED)
        alarmStatus = OFF;
        setAlarmFreq(0);
        toggleAlarm(OFF);
        // toggleLED(OFF);
        // Transition
        systemState = systemOff;
        // systemState = nothingOff;
        break;

      case systemOff:
        Serial.print("Master is off, NOT monitoring. Alarm status: ");
        Serial.print(alarmStatus);
        Serial.print(" Data: ");
        Serial.println(data);
        data = receiveData();
        // Do nothing
        break;

      case systemTurnOn:
        Serial.println("Turning ON Master/Slave.");
        // Transition
        systemState = systemOn;
        // systemState = nothingOn;
        break;

      case systemOn:
        Serial.print("Master is on, IS monitoring. Alarm status: ");
        Serial.print(alarmStatus);
        // Sampling IR
        // getIrSample();
        // PIR will always sample if the PINA1 has been enabled.
        // _delay_ms(100);
        // Receive info from slave, check if threshold breached
        // Serial.println("before receive");
        data = receiveData();
        // Serial.println("after receive");
        if (data == ON) {
          alarmStatus = ON;
        }
        alarmFreq = (alarmFreq == 24000 ? 2000 : 24000);
        // If master receives that motion detected, sound alarm
        if (alarmStatus == ON) {
          Serial.print("Threshold triggered: ");
          toggleAlarm(ON);
          // toggleLED(ON);
          setAlarmFreq(alarmFreq);
          // delayMs(45);
        }
        Serial.println();
        break;
      // case nothingOn:
      //   break;
      // case nothingOff:
      //   break;
    }
  }
  return 0;
}

ISR(PCINT0_vect) {
  if (!(PINB & (1 << PORTB3))) {
      // If pushed, do nothing
  }
  else if ((PINB & (1 << PORTB3))) {
    switch(systemState) {
      case systemOff:
        systemState = systemTurnOn;
        break;
      case systemOn:
        systemState = systemTurnOff;
        break;
      // case nothingOn:
      //   systemState = systemOn;
      //   break;
      // case nothingOff:
      //   systemState = systemOff;
      //   break;
    }
  }
}

/*

unsigned char temp = 'A';

// temp = (temp == 'A' ? 'B' : 'A');
temp = 'A';
Serial.print("Master sent: ");
Serial.println(temp);
transmitData(temp);
_delay_ms(1000);
temp = receiveData();
Serial.print("Master received: ");
Serial.println(temp);
*/
