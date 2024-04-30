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
//    const uint8_t carrierFrequency[] = {};
//    interactWithRegisters(0x01, &configurationBytes, 0x00000000, 0x00000000);  //Send the desired default configuration to the transceiver
}






/*****************************************
 *  Transceiver Configuration Functions  *
 *****************************************/


//Set Carrier Frequency Function, sets the RF transceiver to tune to the desired carrier frequency
void setCarrierFreq(uint32_t freqRF)
{
    const double freqStep = 32000000 / 2 ^ 19;            //Calculate the F_step constant, the resolution of the carrier PLL in the transceiver IC
    uint32_t registerValue = (double) freqRF / freqStep;  //Determine the value to write to the RegFrf register in the transceiver IC to obtain the desired carrier frequency

    uint8_t registerValues[0x00000003];  //Create an array of 3 bytes to use for separating the splitting the contents of register value across

    registerValues[0x02] = registerValue & 0x000000FF;  //Write the first 8 bits of registerValue into the 3rd element of the registerValues array
    registerValue >>= 0x00000008;                       //Shift the contents of the registerValue variable to the right by 8 bits
    registerValues[0x01] = registerValue & 0x000000FF;  //Write the next 8 bits of registerValue into the 2nd element of the registerValues array
    registerValue >>= 0x00000008;                       //Shift the contents of the registerValue variable to the right by 8 bits
    registerValues[0x00] = registerValue & 0x000000FF;  //Write the final 8 bits of the registerValue variable into the first index of the array
    
    registerValues[0x00] = 0x6C;
    registerValues[0x01] = 0x41;
    registerValues[0x02] = 0x9B;

    interactWithRegisters(0x07, registerValues, 0x00000003, 0x00);  //Write the configuration bits to the transceiver IC
}






/***************************************
 *  Transceiver Interaction Functions  *
 ***************************************/


//Interact With Registers Functions, reads/writes to the registers in the transceiver at the given start address using/into dataBytes 
void interactWithRegisters(uint8_t startAddress, uint8_t *dataBytes, uint32_t bufferLength, uint8_t readMode)
{
    uint8_t test = 0x00;
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