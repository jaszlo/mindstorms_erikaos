#ifndef __INCLUDE_ARM9_UART__
#define __INCLUDE_ARM9_UART__


// Functions
#include "mcu/am1808/inc/uart.h"

/**
 * \brief   Configures the following parameters: 
 *           1> Baud Rate.
 *           2> Data Length in bits in each frame.
 *           3> Number of stop bits per frame.
 *           4> Parity selection(one among NO,ODD or EVEN parity. 
 *             and Stick Parity bit selection).
 *
 * \param     baseAdd         Memory address of the UART instance used.
 * \param     uartClk         Frequency of the clock supplied to the UART module.
 * \param     baudrate        Required baud rate of communication.
 * \param     config          Logical OR of the appropriate macros related to 
 *                            parity, number of stop bits and number of data 
 *                            bits per frame.
 * \param     overSampRate    Over-sampling rate(either 13x or 16x).
 *
 * \return                    None.
 *            
 * ote     The baud rate is configured by setting the divisor values derived 
 *           from the module input clock \uartClk and the over sampling rate 
 *           \overSampleRate. The module input clock depends on the PLL 
 *           configurations and the system clock tree. 
 */
void uart_configure (unsigned int uartClk, unsigned int baudrate, unsigned int config, unsigned int overSampRate);

// Sets the parity mode to be used
void uart_set_parity_mode(unsigned int parityMode);

// Enables free mode for transmitter and receiver
void uart_enable (void);

// Disables free mode for transmitter and receiver
void uart_disable(void);


// Enable FIFO and clear transmitter and receiver buffers
void uart_fifo_enable(void);

// Disable FIFO and clear transmitter and receiver buffers
void uart_fifo_disable(void);

// Checks if data is ready to be received if so returns 1 else 0
unsigned int uart_chars_available(void);

// This function does not waits for the arrival of a byte and will
// return -1 if no data was ready to be received
char uart_get_char(void);

// This function waits indefinitely for the arrival of a byte and will
// return the byte when received
char uart_get_char_blocking(void);

/**
 * This function enables the specified interrupts of the UART module.
 * intFlags is bitwise OR'ed to specify which irq source of the uart to disabled.
 * [1       1       1         0b0]
 *  Modem   Line    TX Empty  RX Filled
 */
void uart_irq_enable(unsigned int intFlags);


/**
 * This function disables the specified interrupts of the UART module.
 * intFlags is bitwise OR'ed to specify which irq source of the uart to disabled.
 * [1       1       1         0b0]
 *  Modem   Line    TX Empty  RX Filled
 */
void uart_irq_disable(unsigned int intFlags);


/**
 * This function returns highest priority UART interrupt status
 * Returns either 1,2,3 or 4:      
 * 1> UART_IRQID_TX_EMPTY.
 * 2> UART_IRQID_RX_DATA.
 * 3> UART_IRQID_RX_LINE_STAT.
 * 4> UART_IRQID_CTI.
 */
unsigned int uart_irq_status(void);

// Defines for the Configuration of the UART
#define BAUD_115200                   115200
#define CLK_SPEED                     300000000 / 2

// Base addresses of memory mapped uart registers
#define UART_0_BASE (0x01C42000)
#define UART_1_BASE (0x01D0C000)
#define UART_2_BASE (0x01D0D000)

///* UART Control Bits
#define UART_WORDL    (0x03)
#define UART_STOP_BIT (0x04)
#define UART_PARITY   (0x08)

// UART_LCR Register Values to Configure UART
#define UART_SET_PARITY_TYPE (0x10)
#define UART_STICK_PARITY    (0x20)
#define UART_BREAK_CTRL      (0x40)
#define UART_DLAB            (0x80)

// UART_PWREMU_MGMT Register Values to Manage Power
#define UART_FREE_MODE (0x10)
#define UART_RX_RST_ENABLE (0x2000)
#define UART_TX_RST_ENABLE (0x4000)

// UART_FCR Register Values To Configure FIFO Mode
#define UART_FIFO_MODE (0x01)
#define UART_RX_CLEAR  (0x02)
#define UART_TX_CLEAR  (0x04)

// UART_IER Register Values to enable/disable UART IRQ source
#define UART_INT_MODEM_STAT (0x08)
#define UART_INT_LINE_STAT  (0x04)
#define UART_INT_TX_EMPTY   (0x02)
#define UART_INT_RHR_CTI    (0x01)
#define UART_INT_RXDATA_CTI (0x01)

// UART IRQ sources correspond with UART_IER configuration above
#define UART_IRQID_TX_EMPTY 1
#define UART_IRQID_RX_DATA 2
#define UART_IRQID_RX_LINE_STAT 3
#define UART_IRQID_CTI 4


///* End of UART Control Bits

// Uart Registers offset from base reg
#define UART_RBR (volatile unsigned char *) (UART_1_BASE + 0x00)           // Receiver Buffer Register (read only)
#define UART_THR (volatile unsigned char *) (UART_1_BASE + 0x00)           // Transmitter Holding Register (write only)
#define UART_IER (volatile unsigned char *) (UART_1_BASE + 0x04)           // Interrupt Enable Register
#define UART_IIR (volatile unsigned char *) (UART_1_BASE + 0x08)           // Interrupt Identification Register (read only)
#define UART_FCR (volatile unsigned char *) (UART_1_BASE + 0x08)           // FIFO Control Register (write only)
#define UART_LCR (volatile unsigned char *) (UART_1_BASE + 0x0C)           // Line Control Register
#define UART_MCR (volatile unsigned char *) (UART_1_BASE + 0x10)           // Modem Control Register
#define UART_LSR (volatile unsigned char *) (UART_1_BASE + 0x14)           // Line Status Register
#define UART_MSR (volatile unsigned char *) (UART_1_BASE + 0x18)           // Modem Status Register
#define UART_SCR (volatile unsigned char *) (UART_1_BASE + 0x1C)           // Scratch Pad Register
#define UART_DLL (volatile unsigned char *) (UART_1_BASE + 0x20)           // Divisor LSB Latch
#define UART_DLH (volatile unsigned char *) (UART_1_BASE + 0x24)           // Divisor MSB Latch
#define UART_REVID1 (volatile unsigned char *) (UART_1_BASE + 0x28)        // Revision Identification Register 1
#define UART_REVID2 (volatile unsigned char *) (UART_1_BASE + 0x2C)        // Revision Identification Register 2
#define UART_PWREMU_MGMT (volatile unsigned char *) (UART_1_BASE + 0x30)   // Power and Emulation Management Register
#define UART_MDR (volatile unsigned char *) (UART_1_BASE + 0x34)           // Mode Definition Register


#endif /* __INCLUDE_ARM9_UART__ */