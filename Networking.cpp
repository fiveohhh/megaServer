 /*
 * Networking.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: Andy
 */

#include "Networking.h"

#define PORT 23

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {
  192,168,1,177 };
byte gateway[] = { 192,168,1, 1 };
byte subnet[] = { 255, 255, 255, 0 };

Server server(PORT);

void InitializeNetwork()
{
	// start ethernet
		Ethernet.begin(mac,ip, gateway, subnet);
		server.begin();
}

//void ServiceTelnet()
//{
//	static uint8_t buf[MAX_MSG_LENGTH_SERIAL];
//	static uint8_t index = 0;
//	while(Serial.available())
//	{
//		//Serial.println("serialAvail");
//		//Serial.println(Serial.read(), DEC);
//		if (index > MAX_MSG_LENGTH_SERIAL)
//		{
//			Serial.println("Max Serial buffer reached... Flushing UART");
//			Serial.flush();
//			index = 0;
//
//		}
//		else
//		{
//			buf[index] = Serial.read();
//			if (buf[index] == 13)
//			{
//				char str[MAX_MSG_LENGTH_SERIAL];
//				Serial.println("Msg Received From Serial...");
//				for (int i = 0; i < index; i++)
//				 {
//					 str[i] = buf[i];
//					 //Serial.print(buf[i]);
//				 }
//				 str[index] = '\0';
//				 strcpy(messages[msgCount],str);
//				 msgCount++;
//				 Serial.println(str);
//				 index = 0;
//			}
//			else
//			{
//				index++;
//			}
//		}
//	}
//}
