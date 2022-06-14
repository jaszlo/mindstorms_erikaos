#include "mcu/am1808/inc/uart.h"

void uart_configure (unsigned int uartClk, unsigned int baudrate, unsigned int config, 
                     unsigned int overSampRate) 
{                                         
    unsigned int divisor = 0;
    
    /* Calculating the divisor value */
    switch (overSampRate)
    {
        case 13:
            divisor = uartClk/(baudrate * 13);
            *(UART_MDR) = 1;
        break;
        
        case 16:
        default: 
            divisor = uartClk/(baudrate * 16);
            *(UART_MDR) &= ~1;
        break;
    }
    
    /*
    ** Writing the divisor value onto the Divisor Latch registers.
    ** Programming the divisor latch registers with an appropriate value sets
    ** the corresponding baud rate of communication for the device.
    */
    *(UART_DLL) = ((divisor & 0xFF));
    *(UART_DLH) = ((divisor & 0xFF00) >> 8);

    /*
    ** Write only relevant values to the LCR. LCR controls the number of data
    ** bits and stop bits per frame, parity enable feature, type of parity
    ** (even of odd), stick parity enable feature, Break control and DLAB 
    ** selection bits.
    */

    *(UART_LCR) = (config & ( UART_STOP_BIT | UART_WORDL |          \
                                        UART_PARITY | UART_SET_PARITY_TYPE |  \
                                        UART_STICK_PARITY | UART_BREAK_CTRL | \
                                        UART_DLAB));
}

void uart_set_parity_mode(unsigned int parityMode)
{
    /* Clearing the Parity related bits.*/ 
    *(UART_LCR) &= ~(UART_PARITY  | UART_SET_PARITY_TYPE | 
                                   UART_STICK_PARITY);
    /* Setting the Parity related bits depending upon 'parityMode'.*/ 
    *(UART_LCR) |= (parityMode & (UART_PARITY |
                                                UART_SET_PARITY_TYPE |
                                                UART_STICK_PARITY));
}


void uart_enable (void)
{
    /* Enable the Tx, Rx and the free running mode of operation. */
    *(UART_PWREMU_MGMT) = (char) (UART_FREE_MODE | UART_RX_RST_ENABLE | UART_TX_RST_ENABLE);
}


void uart_disable(void)
{
    /* Disable the Tx, Rx and Free running mode of operation.*/
    *(UART_PWREMU_MGMT) &= (char) ~(UART_FREE_MODE | UART_RX_RST_ENABLE | UART_TX_RST_ENABLE);
}


void uart_fifo_enable(void)
{
    *(UART_FCR) = (UART_FIFO_MODE | UART_RX_CLEAR | UART_TX_CLEAR);
}


void uart_fifo_disable(void)  
{
    *(UART_FCR) = 0;
}


unsigned int uart_chars_available(void)
{
    unsigned int available = 0;    

    if (*(UART_LSR) & 0b1)
    {                                         
        available = 1;                                              
    }
    
    return available;
}


char uart_get_char(void)
{
    char data = -1;

    if(*(UART_LSR) & 0b1)
    {
       data = (char) *(UART_RBR);
    }
    
    return data;
}


char uart_get_char_blocking(void)
{
    char data = 0;
    
    while ((*(UART_LSR) & 1) == 0);
    
    data = (char) *(UART_RBR);

    return data;
}


void uart_irq_enable(unsigned int intFlags)
{
    *(UART_IER) |= (intFlags & (UART_INT_MODEM_STAT | UART_INT_LINE_STAT |
                                UART_INT_TX_EMPTY   | UART_INT_RXDATA_CTI));
}


void uart_irq_disable(unsigned int intFlags)
{
    *(UART_IER) &=  ~(intFlags & (UART_INT_MODEM_STAT | UART_INT_LINE_STAT |
                                  UART_INT_TX_EMPTY   | UART_INT_RXDATA_CTI));
}


unsigned int uart_irq_status(void)
{

    unsigned int status = 0;

    status = *(UART_IIR);
    status &= 0xE; 
    status >>= 1;

    return status;
}