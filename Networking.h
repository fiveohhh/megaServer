/*
 * Networking.h
 *
 *  Created on: Jan 18, 2011
 *      Author: Andy
 */

#ifndef NETWORKING_H_
#define NETWORKING_H_

#include "WProgram.h" //Include arduino headers
//#include "SPI/SPI.h"
#include "Ethernet/Ethernet.h"
#include "globals.h"
#include "VirtualWire/VirtualWire.h"

extern char messages[MAX_MESSAGES][VW_MAX_MESSAGE_LEN];
extern int msgCount;




// function prototypes
void InitializeNetwork();
void ServiceTelnet();

#endif /* NETWORKING_H_ */
