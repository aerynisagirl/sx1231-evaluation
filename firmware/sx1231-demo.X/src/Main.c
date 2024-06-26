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
    SPI2BRG = 0x00000001;   //Set the clock frequency of SPI2 to operate at 4MHz
    SPI2CON2 = 0x00000C00;  //Disable all audio codec functionality of SPI2
    SPI2CON = 0x00008120;   //Enable SPI2 in master mode, configured for 8-bit words in standard buffer mode

    //Configure Port A
    LATA = 0x00000000;   //Clear all of Port A to logic LOW
    TRISA = 0x0000078F;  //Set RA4 to an output

    //Configure Port B
    LATB = 0x00001000;    //Clear all of Port B to logic LOW
    ODCB = 0x00001000;    //Enable the open-drain function on RB12
    ANSELB = 0x0000C00F;  //Set both RB13 and RB12 as digital inputs
    TRISB = 0x0000EFFF;   //Set RB12 to an output
}


//Main Function, called upon reset of the MCU
void main()
{
    setupMCU();  //Configure the main functionality of the microcontroller for the application

    uint32_t timer = 0x000FFFFF;
    while (timer--);



    initializeTransceiver(FSK_F_BT10, 433000000, 750, 4800);




    //Infinite loop of death :3
    while (0xFFFFFFFF)
    {
        uint8_t powerSetting = 0x01;

        while (powerSetting < 0x17)
        {
            LATASET = 0x00000010;  //Put RA4 to logic HIGH

            loadPacket("This is a test of the SX1231H", 29);
            setPowerLevel(powerSetting++);
            setDeviceMode(TX);

            uint8_t irqValue = 0x00;
            do
            {
                interactWithRegisters(REGADDR_IRQFLAGS2, &irqValue, 0x01, 0xFF);
            }
            while ((irqValue & 0x08) == 0x00);

            setPowerLevel(0x00);
            setDeviceMode(STBY);

            LATACLR = 0x00000010;  //Put RA4 to logic LOW

            timer = 0x0007FFFF;
            while (timer--);
        }

        timer = 0x01FFFFFF;
        while (timer--);
    }
}






//END OF FILE