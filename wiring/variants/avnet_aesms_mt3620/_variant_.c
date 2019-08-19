
#include "variant.h"

#include <mt3620-baremetal.h>
#include <mt3620-gpio.h>

// Block includes led1RedGpio, GPIO8.
static const GpioBlock pwm2 = {
    .baseAddr = 0x38030000, .type = GpioBlock_PWM, .firstPin = 8, .pinCount = 4};

// Block includes buttonAGpio, GPIO12
static const GpioBlock grp3 = {
    .baseAddr = 0x38040000, .type = GpioBlock_GRP, .firstPin = 12, .pinCount = 4};

void init(void)
{
    Mt3620_Gpio_AddBlock(&pwm2);
    Mt3620_Gpio_AddBlock(&grp3);
}