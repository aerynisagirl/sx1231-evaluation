/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  SX1231Interface.c - Contains all SX1231 related functions                                    *
 *************************************************************************************************/

#include "SX1231Interface.h"



/******************************
 *  Initialization Functions  *
 ******************************/


//Initialize Transceiver Function, configures the transceiver IC to operate as required for the application
void initializeTransceiver()
{
    uint8_t configBytes[0x00000010] = {0x04, 0x09, 0x19, 0x00, 0x00, 0x52, 0x6C, 0x40, 0x00};
    interactWithRegisters(REGADDR_OPMODE, configBytes, 0x09, 0x00);

    configBytes[0x00] = 0x5F;
    configBytes[0x01] = 0x09;
    configBytes[0x02] = 0x0F;
    interactWithRegisters(REGADDR_PALEVEL, configBytes, 0x03, 0x00);

    configBytes[0x00] = 0x00;
    configBytes[0x01] = 0x0F;
    configBytes[0x02] = 0x18;
    interactWithRegisters(REGADDR_PREAMBLE_MSB, configBytes, 0x03, 0x00);

    configBytes[0x00] = 0x80;
    configBytes[0x01] = 0x40;
    configBytes[0x02] = 0x00;
    configBytes[0x03] = 0x00;
    configBytes[0x04] = 0x00;
    configBytes[0x05] = 0x8F;
    interactWithRegisters(REGADDR_PACKETCONFIG1, configBytes, 0x06, 0x00);

    setCarrierFreq(431500000);
}



/*****************************************
 *  Transceiver Configuration Functions  *
 *****************************************/


//Set Carrier Frequency Function, sets the RF transceiver to tune to the desired carrier frequency
void setCarrierFreq(uint32_t freqRF)
{
    double calculatedFrequency = freqRF / SX1231_F_STEP;  //Calculate the value of Frf to provide the transceiver IC to achieve the desired carrier frequency
    uint32_t regFrfValue = calculatedFrequency;           //Force cast the calculated value into an unsigned 32-bit integer to make byte separation easier

    uint8_t registerValues[0x00000003];  //Create an array of 3 bytes to use for separating the splitting the contents of register value across

    registerValues[0x02] = regFrfValue & 0x000000FF;  //Write the first 8 bits of regFrfValue into the 3rd element of the registerValues array
    regFrfValue >>= 0x00000008;                       //Shift the contents of the registerValue variable to the right by 8 bits
    registerValues[0x01] = regFrfValue & 0x000000FF;  //Write the next 8 bits of regFrfValue into the 2nd element of the registerValues array
    regFrfValue >>= 0x00000008;                       //Shift the contents of the registerValue variable to the right by 8 bits
    registerValues[0x00] = regFrfValue & 0x000000FF;  //Write the final 8 bits of the regFrfValue variable into the first index of the array

    interactWithRegisters(REGADDR_FRF_MSB, registerValues, 0x03, 0x00);  //Write the configuration bits to the transceiver IC
}


//Set Mode Function, puts the transceiver into the desired operating mode
void setMode(SX1231Mode newMode)
{
    uint8_t registerValue = newMode << 0x00000002;  //Write the value of the newMode enum to the registerValue variable and shift it to the left by 2 bits

    interactWithRegisters(0x01, &registerValue, 0x01, 0x00);  //Write the configuration byte to the transceiver IC
}



/***************************************
 *  Transceiver Interaction Functions  *
 ***************************************/


//Interact With Registers Functions, reads/writes to the registers in the transceiver at the given start address using/into dataBytes 
void interactWithRegisters(uint8_t startAddress, uint8_t *dataBytes, uint8_t bufferLength, uint8_t readMode)
{
    while (SPI2CON & 0x00000800);  //Wait until the SPI2 peripheral is in idle mode before starting the data transaction

    startAddress |= 0x80;                //Force-set Bit-7 of the startAddress variable to indicate the assumed write operation
    if (readMode) startAddress &= 0x7F;  //Clear Bit-7 of startAddress when the readMode parameter is not 0

    LATBCLR = 0x00001000;    //Clear RB12 to pull the SS line down to logic LOW
    SPI2BUF = startAddress;  //Begin the transaction by writing the contents of the startAddress variable to the data buffer of SPI2

    while (SPI2STAT & 0x00000800);  //Wait until the SPI2 peripheral is no longer busy before continuing
    SPI2BUF;                        //Read from the SPI2 peripherals input buffer to clear it
    SPI2STATCLR = 0x00000040;       //Clear the Read Buffer Overflow flag in the SPI2 status register
    
    //Perform the data exchange for the size of the provided buffer
    while (bufferLength--)
    {
        //Determine what data to send based on what operation is being performed
        if (readMode)
        {
            SPI2BUF = 0x00;  //Send a series of blank of 0's when performing a read operation
        }
        else
        {
            SPI2BUF = *(dataBytes++);  //Transmit the value stored at the address given by the dataBytes pointer, incrementing the pointer address by 1 afterwards
        }

        while (SPI2STAT & 0x00000800);  //Wait until the SPI2 peripheral is no longer busy before continuing

        //Collect the obtained data byte when in read mode from the SPI2 peripheral, ignoring the first byte in the sequence
        if (readMode)
        {
            *(dataBytes++) = (SPI2BUF & 0x000000FF);  //Write the contents of the SPI2 receive buffer into the address specified by the dataBytes pointer
        }
        else
        {
            SPI2BUF;  //Clear the SPI2 receive buffer and its associated flags by reading from the SPI2BUF register
        }
    }

    LATBSET = 0x00001000;  //Clear RB12 to bring the SS line back up to its idle state of logic HIGH
}






//END OF FILE