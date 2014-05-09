//=============================================================================
//
//    m8c.h: Microcontroller Device System Declarations
//
//    Copyright (c) Cypress Semiconductor 2010. All Rights Reserved.
//
//    This file provides address constants, bit field masks and a set of macro
//    facilities for the Cypress Semiconductor CY8C24090 Microcontroller families.
//
//=============================================================================

#ifndef M8C_C_HEADER
#define M8C_C_HEADER

//-----------------------------------------------
// Define System Types
//-----------------------------------------------
//typedef  unsigned char  BOOL;
typedef  unsigned char  BYTE;
//typedef  signed   char  CHAR;
//typedef  unsigned int   WORD;
typedef  signed   int   INT;
typedef  unsigned long  DWORD;
typedef  signed   long  LONG;

//-----------------------------------------------
// Define Boolean TRUE/FALSE
//-----------------------------------------------
#define  TRUE  ((BOOL) 1)
#define  FALSE ((BOOL) 0)


//=============================================================================
//=============================================================================
//      System Registers
//=============================================================================
//=============================================================================

//-----------------------------------------------
//  Flag Register Bit Fields
//-----------------------------------------------
#define  FLAG_PGMODE_MASK  (0xC0)
#define  FLAG_PGMODE_0     (0x00)
#define  FLAG_PGMODE_1     (0x40)
#define  FLAG_PGMODE_2     (0x80)
#define  FLAG_PGMODE_3     (0xC0)
#define  FLAG_PGMODE_00b   (0x00)
#define  FLAG_PGMODE_01b   (0x40)
#define  FLAG_PGMODE_10b   (0x80)
#define  FLAG_PGMODE_11b   (0xC0)
#define  FLAG_XIO_MASK     (0x10)
#define  FLAG_SUPER        (0x08)
#define  FLAG_CARRY        (0x04)
#define  FLAG_ZERO         (0x02)
#define  FLAG_GLOBAL_IE    (0x01)


//=============================================================================
//=============================================================================
//      Register Space, Bank 0
//=============================================================================
//=============================================================================

//-----------------------------------------------
//  Port Registers
//  Note: Also see this address range in Bank 1.
//-----------------------------------------------
// Port 0
#pragma  ioport   PRT0DR:     0x000  // Port 0 Data Register
BYTE              PRT0DR;
#pragma  ioport   PRT0IE:     0x001  // Port 0 Interrupt Enable Register
BYTE              PRT0IE;
#pragma  ioport   PRT0GS:     0x002  // Port 0 Global Select Register
BYTE              PRT0GS;
#pragma  ioport   PRT0DM2:    0x003  // Port 0 Drive Mode 2
BYTE              PRT0DM2;
// Port 1
#pragma  ioport   PRT1DR:     0x004  // Port 1 Data Register
BYTE              PRT1DR;
#pragma  ioport   PRT1IE:     0x005  // Port 1 Interrupt Enable Register
BYTE              PRT1IE;
#pragma  ioport   PRT1GS:     0x006  // Port 1 Global Select Register
BYTE              PRT1GS;
#pragma  ioport   PRT1DM2:    0x007  // Port 1 Drive Mode 2
BYTE              PRT1DM2;
// Port 2
#pragma  ioport   PRT2DR:     0x008  // Port 2 Data Register
BYTE              PRT2DR;
#pragma  ioport   PRT2IE:     0x009  // Port 2 Interrupt Enable Register
BYTE              PRT2IE;
#pragma  ioport   PRT2GS:     0x00A  // Port 2 Global Select Register
BYTE              PRT2GS;
#pragma  ioport   PRT2DM2:    0x00B  // Port 2 Drive Mode 2
BYTE              PRT2DM2;
// Port 3
#pragma  ioport   PRT3DR:     0x00C  // Port 3 Data Register
BYTE              PRT3DR;
#pragma  ioport   PRT3IE:     0x00D  // Port 3 Interrupt Enable Register
BYTE              PRT3IE;
#pragma  ioport   PRT3GS:     0x00E  // Port 3 Global Select Register
BYTE              PRT3GS;
#pragma  ioport   PRT3DM2:    0x00F  // Port 3 Drive Mode 2
BYTE              PRT3DM2;
// Port 4
#pragma  ioport   PRT4DR:     0x010  // Port 4 Data Register
BYTE              PRT4DR;
#pragma  ioport   PRT4IE:     0x011  // Port 4 Interrupt Enable Register
BYTE              PRT4IE;
#pragma  ioport   PRT4GS:     0x012  // Port 4 Global Select Register
BYTE              PRT4GS;
#pragma  ioport   PRT4DM2:    0x013  // Port 4 Drive Mode 2
BYTE              PRT4DM2;
// Port 5
#pragma  ioport   PRT5DR:     0x014  // Port 5 Data Register
BYTE              PRT5DR;
#pragma  ioport   PRT5IE:     0x015  // Port 5 Interrupt Enable Register
BYTE              PRT5IE;
#pragma  ioport   PRT5GS:     0x016  // Port 5 Global Select Register
BYTE              PRT5GS;
#pragma  ioport   PRT5DM2:    0x017  // Port 5 Drive Mode 2
BYTE              PRT5DM2;
// Port 7
#pragma  ioport   PRT7DR:     0x01C  // Port 7 Data Register
BYTE              PRT7DR;
#pragma  ioport   PRT7IE:     0x01D  // Port 7 Interrupt Enable Register
BYTE              PRT7IE;
#pragma  ioport   PRT7GS:     0x01E  // Port 7 Global Select Register
BYTE              PRT7GS;
#pragma  ioport   PRT7DM2:    0x01F  // Port 7 Drive Mode 2
BYTE              PRT7DM2;

//-----------------------------------------------
//  Digital PSoC(tm) block Registers
//  Note: Also see this address range in Bank 1.
//-----------------------------------------------

// Digital PSoC block 00, Basic Type B
#pragma  ioport   DBB00DR0:   0x020  // data register 0
BYTE              DBB00DR0;
#pragma  ioport   DBB00DR1:   0x021  // data register 1
BYTE              DBB00DR1;
#pragma  ioport   DBB00DR2:   0x022  // data register 2
BYTE              DBB00DR2;
#pragma  ioport   DBB00CR0:   0x023  // control & status register 0
BYTE              DBB00CR0;

// Digital PSoC block 01, Basic Type B
#pragma  ioport   DBB01DR0:   0x024  // data register 0
BYTE              DBB01DR0;
#pragma  ioport   DBB01DR1:   0x025  // data register 1
BYTE              DBB01DR1;
#pragma  ioport   DBB01DR2:   0x026  // data register 2
BYTE              DBB01DR2;
#pragma  ioport   DBB01CR0:   0x027  // control & status register 0
BYTE              DBB01CR0;

// Digital PSoC block 02, Communication Type B
#pragma  ioport   DCB02DR0:   0x028  // data register 0
BYTE              DCB02DR0;
#pragma  ioport   DCB02DR1:   0x029  // data register 1
BYTE              DCB02DR1;
#pragma  ioport   DCB02DR2:   0x02A  // data register 2
BYTE              DCB02DR2;
#pragma  ioport   DCB02CR0:   0x02B  // control & status register 0
BYTE              DCB02CR0;

// Digital PSoC block 03, Communication Type B
#pragma  ioport   DCB03DR0:   0x02C  // data register 0
BYTE              DCB03DR0;
#pragma  ioport   DCB03DR1:   0x02D  // data register 1
BYTE              DCB03DR1;
#pragma  ioport   DCB03DR2:   0x02E  // data register 2
BYTE              DCB03DR2;
#pragma  ioport   DCB03CR0:   0x02F  // control & status register 0
BYTE              DCB03CR0;

//-----------------------------------------------
// PMA Data Registers
//-----------------------------------------------

#pragma  ioport   PMA0_DR:    0x040  // PMA 0 data register
BYTE              PMA0_DR;
#pragma  ioport   PMA1_DR:    0x041  // PMA 1 data register
BYTE              PMA1_DR;
#pragma  ioport   PMA2_DR:    0x042  // PMA 2 data register
BYTE              PMA2_DR;
#pragma  ioport   PMA3_DR:    0x043  // PMA 3 data register
BYTE              PMA3_DR;
#pragma  ioport   PMA4_DR:    0x044  // PMA 4 data register
BYTE              PMA4_DR;
#pragma  ioport   PMA5_DR:    0x045  // PMA 5 data register
BYTE              PMA5_DR;
#pragma  ioport   PMA6_DR:    0x046  // PMA 6 data register
BYTE              PMA6_DR;
#pragma  ioport   PMA7_DR:    0x047  // PMA 7 data register
BYTE              PMA7_DR;

//-----------------------------------------------
//  USB Control Registers
//-----------------------------------------------
#pragma  ioport   USB_SOF0:   0x048  // USB SOF LSB Byte
BYTE              USB_SOF0;
#pragma  ioport   USB_SOF1:   0x049  // USB SOF MSB Byte
BYTE              USB_SOF1;

#pragma  ioport   USB_CR0:    0x04A  // USB Control Register 0
BYTE              USB_CR0;
#define USB_CR0_ENABLE      (0x80)
#define USB_CR0_DEVICE_ADDR (0x7F)

#pragma  ioport   USBIO_CR0:  0x04B  // USBIO Control Register 0
BYTE              USBIO_CR0;
#define USBIO_CR0_TEN       (0x80)
#define USBIO_CR0_TSE0      (0x40)
#define USBIO_CR0_TD        (0x20)
#define USBIO_CR0_RD        (0x01)

#pragma  ioport   USBIO_CR1:  0x04C  // USBIO Control Register 1
BYTE              USBIO_CR1;
#define USBIO_CR1_IOMODE    (0x80)
#define USBIO_CR1_DRV_MODE  (0x40)
#define USBIO_CR1_DPI       (0x20)
#define USBIO_CR1_DMI       (0x10)
#define USBIO_CR1_PS2PUEN   (0x08)
#define USBIO_CR1_USBPUEN   (0x04)
#define USBIO_CR1_DPO       (0x02)
#define USBIO_CR1_DMO       (0x01)

//-----------------------------------------------
//  Endpoint Registers
//-----------------------------------------------
#pragma  ioport   EP1_CNT1:   0x04E  // EP1 Count Register 1
BYTE              EP1_CNT1;
#define EP1_CNT1_DATA_TOGGLE (0x80)
#define EP1_CNT1_DATA_VALID  (0x40)
#define EP1_CNT1_CNT_MSB     (0x01)

#pragma  ioport   EP1_CNT:   0x04F   // EP1 Count Register 0
BYTE              EP1_CNT;

#pragma  ioport   EP2_CNT1:   0x050  // EP2 Count Register 1
BYTE              EP2_CNT1;
#define EP2_CNT1_DATA_TOGGLE (0x80)
#define EP2_CNT1_DATA_VALID  (0x40)
#define EP2_CNT1_CNT_MSB     (0x01)

#pragma  ioport   EP2_CNT:   0x051   // EP2 Count Register 0
BYTE              EP2_CNT;

#pragma  ioport   EP3_CNT1:   0x052  // EP3 Count Register 1
BYTE              EP3_CNT1;
#define EP3_CNT1_DATA_TOGGLE (0x80)
#define EP3_CNT1_DATA_VALID  (0x40)
#define EP3_CNT1_CNT_MSB     (0x01)

#pragma  ioport   EP3_CNT:   0x053   // EP3 Count Register 0
BYTE              EP3_CNT;

#pragma  ioport   EP4_CNT1:   0x054  // EP4 Count Register 1
BYTE              EP4_CNT1;
#define EP4_CNT1_DATA_TOGGLE (0x80)
#define EP4_CNT1_DATA_VALID  (0x40)
#define EP4_CNT1_CNT_MSB     (0x01)

#pragma  ioport   EP4_CNT:   0x055   // EP4 Control Register
BYTE              EP4_CNT;

#pragma  ioport   EP0_CR:     0x056  // EP4 Control Register
BYTE              EP0_CR;
#define EP0_CR_SETUP_RCVD    (0x80)
#define EP0_CR_IN_RCVD       (0x40)
#define EP0_CR_OUT_RCVD      (0x20)
#define EP0_CR_ACKD          (0x10)
#define EP0_CR_MODE          (0x0F)

#pragma  ioport   EP0_CNT:    0x057  // EP0 Count Register
BYTE              EP0_CNT;
#define EP0_CNT_DATA_TOGGLE (0x80)
#define EP0_CNT_DATA_VALID  (0x40)
#define EP0_CNT_BYTE_CNT    (0x0F)

#pragma  ioport   EP0_DR0:    0x058  // EP0 Data Register 0
BYTE              EP0_DR0;
#pragma  ioport   EP0_DR1:    0x059  // EP0 Data Register 0
BYTE              EP0_DR1;
#pragma  ioport   EP0_DR2:    0x05A  // EP0 Data Register 0
BYTE              EP0_DR2;
#pragma  ioport   EP0_DR3:    0x05B  // EP0 Data Register 0
BYTE              EP0_DR3;
#pragma  ioport   EP0_DR4:    0x05C  // EP0 Data Register 0
BYTE              EP0_DR4;
#pragma  ioport   EP0_DR5:    0x05D  // EP0 Data Register 0
BYTE              EP0_DR5;
#pragma  ioport   EP0_DR6:    0x05E  // EP0 Data Register 0
BYTE              EP0_DR6;
#pragma  ioport   EP0_DR7:    0x05F  // EP0 Data Register 0
BYTE              EP0_DR7;

//-----------------------------------------------
//  Analog Control Registers
//-----------------------------------------------

#pragma  ioport   AMX_IN:     0x060  // Analog Input Multiplexor Control
BYTE              AMX_IN;
#define AMX_IN_ACI1       (0x0C)
#define AMX_IN_ACI0       (0x03)

#pragma  ioport   AMUXCFG:    0x061  // Analog MUX Configuration
BYTE              AMUXCFG;
#define AMUXCFG_BCOL1MUX  (0x80)
#define AMUXCFG_ACOLOMUX  (0x40)
#define AMUXCFG_INTCAP    (0x30)
#define AMUXCFG_MUXCLK    (0x0E)
#define AMUXCFG_EN        (0x01)

#pragma  ioport   ARF_CR:     0x063  // Analog Reference Control Register
BYTE              ARF_CR;
#define ARF_CR_HBE      (0x40)
#define ARF_CR_REF      (0x38)
#define ARF_CR_REFPWR   (0x07)
#define ARF_CR_SCPWR    (0x03)

#pragma  ioport   CMP_CR0:     0x064  // Analog Comparator Bus Register 0
BYTE              CMP_CR0;
#define CMP_CR0_COMP1    (0x20)
#define CMP_CR0_COMP0    (0x10)
#define CMP_CR0_AINT1    (0x02)
#define CMP_CR0_AINT0    (0x01)

#pragma  ioport   ASY_CR:     0x065  // Analog Synchronizaton Control Register
BYTE              ASY_CR;
#define ASY_CR_SARCOUNT (0x70)
#define ASY_CR_SARSIGN  (0x08)
#define ASY_CR_SARCOL   (0x06)
#define ASY_CR_SYNCEN   (0x01)

#pragma  ioport  CMP_CR1:     0x066   // Analog Comparator Bus Register 1
BYTE             CMP_CR1;
#define CMP_CR1_CLDIS1  (0x20)
#define CMP_CR1_CLDIS0  (0x10)
#define CMP_CR1_CLK1X1  (0x02)
#define CMP_CR1_CLK1X0  (0x01)


//-----------------------------------------------
//  Analog PSoC block Registers
//
//  Note: the following registers are mapped into
//  both register bank 0 AND register bank 1.
//-----------------------------------------------

// Continuous Time PSoC Block Type B Row 0 Col 0
#pragma  ioport   ACB00CR3:   0x70  // Control register 3
BYTE              ACB00CR3;
#pragma  ioport   ACB00CR0:   0x71  // Control register 0
BYTE              ACB00CR0;
#pragma  ioport   ACB00CR1:   0x72  // Control register 1
BYTE              ACB00CR1;
#pragma  ioport   ACB00CR2:   0x73  // Control register 2
BYTE              ACB00CR2;

// Continuous Time PSoC Block Type B Row 0 Col 1
#pragma  ioport   ACB01CR3:   0x74  // Control register 3
BYTE              ACB01CR3;
#pragma  ioport   ACB01CR0:   0x75  // Control register 0
BYTE              ACB01CR0;
#pragma  ioport   ACB01CR1:   0x76  // Control register 1
BYTE              ACB01CR1;
#pragma  ioport   ACB01CR2:   0x77  // Control register 2
BYTE              ACB01CR2;

// Switched Cap PSoC Block Type C Row 1 Col 0
#pragma  ioport   ASC10CR0:   0x80  // Control register 0
BYTE              ASC10CR0;
#pragma  ioport   ASC10CR1:   0x81  // Control register 1
BYTE              ASC10CR1;
#pragma  ioport   ASC10CR2:   0x82  // Control register 2
BYTE              ASC10CR2;
#pragma  ioport   ASC10CR3:   0x83  // Control register 3
BYTE              ASC10CR3;

// Switched Cap PSoC Block Type D Row 1 Col 1
#pragma  ioport   ASD11CR0:   0x84  // Control register 0
BYTE              ASD11CR0;
#pragma  ioport   ASD11CR1:   0x85  // Control register 1
BYTE              ASD11CR1;
#pragma  ioport   ASD11CR2:   0x86  // Control register 2
BYTE              ASD11CR2;
#pragma  ioport   ASD11CR3:   0x87  // Control register 3
BYTE              ASD11CR3;

// Switched Cap PSoC Block Type D Row 2 Col 0
#pragma  ioport   ASD20CR0:   0x90  // Control register 0
BYTE              ASD20CR0;
#pragma  ioport   ASD20CR1:   0x91  // Control register 1
BYTE              ASD20CR1;
#pragma  ioport   ASD20CR2:   0x92  // Control register 2
BYTE              ASD20CR2;
#pragma  ioport   ASD20CR3:   0x93  // Control register 3
BYTE              ASD20CR3;

// Switched Cap PSoC Block Type C Row 2 Col 1
#pragma  ioport   ASC21CR0:   0x94  // Control register 0
BYTE              ASC21CR0;
#pragma  ioport   ASC21CR1:   0x95  // Control register 1
BYTE              ASC21CR1;
#pragma  ioport   ASC21CR2:   0x96  // Control register 2
BYTE              ASC21CR2;
#pragma  ioport   ASC21CR3:   0x97  // Control register 3
BYTE              ASC21CR3;

//-----------------------------------------------
//  Global General Purpose Data Registers
//-----------------------------------------------
#pragma  ioport   TMP_DR0:     0x6C  // Temp Data Register 0
BYTE              TMP_DR0;
#pragma  ioport   TMP_DR1:     0x6D  // Temp Data Register 1
BYTE              TMP_DR1;
#pragma  ioport   TMP_DR2:     0x6E  // Temp Data Register 2
BYTE              TMP_DR2;
#pragma  ioport   TMP_DR3:     0x6F  // Temp Data Register 3
BYTE              TMP_DR3;

//-----------------------------------------------
//  Row Digital Interconnects
//
//  Note: the following registers are mapped into
//  both register bank 0 AND register bank 1.
//-----------------------------------------------

#pragma  ioport   RDI0RI:     0xB0  // Row Digital Interconnect Row 0 Input
BYTE              RDI0RI;
#pragma  ioport   RDI0SYN:    0xB1  // Row Digital Interconnect Row 0 Sync Reg
BYTE              RDI0SYN;
#pragma  ioport   RDI0IS:     0xB2  // Row 0 Input Select Register
BYTE              RDI0IS;
#pragma  ioport   RDI0LT0:    0xB3  // Row 0 Look Up Table Register 0
BYTE              RDI0LT0;
#pragma  ioport   RDI0LT1:    0xB4  // Row 0 Look Up Table Register 1
BYTE              RDI0LT1;
#pragma  ioport   RDI0RO0:    0xB5  // Row 0 Output Register 0
BYTE              RDI0RO0;
#pragma  ioport   RDI0RO1:    0xB6  // Row 0 Output Register 1
BYTE              RDI0RO1;

//-----------------------------------------------
//  Ram Page Pointers
//-----------------------------------------------
#pragma  ioport   CUR_PP:     0x0D0  // Current   Page Pointer
BYTE              CUR_PP;
#pragma  ioport   STK_PP:     0x0D1  // Stack     Page Pointer
BYTE              STK_PP;
#pragma  ioport   IDX_PP:     0x0D3  // Index     Page Pointer
BYTE              IDX_PP;
#pragma  ioport   MVR_PP:     0x0D4  // MVI Read  Page Pointer
BYTE              MVR_PP;
#pragma  ioport   MVW_PP:     0x0D5  // MVI Write Page Pointer
BYTE              MVW_PP;

//-----------------------------------------------
//  I2C Configuration Registers
//-----------------------------------------------
#pragma  ioport   I2C_CFG:    0x0D6  // I2C Configuration Register
BYTE              I2C_CFG;
#define I2C_CFG_PINSEL         (0x40)
#define I2C_CFG_BUSERR_IE      (0x20)
#define I2C_CFG_STOP_IE        (0x10)
#define I2C_CFG_CLK_RATE_100K  (0x00)
#define I2C_CFG_CLK_RATE_400K  (0x04)
#define I2C_CFG_CLK_RATE_50K   (0x08)
#define I2C_CFG_CLK_RATE_1M6   (0x0C)
#define I2C_CFG_CLK_RATE       (0x0C)
#define I2C_CFG_PSELECT_MASTER (0x02)
#define I2C_CFG_PSELECT_SLAVE  (0x01)

#pragma  ioport   I2C_SCR:    0x0D7  // I2C Status and Control Register
BYTE              I2C_SCR;
#define I2C_SCR_BUSERR       (0x80)
#define I2C_SCR_LOSTARB      (0x40)
#define I2C_SCR_STOP         (0x20)
#define I2C_SCR_ACK          (0x10)
#define I2C_SCR_ADDR         (0x08)
#define I2C_SCR_XMIT         (0x04)
#define I2C_SCR_LRB          (0x02)
#define I2C_SCR_BYTECOMPLETE (0x01)

#pragma  ioport   I2C_DR:     0x0D8  // I2C Data Register
BYTE              I2C_DR;

#pragma  ioport   I2C_MSCR:   0x0D9  // I2C Master Status and Control Register
BYTE              I2C_MSCR;
#define I2C_MSCR_BUSY    (0x08)
#define I2C_MSCR_MODE    (0x04)
#define I2C_MSCR_RESTART (0x02)
#define I2C_MSCR_START   (0x01)

//-----------------------------------------------
//  System and Global Resource Registers
//-----------------------------------------------
#pragma  ioport   INT_CLR0:   0x0DA  // Interrupt Clear Register 0
BYTE              INT_CLR0;
#pragma  ioport   INT_CLR1:   0x0DB  // Interrupt Clear Register 1
BYTE              INT_CLR1;
#pragma  ioport   INT_CLR2:   0x0DC  // Interrupt Clear Register 2
BYTE              INT_CLR2;
#pragma  ioport   INT_CLR3:   0x0DD  // Interrupt Clear Register 3
BYTE              INT_CLR3;

#pragma  ioport   INT_MSK3:   0x0DE  // I2C and Software Mask Register
BYTE              INT_MSK3;
#define INT_MSK3_ENSWINT          (0x80)
#define INT_MSK3_I2C              (0x01)

#pragma  ioport   INT_MSK2:   0x0DF  // General Interrupt Mask Register
BYTE              INT_MSK2;
#define  INT_MSK2_WAKEUP          (0x80)
#define  INT_MSK2_EP4             (0x40)
#define  INT_MSK2_EP3             (0x20)
#define  INT_MSK2_EP2             (0x10)
#define  INT_MSK2_EP1             (0x08)
#define  INT_MSK2_EP0             (0x04)
#define  INT_MSK2_SOF             (0x02)
#define  INT_MSK2_BUS_RESET       (0x01)

#pragma  ioport   INT_MSK0:   0x0E0  // General Interrupt Mask Register
BYTE              INT_MSK0;
#define  INT_MSK0_VC3             (0x80)
#define  INT_MSK0_SLEEP           (0x40)
#define  INT_MSK0_GPIO            (0x20)
#define  INT_MSK0_ACOLUMN_1       (0x04)
#define  INT_MSK0_ACOLUMN_0       (0x02)
#define  INT_MSK0_VOLTAGE_MONITOR (0x01)


#pragma  ioport   INT_MSK1:   0x0E1  // Digital PSoC block Mask Register
BYTE              INT_MSK1;
#define  INT_MSK1_DCB03           (0x08)
#define  INT_MSK1_DCB02           (0x04)
#define  INT_MSK1_DBB01           (0x02)
#define  INT_MSK1_DBB00           (0x01)

#pragma  ioport   INT_VC:     0x0E2  // Interrupt vector register
BYTE              INT_VC;

#pragma  ioport   RES_WDT:    0x0E3  // Watch Dog Timer
BYTE              RES_WDT;

// DECIMATOR Registers
#pragma  ioport   DEC_DH:     0x0E4  // Data Register (high byte)
CHAR              DEC_DH;
#pragma  ioport   DEC_DL:     0x0E5  // Data Register ( low byte)
CHAR              DEC_DL;
#pragma  ioport   DEC_CR0:    0x0E6  // Data Control Register
BYTE              DEC_CR0;
#pragma  ioport   DEC_CR1:    0x0E7  // Data Control Register
BYTE              DEC_CR1;

// Multiplier and MAC (Multiply/Accumulate)
#pragma  ioport   MUL0_X:         0x0E8  // Multiplier X Register (write)
CHAR              MUL0_X;
#pragma  ioport   MUL0_Y:         0x0E9  // Multiplier Y Register (write)
CHAR              MUL0_Y;
#pragma  ioport   MUL0_DH:        0x0EA  // Multiplier Result Data (high byte read)
CHAR              MUL0_DH;
#pragma  ioport   MUL0_DL:        0x0EB  // Multiplier Result Data ( low byte read)
CHAR              MUL0_DL;
#pragma  ioport   ACC0_DR1:       0x0EC  // ACC0_DR1 (write) [see ACC_DR1]
CHAR              ACC0_DR1;
#pragma  ioport   ACC0_DR0:       0x0ED  // ACC0_DR0 (write) [see ACC_DR1]
CHAR              ACC0_DR0;
#pragma  ioport   ACC0_DR3:       0x0EE  // ACC0_DR3 (write) [see ACC_DR1]
CHAR              ACC0_DR3;
#pragma  ioport   ACC0_DR2:       0x0EF  // ACC0_DR2 (write) [see ACC_DR1]
CHAR              ACC0_DR2;
#pragma  ioport   MAC_Y:         0x0ED  // MAC Y register (write) [see ACC_DR0]
CHAR              MAC_Y;
#pragma  ioport   MAC_CL0:       0x0EE  // MAC Clear Accum (write)[see ACC_DR3]
BYTE              MAC_CL0;
#pragma  ioport   MAC_CL1:       0x0EF  // MAC Clear Accum (write)[see ACC_DR2]
BYTE              MAC_CL1;
#pragma  ioport   ACC_DR1:       0x0EC  // MAC Accumulator (Read, byte 1)
CHAR              ACC_DR1;
#pragma  ioport   ACC_DR0:       0x0ED  // MAC Accumulator (Read, byte 0)
CHAR              ACC_DR0;
#pragma  ioport   ACC_LOW_WORD:  0x0EC  // MAC Accumulator (Read low word)
INT               ACC_LOW_WORD;
#pragma  ioport   ACC_DR3:       0x0EE  // MAC Accumulator (Read, byte 3)
CHAR              ACC_DR3;
#pragma  ioport   ACC_DR2:       0x0EF  // MAC Accumulator (Read, byte 2)
CHAR              ACC_DR2;
#pragma  ioport   ACC_HI_WORD:   0x0EE  // MAC Accumulator (Read high word)
INT               ACC_HI_WORD;

// Multiplier and MAC (Multiply/Accumulate) Unit
//   Compatibility Set: Maps onto MAC0
#pragma  ioport   MUL_X:         0x0E8  // Multiplier X Register (write)
CHAR              MUL_X;
#pragma  ioport   MUL_Y:         0x0E9  // Multiplier Y Register (write)
CHAR              MUL_Y;
#pragma  ioport   MUL_DH:        0x0EA  // Multiplier Result Data (high byte read)
CHAR              MUL_DH;
#pragma  ioport   MUL_DL:        0x0EB  // Multiplier Result Data ( low byte read)
CHAR              MUL_DL;
#pragma  ioport   MUL_RESULT:    0x0EA  // Multiplier Result Data - WORD
INT               MUL_RESULT;
#pragma  ioport   MAC_X:         0x0EC  // MAC X register (write) [see ACC_DR1]
CHAR              MAC_X;
#pragma  ioport   MAC_Y:         0x0ED  // MAC Y register (write) [see ACC_DR0]
//CHAR              MAC_Y;
#pragma  ioport   MAC_CL0:       0x0EE  // MAC Clear Accum (write)[see ACC_DR3]
//BYTE              MAC_CL0;
#pragma  ioport   MAC_CL1:       0x0EF  // MAC Clear Accum (write)[see ACC_DR2]
//BYTE              MAC_CL1;
#pragma  ioport   ACC_DR1:       0x0EC  // MAC Accumulator (Read, byte 1)
//CHAR              ACC_DR1;
#pragma  ioport   ACC_DR0:       0x0ED  // MAC Accumulator (Read, byte 0)
//CHAR              ACC_DR0;
#pragma  ioport   ACC_LOW_WORD:  0x0EC  // MAC Accumulator (Read low word)
//INT               ACC_LOW_WORD;
#pragma  ioport   ACC_DR3:       0x0EE  // MAC Accumulator (Read, byte 3)
//CHAR              ACC_DR3;
#pragma  ioport   ACC_DR2:       0x0EF  // MAC Accumulator (Read, byte 2)
//CHAR              ACC_DR2;
#pragma  ioport   ACC_HI_WORD:   0x0EE  // MAC Accumulator (Read high word)
//INT               ACC_HI_WORD;

// Multiply/Accumulate Unit 1
#pragma  ioport   MUL1_X:        0x0A8  // Multiplier X Register (write)
CHAR              MUL1_X;
#pragma  ioport   MUL1_Y:        0x0A9  // Multiplier Y Register (write)
CHAR              MUL1_Y;
#pragma  ioport   MUL1_DH:       0x0AA  // Multiplier Result Data (high byte read)
CHAR              MUL1_DH;
#pragma  ioport   MUL1_DL:       0x0AB  // Multiplier Result Data ( low byte read)
CHAR              MUL1_DL;
#pragma  ioport   MUL1_RESULT:   0x0AA  // Multiplier Result Data - WORD
INT               MUL1_RESULT;
#pragma  ioport   MAC1_X:        0x0AC  // MAC X register (write) [see ACC_DR1]
CHAR              MAC1_X;
#pragma  ioport   MAC1_Y:        0x0AD  // MAC Y register (write) [see ACC_DR0]
CHAR              MAC1_Y;
#pragma  ioport   MAC1_CL0:      0x0AE  // MAC Clear Accum (write)[see ACC_DR3]
BYTE              MAC1_CL0;
#pragma  ioport   MAC1_CL1:      0x0AF  // MAC Clear Accum (write)[see ACC_DR2]
BYTE              MAC1_CL1;
#pragma  ioport   ACC1_DR1:      0x0AC  // MAC Accumulator (Read, byte 1)
CHAR              ACC1_DR1;
#pragma  ioport   ACC1_DR0:      0x0AD  // MAC Accumulator (Read, byte 0)
CHAR              ACC1_DR0;
#pragma  ioport   ACC1_LOW_WORD: 0x0AC  // MAC Accumulator (Read low word)
INT               ACC1_LOW_WORD;
#pragma  ioport   ACC1_DR3:      0x0AE  // MAC Accumulator (Read, byte 3)
CHAR              ACC1_DR3;
#pragma  ioport   ACC1_DR2:      0x0AF  // MAC Accumulator (Read, byte 2)
CHAR              ACC1_DR2;
#pragma  ioport   ACC1_HI_WORD:  0x0AE  // MAC Accumulator (Read high word)
INT               ACC1_HI_WORD;

//-----------------------------------------------
//  System Status and Control Register
//
//  Note: the following register is mapped into
//  both register bank 0 AND register bank 1.
//-----------------------------------------------
#pragma  ioport   CPU_F:      0xF7   // CPU Flag Register Access
BYTE              CPU_F;             // Use FLAG_ masks defined at top of file

#pragma  ioport   DAC_D:      0xFD   // DAC Data Register
BYTE              DAC_D;

#pragma  ioport   CPU_SCR1:   0xFE   // System Status and Control Register 1
BYTE              CPU_SCR1;
#define  CPU_SCR1_IRESS        (0x80)
#define  CPU_SCR1_SLIMO        (0x10)
#define  CPU_SCR1_ECO_ALWD_WR  (0x08)
#define  CPU_SCR1_ECO_ALLOWED  (0x04)
#define  CPU_SCR1_IRAMDIS      (0x01)

#pragma  ioport   CPU_SCR0:   0xFF  // System Status and Control Register 0
BYTE              CPU_SCR0;
#define  CPU_SCR0_GIE_MASK     (0x80)
#define  CPU_SCR0_WDRS_MASK    (0x20)
#define  CPU_SCR0_PORS_MASK    (0x10)
#define  CPU_SCR0_SLEEP_MASK   (0x08)
#define  CPU_SCR0_STOP_MASK    (0x01)


//=============================================================================
//=============================================================================
//      Register Space, Bank 1
//=============================================================================
//=============================================================================


//-----------------------------------------------
//  Port Registers
//  Note: Also see this address range in Bank 0.
//-----------------------------------------------
// Port 0
#pragma  ioport   PRT0DM0:    0x100  // Port 0 Drive Mode 0
BYTE              PRT0DM0;
#pragma  ioport   PRT0DM1:    0x101  // Port 0 Drive Mode 1
BYTE              PRT0DM1;
#pragma  ioport   PRT0IC0:    0x102  // Port 0 Interrupt Control 0
BYTE              PRT0IC0;
#pragma  ioport   PRT0IC1:    0x103  // Port 0 Interrupt Control 1
BYTE              PRT0IC1;
// Port 1
#pragma  ioport   PRT1DM0:    0x104  // Port 1 Drive Mode 0
BYTE              PRT1DM0;
#pragma  ioport   PRT1DM1:    0x105  // Port 1 Drive Mode 1
BYTE              PRT1DM1;
#pragma  ioport   PRT1IC0:    0x106  // Port 1 Interrupt Control 0
BYTE              PRT1IC0;
#pragma  ioport   PRT1IC1:    0x107  // Port 1 Interrupt Control 1
BYTE              PRT1IC1;
// Port 2
#pragma  ioport   PRT2DM0:    0x108  // Port 2 Drive Mode 0
BYTE              PRT2DM0;
#pragma  ioport   PRT2DM1:    0x109  // Port 2 Drive Mode 1
BYTE              PRT2DM1;
#pragma  ioport   PRT2IC0:    0x10A  // Port 2 Interrupt Control 0
BYTE              PRT2IC0;
#pragma  ioport   PRT2IC1:    0x10B  // Port 2 Interrupt Control 1
BYTE              PRT2IC1;
// Port 3
#pragma  ioport   PRT3DM0:    0x10C  // Port 3 Drive Mode 0
BYTE              PRT3DM0;
#pragma  ioport   PRT3DM1:    0x10D  // Port 3 Drive Mode 1
BYTE              PRT3DM1;
#pragma  ioport   PRT3IC0:    0x10E  // Port 3 Interrupt Control 0
BYTE              PRT3IC0;
#pragma  ioport   PRT3IC1:    0x10F  // Port 3 Interrupt Control 1
BYTE              PRT3IC1;
// Port 4
#pragma  ioport   PRT4DM0:    0x110  // Port 4 Drive Mode 0
BYTE              PRT4DM0;
#pragma  ioport   PRT4DM1:    0x111  // Port 4 Drive Mode 1
BYTE              PRT4DM1;
#pragma  ioport   PRT4IC0:    0x112  // Port 4 Interrupt Control 0
BYTE              PRT4IC0;
#pragma  ioport   PRT4IC1:    0x113  // Port 4 Interrupt Control 1
BYTE              PRT4IC1;
// Port 5
#pragma  ioport   PRT5DM0:    0x114  // Port 5 Drive Mode 0
BYTE              PRT5DM0;
#pragma  ioport   PRT5DM1:    0x115  // Port 5 Drive Mode 1
BYTE              PRT5DM1;
#pragma  ioport   PRT5IC0:    0x116  // Port 5 Interrupt Control 0
BYTE              PRT5IC0;
#pragma  ioport   PRT5IC1:    0x117  // Port 5 Interrupt Control 1
BYTE              PRT5IC1;
// Port 7
#pragma  ioport   PRT7DM0:    0x11C  // Port 7 Drive Mode 0
BYTE              PRT7DM0;
#pragma  ioport   PRT7DM1:    0x11D  // Port 7 Drive Mode 1
BYTE              PRT7DM1;
#pragma  ioport   PRT7IC0:    0x11E  // Port 7 Interrupt Control 0
BYTE              PRT7IC0;
#pragma  ioport   PRT7IC1:    0x11F  // Port 7 Interrupt Control 1
BYTE              PRT7IC1;

//-----------------------------------------------
//  Digital PSoC(tm) block Registers
//  Note: Also see this address range in Bank 1.
//-----------------------------------------------

// Digital PSoC block 00, Basic Type B
#pragma  ioport   DBB00FN:    0x120  // Function Register
BYTE              DBB00FN;
#pragma  ioport   DBB00IN:    0x121  //    Input Register
BYTE              DBB00IN;
#pragma  ioport   DBB00OU:    0x122  //   Output Register
BYTE              DBB00OU;

// Digital PSoC block 01, Basic Type B
#pragma  ioport   DBB01FN:    0x124  // Function Register
BYTE              DBB01FN;
#pragma  ioport   DBB01IN:    0x125  //    Input Register
BYTE              DBB01IN;
#pragma  ioport   DBB01OU:    0x126  //   Output Register
BYTE              DBB01OU;

// Digital PSoC block 02, Communications Type B
#pragma  ioport   DCB02FN:    0x128  // Function Register
BYTE              DCB02FN;
#pragma  ioport   DCB02IN:    0x129  //    Input Register
BYTE              DCB02IN;
#pragma  ioport   DCB02OU:    0x12A  //   Output Register
BYTE              DCB02OU;

// Digital PSoC block 03, Communications Type B
#pragma  ioport   DCB03FN:    0x12C  // Function Register
BYTE              DCB03FN;
#pragma  ioport   DCB03IN:    0x12D  //    Input Register
BYTE              DCB03IN;
#pragma  ioport   DCB03OU:    0x12E  //   Output Register
BYTE              DCB03OU;

//-----------------------------------------------
//  PMA Write and Read Pointer Registers
//-----------------------------------------------
#pragma  ioport   PMA0_WA:    0x140  // PMA 0 Write Pointer
BYTE              PMA0_WA;
#pragma  ioport   PMA1_WA:    0x141  // PMA 1 Write Pointer
BYTE              PMA1_WA;
#pragma  ioport   PMA2_WA:    0x142  // PMA 2 Write Pointer
BYTE              PMA2_WA;
#pragma  ioport   PMA3_WA:    0x143  // PMA 3 Write Pointer
BYTE              PMA3_WA;
#pragma  ioport   PMA4_WA:    0x144  // PMA 4 Write Pointer
BYTE              PMA4_WA;
#pragma  ioport   PMA5_WA:    0x145  // PMA 5 Write Pointer
BYTE              PMA5_WA;
#pragma  ioport   PMA6_WA:    0x146  // PMA 6 Write Pointer
BYTE              PMA6_WA;
#pragma  ioport   PMA7_WA:    0x147  // PMA 7 Write Pointer
BYTE              PMA7_WA;

#pragma  ioport   PMA0_RA:    0x150  // PMA 0 Read Pointer
BYTE              PMA0_RA;
#pragma  ioport   PMA1_RA:    0x151  // PMA 1 Read Pointer
BYTE              PMA1_RA;
#pragma  ioport   PMA2_RA:    0x152  // PMA 2 Read Pointer
BYTE              PMA2_RA;
#pragma  ioport   PMA3_RA:    0x153  // PMA 3 Read Pointer
BYTE              PMA3_RA;
#pragma  ioport   PMA4_RA:    0x154  // PMA 4 Read Pointer
BYTE              PMA4_RA;
#pragma  ioport   PMA5_RA:    0x155  // PMA 5 Read Pointer
BYTE              PMA5_RA;
#pragma  ioport   PMA6_RA:    0x156  // PMA 6 Read Pointer
BYTE              PMA6_RA;
#pragma  ioport   PMA7_RA:    0x157  // PMA 7 Read Pointer
BYTE              PMA7_RA;

//-----------------------------------------------
//  System and Global Resource Registers
//  Note: Also see this address range in Bank 0.
//-----------------------------------------------

#pragma  ioport   CLK_CR0:    0x160  // Analog Column Clock Select Register
BYTE              CLK_CR0;
#define CLK_CR0_ACOLUMN1              (0x0C)
#define CLK_CR0_ACOLUMN0              (0x03)

#pragma  ioport   CLK_CR1:    0x161  // Analog Clock Source Select Register
BYTE              CLK_CR1;
#define CLK_CR1_SHDIS                 (0x40)
#define CLK_CR1_ACLK1                 (0x38)
#define CLK_CR1_ACLK2                 (0x07)

#pragma  ioport   ABF_CR0:    0x162  // Analog Output Buffer Control Register
BYTE              ABF_CR0;
#define ABF_CR0_ACOL1MUX              (0x80)
#define ABF_CR0_ABUF1EN               (0x20)
#define ABF_CR0_ABUF0EN               (0x08)
#define ABF_CR0_BYPASS                (0x02)
#define ABF_CR0_PWR                   (0x01)

#pragma  ioport   AMD_CR0:    0x163  // Analog Modulator Control Register
BYTE              AMD_CR0;
#define AMD_CR0_AMOD0                 (0x07)

#pragma  ioport   CMP_GO_EN:  0x164  // Comparator Bus To Global Out Enable
BYTE              CMP_GO_EN;
#define CMP_GO_EN_GOO5                (0x80)
#define CMP_GO_EN_GOO1                (0x40)
#define CMP_GO_EN_SEL1                (0x30)
#define CMP_GO_EN_GOO4                (0x08)
#define CMP_GO_EN_GOO0                (0x04)
#define CMP_GO_EN_SEL0                (0x03)

#pragma  ioport   CMP_GO_EN1: 0x165  // Comparator Bus To Global Out Enable 1
BYTE              CMP_GO_EN1;
#define CMP_GO_EN1_GOO7               (0x80)
#define CMP_GO_EN1_GOO3               (0x40)
#define CMP_GO_EN1_SEL3               (0x30)
#define CMP_GO_EN1_GOO6               (0x08)
#define CMP_GO_EN1_GOO2               (0x04)
#define CMP_GO_EN1_SEL2               (0x03)

#pragma  ioport   AMD_CR1:    0x166  // Analog Modulator Control Register 1
BYTE              AMD_CR1;
#define AMD_CR1_AMOD1                 (0x07)

#pragma  ioport   ALT_CR0:    0x167  // Analog Look Up Table (LUT) Register 0
BYTE              ALT_CR0;
#define ALT_CR0_LUT1                  (0xF0)
#define ALT_CR0_LUT0                  (0x0F)


//-----------------------------------------------
//  USB Registers
//-----------------------------------------------
#pragma  ioport   USB_CR1:    0x1C1  // USB Control Register 1
BYTE              USB_CR1;
#define USB_CR1_BUS_ACTIVITY           (0x04)
#define USB_CR1_ENABLE_LOCK            (0x02)
#define USB_CR1_REG_ENABLE             (0x01)

#pragma  ioport   EP1_CR0:    0x1C4  // Endpoint 1 Control Register 0
BYTE              EP1_CR0;
#define EP1_CR0_STALL                  (0x80)
#define EP1_CR0_NAK_INT_EN             (0x20)
#define EP1_CR0_ACKD                   (0x10)
#define EP1_CR0_MODE                   (0x0F)

#pragma  ioport   EP2_CR0:    0x1C5  // Endpoint 2 Control Register 0
BYTE              EP2_CR0;
#define EP2_CR0_STALL                  (0x80)
#define EP2_CR0_NAK_INT_EN             (0x20)
#define EP2_CR0_ACKD                   (0x10)
#define EP2_CR0_MODE                   (0x0F)

#pragma  ioport   EP3_CR0:    0x1C6  // Endpoint 3 Control Register 0
BYTE              EP3_CR0;
#define EP3_CR0_STALL                  (0x80)
#define EP3_CR0_NAK_INT_EN             (0x20)
#define EP3_CR0_ACKD                   (0x10)
#define EP3_CR0_MODE                   (0x0F)

#pragma  ioport   EP4_CR0:    0x1C7  // Endpoint 4 Control Register 0
BYTE              EP4_CR0;
#define EP4_CR0_STALL                  (0x80)
#define EP4_CR0_NAK_INT_EN             (0x20)
#define EP4_CR0_ACKD                   (0x10)
#define EP4_CR0_MODE                   (0x0F)

//-----------------------------------------------
//  Global Digital Interconnects
//-----------------------------------------------


#pragma  ioport   GDI_O_IN:   0x1D0  // Global Dig Interconnect Odd Inputs
BYTE              GDI_O_IN;
#pragma  ioport   GDI_E_IN:   0x1D1  // Global Dig Interconnect Even Inputs
BYTE              GDI_E_IN;
#pragma  ioport   GDI_O_OU:   0x1D2  // Global Dig Interconnect Odd Outputs
BYTE              GDI_O_OU;
#pragma  ioport   GDI_E_OU:   0x1D3  // Global Dig Interconnect Even Outputs
BYTE              GDI_E_OU;

//------------------------------------------------
//  Analog Mux Bus Select Registers
//------------------------------------------------

#pragma  ioport   MUX_CR0:    0x1D8  // Analog Mux Port 0 Bit Enables
BYTE              MUX_CR0;
#pragma  ioport   MUX_CR1:    0x1D9  // Analog Mux Port 1 Bit Enables
BYTE              MUX_CR1;
#pragma  ioport   MUX_CR2:    0x1DA  // Analog Mux Port 2 Bit Enables
BYTE              MUX_CR2;
#pragma  ioport   MUX_CR3:    0x1DB  // Analog Mux Port 3 Bit Enables
BYTE              MUX_CR3;
#pragma  ioport   MUX_CR4:    0x1EC  // Analog Mux Port 4 Bit Enables
BYTE              MUX_CR4;
#pragma  ioport   MUX_CR5:    0x1ED  // Analog Mux Port 5 Bit Enables
BYTE              MUX_CR5;

//------------------------------------------------
//  Clock and System Control Registers
//------------------------------------------------

#pragma  ioport   OSC_GO_EN:  0x1DD  // Oscillator to Global Outputs Enable Register (RW)
BYTE              OSC_GO_EN;
#define OSC_GO_EN_SLPINT              (0x80)
#define OSC_GO_EN_VC3                 (0x40)
#define OSC_GO_EN_VC2                 (0x20)
#define OSC_GO_EN_VC1                 (0x10)
#define OSC_GO_EN_SYSCLKX2            (0x08)
#define OSC_GO_EN_SYSCLK              (0x04)
#define OSC_GO_EN_CLK24M              (0x02)
#define OSC_GO_EN_CLK32K              (0x01)

#pragma  ioport   OSC_CR4:    0x1DE  // Oscillator Control Register 4
BYTE              OSC_CR4;
#define OSC_CR4_VC3SEL                (0x03)

#pragma  ioport   OSC_CR3:    0x1DF  // Oscillator Control Register 3
BYTE              OSC_CR3;

#pragma  ioport   OSC_CR0:    0x1E0  // System Oscillator Control Register 0
BYTE              OSC_CR0;
#define OSC_CR0_32K_SELECT            (0x80)
#define OSC_CR0_PLL_MODE              (0x40)
#define OSC_CR0_NO_BUZZ               (0x20)
#define OSC_CR0_SLEEP                 (0x18)
#define OSC_CR0_SLEEP_512Hz           (0x00)
#define OSC_CR0_SLEEP_64Hz            (0x08)
#define OSC_CR0_SLEEP_8Hz             (0x10)
#define OSC_CR0_SLEEP_1Hz             (0x18)
#define OSC_CR0_CPU                   (0x07)
#define OSC_CR0_CPU_3MHz              (0x00)
#define OSC_CR0_CPU_6MHz              (0x01)
#define OSC_CR0_CPU_12MHz             (0x02)
#define OSC_CR0_CPU_24MHz             (0x03)
#define OSC_CR0_CPU_1d5MHz            (0x04)
#define OSC_CR0_CPU_750kHz            (0x05)
#define OSC_CR0_CPU_187d5kHz          (0x06)
#define OSC_CR0_CPU_93d7kHz           (0x07)

#pragma  ioport   OSC_CR1:    0x1E1  // System V1/V2 Divider Control Register
BYTE              OSC_CR1;
#define OSC_CR1_VC1                   (0xF0)
#define OSC_CR1_VC2                   (0x0F)

#pragma  ioport   OSC_CR2:    0x1E2  // Oscillator Control Register 2
BYTE              OSC_CR2;
#define OSC_CR2_PLLGAIN               (0x80)
#define OSC_CR2_EXTCLKEN              (0x04)
#define OSC_CR2_IMODIS                (0x02)
#define OSC_CR2_SYSCLKX2DIS           (0x01)

#pragma  ioport   VLT_CR:     0x1E3  // Voltage Monitor Control Register
BYTE              VLT_CR;
#define VLT_CR_SMP                    (0x80)
#define VLT_CR_PORLEV                 (0x30)
#define VLT_CR_POR_MID                (0x10)
#define VLT_CR_POR_HIGH               (0x20)
#define VLT_CR_LVDTBEN                (0x08)
#define VLT_CR_VM                     (0x07)

#pragma  ioport   VLT_CMP:    0x1E4  // Voltage Monitor Comparators Register
BYTE              VLT_CMP;
#define VLT_CMP_PUMP                  (0x04)
#define VLT_CMP_LVD                   (0x02)
#define VLT_CMP_PPOR                  (0x01)

#pragma  ioport   DEC_CR2:    0x1E7  // Data Control Register
BYTE              DEC_CR2;

#pragma  ioport   IMO_TR:     0x1E8  // Internal Main Oscillator Trim Register
BYTE              IMO_TR;
#pragma  ioport   ILO_TR:     0x1E9  // Internal Low-speed Oscillator Trim
BYTE              ILO_TR;
#pragma  ioport   BDG_TR:     0x1EA  // Band Gap Trim Register
BYTE              BDG_TR;
#pragma  ioport   ECO_TR:     0x1EB  // External Oscillator Trim Register
BYTE              ECO_TR;
#pragma  ioport   IMO_TR2:    0x1EF  // Internal Main Oscillator Gain Trim Register
BYTE              IMO_TR2;

#pragma  ioport   DAC_CR:     0x1FD  // DAC Control Register
BYTE              DAC_CR;



#define DAC_CR_SPLIT_MUX              (0x80)
#define DAC_CR_MUXCLK_GE              (0x40)
#define DAC_CR_RANGE                  (0x08)
#define DAC_CR_OSCMODE                (0x06)
#define DAC_CR_ENABLE                 (0x01)

//=============================================================================
//=============================================================================
//      M8C System Macros
//=============================================================================
//=============================================================================


//-----------------------------------------------
//  Swapping Register Banks
//-----------------------------------------------
#define  M8C_SetBank0            asm("and F, EFh")
#define  M8C_SetBank1            asm("or  F, 10h")

//-----------------------------------------------
//  Global Interrupt Enable/Disable
//-----------------------------------------------
#define  M8C_EnableGInt          asm("or  F, 01h")
#define  M8C_DisableGInt         asm("and F, FEh")

//---------------------------------------------------
// Enable/Disable Interrupt Mask
//
// Usage:    M8C_DisableIntMask INT_MSKN, MASK
//           M8C_EnableIntMask  INT_MSKN, MASK
//
// where INT_MSKN is INT_MSK0, INT_MSK1 or INT_MSK3
//       and MASK is the bit set to enable or disable
//---------------------------------------------------
// Disable Interrupt Bit Mask(s)
#define M8C_DisableIntMask( INT_MSKN_REG, MASK )   (INT_MSKN_REG &= ~MASK)

// Enable Interrupt Bit Mask(s)
#define M8C_EnableIntMask( INT_MSKN_REG, MASK )    (INT_MSKN_REG |= MASK)

//---------------------------------------------------
// Clear Posted Interrupt Flag
//
// Usage:    M8C_ClearIntFlag   INT_CLRN, MASK
//
// where INT_MSKN is INT_CLR0, INT_CLR1 or INT_CLR3
//       and MASK is the bit set to enable or disable
//---------------------------------------------------
#define M8C_ClearIntFlag( INT_CLRN_REG, MASK )    (INT_CLRN_REG = ~MASK)


//-----------------------------------------------
//  Power-On Reset & WatchDog Timer Functions
//-----------------------------------------------
#define  M8C_EnableWatchDog      (CPU_SCR0 &= ~CPU_SCR0_PORS_MASK)
#define  M8C_ClearWDT            (RES_WDT = 0x00)
#define  M8C_ClearWDTAndSleep    (RES_WDT = 0x38)

//-----------------------------------------------
//  CPU Stall for Analog PSoC Block Writes
//-----------------------------------------------
#define  M8C_Stall               (ASY_CR |=  ASY_CR_SYNCEN)
#define  M8C_Unstall             (ASY_CR &= ~ASY_CR_SYNCEN)

//-----------------------------------------------
//  Sleep, CPU Stop & Software Reset
//-----------------------------------------------
#define  M8C_Sleep               (CPU_SCR0 |= CPU_SCR0_SLEEP_MASK)
#define  M8C_Stop                (CPU_SCR0 |= CPU_SCR0_STOP_MASK)

#define  M8C_Reset               asm("mov A, 0\nSSC");


//-----------------------------------------------
// ImageCraft Code Compressor Actions
//-----------------------------------------------

    // Suspend Code Compressor
    // Must not span a RET or RETI instruction
    // without resuming code compression

#define Suspend_CodeCompressor asm("or F, 0")

    // Resume Code Compressor
#define Resume_CodeCompressor asm("add SP,0")

#endif


// end of file m8c.h
