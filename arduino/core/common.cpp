#include <interface.h>
#include <applibs/networking.h>

void waitWifi(void)
{
    bool outIsNetworkingReady = false;
    while (Networking_IsNetworkingReady(&outIsNetworkingReady) < 0 || false == outIsNetworkingReady)
        delay(100); // ~15 seconds on reset
    delay(10);
}
