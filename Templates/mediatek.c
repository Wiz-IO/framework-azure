/*  
    Azure Sphere 2019 Georgi Angelov
        https://github.com/Wiz-IO/platform-azure
        http://www.wizio.eu/

    OPEN: 'platformio.ini' and edit your settings
    OPEN: 'src/app_manifest.json' and enter your 'Capabilities'
 */

#include <stdio.h>
#include <stdarg.h>

#include "mt3620.h"
#include <os_hal_uart.h>
#include <os_hal_gpt.h>

_Noreturn void RTCoreMain(void)
{
    NVIC_SetupVectorTable();
    STD_Init();

    // SETUP

    for (;;)
    {
        __asm__("wfi");
    }
}