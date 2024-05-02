/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  SX1231Interface.h - Defines all things related to interactions with the SX1231 IC            *
 *************************************************************************************************/

#ifndef _SX1231_INTERFACE_H_
#define _SX1231_INTERFACE_H_

//Import any libraries used by this file
#include <xc.h>               //Include the primary header used by the XC32 compiler
#include "SX1231Registers.h"  //Include a list of handy register address definitons for the transceiver
#include "AppRF.h"            //Include the users application settings to use when initializing the transceiver



//Define any enum types used in this file
typedef enum
{
    SLEEP, STBY, FS, TX, RX, MODE_RESERVED
} sx1231opmode_t;

typedef enum
{
    FSK_NOSHAPING = 0x00, FSK_F_BT10 = 0x01, FSK_F_BT05 = 0x02, FSK_F_BT03 = 0x03,
    OOK_NOSHAPING = 0x08, OOK_F_BR = 0x09, OOK_F_2BR = 0x0A, MOD_RESERVED = 0x0B
} sx1231modscheme_t;


//Define any variables that are external to this file


//Define prototypes for functions used in the SX1231 source file
extern void initializeTransceiver(sx1231modscheme_t modScheme,  //Initialize Transceiver Function, configures the transceiver IC to operate as required for the application
                                  uint32_t carrierFreq,
                                  uint32_t fskDev,
                                  uint32_t bitRate);

extern void loadPacket(uint8_t *payloadBytes,   //Load Packet Function, writes the desired packet to the FIFO buffer on the transceiver IC
                       uint8_t payloadLength);

extern void setDeviceMode(sx1231opmode_t newMode);  //Set Device Mode Function, instructs the RF transceiver to enter the desired mode
extern void setCarrierFreq(uint32_t freqRF);        //Set Carrier Frequency Function, sets the RF transceiver to tune to the desired carrier frequency
extern void setPowerLevel(uint8_t txPower);         //Set Power Level Function, sets the TX output power strength

extern sx1231opmode_t getDeviceMode();  //Get Device Mode Function, returns the current mode that the transceiver is operating in

extern void interactWithRegisters(uint8_t startAddress,  //Interact With Registers Functions, reads/writes to the registers in the transceiver at the given start address using/into dataBytes
                                  uint8_t *dataBytes,
                                  uint8_t bufferLength,
                                  uint8_t readMode);


#endif






//END OF FILE