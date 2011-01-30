/*
 * SerialLCD.cpp
 *
 *  Created on: Jan 30, 2011
 *      Author: Andy
 */

#include "SerialLCD.h"

#define MAX_TEMP_DISPLAY_LENGTH 20



char * tempSensors[][10] = {"Outside", "Garage"};

void ClearLCD()
{
	char null = '\0';
	Serial1.print(null);
}

void DisplayTemp(char * temp, int sensor)
{
	char  msg[MAX_TEMP_DISPLAY_LENGTH];
	sprintf(msg, "%s: %s",tempSensors[sensor][0], temp);
	Serial1.print(msg);
}
