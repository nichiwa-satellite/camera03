/***************************************************************************//**
* \file .h
* \version 3.10
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_DEBUGPRINT_pvt_H)
#define CY_USBFS_DEBUGPRINT_pvt_H

#include "DEBUGPRINT.h"
   
#ifdef DEBUGPRINT_ENABLE_AUDIO_CLASS
    #include "DEBUGPRINT_audio.h"
#endif /* DEBUGPRINT_ENABLE_AUDIO_CLASS */

#ifdef DEBUGPRINT_ENABLE_CDC_CLASS
    #include "DEBUGPRINT_cdc.h"
#endif /* DEBUGPRINT_ENABLE_CDC_CLASS */

#if (DEBUGPRINT_ENABLE_MIDI_CLASS)
    #include "DEBUGPRINT_midi.h"
#endif /* (DEBUGPRINT_ENABLE_MIDI_CLASS) */

#if (DEBUGPRINT_ENABLE_MSC_CLASS)
    #include "DEBUGPRINT_msc.h"
#endif /* (DEBUGPRINT_ENABLE_MSC_CLASS) */

#if (DEBUGPRINT_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u))
            #include "DEBUGPRINT_EP_DMA_Done_isr.h"
            #include "DEBUGPRINT_EP8_DMA_Done_SR.h"
            #include "DEBUGPRINT_EP17_DMA_Done_SR.h"
        #endif /* ((DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

#if (DEBUGPRINT_DMA1_ACTIVE)
    #include "DEBUGPRINT_ep1_dma.h"
    #define DEBUGPRINT_EP1_DMA_CH     (DEBUGPRINT_ep1_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA1_ACTIVE) */

#if (DEBUGPRINT_DMA2_ACTIVE)
    #include "DEBUGPRINT_ep2_dma.h"
    #define DEBUGPRINT_EP2_DMA_CH     (DEBUGPRINT_ep2_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA2_ACTIVE) */

#if (DEBUGPRINT_DMA3_ACTIVE)
    #include "DEBUGPRINT_ep3_dma.h"
    #define DEBUGPRINT_EP3_DMA_CH     (DEBUGPRINT_ep3_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA3_ACTIVE) */

#if (DEBUGPRINT_DMA4_ACTIVE)
    #include "DEBUGPRINT_ep4_dma.h"
    #define DEBUGPRINT_EP4_DMA_CH     (DEBUGPRINT_ep4_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA4_ACTIVE) */

#if (DEBUGPRINT_DMA5_ACTIVE)
    #include "DEBUGPRINT_ep5_dma.h"
    #define DEBUGPRINT_EP5_DMA_CH     (DEBUGPRINT_ep5_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA5_ACTIVE) */

#if (DEBUGPRINT_DMA6_ACTIVE)
    #include "DEBUGPRINT_ep6_dma.h"
    #define DEBUGPRINT_EP6_DMA_CH     (DEBUGPRINT_ep6_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA6_ACTIVE) */

#if (DEBUGPRINT_DMA7_ACTIVE)
    #include "DEBUGPRINT_ep7_dma.h"
    #define DEBUGPRINT_EP7_DMA_CH     (DEBUGPRINT_ep7_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA7_ACTIVE) */

#if (DEBUGPRINT_DMA8_ACTIVE)
    #include "DEBUGPRINT_ep8_dma.h"
    #define DEBUGPRINT_EP8_DMA_CH     (DEBUGPRINT_ep8_dma_CHANNEL)
#endif /* (DEBUGPRINT_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE DEBUGPRINT_DEVICE0_DESCR[18u];
extern const uint8 CYCODE DEBUGPRINT_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE DEBUGPRINT_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE DEBUGPRINT_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_DEBUGPRINT_LUT CYCODE DEBUGPRINT_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_DEBUGPRINT_LUT CYCODE DEBUGPRINT_DEVICE0_TABLE[3u];
extern const T_DEBUGPRINT_LUT CYCODE DEBUGPRINT_TABLE[1u];
extern const uint8 CYCODE DEBUGPRINT_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE DEBUGPRINT_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE DEBUGPRINT_MSOS_DESCRIPTOR[DEBUGPRINT_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE DEBUGPRINT_MSOS_CONFIGURATION_DESCR[DEBUGPRINT_MSOS_CONF_DESCR_LENGTH];
#if defined(DEBUGPRINT_ENABLE_IDSN_STRING)
    extern uint8 DEBUGPRINT_idSerialNumberStringDescriptor[DEBUGPRINT_IDSN_DESCR_LENGTH];
#endif /* (DEBUGPRINT_ENABLE_IDSN_STRING) */

extern volatile uint8 DEBUGPRINT_interfaceNumber;
extern volatile uint8 DEBUGPRINT_interfaceSetting[DEBUGPRINT_MAX_INTERFACES_NUMBER];
extern volatile uint8 DEBUGPRINT_interfaceSettingLast[DEBUGPRINT_MAX_INTERFACES_NUMBER];
extern volatile uint8 DEBUGPRINT_deviceAddress;
extern volatile uint8 DEBUGPRINT_interfaceStatus[DEBUGPRINT_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *DEBUGPRINT_interfaceClass;

extern volatile T_DEBUGPRINT_EP_CTL_BLOCK DEBUGPRINT_EP[DEBUGPRINT_MAX_EP];
extern volatile T_DEBUGPRINT_TD DEBUGPRINT_currentTD;

#if (DEBUGPRINT_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 DEBUGPRINT_DmaChan[DEBUGPRINT_MAX_EP];
    #else
        extern uint8 DEBUGPRINT_DmaChan[DEBUGPRINT_MAX_EP];
        extern uint8 DEBUGPRINT_DmaTd  [DEBUGPRINT_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  DEBUGPRINT_DmaEpBurstCnt   [DEBUGPRINT_MAX_EP];
    extern uint8  DEBUGPRINT_DmaEpLastBurstEl[DEBUGPRINT_MAX_EP];

    extern uint8  DEBUGPRINT_DmaEpBurstCntBackup  [DEBUGPRINT_MAX_EP];
    extern uint32 DEBUGPRINT_DmaEpBufferAddrBackup[DEBUGPRINT_MAX_EP];
    
    extern const uint8 DEBUGPRINT_DmaReqOut     [DEBUGPRINT_MAX_EP];    
    extern const uint8 DEBUGPRINT_DmaBurstEndOut[DEBUGPRINT_MAX_EP];
#else
    #if (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)
        extern uint8 DEBUGPRINT_DmaNextTd[DEBUGPRINT_MAX_EP];
        extern volatile uint16 DEBUGPRINT_inLength [DEBUGPRINT_MAX_EP];
        extern volatile uint8  DEBUGPRINT_inBufFull[DEBUGPRINT_MAX_EP];
        extern const uint8 DEBUGPRINT_epX_TD_TERMOUT_EN[DEBUGPRINT_MAX_EP];
        extern const uint8 *DEBUGPRINT_inDataPointer[DEBUGPRINT_MAX_EP];
    #endif /* (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 DEBUGPRINT_ep0Toggle;
extern volatile uint8 DEBUGPRINT_lastPacketSize;
extern volatile uint8 DEBUGPRINT_ep0Mode;
extern volatile uint8 DEBUGPRINT_ep0Count;
extern volatile uint16 DEBUGPRINT_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  DEBUGPRINT_ReInitComponent(void)            ;
void  DEBUGPRINT_HandleSetup(void)                ;
void  DEBUGPRINT_HandleIN(void)                   ;
void  DEBUGPRINT_HandleOUT(void)                  ;
void  DEBUGPRINT_LoadEP0(void)                    ;
uint8 DEBUGPRINT_InitControlRead(void)            ;
uint8 DEBUGPRINT_InitControlWrite(void)           ;
void  DEBUGPRINT_ControlReadDataStage(void)       ;
void  DEBUGPRINT_ControlReadStatusStage(void)     ;
void  DEBUGPRINT_ControlReadPrematureStatus(void) ;
uint8 DEBUGPRINT_InitControlWrite(void)           ;
uint8 DEBUGPRINT_InitZeroLengthControlTransfer(void) ;
void  DEBUGPRINT_ControlWriteDataStage(void)      ;
void  DEBUGPRINT_ControlWriteStatusStage(void)    ;
void  DEBUGPRINT_ControlWritePrematureStatus(void);
uint8 DEBUGPRINT_InitNoDataControlTransfer(void)  ;
void  DEBUGPRINT_NoDataControlStatusStage(void)   ;
void  DEBUGPRINT_InitializeStatusBlock(void)      ;
void  DEBUGPRINT_UpdateStatusBlock(uint8 completionCode) ;
uint8 DEBUGPRINT_DispatchClassRqst(void)          ;

void DEBUGPRINT_Config(uint8 clearAltSetting) ;
void DEBUGPRINT_ConfigAltChanged(void)        ;
void DEBUGPRINT_ConfigReg(void)               ;
void DEBUGPRINT_EpStateInit(void)             ;


const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetConfigTablePtr(uint8 confIndex);
const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetDeviceTablePtr(void)           ;
#if (DEBUGPRINT_BOS_ENABLE)
    const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetBOSPtr(void)               ;
#endif /* (DEBUGPRINT_BOS_ENABLE) */
const uint8 CYCODE *DEBUGPRINT_GetInterfaceClassTablePtr(void)                    ;uint8 DEBUGPRINT_ClearEndpointHalt(void)                                          ;
uint8 DEBUGPRINT_SetEndpointHalt(void)                                            ;
uint8 DEBUGPRINT_ValidateAlternateSetting(void)                                   ;

void DEBUGPRINT_SaveConfig(void)      ;
void DEBUGPRINT_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u))
        void DEBUGPRINT_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(DEBUGPRINT_ENABLE_IDSN_STRING)
    void DEBUGPRINT_ReadDieID(uint8 descr[])  ;
#endif /* DEBUGPRINT_ENABLE_IDSN_STRING */

#if defined(DEBUGPRINT_ENABLE_HID_CLASS)
    uint8 DEBUGPRINT_DispatchHIDClassRqst(void) ;
#endif /* (DEBUGPRINT_ENABLE_HID_CLASS) */

#if defined(DEBUGPRINT_ENABLE_AUDIO_CLASS)
    uint8 DEBUGPRINT_DispatchAUDIOClassRqst(void) ;
#endif /* (DEBUGPRINT_ENABLE_AUDIO_CLASS) */

#if defined(DEBUGPRINT_ENABLE_CDC_CLASS)
    uint8 DEBUGPRINT_DispatchCDCClassRqst(void) ;
#endif /* (DEBUGPRINT_ENABLE_CDC_CLASS) */

#if (DEBUGPRINT_ENABLE_MSC_CLASS)
    #if (DEBUGPRINT_HANDLE_MSC_REQUESTS)
        uint8 DEBUGPRINT_DispatchMSCClassRqst(void) ;
    #endif /* (DEBUGPRINT_HANDLE_MSC_REQUESTS) */
#endif /* (DEBUGPRINT_ENABLE_MSC_CLASS */

CY_ISR_PROTO(DEBUGPRINT_EP_0_ISR);
CY_ISR_PROTO(DEBUGPRINT_BUS_RESET_ISR);

#if (DEBUGPRINT_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_SOF_ISR);
#endif /* (DEBUGPRINT_SOF_ISR_ACTIVE) */

#if (DEBUGPRINT_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_1_ISR);
#endif /* (DEBUGPRINT_EP1_ISR_ACTIVE) */

#if (DEBUGPRINT_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_2_ISR);
#endif /* (DEBUGPRINT_EP2_ISR_ACTIVE) */

#if (DEBUGPRINT_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_3_ISR);
#endif /* (DEBUGPRINT_EP3_ISR_ACTIVE) */

#if (DEBUGPRINT_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_4_ISR);
#endif /* (DEBUGPRINT_EP4_ISR_ACTIVE) */

#if (DEBUGPRINT_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_5_ISR);
#endif /* (DEBUGPRINT_EP5_ISR_ACTIVE) */

#if (DEBUGPRINT_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_6_ISR);
#endif /* (DEBUGPRINT_EP6_ISR_ACTIVE) */

#if (DEBUGPRINT_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_7_ISR);
#endif /* (DEBUGPRINT_EP7_ISR_ACTIVE) */

#if (DEBUGPRINT_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_EP_8_ISR);
#endif /* (DEBUGPRINT_EP8_ISR_ACTIVE) */

#if (DEBUGPRINT_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(DEBUGPRINT_ARB_ISR);
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

#if (DEBUGPRINT_DP_ISR_ACTIVE)
    CY_ISR_PROTO(DEBUGPRINT_DP_ISR);
#endif /* (DEBUGPRINT_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(DEBUGPRINT_INTR_HI_ISR);
    CY_ISR_PROTO(DEBUGPRINT_INTR_MED_ISR);
    CY_ISR_PROTO(DEBUGPRINT_INTR_LO_ISR);
    #if (DEBUGPRINT_LPM_ACTIVE)
        CY_ISR_PROTO(DEBUGPRINT_LPM_ISR);
    #endif /* (DEBUGPRINT_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (DEBUGPRINT_DMA1_ACTIVE)
        void DEBUGPRINT_EP1_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA1_ACTIVE) */

    #if (DEBUGPRINT_DMA2_ACTIVE)
        void DEBUGPRINT_EP2_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA2_ACTIVE) */

    #if (DEBUGPRINT_DMA3_ACTIVE)
        void DEBUGPRINT_EP3_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA3_ACTIVE) */

    #if (DEBUGPRINT_DMA4_ACTIVE)
        void DEBUGPRINT_EP4_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA4_ACTIVE) */

    #if (DEBUGPRINT_DMA5_ACTIVE)
        void DEBUGPRINT_EP5_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA5_ACTIVE) */

    #if (DEBUGPRINT_DMA6_ACTIVE)
        void DEBUGPRINT_EP6_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA6_ACTIVE) */

    #if (DEBUGPRINT_DMA7_ACTIVE)
        void DEBUGPRINT_EP7_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA7_ACTIVE) */

    #if (DEBUGPRINT_DMA8_ACTIVE)
        void DEBUGPRINT_EP8_DMA_DONE_ISR(void);
    #endif /* (DEBUGPRINT_DMA8_ACTIVE) */

#else
    #if (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(DEBUGPRINT_EP_DMA_DONE_ISR);
    #endif /* (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 DEBUGPRINT_HandleStandardRqst(void) ;
uint8 DEBUGPRINT_DispatchClassRqst(void)  ;
uint8 DEBUGPRINT_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(DEBUGPRINT_ENABLE_HID_CLASS)
    void DEBUGPRINT_FindReport(void)            ;
    void DEBUGPRINT_FindReportDescriptor(void)  ;
    void DEBUGPRINT_FindHidClassDecriptor(void) ;
#endif /* DEBUGPRINT_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(DEBUGPRINT_ENABLE_MIDI_STREAMING)
    void DEBUGPRINT_MIDI_IN_EP_Service(void)  ;
#endif /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(DEBUGPRINT_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_DEBUGPRINT_cdc_notification;

    uint8 DEBUGPRINT_GetInterfaceComPort(uint8 interface) ;
    uint8 DEBUGPRINT_Cdc_EpInit( const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  DEBUGPRINT_cdc_dataInEpList[DEBUGPRINT_MAX_MULTI_COM_NUM];
    extern volatile uint8  DEBUGPRINT_cdc_dataOutEpList[DEBUGPRINT_MAX_MULTI_COM_NUM];
    extern volatile uint8  DEBUGPRINT_cdc_commInEpList[DEBUGPRINT_MAX_MULTI_COM_NUM];
#endif /* (DEBUGPRINT_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_DEBUGPRINT_pvt_H */


/* [] END OF FILE */
