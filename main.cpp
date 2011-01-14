#include "WProgram.h" //Include arduino headers
#include "EEPROM/EEPROM.h"
#include "Ethernet/Ethernet.h"
#include "Ethernet/Udp.h"
#include "SPI/SPI.h"
#include "LCD/LiquidCrystal.h"
#include "RTC1307/RTClib.h"
#include "VirtualWire/VirtualWire.h"
#include "types.h"
//#include "GetTime.h"


#undef int
#undef abs
#undef double
#undef float
#undef round

///CONSTANTS///
#define MAX_MESSAGES 10

//The onboard test LED is connected to pin number 13
const int ledPin = 13;
const int interval = 1000; //Milliseconds

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {
  192,168,1,177 };

// Real Time Clock
RTC_DS1307 RTC;

//** FUNCTION PROTOTYPES **//
void ProcessMessages();
msgTypes_E GetMsgType(char *p);

LiquidCrystal lcd(32, 31, 25, 24, 23, 22);

int msgCount = 0;
char messages[MAX_MESSAGES][VW_MAX_MESSAGE_LEN];


///MAIN///
int main()
{
	//Initialize the Arduino library.
	//Not doing so will prevent the delay function
	//from working. Calling this functions is a must
	//for all arduino projects.
	init();

	//Initialize the serial port. This will be used
	//to send diagnostic information in this project.
	Serial.begin(57600);

	// start ethernet
	Ethernet.begin(mac,ip);
	//unsigned long epoch = GetEpoch();
	//RTC.adjust(DateTime(epoch));

	 // Initialize the IO and ISR
	    vw_set_ptt_inverted(true); // Required for DR3100
	    vw_setup(2000);	 // Bits per sec

	// set up the LCD's number of rows and columns:
	  lcd.begin(16, 2);
	   vw_rx_start();

	//Configure ledPin as an output
	pinMode(ledPin, OUTPUT);

	//Announce the start of program. Usually a
	//hyper-terminal is connected to the serial
	//port on the PC so this message can be seen
	//there
	Serial.println("Ready.");

	//Enter the infinite loop responsible for making
	//the microcontroller do the same thing over and
	//over again. (Almost every microcontroller has
	//such a loop)
	while(true)
	{
		//*************************Check for message from virtual Wire
		 uint8_t buf[VW_MAX_MESSAGE_LEN];
		 uint8_t buflen = VW_MAX_MESSAGE_LEN;
		 if (vw_get_message(buf, &buflen)) // Non-blocking
		 {
			 char str[VW_MAX_MESSAGE_LEN];
			 Serial.println("Msg Received From Virtual Wire...");
			 for (int i = 0; i < buflen; i++)
			 {
				 str[i] = buf[i];
				 //Serial.print(buf[i]);
			 }
			 str[buflen] = '\0';
			 //messages[msgCount] = str;
			 strcpy(messages[msgCount],str);
			 msgCount++;
			 Serial.println(str);
		 }
		 //**************************************************


		 //**********************Process Incoming Messages
		if (Serial.available() > 0)
		{
		}
		//********************************************


		ProcessMessages();
		//Turn on the LED
		digitalWrite(ledPin, HIGH);
		//Wait for half of "interval".
		//The LED remains ON during this time.
		delay(interval/2);
		//Turn off the LED
		digitalWrite(ledPin, LOW);
		//Wait for half of "interval".
		//The LED remains OFF during this time.
		delay(interval/2);

	}

	//Unreachable code but it's required by
	//the compiler
	return 0;
}


void ProcessMessages()
{
	Serial.println("Processing...");
	for (int i = 0; i < msgCount; i++)
	{
		Serial.println(messages[i]);
		msgTypes_E t = GetMsgType(messages[i]);
		switch(t)
		{
		case e_TMP:

			break;
		case e_UNKNOWN:
			Serial.print("Unknown message received: ");
			Serial.print(messages[i]);
			break;
		}



		msgCount--;
	}
}

msgTypes_E GetMsgType(char *p)
{
	if (p[0] == 'T')
	{
		if(p[1] == 'M')
		{
			if(p[2] == 'P')
			{
				return e_TMP;
			}
		}
	}

	return e_UNKNOWN;
}

void ProcessTMPMsg(char* msg)
{

}
