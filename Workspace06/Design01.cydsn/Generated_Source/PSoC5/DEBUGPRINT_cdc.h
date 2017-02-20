/***************************************************************************//**
* \file DEBUGPRINT_cdc.h
* \version 3.10
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  CDC class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_DEBUGPRINT_cdc_H)
#define CY_USBFS_DEBUGPRINT_cdc_H

#include "DEBUGPRINT.h"


/*******************************************************************************
* Prototypes of the DEBUGPRINT_cdc API.
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
#if (DEBUGPRINT_ENABLE_CDC_CLASS_API != 0u)
    uint8 DEBUGPRINT_CDC_Init(void)            ;
    void DEBUGPRINT_PutData(const uint8* pData, uint16 length) ;
    void DEBUGPRINT_PutString(const char8 string[])            ;
    void DEBUGPRINT_PutChar(char8 txDataByte) ;
    void DEBUGPRINT_PutCRLF(void)             ;
    uint16 DEBUGPRINT_GetCount(void)          ;
    uint8  DEBUGPRINT_CDCIsReady(void)        ;
    uint8  DEBUGPRINT_DataIsReady(void)       ;
    uint16 DEBUGPRINT_GetData(uint8* pData, uint16 length)     ;
    uint16 DEBUGPRINT_GetAll(uint8* pData)    ;
    uint8  DEBUGPRINT_GetChar(void)           ;
    uint8  DEBUGPRINT_IsLineChanged(void)     ;
    uint32 DEBUGPRINT_GetDTERate(void)        ;
    uint8  DEBUGPRINT_GetCharFormat(void)     ;
    uint8  DEBUGPRINT_GetParityType(void)     ;
    uint8  DEBUGPRINT_GetDataBits(void)       ;
    uint16 DEBUGPRINT_GetLineControl(void)    ;
    void DEBUGPRINT_SendSerialState (uint16 serialState) ;
    uint16 DEBUGPRINT_GetSerialState (void)   ;
    void DEBUGPRINT_SetComPort (uint8 comNumber) ;
    uint8 DEBUGPRINT_GetComPort (void)        ;
    uint8 DEBUGPRINT_NotificationIsReady(void) ;

#endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS_API) */
/** @} cdc */

/*******************************************************************************
*  Constants for DEBUGPRINT_cdc API.
*******************************************************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define DEBUGPRINT_CDC_SET_LINE_CODING        (0x20u)
#define DEBUGPRINT_CDC_GET_LINE_CODING        (0x21u)
#define DEBUGPRINT_CDC_SET_CONTROL_LINE_STATE (0x22u)

/*PSTN Subclass Specific Notifications (CDC ver 1.2 Table 30)*/
#define DEBUGPRINT_SERIAL_STATE               (0x20u)

#define DEBUGPRINT_LINE_CODING_CHANGED        (0x01u)
#define DEBUGPRINT_LINE_CONTROL_CHANGED       (0x02u)

#define DEBUGPRINT_1_STOPBIT                  (0x00u)
#define DEBUGPRINT_1_5_STOPBITS               (0x01u)
#define DEBUGPRINT_2_STOPBITS                 (0x02u)

#define DEBUGPRINT_PARITY_NONE                (0x00u)
#define DEBUGPRINT_PARITY_ODD                 (0x01u)
#define DEBUGPRINT_PARITY_EVEN                (0x02u)
#define DEBUGPRINT_PARITY_MARK                (0x03u)
#define DEBUGPRINT_PARITY_SPACE               (0x04u)

#define DEBUGPRINT_LINE_CODING_SIZE           (0x07u)
#define DEBUGPRINT_LINE_CODING_RATE           (0x00u)
#define DEBUGPRINT_LINE_CODING_STOP_BITS      (0x04u)
#define DEBUGPRINT_LINE_CODING_PARITY         (0x05u)
#define DEBUGPRINT_LINE_CODING_DATA_BITS      (0x06u)

#define DEBUGPRINT_LINE_CONTROL_DTR           (0x01u)
#define DEBUGPRINT_LINE_CONTROL_RTS           (0x02u)

#define DEBUGPRINT_MAX_MULTI_COM_NUM          (2u) 

#define DEBUGPRINT_COM_PORT1                  (0u) 
#define DEBUGPRINT_COM_PORT2                  (1u) 

#define DEBUGPRINT_SUCCESS                    (0u)
#define DEBUGPRINT_FAILURE                    (1u)

#define DEBUGPRINT_SERIAL_STATE_SIZE          (10u)

/* SerialState constants*/
#define DEBUGPRINT_SERIAL_STATE_REQUEST_TYPE  (0xA1u)
#define DEBUGPRINT_SERIAL_STATE_LENGTH        (0x2u)

/*******************************************************************************
* External data references
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
extern volatile uint8  DEBUGPRINT_linesCoding[DEBUGPRINT_MAX_MULTI_COM_NUM][DEBUGPRINT_LINE_CODING_SIZE];
extern volatile uint8  DEBUGPRINT_linesChanged[DEBUGPRINT_MAX_MULTI_COM_NUM];
extern volatile uint16 DEBUGPRINT_linesControlBitmap[DEBUGPRINT_MAX_MULTI_COM_NUM];
extern volatile uint16 DEBUGPRINT_serialStateBitmap[DEBUGPRINT_MAX_MULTI_COM_NUM];
extern volatile uint8  DEBUGPRINT_cdcDataInEp[DEBUGPRINT_MAX_MULTI_COM_NUM];
extern volatile uint8  DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_MAX_MULTI_COM_NUM];
extern volatile uint8  DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** @} cdc */

/*******************************************************************************
* The following code is DEPRECATED and
* must not be used.
*******************************************************************************/


#define DEBUGPRINT_lineCoding             DEBUGPRINT_linesCoding[0]
#define DEBUGPRINT_lineChanged            DEBUGPRINT_linesChanged[0]
#define DEBUGPRINT_lineControlBitmap      DEBUGPRINT_linesControlBitmap[0]
#define DEBUGPRINT_cdc_data_in_ep         DEBUGPRINT_cdcDataInEp[0]
#define DEBUGPRINT_cdc_data_out_ep        DEBUGPRINT_cdcDataOutEp[0]

#endif /* (CY_USBFS_DEBUGPRINT_cdc_H) */


/* [] END OF FILE */
