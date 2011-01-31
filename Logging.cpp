/*
 * Logging.cpp
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

// temp is in Kelvin.  normalized to K*100
#include "Logging.h"

static unsigned long SecondsTempsLastLogged[NUMBER_OF_TEMP_SENSORS];

void InitializeLogging()
{
	for (int i = 0; i < NUMBER_OF_TEMP_SENSORS; i++)
	{
		SecondsTempsLastLogged[i] = 0;
	}

	// get starting address for data logging
		uint8_t lsb = EEPROM.read(ADDR_LSB);
		uint8_t msb = EEPROM.read(ADDR_MSB);
		currentEEAddress = msb << 4;
		currentEEAddress = currentEEAddress | lsb;
		char * startMsg = "Starting Address: ";
		LogLine(startMsg, (int)strlen(startMsg));
		LogLine(currentEEAddress);
}

void LogLine(char * msg, int len)
{
	char * mg;

	msg[len] = '\0';
	//sprintf(mg,"%sh",msg,len);
	Serial.println(msg);
}

void Log(char* msg, int len)
{
	char * mg;

	msg[len] = '\0';
	sprintf(mg,"%sh",msg,len);
	Serial.print(msg);
}




void LogLine(int val)
{
	char * msg;
	sprintf(msg,"%d",val);
	Serial.println(msg);
}

void LogTemp(uint8_t sensor, uint16_t kelvInt)
{
	if (millis()/1000 - SecondsTempsLastLogged[sensor] > TEMP_LOGGING_INTERVAL)
	{
		PrintTime();
		SecondsTempsLastLogged[sensor] = millis()/1000;
		static int writes = 0;

		Serial.print("Logging temp from sensor: ");
		Serial.print(sensor);
		Serial.print(" Temp in K: ");
		Serial.println(kelvInt, DEC);
		Serial.print("Logging to: ");
		Serial.println(currentEEAddress, DEC);
		uint8_t msbK = kelvInt >> 8;
		uint8_t lsbK = kelvInt & 0xFF;
		 if (currentEEAddress > EEPROM_SIZE)
		 {
			 currentEEAddress = EEPROM_DATA_START;
		 }
		 EEPROM.write(currentEEAddress , sensor);
		 EEPROM.write(currentEEAddress + ADDR_MSB + 1, msbK);
		 EEPROM.write(currentEEAddress + ADDR_LSB + 1, lsbK);
		 writes++;
		 currentEEAddress += 3;

		 if (((writes + 1) % 30) == 0)
		 {
			 writes = 0;
			 WriteStartAddress(currentEEAddress);
		 }
	}
}

void DisplayEEProm()
{
	for (int index = 0; index < EEPROM_SIZE; index++)
	{
	  uint8_t b = EEPROM.read(index);
	  char m[3];
	  sprintf(m,"%02X",b);
	  Serial.print(m);
	  if (((index + 1) % 32) == 0)
	  {
		Serial.println();
	  }
	}
}


void ResetEEProm()
{
	Serial.println("Resetting Log Pointer");
	currentEEAddress = EEPROM_DATA_START;
	WriteStartAddress(currentEEAddress);
}

void WriteStartAddress(uint16_t startingAddress)
{
	uint8_t lsb = (uint8_t)startingAddress;
	 uint8_t msb = startingAddress >> 8;

	 Serial.println("Writing starting address");
	 Serial.print("low:");
	 Serial.print(lsb,HEX);
	 Serial.print("high:");
	 Serial.println(msb,HEX);

	 EEPROM.write(ADDR_MSB, msb);
	 EEPROM.write(ADDR_LSB, lsb);

}

void PrintTime()
{
	   DateTime now = RTC.now();

	    Serial.print(now.year(), DEC);
	    Serial.print('/');
	    Serial.print(now.month(), DEC);
	    Serial.print('/');
	    Serial.print(now.day(), DEC);
	    Serial.print(' ');
	    Serial.print(now.hour(), DEC);
	    Serial.print(':');
	    Serial.print(now.minute(), DEC);
	    Serial.print(':');
	    Serial.print(now.second(), DEC);
	    Serial.println();
}
