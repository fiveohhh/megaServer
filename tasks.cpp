/*
 * tasks.cpp
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */
#include "tasks.h"


static unsigned long secondsRunning;



// Initialize anything we need done before tasks start
void InitializeTaskRunner()
{
	secondsRunning = 0;
}


// run the scheduled tasks
void RunScheduledTasks()
{
	secondsRunning = millis()/1000;

	FastAsPossible();
	OneSecond();
	TenSeconds();
	ThirtySeconds();
	OneMinute();
	Daily();

}

void FastAsPossible()
{
	// Run this every chance we get
	ServiceVirtualWire();
	ServiceSerial();
	//ServiceTelnet();
	ProcessMessages();
}

void OneSecond()
{
	static unsigned long lastRunTime = 0;
	if (secondsRunning - lastRunTime > 1)
	{
		lastRunTime = secondsRunning;
		// commenting this out since I don't want to clutter output
		//Serial.println("Running OneSecond Tasks");
		// run this at a minimum of every 1 seconds
		ToggleLED();
	}
}

void TenSeconds()
{

	static unsigned long lastRunTime = 0;
	if (secondsRunning - lastRunTime >= 10)
	{
		lastRunTime = secondsRunning;
		Serial.println("Running TenSecond Tasks");
		// run this at a minimum of every ten seconds

	}

}

void ThirtySeconds()
{
	static unsigned long lastRunTime = 0;
		if (secondsRunning - lastRunTime >= 30)
		{
			lastRunTime = secondsRunning;
					Serial.println("Running ThirtySecond Tasks");
			// run this at a minimum of every 30 seconds
		}
}

void OneMinute()
{
	static unsigned long lastRunTime = 0;
		if (secondsRunning - lastRunTime >= 60)
		{
			lastRunTime = secondsRunning;
					Serial.println("Running OneMinute Tasks");
		}
}

void Daily()
{
	static unsigned long lastRunTime = 0;
		if (secondsRunning - lastRunTime >= 86400)
		{
			lastRunTime = secondsRunning;
					Serial.println("Running Daily Tasks");
		}
}


// this is just used so we have an external view if we are alive
// turns light on if it was off and off if it was on
void ToggleLED()
{
	static bool tog = false;
	if (tog)
	{
		tog = false;
		digitalWrite(13, HIGH);   // set the LED on
	}
	else
	{
		tog = true;
		digitalWrite(13, LOW);    // set the LED off
	}
}

