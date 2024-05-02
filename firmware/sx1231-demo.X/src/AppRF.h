/*************************************************************************************************
 *  SX1231 Demo - Project to evaluate integrating a Semtech SX1231 with PIC32 microcontrollers.  *
 * --------------------------------------------------------------------------------------------- *
 *  AppRF.h - Defines application RF operation settings                                          *
 *************************************************************************************************/

#ifndef _APP_RF_H
#define	_APP_RF_H



/*************************
 *  Modulation Settings  *
 *************************/



/****************************
 *  Packet Engine Settings  *
 ****************************/

#ifndef APPRF_PE_PREAMBLE_SIZE
#define APPRF_PE_PREAMBLE_SIZE        0x0003    //Preamble length
#endif


//Sync Word
#ifndef APPRF_PE_SYNC_SIZE
#define APPRF_PE_SYNC_SIZE                  0x04    //Sync Word Length (0 disables the sync word entirely)

#define APPRF_PE_SYNC_B0                    0x73    //Sync Word Byte 1
#define APPRF_PE_SYNC_B1                    0x79
#define APPRF_PE_SYNC_B2                    0x6E
#define APPRF_PE_SYNC_B3                    0x63
#define APPRF_PE_SYNC_B4                    0x77
#define APPRF_PE_SYNC_B5                    0x6F
#define APPRF_PE_SYNC_B6                    0x72
#define APPRF_PE_SYNC_B7                    0x64    //Sync Word Byte 8
#endif


#ifndef APPRF_PE_SYNC_TOLERANCE
#define APPRF_PE_SYNC_TOLERANCE             0x00    //Number of bit errors detected in sync word for RX mode
#endif


#ifndef APPRF_PE_CODING
#define APPRF_PE_CODING                     0x00    //DC Free Coding Scheme (0 = Off, 1 = Manchester, 2 = Whitening)
#endif


#ifndef APPRF_PE_PACKET_SIZE
#define APPRF_PE_PACKET_SIZE                0x00    //Packet Size (0 disables fixed length mode)
#endif


#ifndef APPRF_PE_ADDRESS_MODE
#define APPRF_PE_ADDRESS_MODE               0x00    //Address filtering mode (0 = disabled, 1 filters only node address, 2 filters both node and broadcast addresses)
#endif


#ifndef APPRF_ADDRESS_BROADCAST
#define APPRF_ADDRESS_BROADCAST             0x00    //Broadcast address
#endif

#ifndef APPRF_ADDRESS_NODE
#define APPRF_ADDRESS_NODE                  0x01    //Node address
#endif



/*****************************
 *  AES Encryption Settings  *
 *****************************/

//#define APPRF_AES_ENABLED                           //UNCOMMENT ME TO ENABLE THE AES CIPHER


#ifdef APPRF_AES_ENABLED

#ifndef APPRF_AES_KEY00
#define APPRF_AES_KEY00                     0x00    //AES Key Byte 1
#define APPRF_AES_KEY01                     0x00
#define APPRF_AES_KEY02                     0x00
#define APPRF_AES_KEY03                     0x00
#define APPRF_AES_KEY04                     0x00
#define APPRF_AES_KEY05                     0x00
#define APPRF_AES_KEY06                     0x00
#define APPRF_AES_KEY07                     0x00
#define APPRF_AES_KEY08                     0x00
#define APPRF_AES_KEY09                     0x00
#define APPRF_AES_KEY10                     0x00
#define APPRF_AES_KEY11                     0x00
#define APPRF_AES_KEY12                     0x00
#define APPRF_AES_KEY13                     0x00
#define APPRF_AES_KEY14                     0x00
#define APPRF_AES_KEY15                     0x00    //AES Key Byte 16
#endif

#endif



#endif






//END OF FILE