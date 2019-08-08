/*  Copyright (c) Microsoft Corporation. All rights reserved.
        Licensed under the MIT License. 

    PlatformIO 2019 Georgi Angelov
    https://github.com/Wiz-IO
    http://www.wizio.eu/

    OPEN: 'platformio.ini' and edit your settings
    OPEN: 'src/app_manifest.json' and enter your 'Capabilities'

 */

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "applibs_versions.h"
#include <applibs/gpio.h>
#include <applibs/log.h>
#include "epoll_timerfd_utilities.h"

static volatile sig_atomic_t terminationRequired = false;
static int epollFd = -1;

int main(int argc, char *argv[])
{
    Log_Debug("Azure Sphere PlatformIO 2019 WizIO\n");
    while (!terminationRequired) {
        if (WaitForEventAndCallHandler(epollFd) != 0) {
            terminationRequired = true;
        }
    }
    Log_Debug("End\n");
    return 0;
}