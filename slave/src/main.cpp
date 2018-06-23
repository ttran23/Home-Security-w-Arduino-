// Author:         Team 219
// Net ID:         qsz, ttran23 <your IDs here>
// Date:           14 April 2017
// Assignment:     Final Project
//
// Description: This file contains the driver for the device that connects to
//the sensor. The sensor data will be transmitted to the receiver device using USART.
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "serial.h"
#include "sensor.h"

// Defines for constants
#define ON 1
#define OFF 0
#define SYSON 11
#define SYSOFF 10
#define THRESHOLD 500

// State types
typedef enum systemType_enum {
  systemOn, systemOff
} systemType;

// Global variables
volatile systemType systemState = systemOff;
unsigned char data = 's'; // s for slave
volatile unsigned int irAdcVal = 500;

int main() {
  // Debugging w/ Serial.println()
  Serial.begin(9600);
  // Initialization
  initSerial();
  initADC();
  toggleIrAdc(ON);
  togglePirPin(ON);

  while(1) {
    // Sampling distance.
    // irAdcVal = 490; // Hardcode for testing w/out sensor
    getIrSample();  // Testing w/ sensor
    data = OFF;
    if ( (irAdcVal > THRESHOLD) || (PINA & (1 << PORTA1)) ) {
      Serial.print("PINA: ");
      Serial.print(PINA);
      data = ON;
    }
    Serial.print("Data: ");
    Serial.println(data);
    transmitData(data);
  }
  return 0;
}

/*

  temp = 'z';
  Serial.print("Slave sent: ");
  Serial.println(temp);
  transmitData(temp);
  _delay_ms(1000);
  temp = receiveData();
  Serial.print("Slave received: ");
  Serial.println(temp);
  */
