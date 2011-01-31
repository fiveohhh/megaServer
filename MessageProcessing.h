/*
 * MessageProcessing.h
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */

#ifndef MESSAGEPROCESSING_H_
#define MESSAGEPROCESSING_H_

#include "WProgram.h" //Include arduino headers
#include "types.h"
#include "VirtualWire/VirtualWire.h"
#include "globals.h"
#include "Logging.h"
#include "SerialLCD.h"



msgTypes_E GetMsgType(char *p);
void ProcessMessages();
void ProcessTMPMsg(char* msg);
void ServiceVirtualWire();
void ServiceSerial();

extern char messages[MAX_MESSAGES][VW_MAX_MESSAGE_LEN];

extern int msgCount;

#endif /* MESSAGEPROCESSING_H_ */
