#ifndef __CORE_PERIPHERY_MT3620
#define __CORE_PERIPHERY_MT3620

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <core_cm4.h>

/* UART ********************************************************************************/

// [UartCM4Debug] = {.baseAddr = 0x21040000, .nvicIrq = 4},
// [UartIsu0]     = {.baseAddr = 0x38070500, .nvicIrq = 47},

#define UART_BASE               (0x38070500) /* UartIsu0 = 0x38070500 */
#define DEBUG_BASE              (0x21040000) /* UartCM4Debug = 0x21040000 */

#define UART_CLOCK_FREQ         (26000000)

#define   UART_DATA_MASK        (0x0003)
#define   UART_PARITY_MASK      (0x0038)
#define   UART_STOP_MASK        (0x0004)

#define   UART_LCR_DLAB         (0x0080)

//WLS
#define   UART_WLS_8            (0x0003)
#define   UART_WLS_7            (0x0002)
#define   UART_WLS_6            (0x0001)
#define   UART_WLS_5            (0x0000)

//Parity
#define   UART_NONE_PARITY      (0x0000)
#define   UART_ODD_PARITY       (0x0008)
#define   UART_EVEN_PARITY      (0x0018)
#define   UART_MARK_PARITY      (0x0028)
#define   UART_SPACE_PARITY     (0x0038)

//Stop bits
#define   UART_1_STOP           (0x0000)
#define   UART_1_5_STOP         (0x0004) // Only valid for 5 data bits
#define   UART_2_STOP           (0x0004)


#define UART_RBR                (0x00) /* USED, Receive Buffer Register */  /* Read only */
#define UART_THR                (0x00) /* USED, TX Holding Register */      /* Write only */
#define UART_IER                (0x04) /* USED, IER[ERBGI] = 1 -> Enable Receiver Buffer Full Interrupt */
#define UART_IIR                (0x08)            /* Read only */
#define UART_FCR                (0x08)            /* Write only */
  // FCR[RFTL] = 2 -> 12 element RX FIFO trigger
  // FCR[TFTL] = 1 -> 4 element TX FIFO trigger
  // FCR[CLRT] = 1 -> Clear Transmit FIFO
  // FCR[CLRR] = 1 -> Clear Receive FIFO
  // FCR[FIFOE] = 1 -> FIFO Enable
  //(2U << 6) | (1U << 4) | (1U << 2) | (1U << 1) | (1U << 0);

#define UART_LCR                (0x0c) /* USED, 3 = 8-bit word length, 0xBF = enable DLL, DLM */
#define UART_MCR                (0x10)
#define UART_LSR                (0x14) /* USED, When LSR[5] is set, can write another character. */
#define UART_MSR                (0x18)
#define UART_SCR                (0x1c)

#define UART_DLL                (0x00) /* USED */
#define UART_DLH                (0x04) /* USED */
#define UART_EFR                (0x08) /* USED, 0x10 = enable enhancement features */         
#define UART_XON1               (0x10)          
#define UART_XON2               (0x14)          
#define UART_XOFF1              (0x18)          
#define UART_XOFF2              (0x1c)          

#define UART_AUTOBAUD_EN        (0x20)
#define UART_RATE_STEP          (0x24) /* USED HIGHSPEED = 3*/
#define UART_STEP_COUNT         (0x28) /* USED */
#define UART_SAMPLE_COUNT       (0x2c) /* USED */
#define UART_AUTOBAUD_REG       (0x30)
#define UART_RATE_FIX_REG       (0x34)
#define UART_ESCAPE_DATA        (0x40)
#define UART_ESCAPE_EN          (0x44)
#define UART_SLEEP_EN           (0x48)
#define UART_VFIFO_EN_REG       (0x4c)
#define UART_FRACDIV_L          (0x54) /* USED */
#define UART_FRACDIV_M          (0x58) /* USED */

#define UART_IER_CTSI           (0x80UL)
#define UART_IER_RTSI           (0x40UL)
#define UART_IER_XOFFI          (0x20UL)
#define UART_IER_EDSSI          (0x8UL)
#define UART_IER_ELSI           (0x4UL)
#define UART_IER_ETBEI          (0x2UL)
#define UART_IER_ERBFI          (0x1UL)

/// UartSetFormat(uart_base, brg, UART_WLS_8, UART_NONE_PARITY, UART_1_STOP); 
int Uart_SetFormat(uint32_t BASE, uint32_t baudrate, uint16_t databit, uint16_t parity, uint16_t stopbit);

/* GPT ********************************************************************************/
#define  GPT_BASE 0x21030000

#define GPT_ISR                 (GPT_BASE+0x00)
#define GPT_IER                 (GPT_BASE+0x04)
#define GPT0_CTRL               (GPT_BASE+0x10) /* USED */
#define GPT0_ICNT               (GPT_BASE+0x14) /* USED */
#define GPT1_CTRL               (GPT_BASE+0x20) /* USED */
#define GPT1_ICNT               (GPT_BASE+0x24) /* USED */
#define GPT2_CTRL               (GPT_BASE+0x30)
#define GPT2_CNT                (GPT_BASE+0x34)
#define GPT0_CNT                (GPT_BASE+0x40)
#define GPT1_CNT                (GPT_BASE+0x44)

#define GPT3_CTRL               (GPT_BASE+0x50) /* USED */
#define GPT3_INIT               (GPT_BASE+0x54) /* USED */
#define GPT3_CNT                (GPT_BASE+0x58) /* USED */
#define GPT3_EXPIRE             (GPT_BASE+0x5C)

#define GPT4_CTRL               (GPT_BASE+0x60)
#define GPT4_INIT               (GPT_BASE+0x64)
#define GPT4_CNT                (GPT_BASE+0x68)

//GPT_ISR
#define GPT0_INT                (0x01)
#define GPT1_INT                (0x02)

//GPT_IER
#define GPT0_INT_EN             (0x01)
#define GPT1_INT_EN             (0x02)

//GPT_CTRL
#define GPT_CTRL_EN             (0x01)
#define GPT_CTRL_AUTOMODE       (0x02)

//GPT3
#define GPT3_OSC_CNT_1US_SHIFT	(16)
#define GPT3_OSC_CNT_1US_MASK	(0x3F)


#ifdef __cplusplus
}
#endif

#endif /* __CORE_PERIPHERY_MT3620 */

