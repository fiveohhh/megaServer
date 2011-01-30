/*
 * SerialLCD.h
 *
 *  Created on: Jan 30, 2011
 *      Author: Andy
 */

#ifndef SERIALLCD_H_
#define SERIALLCD_H_

#include "WProgram.h" //Include arduino headers




void ClearLCD();
void DisplayTemp(char * temp, int sensor);
#endif /* SERIALLCD_H_ */
