
#include "variant.h"

#include <mt3620-baremetal.h>
#include <mt3620-gpio.h>

/*  
    ADC  = GPIO_41 to GPIO_48 (0x38000000)
    PWM  = GPIO_0  to GPIO_3  (0x38010000)
    PWM  = GPIO_4  to GPIO_7  (0x38020000)
    PWM  = GPIO_8  to GPIO_11 (0x38030000)
    GRP3 = GPIO_12 to GPIO_15 (0x38040000)
    GRP4 = GPIO_16 to GPIO_19 (0x38050000)
    GRP5 = GPIO_20 to GPIO_23 (0x38060000)
    ISU0 = GPIO_26 to GPIO_30 (0x38070000) 
    ISU1 = GPIO_31 to GPIO_35 (0x38080000)
    ISU2 = GPIO_36 to GPIO_40 (0x38090000) 
    ISU3 = GPIO_66 to GPIO_70 (0x380A0000) 
    ISU4 = GPIO_71 to GPIO_75 (0x380B0000) 
*/

/*    
static const GpioBlock gpio_block_0 = { .baseAddr = 0x38000000, .type = GpioBlock_ADC, .firstPin = 41, .pinCount = 8 };    
static const GpioBlock gpio_block_1 = { .baseAddr = 0x38010000, .type = GpioBlock_PWM, .firstPin =  0, .pinCount = 4 };
static const GpioBlock gpio_block_2 = { .baseAddr = 0x38020000, .type = GpioBlock_PWM, .firstPin =  4, .pinCount = 4 };
*/
static const GpioBlock pwm2         = { .baseAddr = 0x38030000, .type = GpioBlock_PWM, .firstPin =  8, .pinCount = 4 };
static const GpioBlock grp3         = { .baseAddr = 0x38040000, .type = GpioBlock_GRP, .firstPin = 12, .pinCount = 4 };
/*
static const GpioBlock gpio_block_5 = { .baseAddr = 0x38050000, .type = GpioBlock_GRP, .firstPin = 16, .pinCount = 4 };
static const GpioBlock gpio_block_6 = { .baseAddr = 0x38060000, .type = GpioBlock_GRP, .firstPin = 20, .pinCount = 4 };
static const GpioBlock gpio_block_7 = { .baseAddr = 0x38070000, .type = GpioBlock_ISU, .firstPin = 26, .pinCount = 5 };
static const GpioBlock gpio_block_8 = { .baseAddr = 0x38080000, .type = GpioBlock_ISU, .firstPin = 31, .pinCount = 5 };
static const GpioBlock gpio_block_9 = { .baseAddr = 0x38090000, .type = GpioBlock_ISU, .firstPin = 36, .pinCount = 5 };
static const GpioBlock gpio_block_A = { .baseAddr = 0x380A0000, .type = GpioBlock_ISU, .firstPin = 66, .pinCount = 5 };
static const GpioBlock gpio_block_B = { .baseAddr = 0x380B0000, .type = GpioBlock_ISU, .firstPin = 71, .pinCount = 5 };
*/

void init(void)
{
/*
   Mt3620_Gpio_AddBlock(&gpio_block_0);
   Mt3620_Gpio_AddBlock(&gpio_block_1);
   Mt3620_Gpio_AddBlock(&gpio_block_2);
*/  
    Mt3620_Gpio_AddBlock(&pwm2); // gpio_block_3
    Mt3620_Gpio_AddBlock(&grp3); // gpio_block_4 
/*
    Mt3620_Gpio_AddBlock(&gpio_block_5);
    Mt3620_Gpio_AddBlock(&gpio_block_6);
    Mt3620_Gpio_AddBlock(&gpio_block_7);
    Mt3620_Gpio_AddBlock(&gpio_block_8);
    Mt3620_Gpio_AddBlock(&gpio_block_9);
    Mt3620_Gpio_AddBlock(&gpio_block_A);
    Mt3620_Gpio_AddBlock(&gpio_block_B);
*/  
}
