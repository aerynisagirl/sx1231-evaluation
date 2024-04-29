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
    //    TODO: Configure the SPI2 module
    //          Setup DMA?
    //          Connect an LED to Port A to do things, maybe a button. Maybe use Port B instead. idk. lol
}


//Main Function, called upon reset of the MCU
void main()
{
    setupMCU();  //Configure the main functionality of the microcontroller for the application

    //Infinite loop of death :3
    while (0xFF)
    {
        //Do things forever <3
        //    (like living in a capitalistic hellscape loooool)
    }
}






//END OF FILE