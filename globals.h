/*
 * globals.h
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_


///CONSTANTS///
#define MAX_MESSAGES 10
#define EEPROM_SIZE 4096
#define EEPROM_DATA_START 2
#define NUMBER_OF_TEMP_SENSORS 2
// first two bytes reserved for previous keeping track of location
#define ADDR_LSB 1
#define ADDR_MSB 0

// max length of serial msgs
#define MAX_MSG_LENGTH_SERIAL 32


#endif /* GLOBALS_H_ */
