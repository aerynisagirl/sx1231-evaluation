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
void initializeTransceiver(sx1231modscheme_t modScheme, uint32_t carrierFreq, uint32_t fskDev, uint32_t bitRate)
{
    uint8_t configBytes[0x00000010];  //Create an array of bytes to use for writing the desired configuration settings to the transceiver IC
    
    //Common configuration registers
    configBytes[0x00000000] = 0x04;       //Put the transceiver into STANDBY mode by default
    configBytes[0x00000001] = modScheme;  //Set the desired modulation scheme

    //Set the modulation bit-rate
    uint32_t regBitrateValue = SX1231_F_XOSC / bitRate;      //Calculate the value to be written to the bitrate registers in order to achieve the desired bit-rate
    configBytes[0x00000003] = regBitrateValue & 0x000000FF;  //Write the first 8 bits of the calculated bitrate value into RegBitrateLsb
    regBitrateValue >>= 0x00000008;                          //Shift the contents of regBitrateValue to the right by 8 bits
    configBytes[0x00000002] = regBitrateValue & 0x000000FF;  //Write the remaining 8 bits of the calculated bitrate value into RegBitrateMsb

    //Set the frequency deviation to use for FSK mode
    double calculatedDeviation = fskDev / SX1231_F_STEP;  //Calculate the value of Fdev to provide to the transceiver to achieve the desired frequency deviation in FSK mode
    uint16_t regFdevValue = calculatedDeviation;          //Force cast the calculated value into an unsigned 16-bit integer to make byte separation easier
    configBytes[0x00000005] = regFdevValue & 0x000000FF;  //Write the first 8 bits of the calculated deviation value into RegFdevLsb
    regFdevValue >>= 0x00000008;                          //Shift the contents of regFdevValue to the right by 8 bits
    configBytes[0x00000004] = regFdevValue & 0x0000003F;  //Write the last 6 bits of the calculated deviation value into RegFdevMsb

    //Set the carrier frequency
    double calculatedFrequency = carrierFreq / SX1231_F_STEP;  //Calculate the value of Frf to provide the transceiver IC to achieve the desired carrier frequency
    uint32_t regFrfValue = calculatedFrequency;                //Force cast the calculated value into an unsigned 32-bit integer to make byte separation easier
    configBytes[0x00000008] = regFrfValue & 0x000000FF;        //Write the first 8 bits of regFrfValue into RegFrfLsb
    regFrfValue >>= 0x00000008;                                //Shift the contents of regFrfValue to the right by 8 bits
    configBytes[0x00000007] = regFrfValue & 0x000000FF;        //Wrist the next 8 bits of regFrfValue into RegFrfMid
    regFrfValue >>= 0x00000008;                                //Shift the contents of regFrfValue to the right by 8 bits again
    configBytes[0x00000006] = regFrfValue & 0x000000FF;        //Write the final 8 bitsof regFrfValue into RegFrfMsb

    interactWithRegisters(0x01, configBytes, 0x09, 0x00);  //Send the configuration bytes to the transceiver IC with a starting address of 0x01 (RegOpMode)



    //Packet engine registers
    configBytes[0x00000001] = APPRF_PE_PREAMBLE_SIZE & 0x000000FF;                  //Write the first 8 bits of the preamble size into RegPreambleLsb
    configBytes[0x00000000] = (APPRF_PE_PREAMBLE_SIZE & 0x0000FF00) >> 0x00000008;  //Write the last 8 bits of the preamble size into RegPreambleMsb

    configBytes[0x00000002] = APPRF_PE_SYNC_TOLERANCE & 0x07;  //Write the desired sync word tolerance to RegSyncConfig

    //Enable the sync word settings in RegSyncConfig when the size of the sync word is specified as greater than 0
    if (APPRF_PE_SYNC_SIZE)
    {
        configBytes[0x00000002] |= 0x80 | ((APPRF_PE_SYNC_SIZE - 0x01) << 0x00000003);  //Set the size of the sync word and enable it
    }

    //Load the sync word bytes into their associated registers
    configBytes[0x00000003] = APPRF_PE_SYNC_B0;
    configBytes[0x00000004] = APPRF_PE_SYNC_B1;
    configBytes[0x00000005] = APPRF_PE_SYNC_B3;
    configBytes[0x00000006] = APPRF_PE_SYNC_B4;
    configBytes[0x00000007] = APPRF_PE_SYNC_B5;
    configBytes[0x00000008] = APPRF_PE_SYNC_B6;
    configBytes[0x00000009] = APPRF_PE_SYNC_B7;

    configBytes[0x0000000A] = ((APPRF_PE_CODING & 0x00000003) << 0x00000005) | (APPRF_PE_ADDRESS_MODE & 0x0000000F);  //Set what DC free coding scheme to use in RegPacketConfig1

    if (!APPRF_PE_PACKET_SIZE) configBytes[0x0000000A] |= 0x80;  //Change the packet mode from fixed to variable length when a packet length is configured
    
    configBytes[0x0000000C] = APPRF_ADDRESS_NODE;       //Provide the configured node address
    configBytes[0x0000000D] = APPRF_ADDRESS_BROADCAST;  //Provide the configured broadcast address

    interactWithRegisters(0x2C, configBytes, 0x0E, 0x00);  //Send the configuration bytes to the transceiver IC with a starting address of 0x2C (RegPreambleMsb)

#ifdef APPRF_AES_ENABLED
    configBytes[0x00000000] = 0x01;

    //Load the AES key into the transceiver
    configBytes[0x00000001] = APPRF_AES_KEY00;
    configBytes[0x00000002] = APPRF_AES_KEY01;
    configBytes[0x00000003] = APPRF_AES_KEY02;
    configBytes[0x00000004] = APPRF_AES_KEY03;
    configBytes[0x00000005] = APPRF_AES_KEY04;
    configBytes[0x00000006] = APPRF_AES_KEY05;
    configBytes[0x00000007] = APPRF_AES_KEY06;
    configBytes[0x00000008] = APPRF_AES_KEY07;
    configBytes[0x00000009] = APPRF_AES_KEY08;
    configBytes[0x0000000A] = APPRF_AES_KEY09;
    configBytes[0x0000000B] = APPRF_AES_KEY10;
    configBytes[0x0000000C] = APPRF_AES_KEY11;
    configBytes[0x0000000D] = APPRF_AES_KEY12;
    configBytes[0x0000000E] = APPRF_AES_KEY13;
    configBytes[0x0000000F] = APPRF_AES_KEY14;
    configBytes[0x00000010] = APPRF_AES_KEY15;

    interactWithRegisters(0x3D, configBytes, 0x11, 0x00);  //Write the AES key to the transceiver IC's internal memory whilst enabling AES mode on the packet engine
#endif

}



/**************************
 *  Transceiver Commands  *
 **************************/


//Load Packet Function, writes the desired packet to the FIFO buffer on the transceiver IC
void loadPacket(uint8_t *payloadBytes, uint8_t payloadLength)
{
    uint8_t formedFrame[0x00000101];    //Create a temporary buffer with the max number of bytes a frame can have
    uint8_t *framePtr = formedFrame;    //Make a pointer to use for iterating through the addresses in the array above
    uint8_t frameSize = payloadLength;  //Declare a variable to use for calculating the total size of the frame

    if (!APPRF_PE_PACKET_SIZE) *framePtr = ++frameSize;  //Start the frame with the number of bytes the frame will contain in variable frame mode
    

    //Add every byte of the payload to the frame buffer
    while (payloadLength--)
    {
        *(++framePtr) = *(payloadBytes++);  //Copy the next byte from the payloadBytes array into the frame buffer
    }

    interactWithRegisters(REGADDR_FIFO, formedFrame, frameSize, 0x00);  //Write the packet frame to the FIFO buffer of the transceiver
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


//Set Device Mode Function, puts the transceiver into the desired operating mode
void setDeviceMode(sx1231opmode_t newMode)
{
    if (newMode == MODE_RESERVED) return;  //Just leave if trying to set the mode of the transceiver to something invalid

    uint8_t registerValue = newMode << 0x00000002;                      //Write the value of the newMode enum to the registerValue variable and shift it to the left by 2 bits
    interactWithRegisters(REGADDR_OPMODE, &registerValue, 0x01, 0x00);  //Write the configuration byte to the transceiver IC
}


//Set Power Level Function, sets the TX output power strength
void setPowerLevel(uint8_t txPower)
{
    uint8_t paLevel = 0x00;               //Create a buffer variable to use for storing the value that will be written to RegPaLevel
    uint8_t overcurrentRegister = 0x19;   //Create another buffer for storing the value to be written to the overcurrent settings register
    uint8_t pa1HighPowerRegister = 0x55;  //Make a buffer for the high power settings register of PA1, defaulting to disabling high power mode
    uint8_t pa2HighPowerRegister = 0x70;  //Make a buffer for the high power settings register of PA2, defaulting to disabling high power mode

    if (txPower > 0x17) txPower = 0x17;  //Force any value of txPower greater than 0x17 back to 0x17 to prevent the offsets from messing up

    if (txPower >= 0x08)
    {
        paLevel = 0x68 + txPower;  //Enable both PA1 and PA2 when operating in high power mode, setting the output level as requested

        pa1HighPowerRegister = 0x5D;  //Put PA1 into high power mode
        pa2HighPowerRegister = 0x7C;  //Put PA2 into high power mode
    }
    else if (txPower >= 0x05)
    {
        paLevel = 0x6B + txPower;  //Enable both PA1 and PA2, setting the output accordingly
    }
    else if (txPower)
    {
        paLevel = 0x4F + txPower;  //Enable PA1, and set the output level accordingly
    }

    interactWithRegisters(REGADDR_PALEVEL, &paLevel, 0x01, 0x00);               //Write the value of paLevel to the RegPaLevel register on the transceiver IC
    interactWithRegisters(REGADDR_OCP, &overcurrentRegister, 0x01, 0x00);       //Write the value of overcurrentRegister to the RegOcp register on the transceiver IC
    interactWithRegisters(REGADDR_TESTPA1, &pa1HighPowerRegister, 0x01, 0x00);  //Write the value of pa1HighPowerRegister to the RegTestPa1 register on the transceiver IC
    interactWithRegisters(REGADDR_TESTPA2, &pa2HighPowerRegister, 0x01, 0x00);  //Write the value of pa2HighPowerRegister to the RegTestPa2 register on the transceiver IC
}


//Get Device Mode Function, returns the current mode that the transceiver is operating in
sx1231opmode_t getDeviceMode()
{
    uint8_t registerValue = 0x00;                                       //Create a buffer variable to use for storing the read byte
    interactWithRegisters(REGADDR_OPMODE, &registerValue, 0x01, 0xFF);  //Read the contents of the RegOpMode register from the transceiver

    registerValue = (registerValue & 0x1C) >> 0x00000002;  //Mask out the bits that set the transceivers mode and shift them over to the right by 2 bits
    if (registerValue >= 0x05) registerValue = 0x05;       //Force the mode number to 0x05 if it's set to any number thats classified as Reserved as per the datasheet

    return (sx1231opmode_t) registerValue;  //Cast the integer to the sx1231mode_t type and return the enum
}



/*****************************************
 *  Transceiver Data Exchange Functions  *
 *****************************************/


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