// Author:         Team 219
// Net ID:         ttran23, <your IDs here>
// Date:           1 April 2017
// Assignment:     Final Project
//----------------------------------------------------------------------//

#ifndef PWM_H
#define PWM_H

// typedef enum motorStateType_enum{
//   forward, reverse, idle
// } motorStateType;

void initPWM();
void setAlarmFreq(int num);
void toggleAlarm(int num);
void initLED();
void toggleLED(int num);

#endif
