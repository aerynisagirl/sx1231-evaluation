/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  Main.c - Defines the main functionality of the program                                       *
 *************************************************************************************************/

#include "Main.h"  //Include the Main header file that houses all global entities to this system



/******************
 *  Main Program  *
 ******************/


//Setup MCU Function, sets the appropriate control registers on the MCU needed to make things work for the application
void setupMCU()
{
    //Enable and configure the second SPI peripheral, SPI2
    SDI2R = 0x000000003;    //Assign RB13 to the SDI input of SPI2
    RPB11R = 0x00000004;    //Assign RB11 to the SDO output of SPI2
    SPI2BRG = 0x00000000;   //Set the clock frequency of SPI2 to operate at 4MHz
    SPI2CON2 = 0x00000C00;  //Disable all audio codec functionality of SPI2
    SPI2CON = 0x00008120;   //Enable SPI2 in master mode, configured for 8-bit words in standard buffer mode

    //Configure Port A
    LATA = 0x00000000;   //Clear all of Port A to logic LOW
    TRISA = 0x0000078F;  //Set RA4 to an output

    //Configure Port B
    LATB = 0x00001000;   //Clear all of Port B to logic LOW
    ODCB = 0x00001000;   //Enable the open-drain function on RB12
    TRISB = 0x0000EFFF;  //Set RB12 to an output
    
    //    TODO: Setup DMA?
}


//Main Function, called upon reset of the MCU
void main()
{
    setupMCU();  //Configure the main functionality of the microcontroller for the application

    //Infinite loop of death :3
    while (0xFFFFFFFF)
    {
        //Do things forever <3
        //    (like living in a capitalistic hellscape loooool)

        uint32_t timer = 0x000FFFFF;
        while (timer--);

        LATAINV = 0x00000010;  //Toggle the state of RA4

        setCarrierFreq(433025000);  //Set the carrier frequency of the RF transceiver to 433.025 MHz

        timer = 0x000000FF;
        while (timer--);
        uint8_t inputBuffer[0x00000003];
        interactWithRegisters(0x07, inputBuffer, 0x00000003, 0xFF);
    }
}






//END OF FILE