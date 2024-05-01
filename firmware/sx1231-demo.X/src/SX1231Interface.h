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



//Define any enum types used in this file
typedef enum {
    SLEEP = 0x00, STBY = 0x01, FS = 0x02, TX = 0x03, RX = 0x04
} SX1231Mode;


//Define any variables that are external to this file


//Define prototypes for functions used in the SX1231 source file
extern void initializeTransceiver();  //Initialize Transceiver Function, configures the transceiver IC to operate as required for the application

extern void setCarrierFreq(uint32_t freqRF);   //Set Carrier Frequency Function, sets the RF transceiver to tune to the desired carrier frequency
extern void setMode(SX1231Mode newMode);  //Set Mode Function, instructs the RF transceiver to enter the desired mode

extern void interactWithRegisters(uint8_t startAddress,  //Interact With Registers Functions, reads/writes to the registers in the transceiver at the given start address using/into dataBytes
                                  uint8_t *dataBytes,
                                  uint8_t bufferLength,
                                  uint8_t readMode);


#endif






//END OF FILE