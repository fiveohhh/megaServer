/*
 * messageProcessing.cpp
 *
 *  Created on: Jan 15, 2011
 *      Author: Andy
 */
#include "MessageProcessing.h"

// Local function prototypes
void ProcessERSMsg(char* msg);
void ProcessEGTMsg(char* msg);




void ProcessMessages()
{

	for (int i = 0; i < msgCount; i++)
	{
		LogLine("Processing...", strlen("Processing..."));
		LogLine(messages[i], strlen(messages[i]));
		msgTypes_E t = GetMsgType(messages[i]);
		switch(t)
		{
		// report a TEMP, TMPXYTTTTT X=Destination address, Y=Sensor #, TTTTT=(Temp in K)*100
		case e_TMP:
			Serial.println(strlen("TMP message received: "));
			LogLine("TMP message received: ", strlen("TMP message received: "));
			ProcessTMPMsg(messages[i]);
			break;
		// reset EEPROM logging back to starting address
		case e_ERS:
			LogLine("ERS message received: ", strlen("ERS message received: "));
			ProcessERSMsg(messages[i]);
			break;
		// Get EEPROM
		case e_EGT:
			LogLine("EGT message received: ", strlen("EGT message received: "));
			ProcessEGTMsg(messages[i]);
			break;
		case e_UNKNOWN:
			LogLine("UNKNOWN message received: ", strlen("UNKNOWN message received: "));
			LogLine(messages[i], VW_MAX_MESSAGE_LEN);
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

	if (p[0] == 'E')
	{
		if(p[1] == 'R')
		{
			if(p[2] == 'S')
			{
				return e_ERS;
			}
		}
	}
	if (p[0] == 'E')
	{
		if(p[1] == 'G')
		{
			if(p[2] == 'T')
			{
				return e_EGT;
			}
		}
	}

	return e_UNKNOWN;
}

void ProcessTMPMsg(char* msg)
{
	char kelvin[6];
	int t = 0;
	for (int i = 5; i < strlen(msg); i++)
	{
		kelvin[t++] = msg[i];
	}
	kelvin[t] = '\0';
	for (int k = 0; k < 5; k++)
	{
		//LogLine(kelvin[k]);
	}
	LogLine(kelvin, t);
	int kelvInt = atoi(kelvin);

	double Kelv = kelvInt/100;

	double Fahr = (Kelv -273.15) *((double)9/5)+ 32;
	char lcdMsg[16];
	int fAsInt = (int)Fahr;
	if (msg[4] == 49)
	{
		//lcd.setCursor(0,0);
		//sprintf(lcdMsg,"Outside: %dF",fAsInt);
		//lcd.print(lcdMsg);
		sprintf(lcdMsg,"%dF", fAsInt);
		Serial1.println(lcdMsg);
		SetTemp(lcdMsg,0);
	}
	else if (msg[4] == 48)
	{
		//lcd.setCursor(0,1);
		//sprintf(lcdMsg,"Garage: %dF",fAsInt);
		//lcd.print(lcdMsg);
		sprintf(lcdMsg,"%dF", fAsInt);
		Serial1.println(lcdMsg);
		SetTemp(lcdMsg,1);
	}

	LogTemp(msg[4], kelvInt);
}

void ProcessERSMsg(char* msg)
{
	ResetEEProm();
}

void ProcessEGTMsg(char* msg)
{
	DisplayEEProm();
}

// get any messages that may be waiting on the virtual wire
void ServiceVirtualWire()
{
	 uint8_t buf[VW_MAX_MESSAGE_LEN];
			 uint8_t buflen = VW_MAX_MESSAGE_LEN;
			 if (vw_get_message(buf, &buflen)) // Non-blocking
			 {
				 char str[VW_MAX_MESSAGE_LEN];
				 LogLine("Msg Received From Virtual Wire...", strlen("Msg Received From Virtual Wire..."));
				 for (int i = 0; i < buflen; i++)
				 {
					 str[i] = buf[i];
					 //Serial.print(buf[i]);
				 }
				 str[buflen] = '\0';
				 //messages[msgCount] = str;
				 strcpy(messages[msgCount],str);
				 msgCount++;
				 LogLine(str, buflen);
			 }
}

void ServiceSerial()
{
	static uint8_t buf[MAX_MSG_LENGTH_SERIAL];
	static uint8_t index = 0;
	while(Serial.available())
	{
		//Serial.println("serialAvail");
		//Serial.println(Serial.read(), DEC);
		if (index > MAX_MSG_LENGTH_SERIAL)
		{
			LogLine("Max Serial buffer reached... Flushing UART", strlen("Max Serial buffer reached... Flushing UART"));
			Serial.flush();
			index = 0;

		}
		else
		{
			buf[index] = Serial.read();
			if (buf[index] == 13)
			{
				char str[MAX_MSG_LENGTH_SERIAL];
				LogLine("Msg Received From Serial...", strlen("Msg Received From Serial..."));
				for (int i = 0; i < index; i++)
				 {
					 str[i] = buf[i];
					 //Serial.print(buf[i]);
				 }
				 str[index] = '\0';
				 strcpy(messages[msgCount],str);
				 msgCount++;
				 LogLine(str, index);
				 index = 0;
			}
			else
			{
				index++;
			}
		}
	}
}
