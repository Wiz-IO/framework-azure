/*  Copyright (c) Microsoft Corporation. All rights reserved.
        Licensed under the MIT License. 

    PlatformIO 2019 Georgi Angelov
    https://github.com/Wiz-IO
    http://www.wizio.eu/

    OPEN: 'platformio.ini' and edit your settings
    OPEN: 'src/app_manifest.json' and enter your 'Capabilities'

 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

extern uint32_t StackTop; // &StackTop == end of TCM0
static const uintptr_t SCB_BASE = 0xE000ED00;
static _Noreturn void DefaultExceptionHandler(void);
static _Noreturn void RTCoreMain(void);

#define INTERRUPT_COUNT 100 // from datasheet
#define EXCEPTION_COUNT (16 + INTERRUPT_COUNT)
#define INT_TO_EXC(i_) (16 + (i_))
const uintptr_t ExceptionVectorTable[EXCEPTION_COUNT]
    __attribute__((section(".vector_table")))
    __attribute__((used)) = {
        [0] = (uintptr_t)&StackTop,                // Main Stack Pointer (MSP)
        [1] = (uintptr_t)RTCoreMain,               // Reset
        [2] = (uintptr_t)DefaultExceptionHandler,  // NMI
        [3] = (uintptr_t)DefaultExceptionHandler,  // HardFault
        [4] = (uintptr_t)DefaultExceptionHandler,  // MPU Fault
        [5] = (uintptr_t)DefaultExceptionHandler,  // Bus Fault
        [6] = (uintptr_t)DefaultExceptionHandler,  // Usage Fault
        [11] = (uintptr_t)DefaultExceptionHandler, // SVCall
        [12] = (uintptr_t)DefaultExceptionHandler, // Debug monitor
        [14] = (uintptr_t)DefaultExceptionHandler, // PendSV
        [15] = (uintptr_t)DefaultExceptionHandler, // SysTick

        [INT_TO_EXC(0)... INT_TO_EXC(INTERRUPT_COUNT - 1)] = (uintptr_t)DefaultExceptionHandler};

static _Noreturn void DefaultExceptionHandler(void)
{
    for (;;)
    {
    }
}

static _Noreturn void RTCoreMain(void)
{
    *(volatile uint32_t *)(SCB_BASE + 8) = (uint32_t)ExceptionVectorTable; // SCB->VTOR = ExceptionVectorTable
    
    /* SETUP */

    while (1)
    {
        /* LOOP */
    }
}
