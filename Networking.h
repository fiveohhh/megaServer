/*
 * Networking.h
 *
 *  Created on: Jan 18, 2011
 *      Author: Andy
 */

#ifndef NETWORKING_H_
#define NETWORKING_H_

#include "WProgram.h" //Include arduino headers
#include "IPAddress.h"
//#include "SPI/SPI.h"

#include "globals.h"
#include "VirtualWire/VirtualWire.h"

extern char messages[MAX_MESSAGES][VW_MAX_MESSAGE_LEN];
extern int msgCount;



// function prototypes
void InitializeNetwork();
void ServiceTelnet();
int GET_asClient(char * msg, IPAddress ipaddr);

#endif /* NETWORKING_H_ */
