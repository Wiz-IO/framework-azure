#include <interface.h>
#include <applibs/networking.h>

void waitWifi(void)
{
    bool outIsNetworkingReady = 0;
    if (Networking_IsNetworkingReady(&outIsNetworkingReady) < 0 && 0 == outIsNetworkingReady)
        delay(100);
}
