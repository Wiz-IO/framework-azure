/*
 *  Created on: 01.01.2019
 *      Author: Georgi Angelov
 */

#include <Wiring.h>
#include <avnet_aesms_mt3620.h>

extern "C" void init(void);

HardwareSerial Serial(AVNET_AESMS_ISU0_UART); 
