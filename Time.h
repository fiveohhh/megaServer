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
static unsigned int localPort = 8888;      // local port to listen for UDP packets



static const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message

 static byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets


//*********************FUNCTIONS
 void InitializeTime();

unsigned long GetEpoch();

unsigned long sendNTPpacket(IPAddress& address);

// Real Time Clock
extern RTC_DS1307 RTC;

#endif /* TIME_H_ */
