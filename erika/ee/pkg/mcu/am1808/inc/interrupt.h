#ifndef __INCLUDE_AM1808_INTERRUPT__
#define __INCLUDE_AM1808_INTERRUPT__

// If we want to include this into .S file do ot include functions!
#ifndef ASM_INC 

// Initializes AINTC ad IRQ in general
void irq_init(void);

// Enables global IRQ
void irq_enable(void);

// Disables global IRQ
void irq_disable(void);

// Gets global IRQ status
unsigned int irq_status(void);

// Registers a ISR for a given IRQ number
void irq_register(unsigned int num, void (*isr)(void));

// Unregisters a ISR for a given IRQ number
void irq_unregister(unsigned int num);

// Clears the status of a given IRQ number
void irq_clear_status(unsigned int num);


// Enables the IRQ given its number
void irq_enable_num(unsigned int num);

// Disables the IRQ given its number
void irq_disable_num(unsigned int num);

// Maps the IRQ by its number to a chanel
void irq_set_channel(unsigned int num, unsigned int channel);

// Gets the channel mapped to and IRQ by its number
unsigned int irq_get_channel(unsigned int num);

// Gets the IRQ number of the currently handled IRQ
unsigned int irq_get_current_num();

// Gets the "priority" i.e. channel of the current IRQ being handled
unsigned int irq_get_current_channel(void);

// Not for external use. Implemented in arm9_interrupt_hannndler.S
void irq_handler(void);

// Disable interrupts at the AINTC
void intctl_enable(void);

// Enable interrupts at the AINTC
void intctl_disable(void);


#endif //!ASM_INC

// ARM interrupt controller (AINTC)
#define AINTC_BASE 0xFFFEE000

/**
 * This is not a complete set of all AINTC (Arm Interrupt Controller) registers.
 * Those are just the ones required for a very basic usage.
 * A complete list can be found in the Technical User Manual
 * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=290
 */

// Global Enable Register to ennable/disable aintc 
#define AINTC_GER (volatile unsigned int *)(AINTC_BASE + 0x0010)

// Vector Base Address Register i.e. where to find ISR addresses 
#define AINTC_VBR (volatile unsigned int *)(AINTC_BASE + 0x0050)

// Vector Size Register i.e. what is the size of the ISR addresses 
#define AINTC_VSR (volatile unsigned int *)(AINTC_BASE + 0x0054)

// Status Clear/Enable register for checking and clearing status  
#define AINTC_SECR1 (volatile unsigned int *)(AINTC_BASE + 0x0280)

// Enable register to enable specific IRQ (Writing 0 has no effect)  
#define AINTC_ESR1 (volatile unsigned int *)(AINTC_BASE + 0x0300)

// Clear Enable (i.e. disable) register to disable specific IRQ (Writing 0 has no effect) 
#define AINTC_ECR1 (volatile unsigned int *)(AINTC_BASE + 0x0380)

// Chanel map register for mapping IRQ num to chanel  
#define AINTC_CMR0 (volatile unsigned int *)(AINTC_BASE + 0x0400)

// Host Interrupt Enable Register to enable IRQ/FIQ in general 
#define AINTC_HIER (volatile unsigned int *)(AINTC_BASE + 0x1500)

// ISR addres register (Host Interrupt Priority Vector Register 2; 1 is for FIQ) 
// As this Register is required in assembler files and assembler files only hardcode address
#define AINTC_HIPVR2 0xFFFEF604

// IRQ number reigster (Host Interrupt Prioritized Index Register 2 ; 1 is for FIQ) 
#define AINTC_HIPIR2 0xFFFEE904


// AINTC bits
#define GER_ENABLE 1      // Bit to enable IRQ globally 
#define GER_DISABLE 0     // Bit to disable IRQ globally 
#define HIER_IRQ (1 << 1) // Bit to enable only IRQ (not FIQ) in HIER register

/**
 * The AINTC can handle 101 Interrupts which have individual flags for status, enablig or disabling.
 * Those flags (if 1 bit in width) are mapped over four 32-bit register (SRS1-4, SECR1-4, ESR1-4, ECR1-4).
 * This macro sets the correct bit in the 32-bit integer given the interrupt number.
 */
#define irq_bit_by_num(n) 1 << (n % 32)


/**
 * Defines total number of Interrupts and the interrupt name with its corresponding number.
 * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=290
 */
#define NUM_INTERRUPTS 101
#define NUM_CHANNELS 32

#define IRQ_NUM_COMMTX 0  // ARM
#define IRQ_NUM_COMMRX 1  // ARM
#define IRQ_NUM_NINT 2  // ARM
#define IRQ_NUM_PRU_EVTOUT0 3  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT1 4  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT2 5  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT3 6  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT4 7  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT5 8  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT6 9  // PRUSS Interrupt
#define IRQ_NUM_PRU_EVTOUT7 10  // PRUSS Interrupt
#define IRQ_NUM_EDMA3_0_CC0_INT0 11  // EDMA3_0 Channel Controller 0 Shadow Region 0 Transfer Completion Interrupt
#define IRQ_NUM_EDMA3_0_CC0_ERRINT 12  // EDMA3_0 Channel Controller 0 Error Interrupt
#define IRQ_NUM_EDMA3_0_TC0_ERRINT 13  // EDMA3_0 Transfer Controller 0 Error Interrupt
#define IRQ_NUM_EMIFA_INT 14  // EMIFA Interrupt
#define IRQ_NUM_IIC0_INT 15  // I2C0 interrupt
#define IRQ_NUM_MMCSD0_INT0 16  // MMCSD0 MMC/SD Interrupt
#define IRQ_NUM_MMCSD0_INT1 17  // MMCSD0 SDIO Interrupt
#define IRQ_NUM_PSC0_ALLINT 18  // PSC0 Interrupt
#define IRQ_NUM_RTC_IRQS 19  // 1:0] RTC Interrupt
#define IRQ_NUM_SPI0_INT 20  // SPI0 Interrupt
#define IRQ_NUM_T64P0_TINT12 21  // Timer64P0 Interrupt (TINT12)
#define IRQ_NUM_T64P0_TINT34 22  // Timer64P0 Interrupt (TINT34)
#define IRQ_NUM_T64P1_TINT12 23  // Timer64P1 Interrupt (TINT12)
#define IRQ_NUM_T64P1_TINT34 24  // Timer64P1 Interrupt (TINT34)
#define IRQ_NUM_UART0_INT 25  // UART0 Interrupt
// #define IRQ_NUM_— 26  // Reserved
#define IRQ_NUM_PROTERR 27  // SYSCFG Protection Shared Interrupt
#define IRQ_NUM_SYSCFG_CHIPINT0 28  // SYSCFG CHIPSIG Register
#define IRQ_NUM_SYSCFG_CHIPINT1 29  // SYSCFG CHIPSIG Register
#define IRQ_NUM_SYSCFG_CHIPINT2 30  // SYSCFG CHIPSIG Register
#define IRQ_NUM_SYSCFG_CHIPINT3 31  // SYSCFG CHIPSIG Register
#define IRQ_NUM_EDMA3_0_TC1_ERRINT 32  // EDMA3_0 Transfer Controller 1 Error Interrupt
#define IRQ_NUM_EMAC_C0RXTHRESH 33  // EMAC - Core 0 Receive Threshold Interrupt
#define IRQ_NUM_EMAC_C0RX 34  // EMAC - Core 0 Receive Interrupt
#define IRQ_NUM_EMAC_C0TX 35  // EMAC - Core 0 Transmit Interrupt
#define IRQ_NUM_EMAC_C0MISC 36  // EMAC - Core 0 Miscellaneous Interrupt
#define IRQ_NUM_EMAC_C1RXTHRESH 37  // EMAC - Core 1 Receive Threshold Interrupt
#define IRQ_NUM_EMAC_C1RX 38  // EMAC - Core 1 Receive Interrupt
#define IRQ_NUM_EMAC_C1TX 39  // EMAC - Core 1 Transmit Interrupt
#define IRQ_NUM_EMAC_C1MISC 40  // EMAC - Core 1 Miscellaneous Interrupt
#define IRQ_NUM_DDR2_MEMERR 41  // DDR2 Controller Interrupt
#define IRQ_NUM_GPIO_B0INT 42  // GPIO Bank 0 Interrupt
#define IRQ_NUM_GPIO_B1INT 43  // GPIO Bank 1 Interrupt
#define IRQ_NUM_GPIO_B2INT 44  // GPIO Bank 2 Interrupt
#define IRQ_NUM_GPIO_B3INT 45  // GPIO Bank 3 Interrupt
#define IRQ_NUM_GPIO_B4INT 46  // GPIO Bank 4 Interrupt
#define IRQ_NUM_GPIO_B5INT 47  // GPIO Bank 5 Interrupt
#define IRQ_NUM_GPIO_B6INT 48  // GPIO Bank 6 Interrupt
#define IRQ_NUM_GPIO_B7INT 49  // GPIO Bank 7 Interrupt
#define IRQ_NUM_GPIO_B8INT 50  // GPIO Bank 8 Interrupt
#define IRQ_NUM_IIC1_INT 51  // I2C1 Interrupt
#define IRQ_NUM_LCDC_INT 52  // LCD Controller Interrupt
#define IRQ_NUM_UART1_INT 53  // UART1 Interrupt
#define IRQ_NUM_MCASP_INT 54  // McASP0 Combined RX/TX Interrupt
#define IRQ_NUM_PSC1_ALLINT 55  // PSC1 Interrupt
#define IRQ_NUM_SPI1_INT 56  // SPI1 Interrupt
#define IRQ_NUM_UHPI_ARMINT 57  // HPI ARM Interrupt
#define IRQ_NUM_USB0_INT 58  // USB0 (USB2.0) Interrupt
#define IRQ_NUM_USB1_HCINT 59  // USB1 (USB1.1) OHCI Host Controller Interrupt
#define IRQ_NUM_USB1_R 60  // WAKEUP USB1 (USB1.1) Remote Wakeup Interrupt
#define IRQ_NUM_UART2_INT 61  // UART2 Interrupt
//#define IRQ_NUM_— 62  // Reserved
#define IRQ_NUM_EHRPWM0 63  // HiResTimer / PWM0 Interrupt
#define IRQ_NUM_EHRPWM0TZ 64  // HiResTimer / PWM0 Trip Zone Interrupt
#define IRQ_NUM_EHRPWM1 65  // HiResTimer / PWM1 Interrupt
#define IRQ_NUM_EHRPWM1TZ 66  // HiResTimer / PWM1 Trip Zone Interrupt
#define IRQ_NUM_SATA_INT 67  // SATA Controller Interrupt
#define IRQ_NUM_T64P2_ALL 68  // Timer64P2 Combined Interrupt (TINT12 and TINT34)
#define IRQ_NUM_ECAP0 69  // eCAP0 Interrupt
#define IRQ_NUM_ECAP1 70  // eCAP1 Interrupt
#define IRQ_NUM_ECAP2 71  // eCAP2 Interrupt
#define IRQ_NUM_MMCSD1_INT0 72  // MMCSD1 MMC/SD Interrupt
#define IRQ_NUM_MMCSD1_INT1 73  // MMCSD1 SDIO Interrupt
#define IRQ_NUM_T64P2_CMPINT0 74  // Timer64P2 - Compare Interrupt 0
#define IRQ_NUM_T64P2_CMPINT1 75  // Timer64P2 - Compare Interrupt 1
#define IRQ_NUM_T64P2_CMPINT2 76  // Timer64P2 - Compare Interrupt 2
#define IRQ_NUM_T64P2_CMPINT3 77  // Timer64P2 - Compare Interrupt 3
#define IRQ_NUM_T64P2_CMPINT4 78  // Timer64P2 - Compare Interrupt 4
#define IRQ_NUM_T64P2_CMPINT5 79  // Timer64P2 - Compare Interrupt 5
#define IRQ_NUM_T64P2_CMPINT6 80  // Timer64P2 - Compare Interrupt 6
#define IRQ_NUM_T64P2_CMPINT7 81  // Timer64P2 - Compare Interrupt 7
#define IRQ_NUM_T64P3_CMPINT0 82  // Timer64P3 - Compare Interrupt 0
#define IRQ_NUM_T64P3_CMPINT1 83  // Timer64P3 - Compare Interrupt 1
#define IRQ_NUM_T64P3_CMPINT2 84  // Timer64P3 - Compare Interrupt 2
#define IRQ_NUM_T64P3_CMPINT3 85  // Timer64P3 - Compare Interrupt 3
#define IRQ_NUM_T64P3_CMPINT4 86  // Timer64P3 - Compare Interrupt 4
#define IRQ_NUM_T64P3_CMPINT5 87  // Timer64P3 - Compare Interrupt 5
#define IRQ_NUM_T64P3_CMPINT6 88  // Timer64P3 - Compare Interrupt 6
#define IRQ_NUM_T64P3_CMPINT7 89  // Timer64P3 - Compare Interrupt 7
#define IRQ_NUM_ARMCLKSTOPREQ 90  // PSC0 Interrupt
#define IRQ_NUM_uPP_ALLINT 91  // uPP Combined Interrupt
#define IRQ_NUM_VPIF_ALLINT 92  // VPIF Combined Interrupt
#define IRQ_NUM_EDMA3_1_CC0_INT0 93  // EDMA3_1 Channel Controller 0 Shadow Region 0 Transfer
#define IRQ_NUM_EDMA3_1_CC0_ERRINT 94  // EDMA3_1 Channel Controller 0 Error Interrupt
#define IRQ_NUM_EDMA3_1_TC0_ERRINT 95  // EDMA3_1 Transfer Controller 0 Error Interrupt
#define IRQ_NUM_T64P3_ALL 96  // Timer64P3 Combined Interrupt (TINT12 and TINT34)
#define IRQ_NUM_MCBSP0_RINT 97  // McBSP0 Receive Interrupt
#define IRQ_NUM_MCBSP0_XINT 98  // McBSP0 Transmit Interrupt
#define IRQ_NUM_MCBSP1_RINT 99  // McBSP1 Receive Interrupt
#define IRQ_NUM_MCBSP1_XINT 100  // McBSP1 Transmit Interrupt

#endif //__INCLUDE_AM1808_INTERRUPT__
