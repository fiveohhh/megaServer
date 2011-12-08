 /*
 * Networking.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: Andy
 */

#include "Networking.h"
#include "Ethernet/Ethernet.h"
//#include "httpclient/HTTPClient.h"

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
static EthernetClient client;

void InitializeNetwork()
{

	// start ethernet
		Ethernet.begin(mac,ip, gateway, subnet);

		delay(1000);

		/*
		//server.begin();
		Serial.println("trying  coddnnected");
		if (client.connect(ipaddr, 8080)) {
		    Serial.println("coddnnected");
		    // Make a HTTP request:
		    client.println("GET /restInterface/sensor=11,temp=22,datetime=3333/ HTTP/1.1");
		    client.println();
		    client.stop();
		}
		*/
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

int GET_asClient(char * msg, IPAddress serverAddr)
{

	Serial.println("connecting to server");

	if (client.connect(serverAddr, 80))
	{
		Serial.println("Connected to server!");
		Serial.println(msg);
		client.print(msg);
		client.print(0x0d);
		client.print(0x0a);
		client.println("Host: 10.12.34.99");
		client.println("");

		delay(1000);
		while (client.available())
		{
			Serial.print( (char)client.read());


		}
		client.flush();
		Serial.println("Flushing");

		client.stop();
	}
	else
	{
		Serial.println("Failed to connect");
	}

	return 0;

}


