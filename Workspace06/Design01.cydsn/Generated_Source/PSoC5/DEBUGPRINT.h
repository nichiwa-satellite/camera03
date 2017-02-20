/***************************************************************************//**
* \file  DEBUGPRINT.h
* \version 3.10
*
* \brief
*  This file provides function prototypes and constants for the USBFS component. 
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_DEBUGPRINT_H)
#define CY_USBFS_DEBUGPRINT_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */

/***************************************
* Enumerated Types and Parameters
***************************************/

/* USB IP memory management options. */
#define DEBUGPRINT__EP_MANUAL    (0u)
#define DEBUGPRINT__EP_DMAMANUAL (1u)
#define DEBUGPRINT__EP_DMAAUTO   (2u)

/* USB IP memory allocation options. */
#define DEBUGPRINT__MA_STATIC    (0u)
#define DEBUGPRINT__MA_DYNAMIC   (1u)


/***************************************
*    Initial Parameter Constants
***************************************/

#define DEBUGPRINT_NUM_DEVICES                 (1u)
#define DEBUGPRINT_ENABLE_CDC_CLASS            
#define DEBUGPRINT_ENABLE_MIDI_CLASS           (0u)
#define DEBUGPRINT_ENABLE_MSC_CLASS            (0u)
#define DEBUGPRINT_BOS_ENABLE                  (0u)
#define DEBUGPRINT_ENABLE_DESCRIPTOR_STRINGS   
#define DEBUGPRINT_ENABLE_SN_STRING            
#define DEBUGPRINT_ENABLE_IDSN_STRING          
#define DEBUGPRINT_ENABLE_STRINGS              
#define DEBUGPRINT_MAX_REPORTID_NUMBER         (0u)

#define DEBUGPRINT_MON_VBUS               (0u)
#define DEBUGPRINT_EXTERN_VBUS            (0u)
#define DEBUGPRINT_POWER_PAD_VBUS         (0u)
#define DEBUGPRINT_EXTERN_VND             (0u)
#define DEBUGPRINT_EXTERN_CLS             (0u)
#define DEBUGPRINT_MAX_INTERFACES_NUMBER  (2u)
#define DEBUGPRINT_EP_MM                  (0u)
#define DEBUGPRINT_EP_MA                  (0u)
#define DEBUGPRINT_ENABLE_BATT_CHARG_DET  (0u)
#define DEBUGPRINT_GEN_16BITS_EP_ACCESS   (1u)

/* Enable Class APIs: MIDI, CDC, MSC. */         
#define DEBUGPRINT_ENABLE_CDC_CLASS_API   (0u != (1u))

/* General parameters */
#define DEBUGPRINT_EP_ALLOC_STATIC            (DEBUGPRINT_EP_MA == DEBUGPRINT__MA_STATIC)
#define DEBUGPRINT_EP_ALLOC_DYNAMIC           (DEBUGPRINT_EP_MA == DEBUGPRINT__MA_DYNAMIC)
#define DEBUGPRINT_EP_MANAGEMENT_MANUAL       (DEBUGPRINT_EP_MM == DEBUGPRINT__EP_MANUAL)
#define DEBUGPRINT_EP_MANAGEMENT_DMA          (DEBUGPRINT_EP_MM != DEBUGPRINT__EP_MANUAL)
#define DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL   (DEBUGPRINT_EP_MM == DEBUGPRINT__EP_DMAMANUAL)
#define DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO     (DEBUGPRINT_EP_MM == DEBUGPRINT__EP_DMAAUTO)
#define DEBUGPRINT_BATT_CHARG_DET_ENABLE      (CY_PSOC4 && (0u != DEBUGPRINT_ENABLE_BATT_CHARG_DET))
#define DEBUGPRINT_16BITS_EP_ACCESS_ENABLE    (CY_PSOC4 && (0u != DEBUGPRINT_GEN_16BITS_EP_ACCESS))
#define DEBUGPRINT_VBUS_MONITORING_ENABLE     (0u != DEBUGPRINT_MON_VBUS)
#define DEBUGPRINT_VBUS_MONITORING_INTERNAL   (0u == DEBUGPRINT_EXTERN_VBUS)
#define DEBUGPRINT_VBUS_POWER_PAD_ENABLE      (0u != DEBUGPRINT_POWER_PAD_VBUS)

/* Control endpoints availability */
#define DEBUGPRINT_SOF_ISR_REMOVE       (0u)
#define DEBUGPRINT_BUS_RESET_ISR_REMOVE (0u)
#define DEBUGPRINT_EP0_ISR_REMOVE       (0u)
#define DEBUGPRINT_ARB_ISR_REMOVE       (0u)
#define DEBUGPRINT_DP_ISR_REMOVE        (0u)
#define DEBUGPRINT_LPM_REMOVE           (1u)
#define DEBUGPRINT_SOF_ISR_ACTIVE       ((0u == DEBUGPRINT_SOF_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_BUS_RESET_ISR_ACTIVE ((0u == DEBUGPRINT_BUS_RESET_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP0_ISR_ACTIVE       ((0u == DEBUGPRINT_EP0_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_ARB_ISR_ACTIVE       ((0u == DEBUGPRINT_ARB_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DP_ISR_ACTIVE        ((0u == DEBUGPRINT_DP_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_LPM_ACTIVE           ((CY_PSOC4 && (0u == DEBUGPRINT_LPM_REMOVE)) ? 1u: 0u)

/* Data endpoints availability */
#define DEBUGPRINT_EP1_ISR_REMOVE     (0u)
#define DEBUGPRINT_EP2_ISR_REMOVE     (0u)
#define DEBUGPRINT_EP3_ISR_REMOVE     (0u)
#define DEBUGPRINT_EP4_ISR_REMOVE     (1u)
#define DEBUGPRINT_EP5_ISR_REMOVE     (1u)
#define DEBUGPRINT_EP6_ISR_REMOVE     (1u)
#define DEBUGPRINT_EP7_ISR_REMOVE     (1u)
#define DEBUGPRINT_EP8_ISR_REMOVE     (1u)
#define DEBUGPRINT_EP1_ISR_ACTIVE     ((0u == DEBUGPRINT_EP1_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP2_ISR_ACTIVE     ((0u == DEBUGPRINT_EP2_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP3_ISR_ACTIVE     ((0u == DEBUGPRINT_EP3_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP4_ISR_ACTIVE     ((0u == DEBUGPRINT_EP4_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP5_ISR_ACTIVE     ((0u == DEBUGPRINT_EP5_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP6_ISR_ACTIVE     ((0u == DEBUGPRINT_EP6_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP7_ISR_ACTIVE     ((0u == DEBUGPRINT_EP7_ISR_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_EP8_ISR_ACTIVE     ((0u == DEBUGPRINT_EP8_ISR_REMOVE) ? 1u: 0u)

#define DEBUGPRINT_EP_DMA_AUTO_OPT    ((CY_PSOC4) ? (1u) : (0u))
#define DEBUGPRINT_DMA1_REMOVE        (1u)
#define DEBUGPRINT_DMA2_REMOVE        (1u)
#define DEBUGPRINT_DMA3_REMOVE        (1u)
#define DEBUGPRINT_DMA4_REMOVE        (1u)
#define DEBUGPRINT_DMA5_REMOVE        (1u)
#define DEBUGPRINT_DMA6_REMOVE        (1u)
#define DEBUGPRINT_DMA7_REMOVE        (1u)
#define DEBUGPRINT_DMA8_REMOVE        (1u)
#define DEBUGPRINT_DMA1_ACTIVE        ((0u == DEBUGPRINT_DMA1_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA2_ACTIVE        ((0u == DEBUGPRINT_DMA2_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA3_ACTIVE        ((0u == DEBUGPRINT_DMA3_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA4_ACTIVE        ((0u == DEBUGPRINT_DMA4_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA5_ACTIVE        ((0u == DEBUGPRINT_DMA5_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA6_ACTIVE        ((0u == DEBUGPRINT_DMA6_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA7_ACTIVE        ((0u == DEBUGPRINT_DMA7_REMOVE) ? 1u: 0u)
#define DEBUGPRINT_DMA8_ACTIVE        ((0u == DEBUGPRINT_DMA8_REMOVE) ? 1u: 0u)


/***************************************
*    Data Structures Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_DEBUGPRINT_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_DEBUGPRINT_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_DEBUGPRINT_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_DEBUGPRINT_XFER_STATUS_BLOCK *pStatusBlock;
} T_DEBUGPRINT_TD;

typedef struct
{
    uint8   c;
    const void *p_list;
} T_DEBUGPRINT_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
#if (CY_PSOC4)
    uint8 intrSeiMask;
#endif /* (CY_PSOC4) */
} DEBUGPRINT_BACKUP_STRUCT;

/* Number of endpoint 0 data registers. */
#define DEBUGPRINT_EP0_DR_MAPPED_REG_CNT  (8u)

/* Structure to access data registers for EP0. */
typedef struct
{
    uint8 epData[DEBUGPRINT_EP0_DR_MAPPED_REG_CNT];
} DEBUGPRINT_ep0_data_struct;

/* Number of SIE endpoint registers group. */
#define DEBUGPRINT_SIE_EP_REG_SIZE   (DEBUGPRINT_USB__SIE_EP1_CR0 - \
                                            DEBUGPRINT_USB__SIE_EP1_CNT0)

/* Size of gap between SIE endpoint registers groups. */
#define DEBUGPRINT_SIE_GAP_CNT        (((DEBUGPRINT_USB__SIE_EP2_CNT0 - \
                                             (DEBUGPRINT_USB__SIE_EP1_CNT0 + \
                                              DEBUGPRINT_SIE_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to SIE registers for endpoint. */
typedef struct
{
    uint8 epCnt0;
    uint8 epCnt1;
    uint8 epCr0;
    uint8 gap[DEBUGPRINT_SIE_GAP_CNT];
} DEBUGPRINT_sie_ep_struct;

/* Number of ARB endpoint registers group. */
#define DEBUGPRINT_ARB_EP_REG_SIZE    (DEBUGPRINT_USB__ARB_RW1_DR - \
                                             DEBUGPRINT_USB__ARB_EP1_CFG)

/* Size of gap between ARB endpoint registers groups. */
#define DEBUGPRINT_ARB_GAP_CNT        (((DEBUGPRINT_USB__ARB_EP2_CFG - \
                                             (DEBUGPRINT_USB__ARB_EP1_CFG + \
                                              DEBUGPRINT_ARB_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to ARB registers for endpoint. */
typedef struct
{
    uint8 epCfg;
    uint8 epIntEn;
    uint8 epSr;
    uint8 reserved;
    uint8 rwWa;
    uint8 rwWaMsb;
    uint8 rwRa;
    uint8 rwRaMsb;
    uint8 rwDr;
    uint8 gap[DEBUGPRINT_ARB_GAP_CNT];
} DEBUGPRINT_arb_ep_struct;

#if (CY_PSOC4)
    /* Number of ARB endpoint registers group (16-bits access). */
    #define DEBUGPRINT_ARB_EP_REG16_SIZE      (DEBUGPRINT_USB__ARB_RW1_DR16 - \
                                                     DEBUGPRINT_USB__ARB_RW1_WA16)

    /* Size of gap between ARB endpoint registers groups (16-bits access). */
    #define DEBUGPRINT_ARB_EP_REG16_GAP_CNT   (((DEBUGPRINT_USB__ARB_RW2_WA16 - \
                                                     (DEBUGPRINT_USB__ARB_RW1_WA16 + \
                                                      DEBUGPRINT_ARB_EP_REG16_SIZE)) / sizeof(reg8)) - 1u)

    /* Structure to access to ARB registers for endpoint (16-bits access). */
    typedef struct
    {
        uint8 rwWa16;
        uint8 reserved0;
        uint8 rwRa16;
        uint8 reserved1;
        uint8 rwDr16;
        uint8 gap[DEBUGPRINT_ARB_EP_REG16_GAP_CNT];
    } DEBUGPRINT_arb_ep_reg16_struct;
#endif /* (CY_PSOC4) */

/* Number of endpoint (takes to account that endpoints numbers are 1-8). */
#define DEBUGPRINT_NUMBER_EP  (9u)

/* Consoled SIE register groups for endpoints 1-8. */
typedef struct
{
    DEBUGPRINT_sie_ep_struct sieEp[DEBUGPRINT_NUMBER_EP];
} DEBUGPRINT_sie_eps_struct;

/* Consolidate ARB register groups for endpoints 1-8.*/
typedef struct
{
    DEBUGPRINT_arb_ep_struct arbEp[DEBUGPRINT_NUMBER_EP];
} DEBUGPRINT_arb_eps_struct;

#if (CY_PSOC4)
    /* Consolidate ARB register groups for endpoints 1-8 (16-bits access). */
    typedef struct
    {
        DEBUGPRINT_arb_ep_reg16_struct arbEp[DEBUGPRINT_NUMBER_EP];
    } DEBUGPRINT_arb_eps_reg16_struct;
#endif /* (CY_PSOC4) */


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void   DEBUGPRINT_InitComponent(uint8 device, uint8 mode) ;
void   DEBUGPRINT_Start(uint8 device, uint8 mode)         ;
void   DEBUGPRINT_Init(void)                              ;
void   DEBUGPRINT_Stop(void)                              ;
uint8  DEBUGPRINT_GetConfiguration(void)                  ;
uint8  DEBUGPRINT_IsConfigurationChanged(void)            ;
uint8  DEBUGPRINT_GetInterfaceSetting(uint8 interfaceNumber) ;
uint8  DEBUGPRINT_GetEPState(uint8 epNumber)              ;
uint16 DEBUGPRINT_GetEPCount(uint8 epNumber)              ;
void   DEBUGPRINT_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                ;
uint16 DEBUGPRINT_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                ;
void   DEBUGPRINT_EnableOutEP(uint8 epNumber)             ;
void   DEBUGPRINT_DisableOutEP(uint8 epNumber)            ;
void   DEBUGPRINT_Force(uint8 bState)                     ;
uint8  DEBUGPRINT_GetEPAckState(uint8 epNumber)           ;
void   DEBUGPRINT_SetPowerStatus(uint8 powerStatus)       ;
void   DEBUGPRINT_TerminateEP(uint8 epNumber)             ;

uint8 DEBUGPRINT_GetDeviceAddress(void) ;

void DEBUGPRINT_EnableSofInt(void)  ;
void DEBUGPRINT_DisableSofInt(void) ;


#if defined(DEBUGPRINT_ENABLE_FWSN_STRING)
    void   DEBUGPRINT_SerialNumString(uint8 snString[]) ;
#endif  /* DEBUGPRINT_ENABLE_FWSN_STRING */

#if (DEBUGPRINT_VBUS_MONITORING_ENABLE)
    uint8  DEBUGPRINT_VBusPresent(void) ;
#endif /*  (DEBUGPRINT_VBUS_MONITORING_ENABLE) */

#if (DEBUGPRINT_16BITS_EP_ACCESS_ENABLE)
    /* PSoC4 specific functions for 16-bit data register access. */
    void   DEBUGPRINT_LoadInEP16 (uint8 epNumber, const uint8 pData[], uint16 length);
    uint16 DEBUGPRINT_ReadOutEP16(uint8 epNumber,       uint8 pData[], uint16 length);
#endif /* (DEBUGPRINT_16BITS_EP_ACCESS_ENABLE) */

#if (DEBUGPRINT_BATT_CHARG_DET_ENABLE)
        uint8 DEBUGPRINT_Bcd_DetectPortType(void);
#endif /* (DEBUGPRINT_BATT_CHARG_DET_ENABLE) */

#if (DEBUGPRINT_EP_MANAGEMENT_DMA)
    void DEBUGPRINT_InitEP_DMA(uint8 epNumber, const uint8 *pData) ;   
    void DEBUGPRINT_Stop_DMA(uint8 epNumber) ;
/** @} general */ 
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

/**
* \addtogroup group_power
* @{
*/
uint8  DEBUGPRINT_CheckActivity(void) ;
void   DEBUGPRINT_Suspend(void)       ;
void   DEBUGPRINT_Resume(void)        ;
uint8  DEBUGPRINT_RWUEnabled(void)    ;

#if (DEBUGPRINT_LPM_ACTIVE)
    uint32 DEBUGPRINT_Lpm_GetBeslValue(void);
    uint32 DEBUGPRINT_Lpm_RemoteWakeUpAllowed(void);
    void   DEBUGPRINT_Lpm_SetResponse(uint32 response);
    uint32 DEBUGPRINT_Lpm_GetResponse(void);
#endif /* (DEBUGPRINT_LPM_ACTIVE) */

/** @} power */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUGPRINT) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
/**
* \addtogroup group_bootloader
* @{
*/
    void DEBUGPRINT_CyBtldrCommStart(void)        ;
    void DEBUGPRINT_CyBtldrCommStop(void)         ;
    void DEBUGPRINT_CyBtldrCommReset(void)        ;
    cystatus DEBUGPRINT_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
    cystatus DEBUGPRINT_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
/** @} bootloader */

    #define DEBUGPRINT_BTLDR_OUT_EP   (0x01u)
    #define DEBUGPRINT_BTLDR_IN_EP    (0x02u)

    #define DEBUGPRINT_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* Endpoint 1 (OUT) buffer size. */
    #define DEBUGPRINT_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* Endpoint 2 (IN)  buffer size. */
    #define DEBUGPRINT_BTLDR_MAX_PACKET_SIZE      DEBUGPRINT_BTLDR_SIZEOF_WRITE_BUFFER

    #define DEBUGPRINT_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* Map-specific USB bootloader communication functions to common bootloader functions */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUGPRINT)
        #define CyBtldrCommStart        DEBUGPRINT_CyBtldrCommStart
        #define CyBtldrCommStop         DEBUGPRINT_CyBtldrCommStop
        #define CyBtldrCommReset        DEBUGPRINT_CyBtldrCommReset
        #define CyBtldrCommWrite        DEBUGPRINT_CyBtldrCommWrite
        #define CyBtldrCommRead         DEBUGPRINT_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUGPRINT) */
#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/

#define DEBUGPRINT_EP0                        (0u)
#define DEBUGPRINT_EP1                        (1u)
#define DEBUGPRINT_EP2                        (2u)
#define DEBUGPRINT_EP3                        (3u)
#define DEBUGPRINT_EP4                        (4u)
#define DEBUGPRINT_EP5                        (5u)
#define DEBUGPRINT_EP6                        (6u)
#define DEBUGPRINT_EP7                        (7u)
#define DEBUGPRINT_EP8                        (8u)
#define DEBUGPRINT_MAX_EP                     (9u)

#define DEBUGPRINT_TRUE                       (1u)
#define DEBUGPRINT_FALSE                      (0u)

#define DEBUGPRINT_NO_EVENT_ALLOWED           (2u)
#define DEBUGPRINT_EVENT_PENDING              (1u)
#define DEBUGPRINT_NO_EVENT_PENDING           (0u)

#define DEBUGPRINT_IN_BUFFER_FULL             DEBUGPRINT_NO_EVENT_PENDING
#define DEBUGPRINT_IN_BUFFER_EMPTY            DEBUGPRINT_EVENT_PENDING
#define DEBUGPRINT_OUT_BUFFER_FULL            DEBUGPRINT_EVENT_PENDING
#define DEBUGPRINT_OUT_BUFFER_EMPTY           DEBUGPRINT_NO_EVENT_PENDING

#define DEBUGPRINT_FORCE_J                    (0xA0u)
#define DEBUGPRINT_FORCE_K                    (0x80u)
#define DEBUGPRINT_FORCE_SE0                  (0xC0u)
#define DEBUGPRINT_FORCE_NONE                 (0x00u)

#define DEBUGPRINT_IDLE_TIMER_RUNNING         (0x02u)
#define DEBUGPRINT_IDLE_TIMER_EXPIRED         (0x01u)
#define DEBUGPRINT_IDLE_TIMER_INDEFINITE      (0x00u)

#define DEBUGPRINT_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define DEBUGPRINT_DEVICE_STATUS_SELF_POWERED (0x01u)

#define DEBUGPRINT_3V_OPERATION               (0x00u)
#define DEBUGPRINT_5V_OPERATION               (0x01u)
#define DEBUGPRINT_DWR_POWER_OPERATION        (0x02u)

#define DEBUGPRINT_MODE_DISABLE               (0x00u)
#define DEBUGPRINT_MODE_NAK_IN_OUT            (0x01u)
#define DEBUGPRINT_MODE_STATUS_OUT_ONLY       (0x02u)
#define DEBUGPRINT_MODE_STALL_IN_OUT          (0x03u)
#define DEBUGPRINT_MODE_RESERVED_0100         (0x04u)
#define DEBUGPRINT_MODE_ISO_OUT               (0x05u)
#define DEBUGPRINT_MODE_STATUS_IN_ONLY        (0x06u)
#define DEBUGPRINT_MODE_ISO_IN                (0x07u)
#define DEBUGPRINT_MODE_NAK_OUT               (0x08u)
#define DEBUGPRINT_MODE_ACK_OUT               (0x09u)
#define DEBUGPRINT_MODE_RESERVED_1010         (0x0Au)
#define DEBUGPRINT_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define DEBUGPRINT_MODE_NAK_IN                (0x0Cu)
#define DEBUGPRINT_MODE_ACK_IN                (0x0Du)
#define DEBUGPRINT_MODE_RESERVED_1110         (0x0Eu)
#define DEBUGPRINT_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define DEBUGPRINT_MODE_MASK                  (0x0Fu)
#define DEBUGPRINT_MODE_STALL_DATA_EP         (0x80u)

#define DEBUGPRINT_MODE_ACKD                  (0x10u)
#define DEBUGPRINT_MODE_OUT_RCVD              (0x20u)
#define DEBUGPRINT_MODE_IN_RCVD               (0x40u)
#define DEBUGPRINT_MODE_SETUP_RCVD            (0x80u)

#define DEBUGPRINT_RQST_TYPE_MASK             (0x60u)
#define DEBUGPRINT_RQST_TYPE_STD              (0x00u)
#define DEBUGPRINT_RQST_TYPE_CLS              (0x20u)
#define DEBUGPRINT_RQST_TYPE_VND              (0x40u)
#define DEBUGPRINT_RQST_DIR_MASK              (0x80u)
#define DEBUGPRINT_RQST_DIR_D2H               (0x80u)
#define DEBUGPRINT_RQST_DIR_H2D               (0x00u)
#define DEBUGPRINT_RQST_RCPT_MASK             (0x03u)
#define DEBUGPRINT_RQST_RCPT_DEV              (0x00u)
#define DEBUGPRINT_RQST_RCPT_IFC              (0x01u)
#define DEBUGPRINT_RQST_RCPT_EP               (0x02u)
#define DEBUGPRINT_RQST_RCPT_OTHER            (0x03u)

#if (DEBUGPRINT_LPM_ACTIVE)
    #define DEBUGPRINT_LPM_REQ_ACK            (0x01u << DEBUGPRINT_LPM_CTRL_LPM_ACK_RESP_POS)
    #define DEBUGPRINT_LPM_REQ_NACK           (0x00u)
    #define DEBUGPRINT_LPM_REQ_NYET           (0x01u << DEBUGPRINT_LPM_CTRL_NYET_EN_POS)
#endif /*(DEBUGPRINT_LPM_ACTIVE)*/

/* USB Class Codes */
#define DEBUGPRINT_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define DEBUGPRINT_CLASS_AUDIO                (0x01u)     /* Audio device */
#define DEBUGPRINT_CLASS_CDC                  (0x02u)     /* Communication device class */
#define DEBUGPRINT_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define DEBUGPRINT_CLASS_PDC                  (0x05u)     /* Physical device class */
#define DEBUGPRINT_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define DEBUGPRINT_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define DEBUGPRINT_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define DEBUGPRINT_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define DEBUGPRINT_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define DEBUGPRINT_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define DEBUGPRINT_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define DEBUGPRINT_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define DEBUGPRINT_CLASS_PHD                  (0x0Fu)     /* Personal Health care device */
#define DEBUGPRINT_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define DEBUGPRINT_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define DEBUGPRINT_CLASS_APP                  (0xEFu)     /* Application Specific */
#define DEBUGPRINT_CLASS_VENDOR               (0xFFu)     /* Vendor specific */

/* Standard Request Types (Table 9-4) */
#define DEBUGPRINT_GET_STATUS                 (0x00u)
#define DEBUGPRINT_CLEAR_FEATURE              (0x01u)
#define DEBUGPRINT_SET_FEATURE                (0x03u)
#define DEBUGPRINT_SET_ADDRESS                (0x05u)
#define DEBUGPRINT_GET_DESCRIPTOR             (0x06u)
#define DEBUGPRINT_SET_DESCRIPTOR             (0x07u)
#define DEBUGPRINT_GET_CONFIGURATION          (0x08u)
#define DEBUGPRINT_SET_CONFIGURATION          (0x09u)
#define DEBUGPRINT_GET_INTERFACE              (0x0Au)
#define DEBUGPRINT_SET_INTERFACE              (0x0Bu)
#define DEBUGPRINT_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define DEBUGPRINT_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define DEBUGPRINT_DESCR_DEVICE                   (1u)
#define DEBUGPRINT_DESCR_CONFIG                   (2u)
#define DEBUGPRINT_DESCR_STRING                   (3u)
#define DEBUGPRINT_DESCR_INTERFACE                (4u)
#define DEBUGPRINT_DESCR_ENDPOINT                 (5u)
#define DEBUGPRINT_DESCR_DEVICE_QUALIFIER         (6u)
#define DEBUGPRINT_DESCR_OTHER_SPEED              (7u)
#define DEBUGPRINT_DESCR_INTERFACE_POWER          (8u)
#if (DEBUGPRINT_BOS_ENABLE)
    #define DEBUGPRINT_DESCR_BOS                  (15u)
#endif /* (DEBUGPRINT_BOS_ENABLE) */
/* Device Descriptor Defines */
#define DEBUGPRINT_DEVICE_DESCR_LENGTH            (18u)
#define DEBUGPRINT_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define DEBUGPRINT_CONFIG_DESCR_LENGTH                (0u)
#define DEBUGPRINT_CONFIG_DESCR_TYPE                  (1u)
#define DEBUGPRINT_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define DEBUGPRINT_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define DEBUGPRINT_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define DEBUGPRINT_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define DEBUGPRINT_CONFIG_DESCR_CONFIGURATION         (6u)
#define DEBUGPRINT_CONFIG_DESCR_ATTRIB                (7u)
#define DEBUGPRINT_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define DEBUGPRINT_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

#if (DEBUGPRINT_BOS_ENABLE)
    /* Config Descriptor BOS */
    #define DEBUGPRINT_BOS_DESCR_LENGTH               (0u)
    #define DEBUGPRINT_BOS_DESCR_TYPE                 (1u)
    #define DEBUGPRINT_BOS_DESCR_TOTAL_LENGTH_LOW     (2u)
    #define DEBUGPRINT_BOS_DESCR_TOTAL_LENGTH_HI      (3u)
    #define DEBUGPRINT_BOS_DESCR_NUM_DEV_CAPS         (4u)
#endif /* (DEBUGPRINT_BOS_ENABLE) */

/* Feature Selectors (Table 9-6) */
#define DEBUGPRINT_DEVICE_REMOTE_WAKEUP           (0x01u)
#define DEBUGPRINT_ENDPOINT_HALT                  (0x00u)
#define DEBUGPRINT_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define DEBUGPRINT_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define DEBUGPRINT_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define DEBUGPRINT_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define DEBUGPRINT_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define DEBUGPRINT_DIR_IN                         (0x80u)
#define DEBUGPRINT_DIR_OUT                        (0x00u)
#define DEBUGPRINT_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define DEBUGPRINT_EP_TYPE_CTRL                   (0x00u)
#define DEBUGPRINT_EP_TYPE_ISOC                   (0x01u)
#define DEBUGPRINT_EP_TYPE_BULK                   (0x02u)
#define DEBUGPRINT_EP_TYPE_INT                    (0x03u)
#define DEBUGPRINT_EP_TYPE_MASK                   (0x03u)

#define DEBUGPRINT_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define DEBUGPRINT_EP_SYNC_TYPE_ASYNC             (0x04u)
#define DEBUGPRINT_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define DEBUGPRINT_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define DEBUGPRINT_EP_SYNC_TYPE_MASK              (0x0Cu)

#define DEBUGPRINT_EP_USAGE_TYPE_DATA             (0x00u)
#define DEBUGPRINT_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define DEBUGPRINT_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define DEBUGPRINT_EP_USAGE_TYPE_RESERVED         (0x30u)
#define DEBUGPRINT_EP_USAGE_TYPE_MASK             (0x30u)

/* Point Status defines */
#define DEBUGPRINT_EP_STATUS_LENGTH               (0x02u)

/* Point Device defines */
#define DEBUGPRINT_DEVICE_STATUS_LENGTH           (0x02u)

#define DEBUGPRINT_STATUS_LENGTH_MAX \
                 ((DEBUGPRINT_EP_STATUS_LENGTH > DEBUGPRINT_DEVICE_STATUS_LENGTH) ? \
                        DEBUGPRINT_EP_STATUS_LENGTH : DEBUGPRINT_DEVICE_STATUS_LENGTH)

/* Transfer Completion Notification */
#define DEBUGPRINT_XFER_IDLE                      (0x00u)
#define DEBUGPRINT_XFER_STATUS_ACK                (0x01u)
#define DEBUGPRINT_XFER_PREMATURE                 (0x02u)
#define DEBUGPRINT_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define DEBUGPRINT_TRANS_STATE_IDLE               (0x00u)
#define DEBUGPRINT_TRANS_STATE_CONTROL_READ       (0x02u)
#define DEBUGPRINT_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define DEBUGPRINT_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define DEBUGPRINT_STRING_MSOS                    (0xEEu)
#define DEBUGPRINT_MSOS_DESCRIPTOR_LENGTH         (18u)
#define DEBUGPRINT_MSOS_CONF_DESCR_LENGTH         (40u)

/* Return values */
#define DEBUGPRINT_BCD_PORT_SDP       (1u) /* Standard downstream port detected */
#define DEBUGPRINT_BCD_PORT_CDP       (2u) /* Charging downstream port detected */
#define DEBUGPRINT_BCD_PORT_DCP       (3u) /* Dedicated charging port detected */
#define DEBUGPRINT_BCD_PORT_UNKNOWN   (0u) /* Unable to detect charging port */
#define DEBUGPRINT_BCD_PORT_ERR       (4u) /* Error condition in detection process*/


/* Timeouts for BCD */
#define DEBUGPRINT_BCD_TIMEOUT                (400u)  /* Copied from PBK#163 TIMEOUT (300 ms) */
#define DEBUGPRINT_BCD_TDCD_DBNC              (10u)  /*BCD v1.2: DCD debounce time 10 ms*/
#define DEBUGPRINT_BCD_PRIMARY_WAIT           (40u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define DEBUGPRINT_BCD_SECONDARY_WAIT         (47u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define DEBUGPRINT_BCD_SUSPEND_DISABLE_WAIT   (2u)    /* Copied from PBK#163 TIMEOUT (2 us)   */

/* Wait cycles required before clearing SUSPEND_DEL in POWER_CTRL: 2us */
#define DEBUGPRINT_WAIT_SUSPEND_DEL_DISABLE   (2u)

/* Wait cycles required for USB regulator stabilization after it is enabled : 50ns */
#define DEBUGPRINT_WAIT_VREF_STABILITY        (0u)

#if (CY_PSOC3 || CY_PSOC5LP)
/* Wait cycles required for USB reference restore: 40us */
#define DEBUGPRINT_WAIT_VREF_RESTORE          (40u)

/* Wait cycles required for stabilization after register is written : 50ns */
#define DEBUGPRINT_WAIT_REG_STABILITY_50NS    (0u)
#define DEBUGPRINT_WAIT_REG_STABILITY_1US     (1u)

/* Wait cycles required after CR0 register write: 1 cycle */
#define DEBUGPRINT_WAIT_CR0_REG_STABILITY     (1u)

/* Wait cycles required after PD_PULLUP_N bit is set in PM_USB_CR0: 2us */
#define DEBUGPRINT_WAIT_PD_PULLUP_N_ENABLE    (2u)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if (CY_PSOC4)
    #if (DEBUGPRINT_EP_MANAGEMENT_DMA)
        #define DEBUGPRINT_DMA_DESCR0         (0u)
        #define DEBUGPRINT_DMA_DESCR1         (1u)
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

    #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define DEBUGPRINT_DMA_BUF_SIZE             (0x55u)
        #define DEBUGPRINT_DMA_BYTES_PER_BURST      (32u)
        #define DEBUGPRINT_DMA_HALFWORDS_PER_BURST  (16u)
        #define DEBUGPRINT_DMA_BURST_BYTES_MASK     (DEBUGPRINT_DMA_BYTES_PER_BURST - 1u)

        #define DEBUGPRINT_DMA_DESCR0_MASK        (0x00u)
        #define DEBUGPRINT_DMA_DESCR1_MASK        (0x80u)
        #define DEBUGPRINT_DMA_DESCR_REVERT       (0x40u)
        #define DEBUGPRINT_DMA_DESCR_16BITS       (0x20u)
        #define DEBUGPRINT_DMA_DESCR_SHIFT        (7u)

        #define DEBUGPRINT_DMA_GET_DESCR_NUM(desrc)
        #define DEBUGPRINT_DMA_GET_BURST_CNT(dmaBurstCnt) \
                    (((dmaBurstCnt) > 2u)? ((dmaBurstCnt) - 2u) : 0u)

        #define DEBUGPRINT_DMA_GET_MAX_ELEM_PER_BURST(dmaLastBurstEl) \
                    ((0u != ((dmaLastBurstEl) & DEBUGPRINT_DMA_DESCR_16BITS)) ? \
                                (DEBUGPRINT_DMA_HALFWORDS_PER_BURST - 1u) : (DEBUGPRINT_DMA_BYTES_PER_BURST - 1u))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
#else
    #if (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL)
        #define DEBUGPRINT_DMA_BYTES_PER_BURST    (0u)
        #define DEBUGPRINT_DMA_REQUEST_PER_BURST  (0u)
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) */

    #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        #define DEBUGPRINT_DMA_BYTES_PER_BURST    (32u)
        #define DEBUGPRINT_DMA_BYTES_REPEAT       (2u)

        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define DEBUGPRINT_DMA_BUF_SIZE           (0x55u)
        #define DEBUGPRINT_DMA_REQUEST_PER_BURST  (1u)

        #define DEBUGPRINT_EP17_SR_MASK           (0x7Fu)
        #define DEBUGPRINT_EP8_SR_MASK            (0x03u)
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
#endif /* (CY_PSOC4) */

/* DIE ID string descriptor defines */
#if defined(DEBUGPRINT_ENABLE_IDSN_STRING)
    #define DEBUGPRINT_IDSN_DESCR_LENGTH      (0x22u)
#endif /* (DEBUGPRINT_ENABLE_IDSN_STRING) */


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 DEBUGPRINT_initVar;
extern volatile uint8 DEBUGPRINT_device;
extern volatile uint8 DEBUGPRINT_transferState;
extern volatile uint8 DEBUGPRINT_configuration;
extern volatile uint8 DEBUGPRINT_configurationChanged;
extern volatile uint8 DEBUGPRINT_deviceStatus;
/** @} globals */

/**
* \addtogroup group_hid
* @{
*/
/* HID Variables */
#if defined(DEBUGPRINT_ENABLE_HID_CLASS)
    extern volatile uint8 DEBUGPRINT_hidProtocol [DEBUGPRINT_MAX_INTERFACES_NUMBER]; 
    extern volatile uint8 DEBUGPRINT_hidIdleRate [DEBUGPRINT_MAX_INTERFACES_NUMBER];
    extern volatile uint8 DEBUGPRINT_hidIdleTimer[DEBUGPRINT_MAX_INTERFACES_NUMBER];
#endif /* (DEBUGPRINT_ENABLE_HID_CLASS) */
/** @} hid */


/***************************************
*              Registers
***************************************/

/* Common registers for all PSoCs: 3/4/5LP */
#define DEBUGPRINT_ARB_CFG_PTR        ( (reg8 *) DEBUGPRINT_USB__ARB_CFG)
#define DEBUGPRINT_ARB_CFG_REG        (*(reg8 *) DEBUGPRINT_USB__ARB_CFG)

#define DEBUGPRINT_ARB_EP1_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP1_CFG)
#define DEBUGPRINT_ARB_EP1_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP1_CFG)
#define DEBUGPRINT_ARB_EP1_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP1_INT_EN)
#define DEBUGPRINT_ARB_EP1_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP1_INT_EN)
#define DEBUGPRINT_ARB_EP1_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP1_SR)
#define DEBUGPRINT_ARB_EP1_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP1_SR)
#define DEBUGPRINT_ARB_EP1_CFG_IND    DEBUGPRINT_USB__ARB_EP1_CFG
#define DEBUGPRINT_ARB_EP1_INT_EN_IND DEBUGPRINT_USB__ARB_EP1_INT_EN
#define DEBUGPRINT_ARB_EP1_SR_IND     DEBUGPRINT_USB__ARB_EP1_SR
#define DEBUGPRINT_ARB_EP_BASE        (*(volatile DEBUGPRINT_arb_eps_struct CYXDATA *) \
                                            (DEBUGPRINT_USB__ARB_EP1_CFG - sizeof(DEBUGPRINT_arb_ep_struct)))

#define DEBUGPRINT_ARB_EP2_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP2_CFG)
#define DEBUGPRINT_ARB_EP2_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP2_CFG)
#define DEBUGPRINT_ARB_EP2_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP2_INT_EN)
#define DEBUGPRINT_ARB_EP2_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP2_INT_EN)
#define DEBUGPRINT_ARB_EP2_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP2_SR)
#define DEBUGPRINT_ARB_EP2_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP2_SR)

#define DEBUGPRINT_ARB_EP3_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP3_CFG)
#define DEBUGPRINT_ARB_EP3_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP3_CFG)
#define DEBUGPRINT_ARB_EP3_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP3_INT_EN)
#define DEBUGPRINT_ARB_EP3_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP3_INT_EN)
#define DEBUGPRINT_ARB_EP3_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP3_SR)
#define DEBUGPRINT_ARB_EP3_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP3_SR)

#define DEBUGPRINT_ARB_EP4_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP4_CFG)
#define DEBUGPRINT_ARB_EP4_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP4_CFG)
#define DEBUGPRINT_ARB_EP4_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP4_INT_EN)
#define DEBUGPRINT_ARB_EP4_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP4_INT_EN)
#define DEBUGPRINT_ARB_EP4_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP4_SR)
#define DEBUGPRINT_ARB_EP4_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP4_SR)

#define DEBUGPRINT_ARB_EP5_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP5_CFG)
#define DEBUGPRINT_ARB_EP5_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP5_CFG)
#define DEBUGPRINT_ARB_EP5_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP5_INT_EN)
#define DEBUGPRINT_ARB_EP5_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP5_INT_EN)
#define DEBUGPRINT_ARB_EP5_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP5_SR)
#define DEBUGPRINT_ARB_EP5_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP5_SR)

#define DEBUGPRINT_ARB_EP6_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP6_CFG)
#define DEBUGPRINT_ARB_EP6_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP6_CFG)
#define DEBUGPRINT_ARB_EP6_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP6_INT_EN)
#define DEBUGPRINT_ARB_EP6_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP6_INT_EN)
#define DEBUGPRINT_ARB_EP6_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP6_SR)
#define DEBUGPRINT_ARB_EP6_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP6_SR)

#define DEBUGPRINT_ARB_EP7_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP7_CFG)
#define DEBUGPRINT_ARB_EP7_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP7_CFG)
#define DEBUGPRINT_ARB_EP7_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP7_INT_EN)
#define DEBUGPRINT_ARB_EP7_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP7_INT_EN)
#define DEBUGPRINT_ARB_EP7_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP7_SR)
#define DEBUGPRINT_ARB_EP7_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP7_SR)

#define DEBUGPRINT_ARB_EP8_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__ARB_EP8_CFG)
#define DEBUGPRINT_ARB_EP8_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__ARB_EP8_CFG)
#define DEBUGPRINT_ARB_EP8_INT_EN_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_EP8_INT_EN)
#define DEBUGPRINT_ARB_EP8_INT_EN_REG (*(reg8 *) DEBUGPRINT_USB__ARB_EP8_INT_EN)
#define DEBUGPRINT_ARB_EP8_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_EP8_SR)
#define DEBUGPRINT_ARB_EP8_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_EP8_SR)

#define DEBUGPRINT_ARB_INT_EN_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_INT_EN)
#define DEBUGPRINT_ARB_INT_EN_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_INT_EN)
#define DEBUGPRINT_ARB_INT_SR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_INT_SR)
#define DEBUGPRINT_ARB_INT_SR_REG     (*(reg8 *) DEBUGPRINT_USB__ARB_INT_SR)

#define DEBUGPRINT_ARB_RW1_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW1_DR)
#define DEBUGPRINT_ARB_RW1_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW1_RA)

#define DEBUGPRINT_ARB_RW1_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW1_RA_MSB)
#define DEBUGPRINT_ARB_RW1_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW1_WA)
#define DEBUGPRINT_ARB_RW1_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW1_WA_MSB)
#define DEBUGPRINT_ARB_RW1_DR_IND     DEBUGPRINT_USB__ARB_RW1_DR
#define DEBUGPRINT_ARB_RW1_RA_IND     DEBUGPRINT_USB__ARB_RW1_RA
#define DEBUGPRINT_ARB_RW1_RA_MSB_IND DEBUGPRINT_USB__ARB_RW1_RA_MSB
#define DEBUGPRINT_ARB_RW1_WA_IND     DEBUGPRINT_USB__ARB_RW1_WA
#define DEBUGPRINT_ARB_RW1_WA_MSB_IND DEBUGPRINT_USB__ARB_RW1_WA_MSB

#define DEBUGPRINT_ARB_RW2_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW2_DR)
#define DEBUGPRINT_ARB_RW2_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW2_RA)
#define DEBUGPRINT_ARB_RW2_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW2_RA_MSB)
#define DEBUGPRINT_ARB_RW2_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW2_WA)
#define DEBUGPRINT_ARB_RW2_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW2_WA_MSB)

#define DEBUGPRINT_ARB_RW3_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW3_DR)
#define DEBUGPRINT_ARB_RW3_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW3_RA)
#define DEBUGPRINT_ARB_RW3_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW3_RA_MSB)
#define DEBUGPRINT_ARB_RW3_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW3_WA)
#define DEBUGPRINT_ARB_RW3_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW3_WA_MSB)

#define DEBUGPRINT_ARB_RW4_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW4_DR)
#define DEBUGPRINT_ARB_RW4_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW4_RA)
#define DEBUGPRINT_ARB_RW4_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW4_RA_MSB)
#define DEBUGPRINT_ARB_RW4_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW4_WA)
#define DEBUGPRINT_ARB_RW4_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW4_WA_MSB)

#define DEBUGPRINT_ARB_RW5_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW5_DR)
#define DEBUGPRINT_ARB_RW5_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW5_RA)
#define DEBUGPRINT_ARB_RW5_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW5_RA_MSB)
#define DEBUGPRINT_ARB_RW5_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW5_WA)
#define DEBUGPRINT_ARB_RW5_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW5_WA_MSB)

#define DEBUGPRINT_ARB_RW6_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW6_DR)
#define DEBUGPRINT_ARB_RW6_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW6_RA)
#define DEBUGPRINT_ARB_RW6_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW6_RA_MSB)
#define DEBUGPRINT_ARB_RW6_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW6_WA)
#define DEBUGPRINT_ARB_RW6_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW6_WA_MSB)

#define DEBUGPRINT_ARB_RW7_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW7_DR)
#define DEBUGPRINT_ARB_RW7_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW7_RA)
#define DEBUGPRINT_ARB_RW7_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW7_RA_MSB)
#define DEBUGPRINT_ARB_RW7_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW7_WA)
#define DEBUGPRINT_ARB_RW7_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW7_WA_MSB)

#define DEBUGPRINT_ARB_RW8_DR_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW8_DR)
#define DEBUGPRINT_ARB_RW8_RA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW8_RA)
#define DEBUGPRINT_ARB_RW8_RA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW8_RA_MSB)
#define DEBUGPRINT_ARB_RW8_WA_PTR     ( (reg8 *) DEBUGPRINT_USB__ARB_RW8_WA)
#define DEBUGPRINT_ARB_RW8_WA_MSB_PTR ( (reg8 *) DEBUGPRINT_USB__ARB_RW8_WA_MSB)

#define DEBUGPRINT_BUF_SIZE_PTR       ( (reg8 *) DEBUGPRINT_USB__BUF_SIZE)
#define DEBUGPRINT_BUF_SIZE_REG       (*(reg8 *) DEBUGPRINT_USB__BUF_SIZE)
#define DEBUGPRINT_BUS_RST_CNT_PTR    ( (reg8 *) DEBUGPRINT_USB__BUS_RST_CNT)
#define DEBUGPRINT_BUS_RST_CNT_REG    (*(reg8 *) DEBUGPRINT_USB__BUS_RST_CNT)
#define DEBUGPRINT_CWA_PTR            ( (reg8 *) DEBUGPRINT_USB__CWA)
#define DEBUGPRINT_CWA_REG            (*(reg8 *) DEBUGPRINT_USB__CWA)
#define DEBUGPRINT_CWA_MSB_PTR        ( (reg8 *) DEBUGPRINT_USB__CWA_MSB)
#define DEBUGPRINT_CWA_MSB_REG        (*(reg8 *) DEBUGPRINT_USB__CWA_MSB)
#define DEBUGPRINT_CR0_PTR            ( (reg8 *) DEBUGPRINT_USB__CR0)
#define DEBUGPRINT_CR0_REG            (*(reg8 *) DEBUGPRINT_USB__CR0)
#define DEBUGPRINT_CR1_PTR            ( (reg8 *) DEBUGPRINT_USB__CR1)
#define DEBUGPRINT_CR1_REG            (*(reg8 *) DEBUGPRINT_USB__CR1)

#define DEBUGPRINT_DMA_THRES_PTR      ( (reg8 *) DEBUGPRINT_USB__DMA_THRES)
#define DEBUGPRINT_DMA_THRES_REG      (*(reg8 *) DEBUGPRINT_USB__DMA_THRES)
#define DEBUGPRINT_DMA_THRES_MSB_PTR  ( (reg8 *) DEBUGPRINT_USB__DMA_THRES_MSB)
#define DEBUGPRINT_DMA_THRES_MSB_REG  (*(reg8 *) DEBUGPRINT_USB__DMA_THRES_MSB)

#define DEBUGPRINT_EP_ACTIVE_PTR      ( (reg8 *) DEBUGPRINT_USB__EP_ACTIVE)
#define DEBUGPRINT_EP_ACTIVE_REG      (*(reg8 *) DEBUGPRINT_USB__EP_ACTIVE)
#define DEBUGPRINT_EP_TYPE_PTR        ( (reg8 *) DEBUGPRINT_USB__EP_TYPE)
#define DEBUGPRINT_EP_TYPE_REG        (*(reg8 *) DEBUGPRINT_USB__EP_TYPE)

#define DEBUGPRINT_EP0_CNT_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_CNT)
#define DEBUGPRINT_EP0_CNT_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_CNT)
#define DEBUGPRINT_EP0_CR_PTR         ( (reg8 *) DEBUGPRINT_USB__EP0_CR)
#define DEBUGPRINT_EP0_CR_REG         (*(reg8 *) DEBUGPRINT_USB__EP0_CR)
#define DEBUGPRINT_EP0_DR0_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR0)
#define DEBUGPRINT_EP0_DR0_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR0)
#define DEBUGPRINT_EP0_DR1_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR1)
#define DEBUGPRINT_EP0_DR1_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR1)
#define DEBUGPRINT_EP0_DR2_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR2)
#define DEBUGPRINT_EP0_DR2_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR2)
#define DEBUGPRINT_EP0_DR3_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR3)
#define DEBUGPRINT_EP0_DR3_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR3)
#define DEBUGPRINT_EP0_DR4_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR4)
#define DEBUGPRINT_EP0_DR4_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR4)
#define DEBUGPRINT_EP0_DR5_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR5)
#define DEBUGPRINT_EP0_DR5_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR5)
#define DEBUGPRINT_EP0_DR6_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR6)
#define DEBUGPRINT_EP0_DR6_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR6)
#define DEBUGPRINT_EP0_DR7_PTR        ( (reg8 *) DEBUGPRINT_USB__EP0_DR7)
#define DEBUGPRINT_EP0_DR7_REG        (*(reg8 *) DEBUGPRINT_USB__EP0_DR7)
#define DEBUGPRINT_EP0_DR0_IND        DEBUGPRINT_USB__EP0_DR0
#define DEBUGPRINT_EP0_DR_BASE        (*(volatile DEBUGPRINT_ep0_data_struct CYXDATA *) DEBUGPRINT_USB__EP0_DR0)

#define DEBUGPRINT_OSCLK_DR0_PTR      ( (reg8 *) DEBUGPRINT_USB__OSCLK_DR0)
#define DEBUGPRINT_OSCLK_DR0_REG      (*(reg8 *) DEBUGPRINT_USB__OSCLK_DR0)
#define DEBUGPRINT_OSCLK_DR1_PTR      ( (reg8 *) DEBUGPRINT_USB__OSCLK_DR1)
#define DEBUGPRINT_OSCLK_DR1_REG      (*(reg8 *) DEBUGPRINT_USB__OSCLK_DR1)

#define DEBUGPRINT_SIE_EP_INT_EN_PTR  ( (reg8 *) DEBUGPRINT_USB__SIE_EP_INT_EN)
#define DEBUGPRINT_SIE_EP_INT_EN_REG  (*(reg8 *) DEBUGPRINT_USB__SIE_EP_INT_EN)
#define DEBUGPRINT_SIE_EP_INT_SR_PTR  ( (reg8 *) DEBUGPRINT_USB__SIE_EP_INT_SR)
#define DEBUGPRINT_SIE_EP_INT_SR_REG  (*(reg8 *) DEBUGPRINT_USB__SIE_EP_INT_SR)

#define DEBUGPRINT_SIE_EP1_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP1_CNT0)
#define DEBUGPRINT_SIE_EP1_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP1_CNT0)
#define DEBUGPRINT_SIE_EP1_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP1_CNT1)
#define DEBUGPRINT_SIE_EP1_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP1_CNT1)
#define DEBUGPRINT_SIE_EP1_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP1_CR0)
#define DEBUGPRINT_SIE_EP1_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP1_CR0)
#define DEBUGPRINT_SIE_EP1_CNT1_IND   DEBUGPRINT_USB__SIE_EP1_CNT1
#define DEBUGPRINT_SIE_EP1_CNT0_IND   DEBUGPRINT_USB__SIE_EP1_CNT0
#define DEBUGPRINT_SIE_EP1_CR0_IND    DEBUGPRINT_USB__SIE_EP1_CR0
#define DEBUGPRINT_SIE_EP_BASE        (*(volatile DEBUGPRINT_sie_eps_struct CYXDATA *) \
                                            (DEBUGPRINT_USB__SIE_EP1_CNT0 - sizeof(DEBUGPRINT_sie_ep_struct)))

#define DEBUGPRINT_SIE_EP2_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP2_CNT0)
#define DEBUGPRINT_SIE_EP2_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP2_CNT0)
#define DEBUGPRINT_SIE_EP2_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP2_CNT1)
#define DEBUGPRINT_SIE_EP2_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP2_CNT1)
#define DEBUGPRINT_SIE_EP2_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP2_CR0)
#define DEBUGPRINT_SIE_EP2_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP2_CR0)

#define DEBUGPRINT_SIE_EP3_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP3_CNT0)
#define DEBUGPRINT_SIE_EP3_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP3_CNT0)
#define DEBUGPRINT_SIE_EP3_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP3_CNT1)
#define DEBUGPRINT_SIE_EP3_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP3_CNT1)
#define DEBUGPRINT_SIE_EP3_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP3_CR0)
#define DEBUGPRINT_SIE_EP3_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP3_CR0)

#define DEBUGPRINT_SIE_EP4_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP4_CNT0)
#define DEBUGPRINT_SIE_EP4_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP4_CNT0)
#define DEBUGPRINT_SIE_EP4_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP4_CNT1)
#define DEBUGPRINT_SIE_EP4_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP4_CNT1)
#define DEBUGPRINT_SIE_EP4_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP4_CR0)
#define DEBUGPRINT_SIE_EP4_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP4_CR0)

#define DEBUGPRINT_SIE_EP5_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP5_CNT0)
#define DEBUGPRINT_SIE_EP5_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP5_CNT0)
#define DEBUGPRINT_SIE_EP5_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP5_CNT1)
#define DEBUGPRINT_SIE_EP5_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP5_CNT1)
#define DEBUGPRINT_SIE_EP5_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP5_CR0)
#define DEBUGPRINT_SIE_EP5_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP5_CR0)

#define DEBUGPRINT_SIE_EP6_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP6_CNT0)
#define DEBUGPRINT_SIE_EP6_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP6_CNT0)
#define DEBUGPRINT_SIE_EP6_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP6_CNT1)
#define DEBUGPRINT_SIE_EP6_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP6_CNT1)
#define DEBUGPRINT_SIE_EP6_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP6_CR0)
#define DEBUGPRINT_SIE_EP6_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP6_CR0)

#define DEBUGPRINT_SIE_EP7_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP7_CNT0)
#define DEBUGPRINT_SIE_EP7_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP7_CNT0)
#define DEBUGPRINT_SIE_EP7_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP7_CNT1)
#define DEBUGPRINT_SIE_EP7_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP7_CNT1)
#define DEBUGPRINT_SIE_EP7_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP7_CR0)
#define DEBUGPRINT_SIE_EP7_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP7_CR0)

#define DEBUGPRINT_SIE_EP8_CNT0_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP8_CNT0)
#define DEBUGPRINT_SIE_EP8_CNT0_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP8_CNT0)
#define DEBUGPRINT_SIE_EP8_CNT1_PTR   ( (reg8 *) DEBUGPRINT_USB__SIE_EP8_CNT1)
#define DEBUGPRINT_SIE_EP8_CNT1_REG   (*(reg8 *) DEBUGPRINT_USB__SIE_EP8_CNT1)
#define DEBUGPRINT_SIE_EP8_CR0_PTR    ( (reg8 *) DEBUGPRINT_USB__SIE_EP8_CR0)
#define DEBUGPRINT_SIE_EP8_CR0_REG    (*(reg8 *) DEBUGPRINT_USB__SIE_EP8_CR0)

#define DEBUGPRINT_SOF0_PTR           ( (reg8 *) DEBUGPRINT_USB__SOF0)
#define DEBUGPRINT_SOF0_REG           (*(reg8 *) DEBUGPRINT_USB__SOF0)
#define DEBUGPRINT_SOF1_PTR           ( (reg8 *) DEBUGPRINT_USB__SOF1)
#define DEBUGPRINT_SOF1_REG           (*(reg8 *) DEBUGPRINT_USB__SOF1)

#define DEBUGPRINT_USB_CLK_EN_PTR     ( (reg8 *) DEBUGPRINT_USB__USB_CLK_EN)
#define DEBUGPRINT_USB_CLK_EN_REG     (*(reg8 *) DEBUGPRINT_USB__USB_CLK_EN)

#define DEBUGPRINT_USBIO_CR0_PTR      ( (reg8 *) DEBUGPRINT_USB__USBIO_CR0)
#define DEBUGPRINT_USBIO_CR0_REG      (*(reg8 *) DEBUGPRINT_USB__USBIO_CR0)
#define DEBUGPRINT_USBIO_CR1_PTR      ( (reg8 *) DEBUGPRINT_USB__USBIO_CR1)
#define DEBUGPRINT_USBIO_CR1_REG      (*(reg8 *) DEBUGPRINT_USB__USBIO_CR1)

#define DEBUGPRINT_DYN_RECONFIG_PTR   ( (reg8 *) DEBUGPRINT_USB__DYN_RECONFIG)
#define DEBUGPRINT_DYN_RECONFIG_REG   (*(reg8 *) DEBUGPRINT_USB__DYN_RECONFIG)

#if (CY_PSOC4)
    #define DEBUGPRINT_ARB_RW1_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_RA16)
    #define DEBUGPRINT_ARB_RW1_RA16_REG   (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_RA16)
    #define DEBUGPRINT_ARB_RW1_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_WA16)
    #define DEBUGPRINT_ARB_RW1_WA16_REG   (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_WA16)
    #define DEBUGPRINT_ARB_RW1_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_DR16)
    #define DEBUGPRINT_ARB_RW1_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW1_DR16)
    #define DEBUGPRINT_ARB_EP16_BASE      (*(volatile DEBUGPRINT_arb_eps_reg16_struct CYXDATA *) \
                                                (DEBUGPRINT_USB__ARB_RW1_WA16 - sizeof(DEBUGPRINT_arb_ep_reg16_struct)))

    #define DEBUGPRINT_ARB_RW2_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW2_DR16)
    #define DEBUGPRINT_ARB_RW2_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW2_RA16)
    #define DEBUGPRINT_ARB_RW2_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW2_WA16)

    #define DEBUGPRINT_ARB_RW3_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW3_DR16)
    #define DEBUGPRINT_ARB_RW3_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW3_RA16)
    #define DEBUGPRINT_ARB_RW3_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW3_WA16)

    #define DEBUGPRINT_ARB_RW4_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW4_DR16)
    #define DEBUGPRINT_ARB_RW4_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW4_RA16)
    #define DEBUGPRINT_ARB_RW4_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW4_WA16)

    #define DEBUGPRINT_ARB_RW5_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW5_DR16)
    #define DEBUGPRINT_ARB_RW5_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW5_RA16)
    #define DEBUGPRINT_ARB_RW5_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW5_WA16)

    #define DEBUGPRINT_ARB_RW6_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW6_DR16)
    #define DEBUGPRINT_ARB_RW6_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW6_RA16)
    #define DEBUGPRINT_ARB_RW6_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW6_WA16)

    #define DEBUGPRINT_ARB_RW7_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW7_DR16)
    #define DEBUGPRINT_ARB_RW7_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW7_RA16)
    #define DEBUGPRINT_ARB_RW7_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW7_WA16)

    #define DEBUGPRINT_ARB_RW8_DR16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW8_DR16)
    #define DEBUGPRINT_ARB_RW8_RA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW8_RA16)
    #define DEBUGPRINT_ARB_RW8_WA16_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__ARB_RW8_WA16)

    #define DEBUGPRINT_OSCLK_DR16_PTR     ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__OSCLK_DR16)
    #define DEBUGPRINT_OSCLK_DR16_REG     (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__OSCLK_DR16)

    #define DEBUGPRINT_SOF16_PTR          ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__SOF16)
    #define DEBUGPRINT_SOF16_REG          (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__SOF16)
    
    #define DEBUGPRINT_CWA16_PTR          ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__CWA16)
    #define DEBUGPRINT_CWA16_REG          (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__CWA16)

    #define DEBUGPRINT_DMA_THRES16_PTR    ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__DMA_THRES16)
    #define DEBUGPRINT_DMA_THRES16_REG    (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__DMA_THRES16)

    #define DEBUGPRINT_USB_CLK_EN_PTR     ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_CLK_EN)
    #define DEBUGPRINT_USB_CLK_EN_REG     (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_CLK_EN)

    #define DEBUGPRINT_USBIO_CR2_PTR      ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USBIO_CR2)
    #define DEBUGPRINT_USBIO_CR2_REG      (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USBIO_CR2)

    #define DEBUGPRINT_USB_MEM            ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__MEM_DATA0)

    #define DEBUGPRINT_POWER_CTRL_REG      (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_POWER_CTRL)
    #define DEBUGPRINT_POWER_CTRL_PTR      ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_POWER_CTRL)

    #define DEBUGPRINT_CHGDET_CTRL_REG     (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_CHGDET_CTRL)
    #define DEBUGPRINT_CHGDET_CTRL_PTR     ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_CHGDET_CTRL)

    #define DEBUGPRINT_USBIO_CTRL_REG      (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_USBIO_CTRL)
    #define DEBUGPRINT_USBIO_CTRL_PTR      ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_USBIO_CTRL)

    #define DEBUGPRINT_FLOW_CTRL_REG       (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_FLOW_CTRL)
    #define DEBUGPRINT_FLOW_CTRL_PTR       ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_FLOW_CTRL)

    #define DEBUGPRINT_LPM_CTRL_REG        (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_LPM_CTRL)
    #define DEBUGPRINT_LPM_CTRL_PTR        ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_LPM_CTRL)

    #define DEBUGPRINT_LPM_STAT_REG        (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_LPM_STAT)
    #define DEBUGPRINT_LPM_STAT_PTR        ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_LPM_STAT)

    #define DEBUGPRINT_PHY_CONTROL_REG     (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_PHY_CONTROL)
    #define DEBUGPRINT_PHY_CONTROL_PTR     ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_PHY_CONTROL)

    #define DEBUGPRINT_INTR_SIE_REG        (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE)
    #define DEBUGPRINT_INTR_SIE_PTR        ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE)

    #define DEBUGPRINT_INTR_SIE_SET_REG    (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_SET)
    #define DEBUGPRINT_INTR_SIE_SET_PTR    ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_SET)

    #define DEBUGPRINT_INTR_SIE_MASK_REG   (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_MASK)
    #define DEBUGPRINT_INTR_SIE_MASK_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_MASK)

    #define DEBUGPRINT_INTR_SIE_MASKED_REG (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_MASKED)
    #define DEBUGPRINT_INTR_SIE_MASKED_PTR ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_SIE_MASKED)

    #define DEBUGPRINT_INTR_LVL_SEL_REG    (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_LVL_SEL)
    #define DEBUGPRINT_INTR_LVL_SEL_PTR    ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_LVL_SEL)

    #define DEBUGPRINT_INTR_CAUSE_HI_REG   (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_HI)
    #define DEBUGPRINT_INTR_CAUSE_HI_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_HI)

    #define DEBUGPRINT_INTR_CAUSE_LO_REG   (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_LO)
    #define DEBUGPRINT_INTR_CAUSE_LO_PTR   ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_LO)

    #define DEBUGPRINT_INTR_CAUSE_MED_REG  (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_MED)
    #define DEBUGPRINT_INTR_CAUSE_MED_PTR  ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_INTR_CAUSE_MED)

    #define DEBUGPRINT_DFT_CTRL_REG        (*(reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_DFT_CTRL)
    #define DEBUGPRINT_DFT_CTRL_PTR        ( (reg32 *) DEBUGPRINT_cy_m0s8_usb__USB_DFT_CTRL)

    #if (DEBUGPRINT_VBUS_MONITORING_ENABLE)
        #if (DEBUGPRINT_VBUS_POWER_PAD_ENABLE)
            /* Vbus power pad pin is hard wired to P13[2] */
            #define DEBUGPRINT_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT13_PS)
            #define DEBUGPRINT_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT13_PS)
            #define DEBUGPRINT_VBUS_VALID         (0x04u)
        #else
            /* Vbus valid pin is hard wired to P0[0] */
            #define DEBUGPRINT_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT0_PS)
            #define DEBUGPRINT_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT0_PS)
            #define DEBUGPRINT_VBUS_VALID         (0x01u)
        #endif
    #endif /*(DEBUGPRINT_VBUS_MONITORING_ENABLE) */

    #define DEBUGPRINT_BURSTEND_0_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND0_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_1_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND1_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_2_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND2_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_3_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND3_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_4_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND4_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_5_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND5_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_6_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND6_TR_OUTPUT)
    #define DEBUGPRINT_BURSTEND_7_TR_OUTPUT    (DEBUGPRINT_cy_m0s8_usb__BURSTEND7_TR_OUTPUT)
    
#else /* (CY_PSOC3 || CY_PSOC5LP) */

    /* DEBUGPRINT_PM_USB_CR0 */
    #define DEBUGPRINT_PM_USB_CR0_PTR     ( (reg8 *) CYREG_PM_USB_CR0)
    #define DEBUGPRINT_PM_USB_CR0_REG     (*(reg8 *) CYREG_PM_USB_CR0)

    /* DEBUGPRINT_PM_ACT/STBY_CFG */
    #define DEBUGPRINT_PM_ACT_CFG_PTR     ( (reg8 *) DEBUGPRINT_USB__PM_ACT_CFG)
    #define DEBUGPRINT_PM_ACT_CFG_REG     (*(reg8 *) DEBUGPRINT_USB__PM_ACT_CFG)
    #define DEBUGPRINT_PM_STBY_CFG_PTR    ( (reg8 *) DEBUGPRINT_USB__PM_STBY_CFG)
    #define DEBUGPRINT_PM_STBY_CFG_REG    (*(reg8 *) DEBUGPRINT_USB__PM_STBY_CFG)

    #if (!CY_PSOC5LP)
        #define DEBUGPRINT_USBIO_CR2_PTR  (  (reg8 *) DEBUGPRINT_USB__USBIO_CR2)
        #define DEBUGPRINT_USBIO_CR2_REG  (* (reg8 *) DEBUGPRINT_USB__USBIO_CR2)
    #endif /* (!CY_PSOC5LP) */

    /* DEBUGPRINT_USB_MEM - USB IP memory buffer */
    #define DEBUGPRINT_USB_MEM            ((reg8 *) CYDEV_USB_MEM_BASE)

    #if (DEBUGPRINT_VBUS_MONITORING_ENABLE)
        #if (DEBUGPRINT_VBUS_MONITORING_INTERNAL)
            #define DEBUGPRINT_VBUS_STATUS_REG    (*(reg8 *) DEBUGPRINT_VBUS__PS)
            #define DEBUGPRINT_VBUS_STATUS_PTR    ( (reg8 *) DEBUGPRINT_VBUS__PS)
            #define DEBUGPRINT_VBUS_VALID         (DEBUGPRINT_VBUS__MASK)
        #else
            #define DEBUGPRINT_VBUS_STATUS_REG    (*(reg8 *) DEBUGPRINT_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define DEBUGPRINT_VBUS_STATUS_PTR    ( (reg8 *) DEBUGPRINT_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define DEBUGPRINT_VBUS_VALID         (DEBUGPRINT_Vbus_ps_sts_sts_reg__MASK)
        #endif /* (DEBUGPRINT_VBUS_MONITORING_INTERNAL) */
    #endif /*(DEBUGPRINT_VBUS_MONITORING_ENABLE) */
#endif /* (CY_PSOC4) */


/***************************************
*       Interrupt source constants
***************************************/

#define DEBUGPRINT_DP_INTC_PRIORITY       DEBUGPRINT_dp_int__INTC_PRIOR_NUM
#define DEBUGPRINT_DP_INTC_VECT_NUM       DEBUGPRINT_dp_int__INTC_NUMBER

#if (CY_PSOC4)
    #define DEBUGPRINT_DMA_AUTO_INTR_PRIO (0u)
    
    #define DEBUGPRINT_INTR_HI_PRIORITY   DEBUGPRINT_high_int__INTC_PRIOR_NUM
    #define DEBUGPRINT_INTR_HI_VECT_NUM   DEBUGPRINT_high_int__INTC_NUMBER

    #define DEBUGPRINT_INTR_MED_PRIORITY  DEBUGPRINT_med_int__INTC_PRIOR_NUM
    #define DEBUGPRINT_INTR_MED_VECT_NUM  DEBUGPRINT_med_int__INTC_NUMBER

    #define DEBUGPRINT_INTR_LO_PRIORITY   DEBUGPRINT_lo_int__INTC_PRIOR_NUM
    #define DEBUGPRINT_INTR_LO_VECT_NUM   DEBUGPRINT_lo_int__INTC_NUMBER

    /* Interrupt sources in DEBUGPRINT_isrCallbacks[] table */
    #define DEBUGPRINT_SOF_INTR_NUM       (0u)
    #define DEBUGPRINT_BUS_RESET_INT_NUM  (1u)
    #define DEBUGPRINT_EP0_INTR_NUM       (2u)
    #define DEBUGPRINT_LPM_INTR_NUM       (3u)
    #define DEBUGPRINT_ARB_EP_INTR_NUM    (4u)
    #define DEBUGPRINT_EP1_INTR_NUM       (5u)
    #define DEBUGPRINT_EP2_INTR_NUM       (6u)
    #define DEBUGPRINT_EP3_INTR_NUM       (7u)
    #define DEBUGPRINT_EP4_INTR_NUM       (8u)
    #define DEBUGPRINT_EP5_INTR_NUM       (9u)
    #define DEBUGPRINT_EP6_INTR_NUM       (10u)
    #define DEBUGPRINT_EP7_INTR_NUM       (11u)
    #define DEBUGPRINT_EP8_INTR_NUM       (12u)

#else
    #define DEBUGPRINT_BUS_RESET_PRIOR    DEBUGPRINT_bus_reset__INTC_PRIOR_NUM
    #define DEBUGPRINT_BUS_RESET_MASK     DEBUGPRINT_bus_reset__INTC_MASK
    #define DEBUGPRINT_BUS_RESET_VECT_NUM DEBUGPRINT_bus_reset__INTC_NUMBER

    #define DEBUGPRINT_SOF_PRIOR          DEBUGPRINT_sof_int__INTC_PRIOR_NUM
    #define DEBUGPRINT_SOF_MASK           DEBUGPRINT_sof_int__INTC_MASK
    #define DEBUGPRINT_SOF_VECT_NUM       DEBUGPRINT_sof_int__INTC_NUMBER

    #define DEBUGPRINT_EP_0_PRIOR         DEBUGPRINT_ep_0__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_0_MASK          DEBUGPRINT_ep_0__INTC_MASK
    #define DEBUGPRINT_EP_0_VECT_NUM      DEBUGPRINT_ep_0__INTC_NUMBER

    #define DEBUGPRINT_EP_1_PRIOR         DEBUGPRINT_ep_1__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_1_MASK          DEBUGPRINT_ep_1__INTC_MASK
    #define DEBUGPRINT_EP_1_VECT_NUM      DEBUGPRINT_ep_1__INTC_NUMBER

    #define DEBUGPRINT_EP_2_PRIOR         DEBUGPRINT_ep_2__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_2_MASK          DEBUGPRINT_ep_2__INTC_MASK
    #define DEBUGPRINT_EP_2_VECT_NUM      DEBUGPRINT_ep_2__INTC_NUMBER

    #define DEBUGPRINT_EP_3_PRIOR         DEBUGPRINT_ep_3__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_3_MASK          DEBUGPRINT_ep_3__INTC_MASK
    #define DEBUGPRINT_EP_3_VECT_NUM      DEBUGPRINT_ep_3__INTC_NUMBER

    #define DEBUGPRINT_EP_4_PRIOR         DEBUGPRINT_ep_4__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_4_MASK          DEBUGPRINT_ep_4__INTC_MASK
    #define DEBUGPRINT_EP_4_VECT_NUM      DEBUGPRINT_ep_4__INTC_NUMBER

    #define DEBUGPRINT_EP_5_PRIOR         DEBUGPRINT_ep_5__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_5_MASK          DEBUGPRINT_ep_5__INTC_MASK
    #define DEBUGPRINT_EP_5_VECT_NUM      DEBUGPRINT_ep_5__INTC_NUMBER

    #define DEBUGPRINT_EP_6_PRIOR         DEBUGPRINT_ep_6__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_6_MASK          DEBUGPRINT_ep_6__INTC_MASK
    #define DEBUGPRINT_EP_6_VECT_NUM      DEBUGPRINT_ep_6__INTC_NUMBER

    #define DEBUGPRINT_EP_7_PRIOR         DEBUGPRINT_ep_7__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_7_MASK          DEBUGPRINT_ep_7__INTC_MASK
    #define DEBUGPRINT_EP_7_VECT_NUM      DEBUGPRINT_ep_7__INTC_NUMBER

    #define DEBUGPRINT_EP_8_PRIOR         DEBUGPRINT_ep_8__INTC_PRIOR_NUM
    #define DEBUGPRINT_EP_8_MASK          DEBUGPRINT_ep_8__INTC_MASK
    #define DEBUGPRINT_EP_8_VECT_NUM      DEBUGPRINT_ep_8__INTC_NUMBER

    /* Set ARB ISR priority 0 to be highest for all EPX ISRs. */
    #define DEBUGPRINT_ARB_PRIOR          (0u)
    #define DEBUGPRINT_ARB_MASK           DEBUGPRINT_arb_int__INTC_MASK
    #define DEBUGPRINT_ARB_VECT_NUM       DEBUGPRINT_arb_int__INTC_NUMBER
#endif /* (CY_PSOC4) */


/***************************************
*       Endpoint 0 offsets (Table 9-2)
***************************************/
#define DEBUGPRINT_bmRequestTypeReg      DEBUGPRINT_EP0_DR_BASE.epData[0u]
#define DEBUGPRINT_bRequestReg           DEBUGPRINT_EP0_DR_BASE.epData[1u]
#define DEBUGPRINT_wValueLoReg           DEBUGPRINT_EP0_DR_BASE.epData[2u]
#define DEBUGPRINT_wValueHiReg           DEBUGPRINT_EP0_DR_BASE.epData[3u]
#define DEBUGPRINT_wIndexLoReg           DEBUGPRINT_EP0_DR_BASE.epData[4u]
#define DEBUGPRINT_wIndexHiReg           DEBUGPRINT_EP0_DR_BASE.epData[5u]
#define DEBUGPRINT_wLengthLoReg          DEBUGPRINT_EP0_DR_BASE.epData[6u]
#define DEBUGPRINT_wLengthHiReg          DEBUGPRINT_EP0_DR_BASE.epData[7u]

/* Compatibility defines */
#define DEBUGPRINT_lengthLoReg           DEBUGPRINT_EP0_DR_BASE.epData[6u]
#define DEBUGPRINT_lengthHiReg           DEBUGPRINT_EP0_DR_BASE.epData[7u]


/***************************************
*       Register Constants
***************************************/

#define DEBUGPRINT_3500MV     (3500u)
#if (CY_PSOC4)
    #define DEBUGPRINT_VDDD_MV    (CYDEV_VBUS_MV)
#else
    #define DEBUGPRINT_VDDD_MV    (CYDEV_VDDD_MV)
#endif /* (CY_PSOC4) */


/* DEBUGPRINT_USB_CLK */
#define DEBUGPRINT_USB_CLK_CSR_CLK_EN_POS (0u)
#define DEBUGPRINT_USB_CLK_CSR_CLK_EN     ((uint8) ((uint8) 0x1u << DEBUGPRINT_USB_CLK_CSR_CLK_EN_POS))
#define DEBUGPRINT_USB_CLK_ENABLE         (DEBUGPRINT_USB_CLK_CSR_CLK_EN)

/* DEBUGPRINT_CR0 */
#define DEBUGPRINT_CR0_DEVICE_ADDRESS_POS     (0u)
#define DEBUGPRINT_CR0_ENABLE_POS             (7u)
#define DEBUGPRINT_CR0_DEVICE_ADDRESS_MASK    ((uint8) ((uint8) 0x7Fu << DEBUGPRINT_CR0_DEVICE_ADDRESS_POS))
#define DEBUGPRINT_CR0_ENABLE                 ((uint8) ((uint8) 0x01u << DEBUGPRINT_CR0_ENABLE_POS))


/* DEBUGPRINT_CR1 */
#define DEBUGPRINT_CR1_REG_ENABLE_POS         (0u)
#define DEBUGPRINT_CR1_ENABLE_LOCK_POS        (1u)
#define DEBUGPRINT_CR1_BUS_ACTIVITY_POS       (2u)
#define DEBUGPRINT_CR1_TRIM_OFFSET_MSB_POS    (3u)
#define DEBUGPRINT_CR1_REG_ENABLE             ((uint8) ((uint8) 0x1u << DEBUGPRINT_CR1_REG_ENABLE_POS))
#define DEBUGPRINT_CR1_ENABLE_LOCK            ((uint8) ((uint8) 0x1u << DEBUGPRINT_CR1_ENABLE_LOCK_POS))
#define DEBUGPRINT_CR1_BUS_ACTIVITY           ((uint8) ((uint8) 0x1u << DEBUGPRINT_CR1_BUS_ACTIVITY_POS))
#define DEBUGPRINT_CR1_TRIM_OFFSET_MSB        ((uint8) ((uint8) 0x1u << DEBUGPRINT_CR1_TRIM_OFFSET_MSB_POS))

/* DEBUGPRINT_EPX_CNT */
#define DEBUGPRINT_EP0_CNT_DATA_TOGGLE        (0x80u)
#define DEBUGPRINT_EPX_CNT_DATA_TOGGLE        (0x80u)
#define DEBUGPRINT_EPX_CNT0_MASK              (0x0Fu)
#define DEBUGPRINT_EPX_CNTX_MSB_MASK          (0x07u)
#define DEBUGPRINT_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define DEBUGPRINT_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define DEBUGPRINT_EPX_CNTX_CRC_COUNT         (0x02u)
#define DEBUGPRINT_EPX_DATA_BUF_MAX           (512u)

/* DEBUGPRINT_USBIO_CR0 */

#define DEBUGPRINT_USBIO_CR0_TEN              (0x80u)
#define DEBUGPRINT_USBIO_CR0_TSE0             (0x40u)
#define DEBUGPRINT_USBIO_CR0_TD               (0x20u)
#define DEBUGPRINT_USBIO_CR0_RD               (0x01u)

/* DEBUGPRINT_USBIO_CR1 */
#define DEBUGPRINT_USBIO_CR1_DM0_POS      (0u)
#define DEBUGPRINT_USBIO_CR1_DP0_POS      (1u)
#define DEBUGPRINT_USBIO_CR1_USBPUEN_POS  (2u)
#define DEBUGPRINT_USBIO_CR1_IOMODE_POS   (5u)
#define DEBUGPRINT_USBIO_CR1_DM0          ((uint8) ((uint8) 0x1u << DEBUGPRINT_USBIO_CR1_DM0_POS))
#define DEBUGPRINT_USBIO_CR1_DP0          ((uint8) ((uint8) 0x1u << DEBUGPRINT_USBIO_CR1_DP0_POS))
#define DEBUGPRINT_USBIO_CR1_USBPUEN      ((uint8) ((uint8) 0x1u << DEBUGPRINT_USBIO_CR1_USBPUEN_POS))
#define DEBUGPRINT_USBIO_CR1_IOMODE       ((uint8) ((uint8) 0x1u << DEBUGPRINT_USBIO_CR1_IOMODE_POS))

/* DEBUGPRINT_FASTCLK_IMO_CR */
#define DEBUGPRINT_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define DEBUGPRINT_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define DEBUGPRINT_FASTCLK_IMO_CR_FX2ON       (0x10u)

/* DEBUGPRINT_ARB_EPX_CFG */
#define DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY_POS    (0u)
#define DEBUGPRINT_ARB_EPX_CFG_DMA_REQ_POS        (1u)
#define DEBUGPRINT_ARB_EPX_CFG_CRC_BYPASS_POS     (2u)
#define DEBUGPRINT_ARB_EPX_CFG_RESET_POS          (3u)
#define DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY        ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY_POS))
#define DEBUGPRINT_ARB_EPX_CFG_DMA_REQ            ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_CFG_DMA_REQ_POS))
#define DEBUGPRINT_ARB_EPX_CFG_CRC_BYPASS         ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_CFG_CRC_BYPASS_POS))
#define DEBUGPRINT_ARB_EPX_CFG_RESET              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_CFG_RESET_POS))

/* DEBUGPRINT_ARB_EPX_INT / SR */
#define DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL_POS    (0u)
#define DEBUGPRINT_ARB_EPX_INT_DMA_GNT_POS        (1u)
#define DEBUGPRINT_ARB_EPX_INT_BUF_OVER_POS       (2u)
#define DEBUGPRINT_ARB_EPX_INT_BUF_UNDER_POS      (3u)
#define DEBUGPRINT_ARB_EPX_INT_ERR_INT_POS        (4u)
#define DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL        ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL_POS))
#define DEBUGPRINT_ARB_EPX_INT_DMA_GNT            ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_DMA_GNT_POS))
#define DEBUGPRINT_ARB_EPX_INT_BUF_OVER           ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_BUF_OVER_POS))
#define DEBUGPRINT_ARB_EPX_INT_BUF_UNDER          ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_BUF_UNDER_POS))
#define DEBUGPRINT_ARB_EPX_INT_ERR_INT            ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_ERR_INT_POS))

#if (CY_PSOC4)
#define DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN_POS     (5u)
#define DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN         ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN_POS))
#endif /* (CY_PSOC4) */

/* Common arbiter interrupt sources for all PSoC devices. */
#define DEBUGPRINT_ARB_EPX_INT_COMMON    (DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL | \
                                                DEBUGPRINT_ARB_EPX_INT_DMA_GNT     | \
                                                DEBUGPRINT_ARB_EPX_INT_BUF_OVER    | \
                                                DEBUGPRINT_ARB_EPX_INT_BUF_UNDER   | \
                                                DEBUGPRINT_ARB_EPX_INT_ERR_INT)

#if (CY_PSOC4)
    #define DEBUGPRINT_ARB_EPX_INT_ALL    (DEBUGPRINT_ARB_EPX_INT_COMMON | DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN)
#else
    #define DEBUGPRINT_ARB_EPX_INT_ALL    (DEBUGPRINT_ARB_EPX_INT_COMMON)
#endif /* (CY_PSOC4) */

/* DEBUGPRINT_ARB_CFG */
#define DEBUGPRINT_ARB_CFG_AUTO_MEM_POS   (4u)
#define DEBUGPRINT_ARB_CFG_DMA_CFG_POS    (5u)
#define DEBUGPRINT_ARB_CFG_CFG_CMP_POS    (7u)
#define DEBUGPRINT_ARB_CFG_AUTO_MEM       ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_CFG_AUTO_MEM_POS))
#define DEBUGPRINT_ARB_CFG_DMA_CFG_MASK   ((uint8) ((uint8) 0x3u << DEBUGPRINT_ARB_CFG_DMA_CFG_POS))
#define DEBUGPRINT_ARB_CFG_DMA_CFG_NONE   ((uint8) ((uint8) 0x0u << DEBUGPRINT_ARB_CFG_DMA_CFG_POS))
#define DEBUGPRINT_ARB_CFG_DMA_CFG_MANUAL ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_CFG_DMA_CFG_POS))
#define DEBUGPRINT_ARB_CFG_DMA_CFG_AUTO   ((uint8) ((uint8) 0x2u << DEBUGPRINT_ARB_CFG_DMA_CFG_POS))
#define DEBUGPRINT_ARB_CFG_CFG_CMP        ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_CFG_CFG_CMP_POS))

/* DEBUGPRINT_DYN_RECONFIG */
#define DEBUGPRINT_DYN_RECONFIG_EP_SHIFT      (1u)
#define DEBUGPRINT_DYN_RECONFIG_ENABLE_POS    (0u)
#define DEBUGPRINT_DYN_RECONFIG_EPNO_POS      (1u)
#define DEBUGPRINT_DYN_RECONFIG_RDY_STS_POS   (4u)
#define DEBUGPRINT_DYN_RECONFIG_ENABLE        ((uint8) ((uint8) 0x1u << DEBUGPRINT_DYN_RECONFIG_ENABLE_POS))
#define DEBUGPRINT_DYN_RECONFIG_EPNO_MASK     ((uint8) ((uint8) 0x7u << DEBUGPRINT_DYN_RECONFIG_EPNO_POS))
#define DEBUGPRINT_DYN_RECONFIG_RDY_STS       ((uint8) ((uint8) 0x1u << DEBUGPRINT_DYN_RECONFIG_RDY_STS_POS))

/* DEBUGPRINT_ARB_INT */
#define DEBUGPRINT_ARB_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define DEBUGPRINT_ARB_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define DEBUGPRINT_ARB_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define DEBUGPRINT_ARB_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define DEBUGPRINT_ARB_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define DEBUGPRINT_ARB_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define DEBUGPRINT_ARB_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define DEBUGPRINT_ARB_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define DEBUGPRINT_ARB_INT_EP1_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP1_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP2_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP2_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP3_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP3_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP4_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP4_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP5_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP5_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP6_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP6_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP7_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP7_INTR_POS))
#define DEBUGPRINT_ARB_INT_EP8_INTR              ((uint8) ((uint8) 0x1u << DEBUGPRINT_ARB_INT_EP8_INTR_POS))

/* DEBUGPRINT_SIE_INT */
#define DEBUGPRINT_SIE_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define DEBUGPRINT_SIE_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define DEBUGPRINT_SIE_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define DEBUGPRINT_SIE_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define DEBUGPRINT_SIE_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define DEBUGPRINT_SIE_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define DEBUGPRINT_SIE_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define DEBUGPRINT_SIE_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define DEBUGPRINT_SIE_INT_EP1_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP1_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP2_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP2_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP3_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP3_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP4_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP4_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP5_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP5_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP6_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP6_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP7_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP7_INTR_POS))
#define DEBUGPRINT_SIE_INT_EP8_INTR              ((uint8) ((uint8) 0x01u << DEBUGPRINT_SIE_INT_EP8_INTR_POS))

#if (CY_PSOC4)
    /* DEBUGPRINT_POWER_CTRL_REG */
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS       (0u)  /* [0] */
    #define DEBUGPRINT_POWER_CTRL_SUSPEND_POS              (2u)  /* [1] */
    #define DEBUGPRINT_POWER_CTRL_SUSPEND_DEL_POS          (3u)  /* [3] */
    #define DEBUGPRINT_POWER_CTRL_ISOLATE_POS              (4u)  /* [4] */
    #define DEBUGPRINT_POWER_CTRL_CHDET_PWR_CTL_POS        (5u)  /* [5] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DM_PULLDOWN_POS   (25u) /* [25] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS (26u) /* [26] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_RCVR_POS          (27u) /* [27] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DPO_POS           (28u) /* [28] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DMO_POS           (29u) /* [29] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_CHGDET_POS        (30u) /* [30] */
    #define DEBUGPRINT_POWER_CTRL_ENABLE_POS               (31u) /* [31] */
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_MASK      ((uint32) 0x03u << DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_0         ((uint32) 0x00u << DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_1         ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_GPIO      ((uint32) 0x02u << DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_PHY       ((uint32) 0x03u << DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define DEBUGPRINT_POWER_CTRL_SUSPEND                  ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_SUSPEND_POS)
    #define DEBUGPRINT_POWER_CTRL_SUSPEND_DEL              ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_SUSPEND_DEL_POS)
    #define DEBUGPRINT_POWER_CTRL_ISOLATE                  ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ISOLATE_POS)
    #define DEBUGPRINT_POWER_CTRL_CHDET_PWR_CTL_MASK       ((uint32) 0x03u << DEBUGPRINT_POWER_CTRL_CHDET_PWR_CTL_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DM_PULLDOWN       ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_DM_PULLDOWN_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_VBUS_PULLDOWN     ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_RCVR              ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_RCVR_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DPO               ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_DPO_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_DMO               ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_DMO_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE_CHGDET            ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_CHGDET_POS)
    #define DEBUGPRINT_POWER_CTRL_ENABLE                   ((uint32) 0x01u << DEBUGPRINT_POWER_CTRL_ENABLE_POS)

    /* DEBUGPRINT_CHGDET_CTRL_REG */
    #define DEBUGPRINT_CHGDET_CTRL_COMP_DP_POS        (0u)  /* [0] */
    #define DEBUGPRINT_CHGDET_CTRL_COMP_DM_POS        (1u)  /* [1] */
    #define DEBUGPRINT_CHGDET_CTRL_COMP_EN_POS        (2u)  /* [2] */
    #define DEBUGPRINT_CHGDET_CTRL_REF_DP_POS         (3u)  /* [3] */
    #define DEBUGPRINT_CHGDET_CTRL_REF_DM_POS         (4u)  /* [4] */
    #define DEBUGPRINT_CHGDET_CTRL_REF_EN_POS         (5u)  /* [5] */
    #define DEBUGPRINT_CHGDET_CTRL_DCD_SRC_EN_POS     (6u)  /* [6] */
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS      (12u) /* [12] */
    #define DEBUGPRINT_CHGDET_CTRL_COMP_OUT_POS       (31u) /* [31] */
    #define DEBUGPRINT_CHGDET_CTRL_COMP_DP            ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_COMP_DP_POS)
    #define DEBUGPRINT_CHGDET_CTRL_COMP_DM            ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_COMP_DM_POS)
    #define DEBUGPRINT_CHGDET_CTRL_COMP_EN            ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_COMP_EN_POS)
    #define DEBUGPRINT_CHGDET_CTRL_REF_DP             ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_REF_DP_POS)
    #define DEBUGPRINT_CHGDET_CTRL_REF_DM             ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_REF_DM_POS)
    #define DEBUGPRINT_CHGDET_CTRL_REF_EN             ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_REF_EN_POS)
    #define DEBUGPRINT_CHGDET_CTRL_DCD_SRC_EN         ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_DCD_SRC_EN_POS)
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_MASK     ((uint32) 0x03u << DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS)
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_NORMAL   ((uint32) 0x00u << DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS)
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_VBG      ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS)
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_DONTUSE  ((uint32) 0x02u << DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS)
    #define DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_ADFTIN   ((uint32) 0x03u << DEBUGPRINT_CHGDET_CTRL_ADFT_CTRL_POS)
    #define DEBUGPRINT_CHGDET_CTRL_COMP_OUT           ((uint32) 0x01u << DEBUGPRINT_CHGDET_CTRL_COMP_OUT_POS)

    /* DEBUGPRINT_LPM_CTRL */
    #define DEBUGPRINT_LPM_CTRL_LPM_EN_POS        (0u)
    #define DEBUGPRINT_LPM_CTRL_LPM_ACK_RESP_POS  (1u)
    #define DEBUGPRINT_LPM_CTRL_NYET_EN_POS       (2u)
    #define DEBUGPRINT_LPM_CTRL_SUB_RESP_POS      (4u)
    #define DEBUGPRINT_LPM_CTRL_LPM_EN            ((uint32) 0x01u << DEBUGPRINT_LPM_CTRL_LPM_EN_POS)
    #define DEBUGPRINT_LPM_CTRL_LPM_ACK_RESP      ((uint32) 0x01u << DEBUGPRINT_LPM_CTRL_LPM_ACK_RESP_POS)
    #define DEBUGPRINT_LPM_CTRL_NYET_EN           ((uint32) 0x01u << DEBUGPRINT_LPM_CTRL_NYET_EN_POS)
    #define DEBUGPRINT_LPM_CTRL_ACK_NYET_MASK     ((uint32) 0x03u << DEBUGPRINT_LPM_CTRL_LPM_ACK_RESP_POS)
    #define DEBUGPRINT_LPM_CTRL_SUB_RESP          ((uint32) 0x01u << DEBUGPRINT_LPM_CTRL_SUB_RESP_POS)

    #define DEBUGPRINT_LPM_STAT_LPM_BESL_POS          (0u)
    #define DEBUGPRINT_LPM_STAT_LPM_REMOTE_WAKE_POS   (4u)
    #define DEBUGPRINT_LPM_STAT_LPM_BESL_MASK         ((uint32) 0x0Fu << DEBUGPRINT_LPM_STAT_LPM_BESL_POS)
    #define DEBUGPRINT_LPM_STAT_LPM_REMOTE_WAKE       ((uint32) 0x01u << DEBUGPRINT_LPM_STAT_LPM_REMOTE_WAKE_POS)

    /* DEBUGPRINT_INTR_SIE */
    #define DEBUGPRINT_INTR_SIE_SOF_INTR_POS          (0u) /* [0] Interrupt for USB SOF   */
    #define DEBUGPRINT_INTR_SIE_BUS_RESET_INTR_POS    (1u) /* [1] Interrupt for BUS RESET */
    #define DEBUGPRINT_INTR_SIE_EP0_INTR_POS          (2u) /* [2] Interrupt for EP0       */
    #define DEBUGPRINT_INTR_SIE_LPM_INTR_POS          (3u) /* [3] Interrupt for LPM       */
    #define DEBUGPRINT_INTR_SIE_RESUME_INTR_POS       (4u) /* [4] Interrupt for RESUME (not used by component) */
    #define DEBUGPRINT_INTR_SIE_SOF_INTR              ((uint32) 0x01u << DEBUGPRINT_INTR_SIE_SOF_INTR_POS)
    #define DEBUGPRINT_INTR_SIE_BUS_RESET_INTR        ((uint32) 0x01u << DEBUGPRINT_INTR_SIE_BUS_RESET_INTR_POS)
    #define DEBUGPRINT_INTR_SIE_EP0_INTR              ((uint32) 0x01u << DEBUGPRINT_INTR_SIE_EP0_INTR_POS)
    #define DEBUGPRINT_INTR_SIE_LPM_INTR              ((uint32) 0x01u << DEBUGPRINT_INTR_SIE_LPM_INTR_POS)
    #define DEBUGPRINT_INTR_SIE_RESUME_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_SIE_RESUME_INTR_POS)

    /* DEBUGPRINT_INTR_CAUSE_LO, MED and HI */
    #define DEBUGPRINT_INTR_CAUSE_SOF_INTR_POS       (0u)  /* [0] Interrupt status for USB SOF    */
    #define DEBUGPRINT_INTR_CAUSE_BUS_RESET_INTR_POS (1u)  /* [1] Interrupt status for USB BUS RSET */
    #define DEBUGPRINT_INTR_CAUSE_EP0_INTR_POS       (2u)  /* [2] Interrupt status for USB EP0    */
    #define DEBUGPRINT_INTR_CAUSE_LPM_INTR_POS       (3u)  /* [3] Interrupt status for USB LPM    */
    #define DEBUGPRINT_INTR_CAUSE_RESUME_INTR_POS    (4u)  /* [4] Interrupt status for USB RESUME */
    #define DEBUGPRINT_INTR_CAUSE_ARB_INTR_POS       (7u)  /* [7] Interrupt status for USB ARB    */
    #define DEBUGPRINT_INTR_CAUSE_EP1_INTR_POS       (8u)  /* [8] Interrupt status for USB EP1    */
    #define DEBUGPRINT_INTR_CAUSE_EP2_INTR_POS       (9u)  /* [9] Interrupt status for USB EP2    */
    #define DEBUGPRINT_INTR_CAUSE_EP3_INTR_POS       (10u) /* [10] Interrupt status for USB EP3   */
    #define DEBUGPRINT_INTR_CAUSE_EP4_INTR_POS       (11u) /* [11] Interrupt status for USB EP4   */
    #define DEBUGPRINT_INTR_CAUSE_EP5_INTR_POS       (12u) /* [12] Interrupt status for USB EP5   */
    #define DEBUGPRINT_INTR_CAUSE_EP6_INTR_POS       (13u) /* [13] Interrupt status for USB EP6   */
    #define DEBUGPRINT_INTR_CAUSE_EP7_INTR_POS       (14u) /* [14] Interrupt status for USB EP7   */
    #define DEBUGPRINT_INTR_CAUSE_EP8_INTR_POS       (15u) /* [15] Interrupt status for USB EP8   */
    #define DEBUGPRINT_INTR_CAUSE_SOF_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_SOF_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_BUS_RESET_INTR     ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_BUS_RESET_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP0_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP0_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_LPM_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_LPM_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_RESUME_INTR        ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_RESUME_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_ARB_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_ARB_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP1_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP1_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP2_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP2_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP3_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP3_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP4_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP4_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP5_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP5_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP6_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP6_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP7_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP7_INTR_POS)
    #define DEBUGPRINT_INTR_CAUSE_EP8_INTR           ((uint32) 0x01u << DEBUGPRINT_INTR_CAUSE_EP8_INTR_POS)

    #define DEBUGPRINT_INTR_CAUSE_CTRL_INTR_MASK     (DEBUGPRINT_INTR_CAUSE_SOF_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_BUS_RESET_INTR | \
                                                            DEBUGPRINT_INTR_CAUSE_EP0_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_LPM_INTR)

    #define DEBUGPRINT_INTR_CAUSE_EP1_8_INTR_MASK    (DEBUGPRINT_INTR_CAUSE_EP1_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP2_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP3_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP4_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP5_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP6_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP7_INTR       | \
                                                            DEBUGPRINT_INTR_CAUSE_EP8_INTR)

    #define DEBUGPRINT_INTR_CAUSE_EP_INTR_SHIFT      (DEBUGPRINT_INTR_CAUSE_ARB_INTR_POS - \
                                                           (DEBUGPRINT_INTR_CAUSE_LPM_INTR_POS + 1u))
    #define DEBUGPRINT_INTR_CAUSE_SRC_COUNT          (13u)

    #define DEBUGPRINT_CHGDET_CTRL_PRIMARY    (DEBUGPRINT_CHGDET_CTRL_COMP_EN | \
                                                     DEBUGPRINT_CHGDET_CTRL_COMP_DM | \
                                                     DEBUGPRINT_CHGDET_CTRL_REF_EN  | \
                                                     DEBUGPRINT_CHGDET_CTRL_REF_DP)

    #define DEBUGPRINT_CHGDET_CTRL_SECONDARY  (DEBUGPRINT_CHGDET_CTRL_COMP_EN | \
                                                     DEBUGPRINT_CHGDET_CTRL_COMP_DP | \
                                                     DEBUGPRINT_CHGDET_CTRL_REF_EN  | \
                                                     DEBUGPRINT_CHGDET_CTRL_REF_DM)

    #define DEBUGPRINT_CHGDET_CTRL_DEFAULT    (0x00000900u)


#else /* (CY_PSOC3 || CY_PSOC5LP) */
    #define DEBUGPRINT_PM_ACT_EN_FSUSB            DEBUGPRINT_USB__PM_ACT_MSK
    #define DEBUGPRINT_PM_STBY_EN_FSUSB           DEBUGPRINT_USB__PM_STBY_MSK
    #define DEBUGPRINT_PM_AVAIL_EN_FSUSBIO        (0x10u)

    #define DEBUGPRINT_PM_USB_CR0_REF_EN          (0x01u)
    #define DEBUGPRINT_PM_USB_CR0_PD_N            (0x02u)
    #define DEBUGPRINT_PM_USB_CR0_PD_PULLUP_N     (0x04u)
#endif /* (CY_PSOC4) */


/***************************************
*       Macros Definitions
***************************************/

#if (CY_PSOC4)
    #define DEBUGPRINT_ClearSieInterruptSource(intMask) \
                do{ \
                    DEBUGPRINT_INTR_SIE_REG = (uint32) (intMask); \
                }while(0)
#else
    #define DEBUGPRINT_ClearSieInterruptSource(intMask) \
                do{ /* Does nothing. */ }while(0)
#endif /* (CY_PSOC4) */

#define DEBUGPRINT_ClearSieEpInterruptSource(intMask) \
            do{ \
                DEBUGPRINT_SIE_EP_INT_SR_REG = (uint8) (intMask); \
            }while(0)

#define DEBUGPRINT_GET_ACTIVE_IN_EP_CR0_MODE(epType)  (((epType) == DEBUGPRINT_EP_TYPE_ISOC) ? \
                                                                (DEBUGPRINT_MODE_ISO_IN) : (DEBUGPRINT_MODE_ACK_IN))

#define DEBUGPRINT_GET_ACTIVE_OUT_EP_CR0_MODE(epType) (((epType) == DEBUGPRINT_EP_TYPE_ISOC) ? \
                                                                (DEBUGPRINT_MODE_ISO_OUT) : (DEBUGPRINT_MODE_ACK_OUT))

#define DEBUGPRINT_GET_EP_TYPE(epNumber)  (DEBUGPRINT_EP[epNumber].attrib & DEBUGPRINT_EP_TYPE_MASK)

#define DEBUGPRINT_GET_UINT16(hi, low)    (((uint16) ((uint16) (hi) << 8u)) | ((uint16) (low) & 0xFFu))


/***************************************
*    Initialization Register Settings
***************************************/

/* Clear device address and enable USB IP respond to USB traffic. */
#define DEBUGPRINT_DEFUALT_CR0    (DEBUGPRINT_CR0_ENABLE)

/* Arbiter configuration depends on memory management mode. */
#define DEBUGPRINT_DEFAULT_ARB_CFG    ((DEBUGPRINT_EP_MANAGEMENT_MANUAL) ? (DEBUGPRINT_ARB_CFG_DMA_CFG_NONE) : \
                                                ((DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) ? \
                                                    (DEBUGPRINT_ARB_CFG_DMA_CFG_MANUAL) : \
                                                        (DEBUGPRINT_ARB_CFG_AUTO_MEM | DEBUGPRINT_ARB_CFG_DMA_CFG_AUTO)))

/* Enable arbiter interrupt for active endpoints only */
#define DEBUGPRINT_DEFAULT_ARB_INT_EN \
        ((uint8) ((uint8) DEBUGPRINT_DMA1_ACTIVE << DEBUGPRINT_ARB_INT_EP1_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA2_ACTIVE << DEBUGPRINT_ARB_INT_EP2_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA3_ACTIVE << DEBUGPRINT_ARB_INT_EP3_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA4_ACTIVE << DEBUGPRINT_ARB_INT_EP4_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA5_ACTIVE << DEBUGPRINT_ARB_INT_EP5_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA6_ACTIVE << DEBUGPRINT_ARB_INT_EP6_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA7_ACTIVE << DEBUGPRINT_ARB_INT_EP7_INTR_POS) | \
         (uint8) ((uint8) DEBUGPRINT_DMA8_ACTIVE << DEBUGPRINT_ARB_INT_EP8_INTR_POS))

/* Enable all SIE endpoints interrupts */
#define DEBUGPRINT_DEFAULT_SIE_EP_INT_EN  (DEBUGPRINT_SIE_INT_EP1_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP2_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP3_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP4_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP5_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP6_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP7_INTR | \
                                                 DEBUGPRINT_SIE_INT_EP8_INTR)

#define DEBUGPRINT_ARB_EPX_CFG_DEFAULT    (DEBUGPRINT_ARB_EPX_CFG_RESET | \
                                                 DEBUGPRINT_ARB_EPX_CFG_CRC_BYPASS)

/* Default EP arbiter interrupt source register */
#define DEBUGPRINT_ARB_EPX_INT_COMMON_MASK   (DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL | \
                                                    DEBUGPRINT_ARB_EPX_INT_BUF_OVER    | \
                                                    DEBUGPRINT_ARB_EPX_INT_BUF_UNDER   | \
                                                    DEBUGPRINT_ARB_EPX_INT_ERR_INT     | \
                                                    (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL ? DEBUGPRINT_ARB_EPX_INT_DMA_GNT : 0u))

#define DEBUGPRINT_CLEAR_REG      (0u)

#if (CY_PSOC4)
    /* Set USB lock option when IMO is locked to USB traffic. */
    #define DEBUGPRINT_DEFUALT_CR1    ((0u != CySysClkImoGetUsbLock()) ? (DEBUGPRINT_CR1_ENABLE_LOCK) : (0u))

    /* Recommended value is increased from 3 to 10 due to suppress glitch on  
     * RSE0 with USB2.0 hubs (LF CLK = 32kHz equal to 350us). */
    #define DEBUGPRINT_DEFUALT_BUS_RST_CNT  (10u)

    /* Select VBUS sources as: valid, PHY of GPIO, and clears isolate bit. */
    /* Application level must ensure that VBUS is valid valid to use. */
    #define DEBUGPRINT_DEFAULT_POWER_CTRL_VBUS    (DEBUGPRINT_POWER_CTRL_ENABLE_VBUS_PULLDOWN | \
                                                         ((!DEBUGPRINT_VBUS_MONITORING_ENABLE) ? \
                                                            (DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_1) : \
                                                                (DEBUGPRINT_VBUS_POWER_PAD_ENABLE ? \
                                                                    (DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_PHY) : \
                                                                    (DEBUGPRINT_POWER_CTRL_VBUS_VALID_OVR_GPIO))))
    /* Enable USB IP. */
    #define DEBUGPRINT_DEFAULT_POWER_CTRL_PHY (DEBUGPRINT_POWER_CTRL_SUSPEND     | \
                                                     DEBUGPRINT_POWER_CTRL_SUSPEND_DEL | \
                                                     DEBUGPRINT_POWER_CTRL_ENABLE_RCVR | \
                                                     DEBUGPRINT_POWER_CTRL_ENABLE_DPO  | \
                                                     DEBUGPRINT_POWER_CTRL_ENABLE_DMO  | \
                                                     DEBUGPRINT_POWER_CTRL_ENABLE)

    /* Assign interrupt between levels lo, med, hi. */
    #define DEBUGPRINT_DEFAULT_INTR_LVL_SEL   ((uint32) (DEBUGPRINT_INTR_LVL_SEL))

    /* Enable interrupt source in the INTR_SIE. The SOF is always disabled and EP0 is enabled. */
    #define DEBUGPRINT_DEFAULT_INTR_SIE_MASK \
                ((uint32) ((uint32) DEBUGPRINT_BUS_RESET_ISR_ACTIVE << DEBUGPRINT_INTR_SIE_BUS_RESET_INTR_POS) | \
                 (uint32) ((uint32) DEBUGPRINT_SOF_ISR_ACTIVE       << DEBUGPRINT_INTR_SIE_SOF_INTR_POS)       | \
                 (uint32) ((uint32) DEBUGPRINT_LPM_ACTIVE           << DEBUGPRINT_INTR_SIE_LPM_INTR_POS)       | \
                 (uint32) ((uint32) DEBUGPRINT_INTR_SIE_EP0_INTR))

    /* Arbiter interrupt sources */
    #define DEBUGPRINT_ARB_EPX_INT_MASK   (DEBUGPRINT_ARB_EPX_INT_COMMON_MASK | \
                                                (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO ? DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN : 0u))

    /* Common DMA configuration */
    #define DEBUGPRINT_DMA_COMMON_CFG     (CYDMA_PULSE | CYDMA_ENTIRE_DESCRIPTOR | \
                                                 CYDMA_NON_PREEMPTABLE)


#else
    #define DEBUGPRINT_ARB_EPX_INT_MASK   (DEBUGPRINT_ARB_EPX_INT_COMMON_MASK)

    #define DEBUGPRINT_DEFUALT_CR1        (DEBUGPRINT_CR1_ENABLE_LOCK)

    /* Recommended value is 3 for LF CLK = 100kHz equal to 100us. */
    #define DEBUGPRINT_DEFUALT_BUS_RST_CNT    (10u)
#endif /* (CY_PSOC4) */

/*
* \addtogroup group_deprecated
* @{
*/

/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Renamed type definitions */
#define DEBUGPRINT_CODE CYCODE
#define DEBUGPRINT_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define DEBUGPRINT_DATA data
    #define DEBUGPRINT_XDATA xdata
#else
    #define DEBUGPRINT_DATA
    #define DEBUGPRINT_XDATA
#endif /*  __C51__ */
#define DEBUGPRINT_NULL       NULL
/** @} deprecated */
/* Renamed structure fields */
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable */
#define CurrentTD           DEBUGPRINT_currentTD
#define DEBUGPRINT_interfaceSetting_last       DEBUGPRINT_interfaceSettingLast

/* Renamed global constants */
#define DEBUGPRINT_DWR_VDDD_OPERATION         (DEBUGPRINT_DWR_POWER_OPERATION)

/* Renamed functions */
#define DEBUGPRINT_bCheckActivity             DEBUGPRINT_CheckActivity
#define DEBUGPRINT_bGetConfiguration          DEBUGPRINT_GetConfiguration
#define DEBUGPRINT_bGetInterfaceSetting       DEBUGPRINT_GetInterfaceSetting
#define DEBUGPRINT_bGetEPState                DEBUGPRINT_GetEPState
#define DEBUGPRINT_wGetEPCount                DEBUGPRINT_GetEPCount
#define DEBUGPRINT_bGetEPAckState             DEBUGPRINT_GetEPAckState
#define DEBUGPRINT_bRWUEnabled                DEBUGPRINT_RWUEnabled
#define DEBUGPRINT_bVBusPresent               DEBUGPRINT_VBusPresent

#define DEBUGPRINT_bConfiguration             DEBUGPRINT_configuration
#define DEBUGPRINT_bInterfaceSetting          DEBUGPRINT_interfaceSetting
#define DEBUGPRINT_bDeviceAddress             DEBUGPRINT_deviceAddress
#define DEBUGPRINT_bDeviceStatus              DEBUGPRINT_deviceStatus
#define DEBUGPRINT_bDevice                    DEBUGPRINT_device
#define DEBUGPRINT_bTransferState             DEBUGPRINT_transferState
#define DEBUGPRINT_bLastPacketSize            DEBUGPRINT_lastPacketSize

#define DEBUGPRINT_LoadEP                     DEBUGPRINT_LoadInEP
#define DEBUGPRINT_LoadInISOCEP               DEBUGPRINT_LoadInEP
#define DEBUGPRINT_EnableOutISOCEP            DEBUGPRINT_EnableOutEP

#define DEBUGPRINT_SetVector                  CyIntSetVector
#define DEBUGPRINT_SetPriority                CyIntSetPriority
#define DEBUGPRINT_EnableInt                  CyIntEnable

/* Replace with register access. */
#define DEBUGPRINT_bmRequestType      DEBUGPRINT_EP0_DR0_PTR
#define DEBUGPRINT_bRequest           DEBUGPRINT_EP0_DR1_PTR
#define DEBUGPRINT_wValue             DEBUGPRINT_EP0_DR2_PTR
#define DEBUGPRINT_wValueHi           DEBUGPRINT_EP0_DR3_PTR
#define DEBUGPRINT_wValueLo           DEBUGPRINT_EP0_DR2_PTR
#define DEBUGPRINT_wIndex             DEBUGPRINT_EP0_DR4_PTR
#define DEBUGPRINT_wIndexHi           DEBUGPRINT_EP0_DR5_PTR
#define DEBUGPRINT_wIndexLo           DEBUGPRINT_EP0_DR4_PTR
#define DEBUGPRINT_length             DEBUGPRINT_EP0_DR6_PTR
#define DEBUGPRINT_lengthHi           DEBUGPRINT_EP0_DR7_PTR
#define DEBUGPRINT_lengthLo           DEBUGPRINT_EP0_DR6_PTR

/* Rename VBUS monitoring registers. */
#if (CY_PSOC3 || CY_PSOC5LP)
    #if (DEBUGPRINT_VBUS_MONITORING_ENABLE)
        #if (DEBUGPRINT_VBUS_MONITORING_INTERNAL)
            #define DEBUGPRINT_VBUS_DR_PTR    ( (reg8 *) DEBUGPRINT_VBUS__DR)
            #define DEBUGPRINT_VBUS_DR_REG    (*(reg8 *) DEBUGPRINT_VBUS__DR)
            #define DEBUGPRINT_VBUS_PS_PTR    ( (reg8 *) DEBUGPRINT_VBUS__PS)
            #define DEBUGPRINT_VBUS_PS_REG    (*(reg8 *) DEBUGPRINT_VBUS__PS)
            #define DEBUGPRINT_VBUS_MASK          DEBUGPRINT_VBUS__MASK
        #else
            #define DEBUGPRINT_VBUS_PS_PTR    ( (reg8 *) DEBUGPRINT_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define DEBUGPRINT_VBUS_MASK      (0x01u)
        #endif /* (DEBUGPRINT_VBUS_MONITORING_INTERNAL) */
    #endif /*(DEBUGPRINT_VBUS_MONITORING_ENABLE) */
        
    /* Pointer DIE structure in flash (8 bytes): Y and X location, wafer, lot msb, lot lsb, 
    *  work week, fab/year, minor. */
    #define DEBUGPRINT_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

     #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        #if (DEBUGPRINT_DMA1_ACTIVE)
            #define DEBUGPRINT_ep1_TD_TERMOUT_EN  (DEBUGPRINT_ep1__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep1_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA1_ACTIVE) */

        #if (DEBUGPRINT_DMA2_ACTIVE)
            #define DEBUGPRINT_ep2_TD_TERMOUT_EN  (DEBUGPRINT_ep2__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep2_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA2_ACTIVE) */

        #if (DEBUGPRINT_DMA3_ACTIVE)
            #define DEBUGPRINT_ep3_TD_TERMOUT_EN  (DEBUGPRINT_ep3__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep3_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA3_ACTIVE) */

        #if (DEBUGPRINT_DMA4_ACTIVE)
            #define DEBUGPRINT_ep4_TD_TERMOUT_EN  (DEBUGPRINT_ep4__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep4_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA4_ACTIVE) */

        #if (DEBUGPRINT_DMA5_ACTIVE)
            #define DEBUGPRINT_ep5_TD_TERMOUT_EN  (DEBUGPRINT_ep5__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep5_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA5_ACTIVE) */

        #if (DEBUGPRINT_DMA6_ACTIVE)
            #define DEBUGPRINT_ep6_TD_TERMOUT_EN  (DEBUGPRINT_ep6__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep6_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA6_ACTIVE) */

        #if (DEBUGPRINT_DMA7_ACTIVE)
            #define DEBUGPRINT_ep7_TD_TERMOUT_EN  (DEBUGPRINT_ep7__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep7_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA7_ACTIVE) */

        #if (DEBUGPRINT_DMA8_ACTIVE)
            #define DEBUGPRINT_ep8_TD_TERMOUT_EN  (DEBUGPRINT_ep8__TD_TERMOUT_EN)
        #else
            #define DEBUGPRINT_ep8_TD_TERMOUT_EN  (0u)
        #endif /* (DEBUGPRINT_DMA8_ACTIVE) */
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */   
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

/* Rename USB IP registers. */
#define DEBUGPRINT_ARB_CFG        DEBUGPRINT_ARB_CFG_PTR

#define DEBUGPRINT_ARB_EP1_CFG    DEBUGPRINT_ARB_EP1_CFG_PTR
#define DEBUGPRINT_ARB_EP1_INT_EN DEBUGPRINT_ARB_EP1_INT_EN_PTR
#define DEBUGPRINT_ARB_EP1_SR     DEBUGPRINT_ARB_EP1_SR_PTR

#define DEBUGPRINT_ARB_EP2_CFG    DEBUGPRINT_ARB_EP2_CFG_PTR
#define DEBUGPRINT_ARB_EP2_INT_EN DEBUGPRINT_ARB_EP2_INT_EN_PTR
#define DEBUGPRINT_ARB_EP2_SR     DEBUGPRINT_ARB_EP2_SR_PTR

#define DEBUGPRINT_ARB_EP3_CFG    DEBUGPRINT_ARB_EP3_CFG_PTR
#define DEBUGPRINT_ARB_EP3_INT_EN DEBUGPRINT_ARB_EP3_INT_EN_PTR
#define DEBUGPRINT_ARB_EP3_SR     DEBUGPRINT_ARB_EP3_SR_PTR

#define DEBUGPRINT_ARB_EP4_CFG    DEBUGPRINT_ARB_EP4_CFG_PTR
#define DEBUGPRINT_ARB_EP4_INT_EN DEBUGPRINT_ARB_EP4_INT_EN_PTR
#define DEBUGPRINT_ARB_EP4_SR     DEBUGPRINT_ARB_EP4_SR_PTR

#define DEBUGPRINT_ARB_EP5_CFG    DEBUGPRINT_ARB_EP5_CFG_PTR
#define DEBUGPRINT_ARB_EP5_INT_EN DEBUGPRINT_ARB_EP5_INT_EN_PTR
#define DEBUGPRINT_ARB_EP5_SR     DEBUGPRINT_ARB_EP5_SR_PTR

#define DEBUGPRINT_ARB_EP6_CFG    DEBUGPRINT_ARB_EP6_CFG_PTR
#define DEBUGPRINT_ARB_EP6_INT_EN DEBUGPRINT_ARB_EP6_INT_EN_PTR
#define DEBUGPRINT_ARB_EP6_SR     DEBUGPRINT_ARB_EP6_SR_PTR

#define DEBUGPRINT_ARB_EP7_CFG    DEBUGPRINT_ARB_EP7_CFG_PTR
#define DEBUGPRINT_ARB_EP7_INT_EN DEBUGPRINT_ARB_EP7_INT_EN_PTR
#define DEBUGPRINT_ARB_EP7_SR     DEBUGPRINT_ARB_EP7_SR_PTR

#define DEBUGPRINT_ARB_EP8_CFG    DEBUGPRINT_ARB_EP8_CFG_PTR
#define DEBUGPRINT_ARB_EP8_INT_EN DEBUGPRINT_ARB_EP8_INT_EN_PTR
#define DEBUGPRINT_ARB_EP8_SR     DEBUGPRINT_ARB_EP8_SR_PTR

#define DEBUGPRINT_ARB_INT_EN     DEBUGPRINT_ARB_INT_EN_PTR
#define DEBUGPRINT_ARB_INT_SR     DEBUGPRINT_ARB_INT_SR_PTR

#define DEBUGPRINT_ARB_RW1_DR     DEBUGPRINT_ARB_RW1_DR_PTR
#define DEBUGPRINT_ARB_RW1_RA     DEBUGPRINT_ARB_RW1_RA_PTR
#define DEBUGPRINT_ARB_RW1_RA_MSB DEBUGPRINT_ARB_RW1_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW1_WA     DEBUGPRINT_ARB_RW1_WA_PTR
#define DEBUGPRINT_ARB_RW1_WA_MSB DEBUGPRINT_ARB_RW1_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW2_DR     DEBUGPRINT_ARB_RW2_DR_PTR
#define DEBUGPRINT_ARB_RW2_RA     DEBUGPRINT_ARB_RW2_RA_PTR
#define DEBUGPRINT_ARB_RW2_RA_MSB DEBUGPRINT_ARB_RW2_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW2_WA     DEBUGPRINT_ARB_RW2_WA_PTR
#define DEBUGPRINT_ARB_RW2_WA_MSB DEBUGPRINT_ARB_RW2_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW3_DR     DEBUGPRINT_ARB_RW3_DR_PTR
#define DEBUGPRINT_ARB_RW3_RA     DEBUGPRINT_ARB_RW3_RA_PTR
#define DEBUGPRINT_ARB_RW3_RA_MSB DEBUGPRINT_ARB_RW3_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW3_WA     DEBUGPRINT_ARB_RW3_WA_PTR
#define DEBUGPRINT_ARB_RW3_WA_MSB DEBUGPRINT_ARB_RW3_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW4_DR     DEBUGPRINT_ARB_RW4_DR_PTR
#define DEBUGPRINT_ARB_RW4_RA     DEBUGPRINT_ARB_RW4_RA_PTR
#define DEBUGPRINT_ARB_RW4_RA_MSB DEBUGPRINT_ARB_RW4_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW4_WA     DEBUGPRINT_ARB_RW4_WA_PTR
#define DEBUGPRINT_ARB_RW4_WA_MSB DEBUGPRINT_ARB_RW4_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW5_DR     DEBUGPRINT_ARB_RW5_DR_PTR
#define DEBUGPRINT_ARB_RW5_RA     DEBUGPRINT_ARB_RW5_RA_PTR
#define DEBUGPRINT_ARB_RW5_RA_MSB DEBUGPRINT_ARB_RW5_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW5_WA     DEBUGPRINT_ARB_RW5_WA_PTR
#define DEBUGPRINT_ARB_RW5_WA_MSB DEBUGPRINT_ARB_RW5_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW6_DR     DEBUGPRINT_ARB_RW6_DR_PTR
#define DEBUGPRINT_ARB_RW6_RA     DEBUGPRINT_ARB_RW6_RA_PTR
#define DEBUGPRINT_ARB_RW6_RA_MSB DEBUGPRINT_ARB_RW6_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW6_WA     DEBUGPRINT_ARB_RW6_WA_PTR
#define DEBUGPRINT_ARB_RW6_WA_MSB DEBUGPRINT_ARB_RW6_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW7_DR     DEBUGPRINT_ARB_RW7_DR_PTR
#define DEBUGPRINT_ARB_RW7_RA     DEBUGPRINT_ARB_RW7_RA_PTR
#define DEBUGPRINT_ARB_RW7_RA_MSB DEBUGPRINT_ARB_RW7_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW7_WA     DEBUGPRINT_ARB_RW7_WA_PTR
#define DEBUGPRINT_ARB_RW7_WA_MSB DEBUGPRINT_ARB_RW7_WA_MSB_PTR

#define DEBUGPRINT_ARB_RW8_DR     DEBUGPRINT_ARB_RW8_DR_PTR
#define DEBUGPRINT_ARB_RW8_RA     DEBUGPRINT_ARB_RW8_RA_PTR
#define DEBUGPRINT_ARB_RW8_RA_MSB DEBUGPRINT_ARB_RW8_RA_MSB_PTR
#define DEBUGPRINT_ARB_RW8_WA     DEBUGPRINT_ARB_RW8_WA_PTR
#define DEBUGPRINT_ARB_RW8_WA_MSB DEBUGPRINT_ARB_RW8_WA_MSB_PTR

#define DEBUGPRINT_BUF_SIZE       DEBUGPRINT_BUF_SIZE_PTR
#define DEBUGPRINT_BUS_RST_CNT    DEBUGPRINT_BUS_RST_CNT_PTR
#define DEBUGPRINT_CR0            DEBUGPRINT_CR0_PTR
#define DEBUGPRINT_CR1            DEBUGPRINT_CR1_PTR
#define DEBUGPRINT_CWA            DEBUGPRINT_CWA_PTR
#define DEBUGPRINT_CWA_MSB        DEBUGPRINT_CWA_MSB_PTR

#define DEBUGPRINT_DMA_THRES      DEBUGPRINT_DMA_THRES_PTR
#define DEBUGPRINT_DMA_THRES_MSB  DEBUGPRINT_DMA_THRES_MSB_PTR

#define DEBUGPRINT_EP_ACTIVE      DEBUGPRINT_EP_ACTIVE_PTR
#define DEBUGPRINT_EP_TYPE        DEBUGPRINT_EP_TYPE_PTR

#define DEBUGPRINT_EP0_CNT        DEBUGPRINT_EP0_CNT_PTR
#define DEBUGPRINT_EP0_CR         DEBUGPRINT_EP0_CR_PTR
#define DEBUGPRINT_EP0_DR0        DEBUGPRINT_EP0_DR0_PTR
#define DEBUGPRINT_EP0_DR1        DEBUGPRINT_EP0_DR1_PTR
#define DEBUGPRINT_EP0_DR2        DEBUGPRINT_EP0_DR2_PTR
#define DEBUGPRINT_EP0_DR3        DEBUGPRINT_EP0_DR3_PTR
#define DEBUGPRINT_EP0_DR4        DEBUGPRINT_EP0_DR4_PTR
#define DEBUGPRINT_EP0_DR5        DEBUGPRINT_EP0_DR5_PTR
#define DEBUGPRINT_EP0_DR6        DEBUGPRINT_EP0_DR6_PTR
#define DEBUGPRINT_EP0_DR7        DEBUGPRINT_EP0_DR7_PTR

#define DEBUGPRINT_OSCLK_DR0      DEBUGPRINT_OSCLK_DR0_PTR
#define DEBUGPRINT_OSCLK_DR1      DEBUGPRINT_OSCLK_DR1_PTR

#define DEBUGPRINT_PM_ACT_CFG     DEBUGPRINT_PM_ACT_CFG_PTR
#define DEBUGPRINT_PM_STBY_CFG    DEBUGPRINT_PM_STBY_CFG_PTR

#define DEBUGPRINT_SIE_EP_INT_EN  DEBUGPRINT_SIE_EP_INT_EN_PTR
#define DEBUGPRINT_SIE_EP_INT_SR  DEBUGPRINT_SIE_EP_INT_SR_PTR

#define DEBUGPRINT_SIE_EP1_CNT0   DEBUGPRINT_SIE_EP1_CNT0_PTR
#define DEBUGPRINT_SIE_EP1_CNT1   DEBUGPRINT_SIE_EP1_CNT1_PTR
#define DEBUGPRINT_SIE_EP1_CR0    DEBUGPRINT_SIE_EP1_CR0_PTR

#define DEBUGPRINT_SIE_EP2_CNT0   DEBUGPRINT_SIE_EP2_CNT0_PTR
#define DEBUGPRINT_SIE_EP2_CNT1   DEBUGPRINT_SIE_EP2_CNT1_PTR
#define DEBUGPRINT_SIE_EP2_CR0    DEBUGPRINT_SIE_EP2_CR0_PTR

#define DEBUGPRINT_SIE_EP3_CNT0   DEBUGPRINT_SIE_EP3_CNT0_PTR
#define DEBUGPRINT_SIE_EP3_CNT1   DEBUGPRINT_SIE_EP3_CNT1_PTR
#define DEBUGPRINT_SIE_EP3_CR0    DEBUGPRINT_SIE_EP3_CR0_PTR

#define DEBUGPRINT_SIE_EP4_CNT0   DEBUGPRINT_SIE_EP4_CNT0_PTR
#define DEBUGPRINT_SIE_EP4_CNT1   DEBUGPRINT_SIE_EP4_CNT1_PTR
#define DEBUGPRINT_SIE_EP4_CR0    DEBUGPRINT_SIE_EP4_CR0_PTR

#define DEBUGPRINT_SIE_EP5_CNT0   DEBUGPRINT_SIE_EP5_CNT0_PTR
#define DEBUGPRINT_SIE_EP5_CNT1   DEBUGPRINT_SIE_EP5_CNT1_PTR
#define DEBUGPRINT_SIE_EP5_CR0    DEBUGPRINT_SIE_EP5_CR0_PTR

#define DEBUGPRINT_SIE_EP6_CNT0   DEBUGPRINT_SIE_EP6_CNT0_PTR
#define DEBUGPRINT_SIE_EP6_CNT1   DEBUGPRINT_SIE_EP6_CNT1_PTR
#define DEBUGPRINT_SIE_EP6_CR0    DEBUGPRINT_SIE_EP6_CR0_PTR

#define DEBUGPRINT_SIE_EP7_CNT0   DEBUGPRINT_SIE_EP7_CNT0_PTR
#define DEBUGPRINT_SIE_EP7_CNT1   DEBUGPRINT_SIE_EP7_CNT1_PTR
#define DEBUGPRINT_SIE_EP7_CR0    DEBUGPRINT_SIE_EP7_CR0_PTR

#define DEBUGPRINT_SIE_EP8_CNT0   DEBUGPRINT_SIE_EP8_CNT0_PTR
#define DEBUGPRINT_SIE_EP8_CNT1   DEBUGPRINT_SIE_EP8_CNT1_PTR
#define DEBUGPRINT_SIE_EP8_CR0    DEBUGPRINT_SIE_EP8_CR0_PTR

#define DEBUGPRINT_SOF0           DEBUGPRINT_SOF0_PTR
#define DEBUGPRINT_SOF1           DEBUGPRINT_SOF1_PTR

#define DEBUGPRINT_USB_CLK_EN     DEBUGPRINT_USB_CLK_EN_PTR

#define DEBUGPRINT_USBIO_CR0      DEBUGPRINT_USBIO_CR0_PTR
#define DEBUGPRINT_USBIO_CR1      DEBUGPRINT_USBIO_CR1_PTR
#define DEBUGPRINT_USBIO_CR2      DEBUGPRINT_USBIO_CR2_PTR

#define DEBUGPRINT_DM_INP_DIS_PTR     ( (reg8 *) DEBUGPRINT_Dm__INP_DIS)
#define DEBUGPRINT_DM_INP_DIS_REG     (*(reg8 *) DEBUGPRINT_Dm__INP_DIS)
#define DEBUGPRINT_DP_INP_DIS_PTR     ( (reg8 *) DEBUGPRINT_Dp__INP_DIS)
#define DEBUGPRINT_DP_INP_DIS_REG     (*(reg8 *) DEBUGPRINT_Dp__INP_DIS)
#define DEBUGPRINT_DP_INTSTAT_PTR     ( (reg8 *) DEBUGPRINT_Dp__INTSTAT)
#define DEBUGPRINT_DP_INTSTAT_REG     (*(reg8 *) DEBUGPRINT_Dp__INTSTAT)
#define DEBUGPRINT_DM_MASK            DEBUGPRINT_Dm__0__MASK
#define DEBUGPRINT_DP_MASK            DEBUGPRINT_Dp__0__MASK

#define USBFS_SIE_EP_INT_EP1_MASK        (0x01u)
#define USBFS_SIE_EP_INT_EP2_MASK        (0x02u)
#define USBFS_SIE_EP_INT_EP3_MASK        (0x04u)
#define USBFS_SIE_EP_INT_EP4_MASK        (0x08u)
#define USBFS_SIE_EP_INT_EP5_MASK        (0x10u)
#define USBFS_SIE_EP_INT_EP6_MASK        (0x20u)
#define USBFS_SIE_EP_INT_EP7_MASK        (0x40u)
#define USBFS_SIE_EP_INT_EP8_MASK        (0x80u)

#define DEBUGPRINT_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define DEBUGPRINT_ARB_EPX_SR_DMA_GNT         (0x02u)
#define DEBUGPRINT_ARB_EPX_SR_BUF_OVER        (0x04u)
#define DEBUGPRINT_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define DEBUGPRINT_ARB_EPX_INT_EN_ALL DEBUGPRINT_ARB_EPX_INT_ALL

#define DEBUGPRINT_CR1_BUS_ACTIVITY_SHIFT     (0x02u)

#define DEBUGPRINT_BUS_RST_COUNT      DEBUGPRINT_DEFUALT_BUS_RST_CNT

#define DEBUGPRINT_ARB_INT_MASK       DEBUGPRINT_DEFAULT_ARB_INT_EN

#if (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* CY_PSOC3 interrupt registers */
    #define DEBUGPRINT_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define DEBUGPRINT_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define DEBUGPRINT_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define DEBUGPRINT_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* CY_PSOC5LP interrupt registers */
    #define DEBUGPRINT_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define DEBUGPRINT_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define DEBUGPRINT_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define DEBUGPRINT_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


#endif /* (CY_USBFS_DEBUGPRINT_H) */


/* [] END OF FILE */
