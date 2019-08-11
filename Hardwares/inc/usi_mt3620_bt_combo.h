/* Copyright (c) Microsoft Corporation. All rights reserved.
   Licensed under the MIT License. */

// This header lists the available peripherals for the USI MT3620 BT COMBO
// and provides the header definition and application manifest values required to use them.

// This file is autogenerated from ..\..\usi_mt3620_bt_combo.json.  Do not edit it directly.

#pragma once
#include "mt3620.h"

// The internal connection to the BT_nRST signal on nRF52810 from MT3620 GPIO 22. USI-MT3620-BT-COMBO U1B pin 37 also exposes this signal.
#define USI_MT3620_BT_COMBO_NRF52_RESET MT3620_GPIO22

// The internal connection to the BT_FW_EN signal on nRF52810 from MT3620 GPIO 23. USI-MT3620-BT-COMBO U1B pin 38 also exposes this signal.
#define USI_MT3620_BT_COMBO_NRF52_DFU MT3620_GPIO23

// USI-MT3620-BT-COMBO pin 1 exposes GPIO 56.
#define USI_MT3620_BT_COMBO_PIN1_GPIO56 MT3620_GPIO56

// USI-MT3620-BT-COMBO pin 2 exposes GPIO 59.
#define USI_MT3620_BT_COMBO_PIN2_GPIO59 MT3620_GPIO59

// USI-MT3620-BT-COMBO pin 3 exposes GPIO 57.
#define USI_MT3620_BT_COMBO_PIN3_GPIO57 MT3620_GPIO57

// USI-MT3620-BT-COMBO pin 93 exposes GPIO 60.
#define USI_MT3620_BT_COMBO_PIN93_GPIO60 MT3620_GPIO60

// USI-MT3620-BT-COMBO pin 94 exposes GPIO 58.
#define USI_MT3620_BT_COMBO_PIN94_GPIO58 MT3620_GPIO58

// USI-MT3620-BT-COMBO pin 23 exposes GPIO 46.
#define USI_MT3620_BT_COMBO_PIN23_GPIO46 MT3620_GPIO46

// USI-MT3620-BT-COMBO pin 24 exposes GPIO 45.
#define USI_MT3620_BT_COMBO_PIN24_GPIO45 MT3620_GPIO45

// USI-MT3620-BT-COMBO pin 25 exposes GPIO 44.
#define USI_MT3620_BT_COMBO_PIN25_GPIO44 MT3620_GPIO44

// USI-MT3620-BT-COMBO pin 26 exposes GPIO 43.
#define USI_MT3620_BT_COMBO_PIN26_GPIO43 MT3620_GPIO43

// USI-MT3620-BT-COMBO pin 27 exposes GPIO 42.
#define USI_MT3620_BT_COMBO_PIN27_GPIO42 MT3620_GPIO42

// USI-MT3620-BT-COMBO pin 28 exposes GPIO 41.
#define USI_MT3620_BT_COMBO_PIN28_GPIO41 MT3620_GPIO41

// USI-MT3620-BT-COMBO pin 33 exposes GPIO 40.
#define USI_MT3620_BT_COMBO_PIN33_GPIO40 MT3620_GPIO40

// USI-MT3620-BT-COMBO pin 34 exposes GPIO 39. Pin shared with SPI2 and UART2.
#define USI_MT3620_BT_COMBO_PIN34_GPIO39 MT3620_GPIO39

// USI-MT3620-BT-COMBO pin 35 exposes GPIO 38. Pin shared with ISU2.
#define USI_MT3620_BT_COMBO_PIN35_GPIO38 MT3620_GPIO38

// USI-MT3620-BT-COMBO pin 36 exposes GPIO 37. Pin shared with ISU2.
#define USI_MT3620_BT_COMBO_PIN36_GPIO37 MT3620_GPIO37

// USI-MT3620-BT-COMBO pin 37 exposes GPIO 36. Pin shared with SPI2 and UART2.
#define USI_MT3620_BT_COMBO_PIN37_GPIO36 MT3620_GPIO36

// USI-MT3620-BT-COMBO pin 38 exposes GPIO 35. Pin shared with SPI1.
#define USI_MT3620_BT_COMBO_PIN38_GPIO35 MT3620_GPIO35

// USI-MT3620-BT-COMBO pin 39 exposes GPIO 34. Pin shared with SPI1 and UART1.
#define USI_MT3620_BT_COMBO_PIN39_GPIO34 MT3620_GPIO34

// USI-MT3620-BT-COMBO pin 40 exposes GPIO 33. Pin shared with ISU1.
#define USI_MT3620_BT_COMBO_PIN40_GPIO33 MT3620_GPIO33

// USI-MT3620-BT-COMBO pin 41 exposes GPIO 32. Pin shared with ISU1.
#define USI_MT3620_BT_COMBO_PIN41_GPIO32 MT3620_GPIO32

// USI-MT3620-BT-COMBO pin 42 exposes GPIO 31. Pin shared with SPI1 and UART1.
#define USI_MT3620_BT_COMBO_PIN42_GPIO31 MT3620_GPIO31

// USI-MT3620-BT-COMBO pin 43 exposes GPIO 30. Pin shared with SPI0.
#define USI_MT3620_BT_COMBO_PIN43_GPIO30 MT3620_GPIO30

// USI-MT3620-BT-COMBO pin 44 exposes GPIO 29. Pin shared with SPI0 and UART0.
#define USI_MT3620_BT_COMBO_PIN44_GPIO29 MT3620_GPIO29

// USI-MT3620-BT-COMBO pin 45 exposes GPIO 28. Pin shared with ISU0.
#define USI_MT3620_BT_COMBO_PIN45_GPIO28 MT3620_GPIO28

// USI-MT3620-BT-COMBO pin 46 exposes GPIO 27. Pin shared with ISU0.
#define USI_MT3620_BT_COMBO_PIN46_GPIO27 MT3620_GPIO27

// USI-MT3620-BT-COMBO pin 47 exposes GPIO 26. Pin shared with SPI0 and UART0.
#define USI_MT3620_BT_COMBO_PIN47_GPIO26 MT3620_GPIO26

// USI-MT3620-BT-COMBO pin 52 exposes GPIO 16. Pin shared with ISU1.
#define USI_MT3620_BT_COMBO_PIN52_GPIO16 MT3620_GPIO16

// USI-MT3620-BT-COMBO pin 53 exposes GPIO 15.
#define USI_MT3620_BT_COMBO_PIN53_GPIO15 MT3620_GPIO15

// USI-MT3620-BT-COMBO pin 54 exposes GPIO 14.
#define USI_MT3620_BT_COMBO_PIN54_GPIO14 MT3620_GPIO14

// USI-MT3620-BT-COMBO pin 55 exposes GPIO 13.
#define USI_MT3620_BT_COMBO_PIN55_GPIO13 MT3620_GPIO13

// USI-MT3620-BT-COMBO pin 56 exposes GPIO 12.
#define USI_MT3620_BT_COMBO_PIN56_GPIO12 MT3620_GPIO12

// USI-MT3620-BT-COMBO pin 58 exposes GPIO 11.
#define USI_MT3620_BT_COMBO_PIN58_GPIO11 MT3620_GPIO11

// USI-MT3620-BT-COMBO pin 59 exposes GPIO 10.
#define USI_MT3620_BT_COMBO_PIN59_GPIO10 MT3620_GPIO10

// USI-MT3620-BT-COMBO pin 60 exposes GPIO 9.
#define USI_MT3620_BT_COMBO_PIN60_GPIO9 MT3620_GPIO9

// USI-MT3620-BT-COMBO pin 61 exposes GPIO 8.
#define USI_MT3620_BT_COMBO_PIN61_GPIO8 MT3620_GPIO8

// USI-MT3620-BT-COMBO pin 62 exposes GPIO 7.
#define USI_MT3620_BT_COMBO_PIN62_GPIO7 MT3620_GPIO7

// USI-MT3620-BT-COMBO pin 63 exposes GPIO 6.
#define USI_MT3620_BT_COMBO_PIN63_GPIO6 MT3620_GPIO6

// USI-MT3620-BT-COMBO pin 64 exposes GPIO 5.
#define USI_MT3620_BT_COMBO_PIN64_GPIO5 MT3620_GPIO5

// USI-MT3620-BT-COMBO pin 65 exposes GPIO 4.
#define USI_MT3620_BT_COMBO_PIN65_GPIO4 MT3620_GPIO4

// USI-MT3620-BT-COMBO pin 66 exposes GPIO 3.
#define USI_MT3620_BT_COMBO_PIN66_GPIO3 MT3620_GPIO3

// USI-MT3620-BT-COMBO pin 67 exposes GPIO 2.
#define USI_MT3620_BT_COMBO_PIN67_GPIO2 MT3620_GPIO2

// USI-MT3620-BT-COMBO pin 68 exposes GPIO 1.
#define USI_MT3620_BT_COMBO_PIN68_GPIO1 MT3620_GPIO1

// USI-MT3620-BT-COMBO pin 69 exposes GPIO 0.
#define USI_MT3620_BT_COMBO_PIN69_GPIO0 MT3620_GPIO0

// USI-MT3620-BT-COMBO pin 87 exposes GPIO 69. Pin shared with SPI3 and UART3.
#define USI_MT3620_BT_COMBO_PIN87_GPIO69 MT3620_GPIO69

// USI-MT3620-BT-COMBO pin 88 exposes GPIO 70. Pin shared with SPI3.
#define USI_MT3620_BT_COMBO_PIN88_GPIO70 MT3620_GPIO70

// USI-MT3620-BT-COMBO pin 89 exposes GPIO 68. Pin shared with ISU3.
#define USI_MT3620_BT_COMBO_PIN89_GPIO68 MT3620_GPIO68

// USI-MT3620-BT-COMBO pin 90 exposes GPIO 67. Pin shared with ISU3.
#define USI_MT3620_BT_COMBO_PIN90_GPIO67 MT3620_GPIO67

// USI-MT3620-BT-COMBO pin 91 exposes GPIO 66. Pin shared with SPI3 and UART3.
#define USI_MT3620_BT_COMBO_PIN91_GPIO66 MT3620_GPIO66

// USI-MT3620-BT-COMBO ISU 0 configured as UART, pin 45 (RX), pin 47 (TX), pin 44 (CTS), and pin 46 (RTS).
#define USI_MT3620_BT_COMBO_ISU0_UART MT3620_ISU0_UART

// USI-MT3620-BT-COMBO ISU 0 configured as SPI, pin 45 (MISO), pin 47 (SCLK), pin 43 (CSB), pin 44 (CSA), and pin 46 (MOSI).
#define USI_MT3620_BT_COMBO_ISU0_SPI MT3620_ISU0_SPI

// USI-MT3620-BT-COMBO ISU 0 configured as I2C,  pin 45 (SDA) and pin 46 (SCL).
#define USI_MT3620_BT_COMBO_ISU0_I2C MT3620_ISU0_I2C

// USI-MT3620-BT-COMBO ISU 1 configured as UART, pin 40 (RX), pin 42 (TX), pin 39 (CTS), and pin 41 (RTS).
#define USI_MT3620_BT_COMBO_ISU1_UART MT3620_ISU1_UART

// USI-MT3620-BT-COMBO ISU 1 configured as SPI, pin 40 (MISO), pin 42 (SCLK), pin 39 (CSA), pin 41 (MOSI) and pin 38 (CSB).
#define USI_MT3620_BT_COMBO_ISU1_SPI MT3620_ISU1_SPI

// USI-MT3620-BT-COMBO ISU 1 configured as I2C,  pin 40 (SDA) and pin 41 (SCL).
#define USI_MT3620_BT_COMBO_ISU1_I2C MT3620_ISU1_I2C

// USI-MT3620-BT-COMBO ISU 2 configured as UART, pin 35 (RX), pin 37 (TX), pin 34 (CTS), pin 36 (RTS).
#define USI_MT3620_BT_COMBO_ISU2_UART MT3620_ISU2_UART

// USI-MT3620-BT-COMBO ISU 2 configured as SPI, pin 35 (MISO), pin 37 (SCLK), pin 34 (CSA), pin 36 (MOSI) and pin 33 (CSB).
#define USI_MT3620_BT_COMBO_ISU2_SPI MT3620_ISU2_SPI

// USI-MT3620-BT-COMBO ISU 2 configured as I2C,  pin 35 (SDA) and pin 36 (SCL).
#define USI_MT3620_BT_COMBO_ISU2_I2C MT3620_ISU2_I2C

// USI-MT3620-BT-COMBO ISU 3 configured as UART, pin 89 (RX), pin 91 (TX), pin 87 (CTS), pin 90 (RTS).
#define USI_MT3620_BT_COMBO_ISU3_UART MT3620_ISU3_UART

// USI-MT3620-BT-COMBO ISU 3 configured as SPI, pin 89 (MISO), pin 91 (SCLK), pin 87 (CSA), pin 90 (MOSI) and pin 88 (CSB).
#define USI_MT3620_BT_COMBO_ISU3_SPI MT3620_ISU3_SPI

// USI-MT3620-BT-COMBO ISU 3 configured as I2C,  pin 89 (SDA) and pin 90 (SCL).
#define USI_MT3620_BT_COMBO_ISU3_I2C MT3620_ISU3_I2C

//  The serial connection to nRF52810 from MT3620. USI-MT3620-BT-COMBO ISU 4 configured as UART, pin 122 (RX), pin 119 (TX), pin 123 (CTS), pin 120 (RTS).
#define USI_MT3620_BT_COMBO_NRF52_UART MT3620_ISU4_UART

