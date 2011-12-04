 /*
 * Networking.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: Andy
 */

#include "Networking.h"


#define TELNET_PORT 23
#define textBuffSize 9 //length of longest command string plus two spaces for CR + LF

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {10,12,34,99 };
byte gateway[] = { 10,12,34, 1 };
byte subnet[] = { 255, 255, 255, 0 };

char textBuff[textBuffSize]; //someplace to put received text
int charsReceived = 0;

boolean connectFlag = 0; //we'll use a flag separate from client.connected
				 //so we can recognize when a new connection has been created
unsigned long timeOfLastActivity; //time in milliseconds of last activity
unsigned long allowedConnectTime = 300000; //five minutes

int ReadResponse();


//Server server(TELNET_PORT);
byte iptarget[] = {10,12,34,135};
IPAddress ipaddr(10,12,34,135);
EthernetClient client;

void InitializeNetwork()
{
	// start ethernet
		Ethernet.begin(mac,ip, gateway, subnet);
		//server.begin();
}

void ServiceTelnet()
{
	/*
	static boolean connected = false; // whether or not you got a message from the client yet
	Client client = server.available();

	  // when the client sends the first byte, say hello:
	  if (client) {
	    if (!connected) {
	      Serial.println("We have a new client");
	      client.println("Hello, client!");
	      connected = true;
	    }

	    // read the bytes incoming from the client:
	    //char thisChar = client.read();
	    // echo the bytes back to the client:
	    //server.write(thisChar);
	    // echo the bytes to the server as well:
	    //Serial.print(thisChar);
	  }

	static uint8_t buf[MAX_MSG_LENGTH_SERIAL];
	static uint8_t index = 0;
	Client client = server.available();

	while(client.available())
	{

		//Serial.println("serialAvail");
		//Serial.println(Serial.read(), DEC);
		if (index > MAX_MSG_LENGTH_SERIAL)
		{
			client.println("Max Serial buffer reached... Flushing UART");
			client.flush();
			index = 0;

		}
		else
		{
			buf[index] = client.read();
			if (buf[index] == 13)
			{
				char str[MAX_MSG_LENGTH_SERIAL];
				Serial.println("Msg Received From telnet client...");
				for (int i = 0; i < index; i++)
				 {
					 str[i] = buf[i];
					 //Serial.print(buf[i]);
				 }
				 str[index] = '\0';
				 strcpy(messages[msgCount],str);
				 msgCount++;
				 client.println(str);
				 index = 0;
			}
			else
			{
				index++;
			}
		}
	}
	*/
}

int GET_asClient(byte * serverIP, const char * msg)
{

	Serial.println("connecting to server");
	//Serial.println(serverIP);
	//Serial.println(msg);

	if (client.connect(ipaddr, 8080))
	{
		Serial.println("Connected!");
		client.flush();
		client.println("GET /restInterface/sensor=11,temp=22,datetime=3333/ HTTP/1.1");
		client.println();
		Serial.print(" - ");
		//Serial.print(ReadResponse(), DEC);
		//Serial.println(" bytes received");
		//client.flush();
		client.stop();


	}
	else
	{
		Serial.println("Failed to connect");
	}

	return 0;
}

int ReadResponse()
{
  int totalBytes=0;
  unsigned long startTime = millis();

// First wait up to 5 seconds for the server to return some data.
// If we don't have this initial timeout period we might try to
// read the data "too quickly" before the server can generate the
// response to the request

  while ((!client.available()) && ((millis() - startTime ) < 5000));

  while (client.available()) {
    char c = client.read();
    totalBytes+=1;
  }
  return totalBytes;
}
