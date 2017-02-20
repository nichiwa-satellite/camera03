/***************************************************************************//**
* \file DEBUGPRINT_midi.h
* \version 3.10
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  MIDI class support.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
*  MIDI 1.0 Detailed Specification Document Version 4.2
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_DEBUGPRINT_midi_H)
#define CY_USBFS_DEBUGPRINT_midi_H

#include "DEBUGPRINT.h"

/***************************************
*    Initial Parameter Constants
***************************************/

#define DEBUGPRINT_ENABLE_MIDI_API    (0u != (1u))
#define DEBUGPRINT_MIDI_EXT_MODE      (0u)


/* Number of external interfaces (UARTs). */
#define DEBUGPRINT_ONE_EXT_INTRF  (0x01u)
#define DEBUGPRINT_TWO_EXT_INTRF  (0x02u)
    
#define DEBUGPRINT_ISR_SERVICE_MIDI_OUT \
            ((DEBUGPRINT_ENABLE_MIDI_API != 0u) && (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0) && \
             (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))

#define DEBUGPRINT_ISR_SERVICE_MIDI_IN \
            ((DEBUGPRINT_ENABLE_MIDI_API != 0u) && (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0))


/***************************************
*    External References
***************************************/

#if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF)
    #include "MIDI1_UART.h"
#endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF) */

#if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF)
    #include "MIDI2_UART.h"
#endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF) */


/***************************************
*    Data Structure Definition
***************************************/

/* The following structure is used to hold status information for
* building and parsing incoming MIDI messages. 
*/
typedef struct
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4u];   /* message buffer */
} DEBUGPRINT_MIDI_RX_STATUS;


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_midi
* @{
*/
#if defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && (DEBUGPRINT_ENABLE_MIDI_API != 0u)
    void DEBUGPRINT_MIDI_Init(void) ;

    #if (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0u)
        void DEBUGPRINT_MIDI_IN_Service(void) ;
        uint8 DEBUGPRINT_PutUsbMidiIn(uint8 ic, const uint8 midiMsg[], uint8 cable) ;
    #endif /* (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0u) */

    #if (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0u)
        void DEBUGPRINT_MIDI_OUT_Service(void) ;
    #endif /* (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0u) */
#endif /*  (DEBUGPRINT_ENABLE_MIDI_API != 0u) */


/*******************************************************************************
*   Callback Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Name: DEBUGPRINT_callbackLocalMidiEvent
****************************************************************************//**
*
*  This is a callback function that locally processes data received from the PC 
*  in main.c. You should implement this function if you want to use it. It is 
*  called from the USB output processing routine for each MIDI output event 
*  processed (decoded) from the output endpoint buffer. 
*
*  \param cable: Cable number
*  
*  \param midiMsg: Pointer to the 3-byte MIDI message
*
*
***************************************************************************/
void DEBUGPRINT_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg)
                                                     ;
/** @} midi */
                                                    
/***************************************
*           MIDI Constants.
***************************************/

/* Flag definitions for use with MIDI device inquiry */
#define DEBUGPRINT_INQ_SYSEX_FLAG             (0x01u)
#define DEBUGPRINT_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define DEBUGPRINT_CIN_MASK                   (0x0Fu)
#define DEBUGPRINT_RESERVED0                  (0x00u)
#define DEBUGPRINT_RESERVED1                  (0x01u)
#define DEBUGPRINT_2BYTE_COMMON               (0x02u)
#define DEBUGPRINT_3BYTE_COMMON               (0x03u)
#define DEBUGPRINT_SYSEX                      (0x04u)
#define DEBUGPRINT_1BYTE_COMMON               (0x05u)
#define DEBUGPRINT_SYSEX_ENDS_WITH1           (0x05u)
#define DEBUGPRINT_SYSEX_ENDS_WITH2           (0x06u)
#define DEBUGPRINT_SYSEX_ENDS_WITH3           (0x07u)
#define DEBUGPRINT_NOTE_OFF                   (0x08u)
#define DEBUGPRINT_NOTE_ON                    (0x09u)
#define DEBUGPRINT_POLY_KEY_PRESSURE          (0x0Au)
#define DEBUGPRINT_CONTROL_CHANGE             (0x0Bu)
#define DEBUGPRINT_PROGRAM_CHANGE             (0x0Cu)
#define DEBUGPRINT_CHANNEL_PRESSURE           (0x0Du)
#define DEBUGPRINT_PITCH_BEND_CHANGE          (0x0Eu)
#define DEBUGPRINT_SINGLE_BYTE                (0x0Fu)

#define DEBUGPRINT_CABLE_MASK                 (0xF0u)
#define DEBUGPRINT_MIDI_CABLE_00              (0x00u)
#define DEBUGPRINT_MIDI_CABLE_01              (0x10u)

#define DEBUGPRINT_EVENT_BYTE0                (0x00u)
#define DEBUGPRINT_EVENT_BYTE1                (0x01u)
#define DEBUGPRINT_EVENT_BYTE2                (0x02u)
#define DEBUGPRINT_EVENT_BYTE3                (0x03u)
#define DEBUGPRINT_EVENT_LENGTH               (0x04u)

#define DEBUGPRINT_MIDI_STATUS_BYTE_MASK      (0x80u)
#define DEBUGPRINT_MIDI_STATUS_MASK           (0xF0u)
#define DEBUGPRINT_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define DEBUGPRINT_MIDI_NOTE_OFF              (0x80u)
#define DEBUGPRINT_MIDI_NOTE_ON               (0x90u)
#define DEBUGPRINT_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define DEBUGPRINT_MIDI_CONTROL_CHANGE        (0xB0u)
#define DEBUGPRINT_MIDI_PROGRAM_CHANGE        (0xC0u)
#define DEBUGPRINT_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define DEBUGPRINT_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define DEBUGPRINT_MIDI_SYSEX                 (0xF0u)
#define DEBUGPRINT_MIDI_EOSEX                 (0xF7u)
#define DEBUGPRINT_MIDI_QFM                   (0xF1u)
#define DEBUGPRINT_MIDI_SPP                   (0xF2u)
#define DEBUGPRINT_MIDI_SONGSEL               (0xF3u)
#define DEBUGPRINT_MIDI_TUNEREQ               (0xF6u)
#define DEBUGPRINT_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define DEBUGPRINT_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define DEBUGPRINT_MIDI_SYSEX_REALTIME        (0x7Fu)

/* ID of target device */
#define DEBUGPRINT_MIDI_SYSEX_ID_ALL          (0x7Fu)

/* Sub-ID#1*/
#define DEBUGPRINT_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define DEBUGPRINT_MIDI_SYSEX_GEN_MESSAGE     (0x09u)

/* Sub-ID#2*/
#define DEBUGPRINT_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define DEBUGPRINT_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define DEBUGPRINT_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define DEBUGPRINT_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

/* UART TX and RX interrupt priority. */
#if (CY_PSOC4)
    #define DEBUGPRINT_CUSTOM_UART_RX_PRIOR_NUM   (0x01u)
    #define DEBUGPRINT_CUSTOM_UART_TX_PRIOR_NUM   (0x02u)
#else
    #define DEBUGPRINT_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)
    #define DEBUGPRINT_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#endif /* (CYPSOC4) */


/***************************************
*    Private Function Prototypes
***************************************/

void DEBUGPRINT_PrepareInBuffer(uint8 ic, const uint8 srcBuff[], uint8 eventLen, uint8 cable)
                                                                ;
#if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF)
    void  DEBUGPRINT_MIDI_InitInterface(void)             ;
    uint8 DEBUGPRINT_ProcessMidiIn(uint8 mData, DEBUGPRINT_MIDI_RX_STATUS *rxStat)
                                                                ;
    uint8 DEBUGPRINT_MIDI1_GetEvent(void)                 ;
    void  DEBUGPRINT_MIDI1_ProcessUsbOut(const uint8 epBuf[])
                                                                ;

    #if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF)
        uint8 DEBUGPRINT_MIDI2_GetEvent(void)             ;
        void  DEBUGPRINT_MIDI2_ProcessUsbOut(const uint8 epBuf[])
                                                                ;
    #endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF) */
#endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF) */


/***************************************
*     Vars with External Linkage
***************************************/

#if defined(DEBUGPRINT_ENABLE_MIDI_STREAMING)

#if (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0)
    #if (DEBUGPRINT_MIDI_IN_BUFF_SIZE >= 256)
/**
* \addtogroup group_midi
* @{
*/  
        extern volatile uint16 DEBUGPRINT_midiInPointer;                       /* Input endpoint buffer pointer */
/** @} midi*/
    #else
        extern volatile uint8 DEBUGPRINT_midiInPointer;                        /* Input endpoint buffer pointer */
    #endif /* (DEBUGPRINT_MIDI_IN_BUFF_SIZE >=256) */
/**
* \addtogroup group_midi
* @{
*/  
    extern volatile uint8 DEBUGPRINT_midi_in_ep;                               /* Input endpoint number */
    extern uint8 DEBUGPRINT_midiInBuffer[DEBUGPRINT_MIDI_IN_BUFF_SIZE];  /* Input endpoint buffer */
#endif /* (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0) */

#if (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0)
    extern volatile uint8 DEBUGPRINT_midi_out_ep;                               /* Output endpoint number */
    extern uint8 DEBUGPRINT_midiOutBuffer[DEBUGPRINT_MIDI_OUT_BUFF_SIZE]; /* Output endpoint buffer */
#endif /* (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0) */

#if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF)
    extern volatile uint8 DEBUGPRINT_MIDI1_InqFlags;                            /* Device inquiry flag */
    
    #if (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF)
        extern volatile uint8 DEBUGPRINT_MIDI2_InqFlags;                        /* Device inquiry flag */
    #endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_TWO_EXT_INTRF) */
#endif /* (DEBUGPRINT_MIDI_EXT_MODE >= DEBUGPRINT_ONE_EXT_INTRF) */
/** @} midi */
#endif /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define DEBUGPRINT_MIDI_EP_Init           DEBUGPRINT_MIDI_Init
#define DEBUGPRINT_MIDI_OUT_EP_Service    DEBUGPRINT_MIDI_OUT_Service

#endif /* (CY_USBFS_DEBUGPRINT_midi_H) */


/* [] END OF FILE */
