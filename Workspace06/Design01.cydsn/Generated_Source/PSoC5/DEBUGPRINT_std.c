/***************************************************************************//**
* \file DEBUGPRINT_std.c
* \version 3.10
*
* \brief
*  This file contains the USB Standard request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_pvt.h"

/***************************************
*   Static data allocation
***************************************/

#if defined(DEBUGPRINT_ENABLE_FWSN_STRING)
    static volatile uint8* DEBUGPRINT_fwSerialNumberStringDescriptor;
    static volatile uint8  DEBUGPRINT_snStringConfirm = DEBUGPRINT_FALSE;
#endif  /* (DEBUGPRINT_ENABLE_FWSN_STRING) */

#if defined(DEBUGPRINT_ENABLE_FWSN_STRING)
    /***************************************************************************
    * Function Name: DEBUGPRINT_SerialNumString
    ************************************************************************//**
    *
    *  This function is available only when the User Call Back option in the 
    *  Serial Number String descriptor properties is selected. Application 
    *  firmware can provide the source of the USB device serial number string 
    *  descriptor during run time. The default string is used if the application 
    *  firmware does not use this function or sets the wrong string descriptor.
    *
    *  \param snString:  Pointer to the user-defined string descriptor. The 
    *  string descriptor should meet the Universal Serial Bus Specification 
    *  revision 2.0 chapter 9.6.7
    *  Offset|Size|Value|Description
    *  ------|----|------|---------------------------------
    *  0     |1   |N     |Size of this descriptor in bytes
    *  1     |1   |0x03  |STRING Descriptor Type
    *  2     |N-2 |Number|UNICODE encoded string
    *  
    * *For example:* uint8 snString[16]={0x0E,0x03,'F',0,'W',0,'S',0,'N',0,'0',0,'1',0};
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void  DEBUGPRINT_SerialNumString(uint8 snString[]) 
    {
        DEBUGPRINT_snStringConfirm = DEBUGPRINT_FALSE;
        
        if (snString != NULL)
        {
            /* Check descriptor validation */
            if ((snString[0u] > 1u) && (snString[1u] == DEBUGPRINT_DESCR_STRING))
            {
                DEBUGPRINT_fwSerialNumberStringDescriptor = snString;
                DEBUGPRINT_snStringConfirm = DEBUGPRINT_TRUE;
            }
        }
    }
#endif  /* DEBUGPRINT_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: DEBUGPRINT_HandleStandardRqst
****************************************************************************//**
*
*  This Routine dispatches standard requests
*
*
* \return
*  TRUE if request handled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_HandleStandardRqst(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    uint8 bmRequestType = DEBUGPRINT_bmRequestTypeReg;

#if defined(DEBUGPRINT_ENABLE_STRINGS)
    volatile uint8 *pStr = 0u;
    #if defined(DEBUGPRINT_ENABLE_DESCRIPTOR_STRINGS)
        uint8 nStr;
        uint8 descrLength;
    #endif /* (DEBUGPRINT_ENABLE_DESCRIPTOR_STRINGS) */
#endif /* (DEBUGPRINT_ENABLE_STRINGS) */
    
    static volatile uint8 DEBUGPRINT_tBuffer[DEBUGPRINT_STATUS_LENGTH_MAX];
    const T_DEBUGPRINT_LUT CYCODE *pTmp;

    DEBUGPRINT_currentTD.count = 0u;

    if (DEBUGPRINT_RQST_DIR_D2H == (bmRequestType & DEBUGPRINT_RQST_DIR_MASK))
    {
        /* Control Read */
        switch (DEBUGPRINT_bRequestReg)
        {
            case DEBUGPRINT_GET_DESCRIPTOR:
                if (DEBUGPRINT_DESCR_DEVICE ==DEBUGPRINT_wValueHiReg)
                {
                    pTmp = DEBUGPRINT_GetDeviceTablePtr();
                    DEBUGPRINT_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    DEBUGPRINT_currentTD.count = DEBUGPRINT_DEVICE_DESCR_LENGTH;
                    
                    requestHandled  = DEBUGPRINT_InitControlRead();
                }
                else if (DEBUGPRINT_DESCR_CONFIG == DEBUGPRINT_wValueHiReg)
                {
                    pTmp = DEBUGPRINT_GetConfigTablePtr((uint8) DEBUGPRINT_wValueLoReg);
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        DEBUGPRINT_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        DEBUGPRINT_currentTD.count = (uint16)((uint16)(DEBUGPRINT_currentTD.pData)[DEBUGPRINT_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                                                            (DEBUGPRINT_currentTD.pData)[DEBUGPRINT_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = DEBUGPRINT_InitControlRead();
                    }
                }
                
            #if(DEBUGPRINT_BOS_ENABLE)
                else if (DEBUGPRINT_DESCR_BOS == DEBUGPRINT_wValueHiReg)
                {
                    pTmp = DEBUGPRINT_GetBOSPtr();
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        DEBUGPRINT_currentTD.pData = (volatile uint8 *)pTmp;
                        DEBUGPRINT_currentTD.count = ((uint16)((uint16)(DEBUGPRINT_currentTD.pData)[DEBUGPRINT_BOS_DESCR_TOTAL_LENGTH_HI] << 8u)) | \
                                                                             (DEBUGPRINT_currentTD.pData)[DEBUGPRINT_BOS_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = DEBUGPRINT_InitControlRead();
                    }
                }
            #endif /*(DEBUGPRINT_BOS_ENABLE)*/
            
            #if defined(DEBUGPRINT_ENABLE_STRINGS)
                else if (DEBUGPRINT_DESCR_STRING == DEBUGPRINT_wValueHiReg)
                {
                /* Descriptor Strings */
                #if defined(DEBUGPRINT_ENABLE_DESCRIPTOR_STRINGS)
                    nStr = 0u;
                    pStr = (volatile uint8 *) &DEBUGPRINT_STRING_DESCRIPTORS[0u];
                    
                    while ((DEBUGPRINT_wValueLoReg > nStr) && (*pStr != 0u))
                    {
                        /* Read descriptor length from 1st byte */
                        descrLength = *pStr;
                        /* Move to next string descriptor */
                        pStr = &pStr[descrLength];
                        nStr++;
                    }
                #endif /* (DEBUGPRINT_ENABLE_DESCRIPTOR_STRINGS) */
                
                /* Microsoft OS String */
                #if defined(DEBUGPRINT_ENABLE_MSOS_STRING)
                    if (DEBUGPRINT_STRING_MSOS == DEBUGPRINT_wValueLoReg)
                    {
                        pStr = (volatile uint8 *)& DEBUGPRINT_MSOS_DESCRIPTOR[0u];
                    }
                #endif /* (DEBUGPRINT_ENABLE_MSOS_STRING) */
                
                /* SN string */
                #if defined(DEBUGPRINT_ENABLE_SN_STRING)
                    if ((DEBUGPRINT_wValueLoReg != 0u) && 
                        (DEBUGPRINT_wValueLoReg == DEBUGPRINT_DEVICE0_DESCR[DEBUGPRINT_DEVICE_DESCR_SN_SHIFT]))
                    {
                    #if defined(DEBUGPRINT_ENABLE_IDSN_STRING)
                        /* Read DIE ID and generate string descriptor in RAM */
                        DEBUGPRINT_ReadDieID(DEBUGPRINT_idSerialNumberStringDescriptor);
                        pStr = DEBUGPRINT_idSerialNumberStringDescriptor;
                    #elif defined(DEBUGPRINT_ENABLE_FWSN_STRING)
                        
                        if(DEBUGPRINT_snStringConfirm != DEBUGPRINT_FALSE)
                        {
                            pStr = DEBUGPRINT_fwSerialNumberStringDescriptor;
                        }
                        else
                        {
                            pStr = (volatile uint8 *)&DEBUGPRINT_SN_STRING_DESCRIPTOR[0u];
                        }
                    #else
                        pStr = (volatile uint8 *)&DEBUGPRINT_SN_STRING_DESCRIPTOR[0u];
                    #endif  /* (DEBUGPRINT_ENABLE_IDSN_STRING) */
                    }
                #endif /* (DEBUGPRINT_ENABLE_SN_STRING) */
                
                    if (*pStr != 0u)
                    {
                        DEBUGPRINT_currentTD.count = *pStr;
                        DEBUGPRINT_currentTD.pData = pStr;
                        requestHandled  = DEBUGPRINT_InitControlRead();
                    }
                }
            #endif /*  DEBUGPRINT_ENABLE_STRINGS */
                else
                {
                    requestHandled = DEBUGPRINT_DispatchClassRqst();
                }
                break;
                
            case DEBUGPRINT_GET_STATUS:
                switch (bmRequestType & DEBUGPRINT_RQST_RCPT_MASK)
                {
                    case DEBUGPRINT_RQST_RCPT_EP:
                        DEBUGPRINT_currentTD.count = DEBUGPRINT_EP_STATUS_LENGTH;
                        DEBUGPRINT_tBuffer[0u]     = DEBUGPRINT_EP[DEBUGPRINT_wIndexLoReg & DEBUGPRINT_DIR_UNUSED].hwEpState;
                        DEBUGPRINT_tBuffer[1u]     = 0u;
                        DEBUGPRINT_currentTD.pData = &DEBUGPRINT_tBuffer[0u];
                        
                        requestHandled  = DEBUGPRINT_InitControlRead();
                        break;
                    case DEBUGPRINT_RQST_RCPT_DEV:
                        DEBUGPRINT_currentTD.count = DEBUGPRINT_DEVICE_STATUS_LENGTH;
                        DEBUGPRINT_tBuffer[0u]     = DEBUGPRINT_deviceStatus;
                        DEBUGPRINT_tBuffer[1u]     = 0u;
                        DEBUGPRINT_currentTD.pData = &DEBUGPRINT_tBuffer[0u];
                        
                        requestHandled  = DEBUGPRINT_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case DEBUGPRINT_GET_CONFIGURATION:
                DEBUGPRINT_currentTD.count = 1u;
                DEBUGPRINT_currentTD.pData = (volatile uint8 *) &DEBUGPRINT_configuration;
                requestHandled  = DEBUGPRINT_InitControlRead();
                break;
                
            case DEBUGPRINT_GET_INTERFACE:
                DEBUGPRINT_currentTD.count = 1u;
                DEBUGPRINT_currentTD.pData = (volatile uint8 *) &DEBUGPRINT_interfaceSetting[DEBUGPRINT_wIndexLoReg];
                requestHandled  = DEBUGPRINT_InitControlRead();
                break;
                
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {
        /* Control Write */
        switch (DEBUGPRINT_bRequestReg)
        {
            case DEBUGPRINT_SET_ADDRESS:
                /* Store address to be set in DEBUGPRINT_NoDataControlStatusStage(). */
                DEBUGPRINT_deviceAddress = (uint8) DEBUGPRINT_wValueLoReg;
                requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                break;
                
            case DEBUGPRINT_SET_CONFIGURATION:
                configurationN = DEBUGPRINT_wValueLoReg;
                
                /* Verify that configuration descriptor exists */
                if(configurationN > 0u)
                {
                    pTmp = DEBUGPRINT_GetConfigTablePtr((uint8) configurationN - 1u);
                }
                
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != DEBUGPRINT_configuration)
                    {
                        DEBUGPRINT_configuration = (uint8) configurationN;
                        DEBUGPRINT_configurationChanged = DEBUGPRINT_TRUE;
                        DEBUGPRINT_Config(DEBUGPRINT_TRUE);
                    }
                    requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                }
                break;
                
            case DEBUGPRINT_SET_INTERFACE:
                if (0u != DEBUGPRINT_ValidateAlternateSetting())
                {
                    /* Get interface number from the request. */
                    interfaceNumber = DEBUGPRINT_wIndexLoReg;
                    DEBUGPRINT_interfaceNumber = (uint8) DEBUGPRINT_wIndexLoReg;
                     
                    /* Check if alternate settings is changed for interface. */
                    if (DEBUGPRINT_interfaceSettingLast[interfaceNumber] != DEBUGPRINT_interfaceSetting[interfaceNumber])
                    {
                        DEBUGPRINT_configurationChanged = DEBUGPRINT_TRUE;
                    
                        /* Change alternate setting for the endpoints. */
                    #if (DEBUGPRINT_EP_MANAGEMENT_MANUAL && DEBUGPRINT_EP_ALLOC_DYNAMIC)
                        DEBUGPRINT_Config(DEBUGPRINT_FALSE);
                    #else
                        DEBUGPRINT_ConfigAltChanged();
                    #endif /* (DEBUGPRINT_EP_MANAGEMENT_MANUAL && DEBUGPRINT_EP_ALLOC_DYNAMIC) */
                    }
                    
                    requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                }
                break;
                
            case DEBUGPRINT_CLEAR_FEATURE:
                switch (bmRequestType & DEBUGPRINT_RQST_RCPT_MASK)
                {
                    case DEBUGPRINT_RQST_RCPT_EP:
                        if (DEBUGPRINT_wValueLoReg == DEBUGPRINT_ENDPOINT_HALT)
                        {
                            requestHandled = DEBUGPRINT_ClearEndpointHalt();
                        }
                        break;
                    case DEBUGPRINT_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (DEBUGPRINT_wValueLoReg == DEBUGPRINT_DEVICE_REMOTE_WAKEUP)
                        {
                            DEBUGPRINT_deviceStatus &= (uint8)~DEBUGPRINT_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                        }
                        break;
                    case DEBUGPRINT_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (DEBUGPRINT_wIndexLoReg < DEBUGPRINT_MAX_INTERFACES_NUMBER)
                        {
                            DEBUGPRINT_interfaceStatus[DEBUGPRINT_wIndexLoReg] &= (uint8) ~DEBUGPRINT_wValueLoReg;
                            requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case DEBUGPRINT_SET_FEATURE:
                switch (bmRequestType & DEBUGPRINT_RQST_RCPT_MASK)
                {
                    case DEBUGPRINT_RQST_RCPT_EP:
                        if (DEBUGPRINT_wValueLoReg == DEBUGPRINT_ENDPOINT_HALT)
                        {
                            requestHandled = DEBUGPRINT_SetEndpointHalt();
                        }
                        break;
                        
                    case DEBUGPRINT_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (DEBUGPRINT_wValueLoReg == DEBUGPRINT_DEVICE_REMOTE_WAKEUP)
                        {
                            DEBUGPRINT_deviceStatus |= DEBUGPRINT_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                        }
                        break;
                        
                    case DEBUGPRINT_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (DEBUGPRINT_wIndexLoReg < DEBUGPRINT_MAX_INTERFACES_NUMBER)
                        {
                            DEBUGPRINT_interfaceStatus[DEBUGPRINT_wIndexLoReg] &= (uint8) ~DEBUGPRINT_wValueLoReg;
                            requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                        }
                        break;
                    
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    
    return (requestHandled);
}


#if defined(DEBUGPRINT_ENABLE_IDSN_STRING)
    /***************************************************************************
    * Function Name: DEBUGPRINT_ReadDieID
    ************************************************************************//**
    *
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    *  \param descr:  pointer on string descriptor. This string size has to be equal or
    *          greater than DEBUGPRINT_IDSN_DESCR_LENGTH.
    *
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void DEBUGPRINT_ReadDieID(uint8 descr[]) 
    {
        const char8 CYCODE hex[] = "0123456789ABCDEF";
        uint8 i;
        uint8 j = 0u;
        uint8 uniqueId[8u];

        if (NULL != descr)
        {
            /* Initialize descriptor header. */
            descr[0u] = DEBUGPRINT_IDSN_DESCR_LENGTH;
            descr[1u] = DEBUGPRINT_DESCR_STRING;
            
            /* Unique ID size is 8 bytes. */
            CyGetUniqueId((uint32 *) uniqueId);

            /* Fill descriptor with unique device ID. */
            for (i = 2u; i < DEBUGPRINT_IDSN_DESCR_LENGTH; i += 4u)
            {
                descr[i]      = (uint8) hex[(uniqueId[j] >> 4u)];
                descr[i + 1u] = 0u;
                descr[i + 2u] = (uint8) hex[(uniqueId[j] & 0x0Fu)];
                descr[i + 3u] = 0u;
                ++j;
            }
        }
    }
#endif /* (DEBUGPRINT_ENABLE_IDSN_STRING) */


/*******************************************************************************
* Function Name: DEBUGPRINT_ConfigReg
****************************************************************************//**
*
*  This routine configures hardware registers from the variables.
*  It is called from DEBUGPRINT_Config() function and from RestoreConfig
*  after Wakeup.
*
*******************************************************************************/
void DEBUGPRINT_ConfigReg(void) 
{
    uint8 ep;

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
    uint8 epType = 0u;
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */

    /* Go thought all endpoints and set hardware configuration */
    for (ep = DEBUGPRINT_EP1; ep < DEBUGPRINT_MAX_EP; ++ep)
    {
        DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epCfg = DEBUGPRINT_ARB_EPX_CFG_DEFAULT;
        
    #if (DEBUGPRINT_EP_MANAGEMENT_DMA)
        /* Enable arbiter endpoint interrupt sources */
        DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epIntEn = DEBUGPRINT_ARB_EPX_INT_MASK;
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */
    
        if (DEBUGPRINT_EP[ep].epMode != DEBUGPRINT_MODE_DISABLE)
        {
            if (0u != (DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN))
            {
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_NAK_IN;
                
            #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4)
                /* Clear DMA_TERMIN for IN endpoint. */
                DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epIntEn &= (uint32) ~DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN;
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4) */
            }
            else
            {
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_NAK_OUT;

            #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
                /* (CY_PSOC4): DMA_TERMIN for OUT endpoint is set above. */
                
                /* Prepare endpoint type mask. */
                epType |= (uint8) (0x01u << (ep - DEBUGPRINT_EP1));
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
            }
        }
        else
        {
            DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_STALL_DATA_EP;
        }
        
    #if (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        #if (CY_PSOC4)
            DEBUGPRINT_ARB_EP16_BASE.arbEp[ep].rwRa16  = (uint32) DEBUGPRINT_EP[ep].buffOffset;
            DEBUGPRINT_ARB_EP16_BASE.arbEp[ep].rwWa16  = (uint32) DEBUGPRINT_EP[ep].buffOffset;
        #else
            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwRa    = LO8(DEBUGPRINT_EP[ep].buffOffset);
            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwRaMsb = HI8(DEBUGPRINT_EP[ep].buffOffset);
            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwWa    = LO8(DEBUGPRINT_EP[ep].buffOffset);
            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwWaMsb = HI8(DEBUGPRINT_EP[ep].buffOffset);
        #endif /* (CY_PSOC4) */
    #endif /* (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
    }

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
     /* BUF_SIZE depend on DMA_THRESS value:0x55-32 bytes  0x44-16 bytes 0x33-8 bytes 0x22-4 bytes 0x11-2 bytes */
    DEBUGPRINT_BUF_SIZE_REG = DEBUGPRINT_DMA_BUF_SIZE;

    /* Configure DMA burst threshold */
#if (CY_PSOC4)
    DEBUGPRINT_DMA_THRES16_REG   = DEBUGPRINT_DMA_BYTES_PER_BURST;
#else
    DEBUGPRINT_DMA_THRES_REG     = DEBUGPRINT_DMA_BYTES_PER_BURST;
    DEBUGPRINT_DMA_THRES_MSB_REG = 0u;
#endif /* (CY_PSOC4) */
    DEBUGPRINT_EP_ACTIVE_REG = DEBUGPRINT_DEFAULT_ARB_INT_EN;
    DEBUGPRINT_EP_TYPE_REG   = epType;
    
    /* Cfg_cmp bit set to 1 once configuration is complete. */
    /* Lock arbiter configtuation */
    DEBUGPRINT_ARB_CFG_REG |= (uint8)  DEBUGPRINT_ARB_CFG_CFG_CMP;
    /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
    DEBUGPRINT_ARB_CFG_REG &= (uint8) ~DEBUGPRINT_ARB_CFG_CFG_CMP;

#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */

    /* Enable interrupt SIE interurpt source from EP0-EP1 */
    DEBUGPRINT_SIE_EP_INT_EN_REG = (uint8) DEBUGPRINT_DEFAULT_SIE_EP_INT_EN;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_EpStateInit
****************************************************************************//**
*
*  This routine initialize state of Data end points based of its type: 
*   IN  - DEBUGPRINT_IN_BUFFER_EMPTY (DEBUGPRINT_EVENT_PENDING)
*   OUT - DEBUGPRINT_OUT_BUFFER_EMPTY (DEBUGPRINT_NO_EVENT_PENDING)
*
*******************************************************************************/
void DEBUGPRINT_EpStateInit(void) 
{
    uint8 i;

    for (i = DEBUGPRINT_EP1; i < DEBUGPRINT_MAX_EP; i++)
    { 
        if (0u != (DEBUGPRINT_EP[i].addr & DEBUGPRINT_DIR_IN))
        {
            /* IN Endpoint */
            DEBUGPRINT_EP[i].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }
        else
        {
            /* OUT Endpoint */
            DEBUGPRINT_EP[i].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;
        }
    }
                    
}


/*******************************************************************************
* Function Name: DEBUGPRINT_Config
****************************************************************************//**
*
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
*  \param clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* DEBUGPRINT_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 curEp;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    
    #if (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        uint16 buffCount = 0u;
    #endif /* (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */

    const T_DEBUGPRINT_LUT CYCODE *pTmp;
    const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear endpoints settings */
    for (ep = 0u; ep < DEBUGPRINT_MAX_EP; ++ep)
    {
        DEBUGPRINT_EP[ep].attrib     = 0u;
        DEBUGPRINT_EP[ep].hwEpState  = 0u;
        DEBUGPRINT_EP[ep].epToggle   = 0u;
        DEBUGPRINT_EP[ep].bufferSize = 0u;
        DEBUGPRINT_EP[ep].interface  = 0u;
        DEBUGPRINT_EP[ep].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;
        DEBUGPRINT_EP[ep].epMode     = DEBUGPRINT_MODE_DISABLE;   
    }

    /* Clear Alternate settings for all interfaces. */
    if (0u != clearAltSetting)
    {
        for (i = 0u; i < DEBUGPRINT_MAX_INTERFACES_NUMBER; ++i)
        {
            DEBUGPRINT_interfaceSetting[i]     = 0u;
            DEBUGPRINT_interfaceSettingLast[i] = 0u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if (DEBUGPRINT_configuration > 0u)
    {
        #if defined(DEBUGPRINT_ENABLE_CDC_CLASS)
            uint8 cdcComNums = 0u;
        #endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS) */  

        pTmp = DEBUGPRINT_GetConfigTablePtr(DEBUGPRINT_configuration - 1u);
        
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if ((pDescr[DEBUGPRINT_CONFIG_DESCR_ATTRIB] & DEBUGPRINT_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            DEBUGPRINT_deviceStatus |= (uint8)  DEBUGPRINT_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            DEBUGPRINT_deviceStatus &= (uint8) ~DEBUGPRINT_DEVICE_STATUS_SELF_POWERED;
        }
        
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if (DEBUGPRINT_EP_MANAGEMENT_MANUAL && DEBUGPRINT_EP_ALLOC_DYNAMIC)
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_DEBUGPRINT_EP_SETTINGS_BLOCK *) pTmp->p_list;
            
            for (i = 0u; i < ep; i++)
            {     
                /* Compare current Alternate setting with EP Alt */
                if (DEBUGPRINT_interfaceSetting[pEP->interface] == pEP->altSetting)
                {                                                          
                    curEp  = pEP->addr & DEBUGPRINT_DIR_UNUSED;
                    epType = pEP->attributes & DEBUGPRINT_EP_TYPE_MASK;
                    
                    DEBUGPRINT_EP[curEp].addr       = pEP->addr;
                    DEBUGPRINT_EP[curEp].attrib     = pEP->attributes;
                    DEBUGPRINT_EP[curEp].bufferSize = pEP->bufferSize;

                    if (0u != (pEP->addr & DEBUGPRINT_DIR_IN))
                    {
                        /* IN Endpoint */
                        DEBUGPRINT_EP[curEp].epMode     = DEBUGPRINT_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                        DEBUGPRINT_EP[curEp].apiEpState = DEBUGPRINT_EVENT_PENDING;
                    
                    #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0))
                        if ((pEP->bMisc == DEBUGPRINT_CLASS_AUDIO) && (epType == DEBUGPRINT_EP_TYPE_BULK))
                        {
                            DEBUGPRINT_midi_in_ep = curEp;
                        }
                    #endif  /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */
                    }
                    else
                    {
                        /* OUT Endpoint */
                        DEBUGPRINT_EP[curEp].epMode     = DEBUGPRINT_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                        DEBUGPRINT_EP[curEp].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;
                        
                    #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0))
                        if ((pEP->bMisc == DEBUGPRINT_CLASS_AUDIO) && (epType == DEBUGPRINT_EP_TYPE_BULK))
                        {
                            DEBUGPRINT_midi_out_ep = curEp;
                        }
                    #endif  /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */
                    }

                #if(defined (DEBUGPRINT_ENABLE_CDC_CLASS))
                    if((pEP->bMisc == DEBUGPRINT_CLASS_CDC_DATA) ||(pEP->bMisc == DEBUGPRINT_CLASS_CDC))
                    {
                        cdcComNums = DEBUGPRINT_Cdc_EpInit(pEP, curEp, cdcComNums);
                    }
                #endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS) */
                }
                
                pEP = &pEP[1u];
            }
            
        #else
            for (i = DEBUGPRINT_EP1; i < DEBUGPRINT_MAX_EP; ++i)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                
                for (curEp = 0u; curEp < ep; ++curEp)
                {
                    if (i == (pEP->addr & DEBUGPRINT_DIR_UNUSED))
                    {
                        /* Compare endpoint buffers size with current size to find greater. */
                        if (DEBUGPRINT_EP[i].bufferSize < pEP->bufferSize)
                        {
                            DEBUGPRINT_EP[i].bufferSize = pEP->bufferSize;
                        }
                        
                        /* Compare current Alternate setting with EP Alt */
                        if (DEBUGPRINT_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {                            
                            DEBUGPRINT_EP[i].addr = pEP->addr;
                            DEBUGPRINT_EP[i].attrib = pEP->attributes;
                            
                            epType = pEP->attributes & DEBUGPRINT_EP_TYPE_MASK;
                            
                            if (0u != (pEP->addr & DEBUGPRINT_DIR_IN))
                            {
                                /* IN Endpoint */
                                DEBUGPRINT_EP[i].epMode     = DEBUGPRINT_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                                DEBUGPRINT_EP[i].apiEpState = DEBUGPRINT_EVENT_PENDING;
                                
                            #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && (DEBUGPRINT_MIDI_IN_BUFF_SIZE > 0))
                                if ((pEP->bMisc == DEBUGPRINT_CLASS_AUDIO) && (epType == DEBUGPRINT_EP_TYPE_BULK))
                                {
                                    DEBUGPRINT_midi_in_ep = i;
                                }
                            #endif  /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */
                            }
                            else
                            {
                                /* OUT Endpoint */
                                DEBUGPRINT_EP[i].epMode     = DEBUGPRINT_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                                DEBUGPRINT_EP[i].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;
                                
                            #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && (DEBUGPRINT_MIDI_OUT_BUFF_SIZE > 0))
                                if ((pEP->bMisc == DEBUGPRINT_CLASS_AUDIO) && (epType == DEBUGPRINT_EP_TYPE_BULK))
                                {
                                    DEBUGPRINT_midi_out_ep = i;
                                }
                            #endif  /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */
                            }

                        #if (defined(DEBUGPRINT_ENABLE_CDC_CLASS))
                            if((pEP->bMisc == DEBUGPRINT_CLASS_CDC_DATA) ||(pEP->bMisc == DEBUGPRINT_CLASS_CDC))
                            {
                                cdcComNums = DEBUGPRINT_Cdc_EpInit(pEP, i, cdcComNums);
                            }
                        #endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS) */

                            #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
                                break;  /* Use first EP setting in Auto memory management */
                            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
                        }
                    }
                    
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (DEBUGPRINT_EP_MANAGEMENT_MANUAL && DEBUGPRINT_EP_ALLOC_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP */
            DEBUGPRINT_EP[pEP->addr & DEBUGPRINT_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        
        /* Init pointer on interface class table */
        DEBUGPRINT_interfaceClass = DEBUGPRINT_GetInterfaceClassTablePtr();
        
    /* Set the endpoint buffer addresses */
    #if (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        buffCount = 0u;
        for (ep = DEBUGPRINT_EP1; ep < DEBUGPRINT_MAX_EP; ++ep)
        {
            DEBUGPRINT_EP[ep].buffOffset = buffCount;        
            buffCount += DEBUGPRINT_EP[ep].bufferSize;
            
        #if (DEBUGPRINT_GEN_16BITS_EP_ACCESS)
            /* Align EP buffers to be event size to access 16-bits DR register. */
            buffCount += (0u != (buffCount & 0x01u)) ? 1u : 0u;
        #endif /* (DEBUGPRINT_GEN_16BITS_EP_ACCESS) */            
        }
    #endif /* (!DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */

        /* Configure hardware registers */
        DEBUGPRINT_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ConfigAltChanged
****************************************************************************//**
*
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 curEp;
    uint8 epType;
    uint8 i;
    uint8 interfaceNum;

    const T_DEBUGPRINT_LUT CYCODE *pTmp;
    const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Init Endpoints and Device Status if configured */
    if (DEBUGPRINT_configuration > 0u)
    {
        /* Get number of endpoints configurations (ep). */
        pTmp = DEBUGPRINT_GetConfigTablePtr(DEBUGPRINT_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;

        /* Get pointer to endpoints setting table (pEP). */
        pEP = (const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        
        /* Look through all possible endpoint configurations. Find endpoints 
        * which belong to current interface and alternate settings for 
        * re-configuration.
        */
        interfaceNum = DEBUGPRINT_interfaceNumber;
        for (i = 0u; i < ep; i++)
        {
            /* Find endpoints which belong to current interface and alternate settings. */
            if ((interfaceNum == pEP->interface) && 
                (DEBUGPRINT_interfaceSetting[interfaceNum] == pEP->altSetting))
            {
                curEp  = ((uint8) pEP->addr & DEBUGPRINT_DIR_UNUSED);
                epType = ((uint8) pEP->attributes & DEBUGPRINT_EP_TYPE_MASK);
                
                /* Change the SIE mode for the selected EP to NAK ALL */
                DEBUGPRINT_EP[curEp].epToggle   = 0u;
                DEBUGPRINT_EP[curEp].addr       = pEP->addr;
                DEBUGPRINT_EP[curEp].attrib     = pEP->attributes;
                DEBUGPRINT_EP[curEp].bufferSize = pEP->bufferSize;

                if (0u != (pEP->addr & DEBUGPRINT_DIR_IN))
                {
                    /* IN Endpoint */
                    DEBUGPRINT_EP[curEp].epMode     = DEBUGPRINT_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                    DEBUGPRINT_EP[curEp].apiEpState = DEBUGPRINT_EVENT_PENDING;
                }
                else
                {
                    /* OUT Endpoint */
                    DEBUGPRINT_EP[curEp].epMode     = DEBUGPRINT_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                    DEBUGPRINT_EP[curEp].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;
                }
                
                /* Make SIE to NAK any endpoint requests */
                DEBUGPRINT_SIE_EP_BASE.sieEp[curEp].epCr0 = DEBUGPRINT_MODE_NAK_IN_OUT;

            #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
                /* Clear IN data ready. */
                DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].epCfg &= (uint8) ~DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY;

                /* Select endpoint number of reconfiguration */
                DEBUGPRINT_DYN_RECONFIG_REG = (uint8) ((curEp - 1u) << DEBUGPRINT_DYN_RECONFIG_EP_SHIFT);
                
                /* Request for dynamic re-configuration of endpoint. */
                DEBUGPRINT_DYN_RECONFIG_REG |= DEBUGPRINT_DYN_RECONFIG_ENABLE;
                
                /* Wait until block is ready for re-configuration */
                while (0u == (DEBUGPRINT_DYN_RECONFIG_REG & DEBUGPRINT_DYN_RECONFIG_RDY_STS))
                {
                }
                
                /* Once DYN_RECONFIG_RDY_STS bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if (0u != (pEP->addr & DEBUGPRINT_DIR_IN))
                {
                    /* Set endpoint type: 0 - IN and 1 - OUT. */
                    DEBUGPRINT_EP_TYPE_REG &= (uint8) ~(uint8)((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Clear DMA_TERMIN for IN endpoint */
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].epIntEn &= (uint32) ~DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                else
                {
                    /* Set endpoint type: 0 - IN and 1- OUT. */
                    DEBUGPRINT_EP_TYPE_REG |= (uint8) ((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Set DMA_TERMIN for OUT endpoint */
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].epIntEn |= (uint32) DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                
                /* Complete dynamic re-configuration: all endpoint related status and signals 
                * are set into the default state.
                */
                DEBUGPRINT_DYN_RECONFIG_REG &= (uint8) ~DEBUGPRINT_DYN_RECONFIG_ENABLE;

            #else
                DEBUGPRINT_SIE_EP_BASE.sieEp[curEp].epCnt0 = HI8(DEBUGPRINT_EP[curEp].bufferSize);
                DEBUGPRINT_SIE_EP_BASE.sieEp[curEp].epCnt1 = LO8(DEBUGPRINT_EP[curEp].bufferSize);
                
                #if (CY_PSOC4)
                    DEBUGPRINT_ARB_EP16_BASE.arbEp[curEp].rwRa16  = (uint32) DEBUGPRINT_EP[curEp].buffOffset;
                    DEBUGPRINT_ARB_EP16_BASE.arbEp[curEp].rwWa16  = (uint32) DEBUGPRINT_EP[curEp].buffOffset;
                #else
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].rwRa    = LO8(DEBUGPRINT_EP[curEp].buffOffset);
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].rwRaMsb = HI8(DEBUGPRINT_EP[curEp].buffOffset);
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].rwWa    = LO8(DEBUGPRINT_EP[curEp].buffOffset);
                    DEBUGPRINT_ARB_EP_BASE.arbEp[curEp].rwWaMsb = HI8(DEBUGPRINT_EP[curEp].buffOffset);
                #endif /* (CY_PSOC4) */                
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
            }
            
            pEP = &pEP[1u]; /* Get next EP element */
        }
        
        /* The main loop has to re-enable DMA and OUT endpoint */
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetConfigTablePtr
****************************************************************************//**
*
*  This routine returns a pointer a configuration table entry
*
*  \param confIndex:  Configuration Index
*
* \return
*  Device Descriptor pointer or NULL when descriptor does not exist.
*
*******************************************************************************/
const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_DEBUGPRINT_LUT CYCODE *pTmp;

    pTmp = (const T_DEBUGPRINT_LUT CYCODE *) DEBUGPRINT_TABLE[DEBUGPRINT_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the second entry point to the BOS Descriptor
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[2u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_DEBUGPRINT_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_DEBUGPRINT_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return (pTmp);
}


#if (DEBUGPRINT_BOS_ENABLE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_GetBOSPtr
    ****************************************************************************//**
    *
    *  This routine returns a pointer a BOS table entry
    *
    *  
    *
    * \return
    *  BOS Descriptor pointer or NULL when descriptor does not exist.
    *
    *******************************************************************************/
    const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetBOSPtr(void)
                                                            
    {
        /* Device Table */
        const T_DEBUGPRINT_LUT CYCODE *pTmp;

        pTmp = (const T_DEBUGPRINT_LUT CYCODE *) DEBUGPRINT_TABLE[DEBUGPRINT_device].p_list;

        /* The first entry points to the Device Descriptor,
        *  the second entry points to the BOS Descriptor
        */
        pTmp = &pTmp[1u];
        pTmp = (const T_DEBUGPRINT_LUT CYCODE *) pTmp->p_list;
        return (pTmp);
    }
#endif /* (DEBUGPRINT_BOS_ENABLE) */


/*******************************************************************************
* Function Name: DEBUGPRINT_GetDeviceTablePtr
****************************************************************************//**
*
*  This routine returns a pointer to the Device table
*
* \return
*  Device Table pointer
*
*******************************************************************************/
const T_DEBUGPRINT_LUT CYCODE *DEBUGPRINT_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_DEBUGPRINT_LUT CYCODE *) DEBUGPRINT_TABLE[DEBUGPRINT_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
****************************************************************************//**
*
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* \return
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *DEBUGPRINT_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_DEBUGPRINT_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = DEBUGPRINT_GetConfigTablePtr(DEBUGPRINT_configuration - 1u);
    if (pTmp != NULL)
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[DEBUGPRINT_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return (pInterfaceClass);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_TerminateEP
****************************************************************************//**
*
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
*  \param ep Contains the data endpoint number.
*
*  \reentrant
*  No.
*
* \sideeffect
* 
* The device responds with a NAK for any transactions on the selected endpoint.
*   
*******************************************************************************/
void DEBUGPRINT_TerminateEP(uint8 epNumber) 
{
    /* Get endpoint number */
    epNumber &= DEBUGPRINT_DIR_UNUSED;

    if ((epNumber > DEBUGPRINT_EP0) && (epNumber < DEBUGPRINT_MAX_EP))
    {
        /* Set the endpoint Halt */
        DEBUGPRINT_EP[epNumber].hwEpState |= DEBUGPRINT_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        DEBUGPRINT_EP[epNumber].epToggle = 0u;
        DEBUGPRINT_EP[epNumber].apiEpState = DEBUGPRINT_NO_EVENT_ALLOWED;

        if ((DEBUGPRINT_EP[epNumber].addr & DEBUGPRINT_DIR_IN) != 0u)
        {   
            /* IN Endpoint */
            DEBUGPRINT_SIE_EP_BASE.sieEp[epNumber].epCr0 = DEBUGPRINT_MODE_NAK_IN;
        }
        else
        {
            /* OUT Endpoint */
            DEBUGPRINT_SIE_EP_BASE.sieEp[epNumber].epCr0 = DEBUGPRINT_MODE_NAK_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_SetEndpointHalt
****************************************************************************//**
*
*  This routine handles set endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_SetEndpointHalt(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    uint8 ep;
    
    /* Set endpoint halt */
    ep = DEBUGPRINT_wIndexLoReg & DEBUGPRINT_DIR_UNUSED;

    if ((ep > DEBUGPRINT_EP0) && (ep < DEBUGPRINT_MAX_EP))
    {
        /* Set the endpoint Halt */
        DEBUGPRINT_EP[ep].hwEpState |= (DEBUGPRINT_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        DEBUGPRINT_EP[ep].epToggle = 0u;
        DEBUGPRINT_EP[ep].apiEpState |= DEBUGPRINT_NO_EVENT_ALLOWED;

        if ((DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = (DEBUGPRINT_MODE_STALL_DATA_EP | 
                                                            DEBUGPRINT_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = (DEBUGPRINT_MODE_STALL_DATA_EP | 
                                                            DEBUGPRINT_MODE_ACK_OUT);
        }
        requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ClearEndpointHalt
****************************************************************************//**
*
*  This routine handles clear endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_ClearEndpointHalt(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    uint8 ep;

    /* Clear endpoint halt */
    ep = DEBUGPRINT_wIndexLoReg & DEBUGPRINT_DIR_UNUSED;

    if ((ep > DEBUGPRINT_EP0) && (ep < DEBUGPRINT_MAX_EP))
    {
        /* Clear the endpoint Halt */
        DEBUGPRINT_EP[ep].hwEpState &= (uint8) ~DEBUGPRINT_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        DEBUGPRINT_EP[ep].epToggle = 0u;
        
        /* Clear toggle bit for already armed packet */
        DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCnt0 = (uint8) ~(uint8)DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
        
        /* Return API State as it was defined before */
        DEBUGPRINT_EP[ep].apiEpState &= (uint8) ~DEBUGPRINT_NO_EVENT_ALLOWED;

        if ((DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(DEBUGPRINT_EP[ep].apiEpState == DEBUGPRINT_IN_BUFFER_EMPTY)
            {       
                /* Wait for next packet from application */
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_NAK_IN;
            }
            else    /* Continue armed transfer */
            {
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_ACK_IN;
            }
        }
        else
        {
            /* OUT Endpoint */
            if (DEBUGPRINT_EP[ep].apiEpState == DEBUGPRINT_OUT_BUFFER_FULL)
            {       
                /* Allow application to read full buffer */
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_NAK_OUT;
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_MODE_ACK_OUT;
            }
        }
        
        requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ValidateAlternateSetting
****************************************************************************//**
*
*  Validates (and records) a SET INTERFACE request.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    
    uint8 interfaceNum;
    uint8 curInterfacesNum;
    const T_DEBUGPRINT_LUT CYCODE *pTmp;
    
    /* Get interface number from the request. */
    interfaceNum = (uint8) DEBUGPRINT_wIndexLoReg;
    
    /* Get number of interfaces for current configuration. */
    pTmp = DEBUGPRINT_GetConfigTablePtr(DEBUGPRINT_configuration - 1u);
    curInterfacesNum  = ((const uint8 *) pTmp->p_list)[DEBUGPRINT_CONFIG_DESCR_NUM_INTERFACES];

    /* Validate that interface number is within range. */
    if ((interfaceNum <= curInterfacesNum) || (interfaceNum <= DEBUGPRINT_MAX_INTERFACES_NUMBER))
    {
        /* Save current and new alternate settings (come with request) to make 
        * desicion about following endpoint re-configuration.
        */
        DEBUGPRINT_interfaceSettingLast[interfaceNum] = DEBUGPRINT_interfaceSetting[interfaceNum];
        DEBUGPRINT_interfaceSetting[interfaceNum]     = (uint8) DEBUGPRINT_wValueLoReg;
        
        requestHandled = DEBUGPRINT_TRUE;
    }

    return (requestHandled);
}


/* [] END OF FILE */
