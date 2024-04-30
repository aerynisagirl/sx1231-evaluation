/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  Main.h - Primary header, contains the program entrance and MCU configuration                 *
 *************************************************************************************************/

#ifndef _MAIN_H
#define _MAIN_H



/********************************
 *  MCU Configuration Settings  *
 ********************************/


//DEVCFG3 Register
#pragma config USERID = 0xFFFF         //Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PMDL1WAY = OFF          //Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF           //Peripheral Pin Select Configuration (Allow multiple reconfigurations)

//DEVCFG2 Register
#pragma config FPLLIDIV = DIV_2        //PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_16        //PLL Multiplier (16x Multiplier)
#pragma config FPLLODIV = DIV_4        //System PLL Output Clock Divider (PLL Divide by 4)

//DEVCFG1 Register
#pragma config FNOSC = FRCPLL          //Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF           //Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON               //Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF           //Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF          //CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2          //Peripheral Clock Divisor (Pb_Clk is Sys_Clk/2)
#pragma config FCKSM = CSDCMD          //Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576       //Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF            //Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF            //Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_25    //Watchdog Timer Window Size (Window Size is 25%)

//DEVCFG0 Register
#pragma config JTAGEN = OFF            //JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1       //ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF               //Program Flash Write Protect (Disable)
#pragma config BWP = OFF               //Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                //Code Protect (Protection Disabled)



/*******************
 *  Main Firmware  *
 *******************/


//Import any libraries used by this file
#include <xc.h>               //Include the primary header used by the XC32 compiler
#include "SX1231Interface.h"  //Include the SX1231 driver header to interface with the SX1231 transceiver IC


//Define any variables that are external to this file


//Define prototypes for functions used in the Main source file
extern void setupMCU();  //Setup MCU Function, sets the appropriate control registers on the MCU needed to make things work for the application
extern void main();      //Main Function, called upon reset of the MCU


#endif






//END OF FILE