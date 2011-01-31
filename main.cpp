


#include "WProgram.h" //Include arduino headers
//#include "EEPROM/EEPROM.h"
#ifdef ETHERNET_INSTALLED
#include "Ethernet/Ethernet.h"
#include "Ethernet/Udp.h"
#include "Networking.h"
#endif

#include "SPI/SPI.h"

#include "RTC1307/RTClib.h"
#include "VirtualWire/VirtualWire.h"
#include "globals.h"
#include "types.h"
#include "Wire/Wire.h"

#include "Time.h"
#include "MessageProcessing.h"
#include "Logging.h"
#include "tasks.h"
#include "SerialLCD.h"

#undef int
#undef abs
#undef double
#undef float
#undef round

//The onboard test LED is connected to pin number 13
const int ledPin = 13;
const int interval = 1000; //Milliseconds

// Real Time Clock
RTC_DS1307 RTC;

//LiquidCrystal lcd(32, 31, 25, 24, 23, 22);



// how many messages we have that need processing
int msgCount = 0;
// array of the messages that need processing
char messages[MAX_MESSAGES][VW_MAX_MESSAGE_LEN];

///MAIN///
int main() {

	//Initialize the Arduino library.
	//Not doing so will prevent the delay function
	//from working. Calling this functions is a must
	//for all arduino projects.
	init();

	//Initialize the serial port. This will be used
	//to send diagnostic information in this project.
	Serial.begin(57600);
	Serial.println("Starting...");

	InitializeSerialLCD();
	//Serial1.begin(115200);
	Serial1.print("Starting...");

	Wire.begin();

	// Initialize the IO and ISR
	vw_set_ptt_inverted(true); // Required for DR3100
	vw_setup(2000); // Bits per sec
	vw_rx_start();

	// set up the LCD's number of rows and columns:
	//lcd.begin(16, 2);
	//


	RTC.begin();
#ifdef ETHERNET_INSTALLED
	InitializeNetwork();
#endif
	InitializeTime();
	//Configure ledPin as an output
	pinMode(ledPin, OUTPUT);

	InitializeLogging();

	InitializeTaskRunner();

	//Announce the start of program. Usually a
	//hyper-terminal is connected to the serial
	//port on the PC so this message can be seen
	//there
	Serial.println("Ready.");

	Serial1.print("Ready");
	ClearLCD();
	DrawScreen();

	//Enter the infinite loop responsible for making
	//the microcontroller do the same thing over and
	//over again. (Almost every microcontroller has
	//such a loop)
	while (true) {
		RunScheduledTasks();
	}

	//Unreachable code but it's required by
	//the compiler
	return 0;
}

