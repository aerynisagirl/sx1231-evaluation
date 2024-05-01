/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  SX1231Registers.h - Provides definitions for all the registers within the transceiver        *
 *************************************************************************************************/

#ifndef _SX1231REGISTERS_H_
#define	_SX1231REGISTERS_H_

//Import any libraries used by this file



/************************
 *  Register Addresses  *
 ************************/

#define REGADDR_FIFO                 0x00
#define REGADDR_OPMODE               0x01
#define REGADDR_DATAMODUL            0x02

#define REGADDR_BITRATE_MSB          0x03
#define REGADDR_BITRATE_LSB          0x04

#define REGADDR_FDEV_MSB             0x05
#define REGADDR_FDEV_LSB             0x06

#define REGADDR_FRF_MSB              0x07
#define REDADDR_FRF_MID              0x08
#define REGADDR_FRF_LSB              0x09

#define REGADDR_OSC1                 0x0A
#define REGADDR_AFCCTRL              0x0B

#define REGADDR_LISTEN1              0x0D
#define REGADDR_LISTEN2              0x0E
#define REGADDR_LISTEN3              0x0F

#define REGADDR_VERSION              0x10
#define REGADDR_PALEVEL              0x11
#define REGADDR_PARAMP               0x12
#define REGADDR_OCP                  0x13
#define REGADDR_LNA                  0x18
#define REGADDR_RXBW                 0x19
#define REGADDR_AFCBW                0x1A
#define REGADDR_OOKPEAK              0x1B
#define REGADDR_OOKAVG               0x1C
#define REGADDR_OOKFIX               0x1D
#define REGADDR_AFCFEI               0x1E

#define REGADDR_AFC_MSB              0x1F
#define REGADDR_AFC_LSB              0x20

#define REGADDR_FEI_MSB              0x21
#define REGADDR_FEI_LSB              0x22

#define REGADDR_RSSICONFIG           0x23
#define REGADDR_RSSIVALUE            0x24

#define REGADDR_DIOMAPPING1          0x25
#define REGADDR_DIOMAPPING2          0x26

#define REGADDR_IRQFLAGS1            0x27
#define REGADDR_IRQFLAGS2            0x28

#define REGADDR_RSSITHRESH           0x29

#define REGADDR_RXTIMEOUT1           0x2A
#define REGADDR_RXTIMEOUT2           0x2B

#define REGADDR_PREAMBLE_MSB         0x2C
#define REGADDR_PREAMBLE_LSB         0x2D

#define REGADDR_SYNCCONFIG           0x2E

#define REGADDR_SYNCVALUE1           0x2F
#define REGADDR_SYNCVALUE2           0x30
#define REGADDR_SYNCVALUE3           0x31
#define REGADDR_SYNCVALUE4           0x32
#define REGADDR_SYNCVALUE5           0x33
#define REGADDR_SYNCVALUE6           0x34
#define REGADDR_SYNCVALUE7           0x35
#define REGADDR_SYNCVALUE8           0x36

#define REGADDR_PACKETCONFIG1        0x37
#define REGADDR_PAYLOADLENGTH        0x38
#define REGADDR_NODEADRS             0x39
#define REGADDR_BROADCASTADRS        0x3A
#define REGADDR_AUTOMODES            0x3B
#define REGADDR_FIFOTHRESH           0x3C
#define REGADDR_PACKETCONFIG2        0x3D

#define REGADDR_AESKEY1              0x3E
#define REGADDR_AESKEY2              0x3F
#define REGADDR_AESKEY3              0x40
#define REGADDR_AESKEY4              0x41
#define REGADDR_AESKEY5              0x42
#define REGADDR_AESKEY6              0x43
#define REGADDR_AESKEY7              0x44
#define REGADDR_AESKEY8              0x45
#define REGADDR_AESKEY9              0x46
#define REGADDR_AESKEY10             0x47
#define REGADDR_AESKEY11             0x48
#define REGADDR_AESKEY12             0x49
#define REGADDR_AESKEY13             0x4A
#define REGADDR_AESKEY14             0x4B
#define REGADDR_AESKEY15             0x4C
#define REGADDR_AESKEY16             0x4D

#define REGADDR_TEMP1                0x4E
#define REGADDR_TEMP2                0x4F

#define REGADDR_TESTLNA              0x58
#define REGADDR_TESTTXCO             0x59

#define REGADDR_TESTPA1              0x5A
#define REGADDR_TESTPA2              0x5C

#define REGADDR_TESTDAGC             0x6F
#define REGADDR_TESTAFC              0x71



/********************
 *  Math Constants  *
 ********************/

#define SX1231_F_XOSC        32000000     //Frequency of the crystal external to the transceiver IC
#define SX1231_F_STEP        61.03515625  //Step resolution of the PLL used to generate the carrier frequency inside the transceiver


#endif






//END OF FILE