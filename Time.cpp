/*
 * Time.cpp
 *
 *  Created on: Jan 16, 2011
 *      Author: Andy
 */

#include "Time.h"

void InitializeTime()
{
	uint32_t epoch = GetEpoch();
	if (epoch == 0)
	{
		Serial.println("Unable to get updated time");
		Serial.print("Using RTC stored time of: ");
		DateTime dt = RTC.now();
		Serial.println(dt.unixtime());
	}
	else
	{
		Serial.print("Setting RTC to: ");
		Serial.println(epoch, DEC);
		if (!RTC.isrunning())
		{
			Serial.println("RTC is NOT running!");
		}
		RTC.adjust(epoch);
	}
}

unsigned long GetEpoch()
{
	Serial.println("test point ge1");
	Udp.begin(localPort);
	Serial.println("test point ge2");
	  sendNTPpacket(timeServer); // send an NTP packet to a time server
	  Serial.println("test point ge3");
	    // wait to see if a reply is available
	  delay(1000);
	  if ( Udp.available() ) {
		  Serial.println("test point 4");
	    Udp.readPacket(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer

	    //the timestamp starts at byte 40 of the received packet and is four bytes,
	    // or two words, long. First, esxtract the two words:

	    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
	    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
	    // combine the four bytes (two words) into a long integer
	    // this is NTP time (seconds since Jan 1 1900):
	    unsigned long secsSince1900 = highWord << 16 | lowWord;
	    Serial.print("Seconds since Jan 1 1900 = " );
	    Serial.println(secsSince1900);

	    // now convert NTP time into everyday time:
	    Serial.print("Unix time = ");
	    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
	    const unsigned long seventyYears = 2208988800UL;
	    // subtract seventy years:
	    unsigned long epoch = secsSince1900 - seventyYears;
	    // print Unix time:
	    Serial.println(epoch);




	    // print the hour, minute and second:
	    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
	    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
	    Serial.print(':');
	    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
	    Serial.print(':');
	    Serial.println(epoch %60); // print the second

	        //top left

	    return epoch;
	  }
	  Serial.println("test point ge5");
	  return 0;
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(byte *address)
{
  Serial.print("Sending Packet\n");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.sendPacket( packetBuffer,NTP_PACKET_SIZE,  address, 123); //NTP requests are to port 123
  return 0;
}
