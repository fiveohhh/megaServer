/*
 * Logging.cpp
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

// temp is in Kelvin.  normalized to K*100
#include "Logging.h"

char FILENAME[] = "datalog.txt";

const int chipSelect = 53;

static unsigned long SecondsTempsLastLogged[NUMBER_OF_TEMP_SENSORS];

void LogToSDCard(char * msg);
void LogTempToSD(uint8_t sensor, uint16_t kelv);


void InitializeLogging()
{
	Serial1.println("Initializing SD card...");
	if (!SD.begin(chipSelect))
	{
	    Serial1.println("Card failed, or not present");
	}
	else
	{
	  Serial1.println("card initialized.");
	}

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


	msg[len] = '\0';
	//sprintf(mg,"%sh",msg,len);
	Serial.println(msg);
}

void Log(char* msg, int len)
{
	char * mg = "";

	msg[len] = '\0';
	sprintf(mg,"%sh",msg,len);
	Serial.print(msg);
}




void LogLine(int val)
{
	Serial.println(val, DEC);
}

void LogTemp(uint8_t sensor, uint16_t kelvInt)
{

	if (millis()/1000 - SecondsTempsLastLogged[sensor] > TEMP_LOGGING_INTERVAL)
	{

		LogTempToSD(sensor,kelvInt);
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

void LogTempToSD(uint8_t sensor, uint16_t kelvInt)
{
	char buf[255] = "";
	DateTime now = RTC.now();
	sprintf(buf,"%d/%d/%d %d:%d:%d,%d,%d",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second(),sensor,kelvInt);
	LogToSDCard(buf);


}

void LogToSDCard(char * msg)
{

	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	File dataFile = SD.open(FILENAME, FILE_WRITE);

	// if the file is available, write to it:
	if (dataFile)
	{
		Serial.print("Logging to SD->");
		Serial.println(msg);
		dataFile.println(msg);
		dataFile.close();
		// print to the serial port too:
		//Serial.println(dataString);
	}
	  // if the file isn't open, pop up an error:
	else
	{

		Serial.println("error opening datalog.txt");
		SetMessage("SD ERROR", strlen("SD ERROR"));

	}
}
