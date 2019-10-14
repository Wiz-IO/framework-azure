/*  
    Azure Sphere 2019 Georgi Angelov
        https://github.com/Wiz-IO/platform-azure
        http://www.wizio.eu/

    OPEN: 'platformio.ini' and edit your settings
    OPEN: 'src/app_manifest.json' and enter your 'Capabilities'
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#define UART_STRUCTS_VERSION 1
#include <applibs/uart.h>
#include <applibs/log.h>
void retarget(int, void *, int);
int fd_uart = -1;

void open_uart(int port)
{
    UART_Config uartConfig;
    UART_InitConfig(&uartConfig);
    uartConfig.baudRate = 115200;
    uartConfig.flowControl = UART_FlowControl_None;
    fd_uart = UART_Open(port, &uartConfig);
    if (fd_uart > 0)
    {
        retarget(fd_uart, stderr, 0);
        retarget(fd_uart, stdout, 0);        
        Log_Debug("Log_Debug\n");
        printf("printf %d\n", 42);
    }
}

int main(int argc, char *argv[])
{
    open_uart(4);
    Log_Debug("Azure Sphere PlatformIO 2019 WizIO\n");
    Log_Debug("Hello World\n");
    while (1)
    {
        Log_Debug("Ping ");
        sleep(5);
        printf("Pong\n");
        sleep(1);
    }
    return 0;
}