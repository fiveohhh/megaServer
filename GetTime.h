#ifndef _GetTime_h
#define _GetTime_h

#include "WProgram.h" //Include arduino headers

#include "Ethernet/Udp.h"

//*********************CONSTANTS
unsigned int localPort = 8888;      // local port to listen for UDP packets

byte timeServer[] = { 
  208, 66, 175, 36}; // time.nist.gov NTP server

const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 


//*********************FUNCTIONS
unsigned long GetEpoch();

unsigned long sendNTPpacket(byte *address);



#endif
