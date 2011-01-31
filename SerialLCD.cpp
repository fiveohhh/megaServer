/*
 * SerialLCD.cpp
 *
 *  Created on: Jan 30, 2011
 *      Author: Andy
 */

#include "SerialLCD.h"

#define MAX_TEMP_DISPLAY_LENGTH 20
#define TOP_PIXEL 63
#define CHAR_HEIGHT 8
#define CHAR_WIDTH 6
#define LAST_UPDATED_LINE 7
#define TIME_ZONE_ADJUST -6


void SetBaudRate();
void SetCursor(uint8_t x, uint8_t y);
void EraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void DrawLine(int x, int y);


#define NUM_OF_SENSORS_TO_DISPLAY 2
char tempSensors[][10] = {"Outside", "Garage"};
char temps[][7] = {"NULL", "NULL"};
void InitializeSerialLCD()
{
	Serial1.begin(115200);


	ClearLCD();
	Serial1.print("Screen initialized");

}


void ClearLCD()
{
	Serial1.write(0x7C);
	Serial1.write((uint8_t)0x00);

}



void SetTemp(char * temp, int sensor)
{
	strcpy(temps[sensor],temp);
	if (temps[sensor] != temp)
	{
		DrawScreen();
	}
}

void DrawScreen()
{
	ClearLCD();
	for (int i = 0; i < NUM_OF_SENSORS_TO_DISPLAY; i++)
	{

		char  msg[MAX_TEMP_DISPLAY_LENGTH];
		sprintf(msg, "%s: %s",tempSensors[i], temps[i]);
		SetCursor(0, TOP_PIXEL - (i*CHAR_HEIGHT));
		Serial1.print(msg);

	}



	// write last updated time
	SetCursor(0, (TOP_PIXEL - (LAST_UPDATED_LINE*CHAR_HEIGHT)));
	//Serial1.println(TOP_PIXEL - (LAST_UPDATED_LINE*CHAR_HEIGHT));
	DateTime now = RTC.now();

	// 20 is max length dateTimestring should be xx/xx/xxxx xx:xx
	char dateTimeStr[20];
	uint8_t hour = now.hour();
	hour = (hour > TIME_ZONE_ADJUST) ? (hour - TIME_ZONE_ADJUST) : (hour + 24 - TIME_ZONE_ADJUST);
	sprintf(dateTimeStr, "%d/%d/%d %d:%02d", now.month(), now.day(), now.year(), hour, now.minute());
	Serial1.print(dateTimeStr);
}

void SetCursor(uint8_t x, uint8_t y)
{
	Serial1.write(0x7C);
	Serial1.write(0x18);
	Serial1.write((uint8_t)x);
	Serial1.write(0x7C);
	Serial1.write(0x19);
	Serial1.write((uint8_t)y);
}

void DrawLine(int x, int y)
{
	Serial1.write(0x7C);
	Serial1.write(0x0C);
	Serial1.write(x);
	Serial1.write(y);
}

void EraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	Serial1.write(0x7C);
	Serial1.write(0x05);
	Serial1.write(x1);
	Serial1.write(y1);
	Serial1.write(x2);
	Serial1.write(y2);
}
