/*
 * Time.h
 *
 *  Created on: Jan 16, 2011
 *      Author: Andy
 */

#ifndef TIME_H_
#define TIME_H_

#include "WProgram.h" //Include arduino headers
#include "RTC1307/RTClib.h"

#ifdef ETHERNET_INSTALLED
#include "Ethernet/EthernetUdp.h"
#endif

#include "globals.h"

//*********************CONSTANTS



//*********************FUNCTIONS
 void InitializeTime();

unsigned long GetEpoch();

unsigned long sendNTPpacket(IPAddress& address);

// Real Time Clock
extern RTC_DS1307 RTC;

#endif /* TIME_H_ */
