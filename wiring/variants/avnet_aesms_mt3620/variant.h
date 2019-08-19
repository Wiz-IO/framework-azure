/*
 *  Created on: 01.15.2019
 *      Author: Georgi Angelov
 */

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <interface.h>

#ifdef __cplusplus
extern "C"
{
#endif

//#include <mt3620.h>
#include <avnet_aesms_mt3620.h>

#define LED_RED 8
#define LED_GREEN 9
#define LED_BLUE 10

#define LED 9
#define LED_BUILTIN 9

#define PINS_MAX 76 



#ifdef __cplusplus
}
#endif //__cplusplus




#ifdef __cplusplus

#include <HardwareSerial.h>
extern HardwareSerial Serial;

#endif //__cplusplus

#endif /* __VARIANT_H__ */
