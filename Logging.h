/*
 * Logging.h
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

#ifndef LOGGING_H_
#define LOGGING_H_
#include "WProgram.h" //Include arduino headers
#include "EEPROM/EEPROM.h"
#include "globals.h"
#include "Time.h"
#include "SD/SD.h"
#include "SerialLCD.h"

void InitializeLogging();
void WriteStartAddress(uint16_t startingAddress);
void DisplayEEProm();
void ResetEEProm();
void LogTemp(uint8_t sensor, uint16_t kelvInt);
void PrintTime();
void LogLine(int val);
void LogLine(char * msg, int len);
void Log(char * msg, int len);


// seconds between temp Logs
#define TEMP_LOGGING_INTERVAL 300

static int currentEEAddress;

#endif /* LOGGING_H_ */
