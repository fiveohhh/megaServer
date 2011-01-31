/*
 * SerialLCD.h
 *
 *  Created on: Jan 30, 2011
 *      Author: Andy
 */

#ifndef SERIALLCD_H_
#define SERIALLCD_H_

#include "WProgram.h" //Include arduino headers
#include "Logging.h"



void ClearLCD();
void SetTemp(char * temp, int sensor);
void InitializeSerialLCD();
void DrawScreen();

#endif /* SERIALLCD_H_ */
