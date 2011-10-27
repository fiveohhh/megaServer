/*
 * tasks.h
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "WProgram.h" //Include arduino headers
#include "Time.h"
#include "MessageProcessing.h"
#include "Networking.h"

void ToggleLED();
void Daily();
void OneMinute();
void ThirtySeconds();
void TenSeconds();
void OneSecond();
void FastAsPossible();
void RunScheduledTasks();
void InitializeTaskRunner();

extern RTC_DS1307 RTC;

#endif /* TASKS_H_ */
