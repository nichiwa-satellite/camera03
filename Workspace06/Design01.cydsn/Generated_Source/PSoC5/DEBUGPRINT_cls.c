/***************************************************************************//**
* \file DEBUGPRINT_cls.c
* \version 3.10
*
* \brief
*  This file contains the USB Class request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_pvt.h"
#include "cyapicallbacks.h"

#if(DEBUGPRINT_EXTERN_CLS == DEBUGPRINT_FALSE)

/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: DEBUGPRINT_DispatchClassRqst
****************************************************************************//**
*  This routine dispatches class specific requests depend on interface class.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_DispatchClassRqst(void) 
{
    uint8 requestHandled;
    uint8 interfaceNumber;

    /* Get interface to which request is intended. */
    switch (DEBUGPRINT_bmRequestTypeReg & DEBUGPRINT_RQST_RCPT_MASK)
    {
        case DEBUGPRINT_RQST_RCPT_IFC:
            /* Class-specific request directed to interface: wIndexLoReg 
            * contains interface number.
            */
            interfaceNumber = (uint8) DEBUGPRINT_wIndexLoReg;
            break;
        
        case DEBUGPRINT_RQST_RCPT_EP:
            /* Class-specific request directed to endpoint: wIndexLoReg contains 
            * endpoint number. Find interface related to endpoint, 
            */
            interfaceNumber = DEBUGPRINT_EP[DEBUGPRINT_wIndexLoReg & DEBUGPRINT_DIR_UNUSED].interface;
            break;
            
        default:
            /* Default interface is zero. */
            interfaceNumber = 0u;
            break;
    }

#if (defined(DEBUGPRINT_ENABLE_HID_CLASS) ||\
            defined(DEBUGPRINT_ENABLE_AUDIO_CLASS) ||\
            defined(DEBUGPRINT_ENABLE_CDC_CLASS) ||\
            DEBUGPRINT_ENABLE_MSC_CLASS)

    /* Handle class request depends on interface type. */
    switch (DEBUGPRINT_interfaceClass[interfaceNumber])
    {
    #if defined(DEBUGPRINT_ENABLE_HID_CLASS)
        case DEBUGPRINT_CLASS_HID:
            requestHandled = DEBUGPRINT_DispatchHIDClassRqst();
            break;
    #endif /* (DEBUGPRINT_ENABLE_HID_CLASS) */
            
    #if defined(DEBUGPRINT_ENABLE_AUDIO_CLASS)
        case DEBUGPRINT_CLASS_AUDIO:
            requestHandled = DEBUGPRINT_DispatchAUDIOClassRqst();
            break;
    #endif /* (DEBUGPRINT_CLASS_AUDIO) */
            
    #if defined(DEBUGPRINT_ENABLE_CDC_CLASS)
        case DEBUGPRINT_CLASS_CDC:
            requestHandled = DEBUGPRINT_DispatchCDCClassRqst();
            break;
    #endif /* (DEBUGPRINT_ENABLE_CDC_CLASS) */
        
    #if (DEBUGPRINT_ENABLE_MSC_CLASS)
        case DEBUGPRINT_CLASS_MSD:
        #if (DEBUGPRINT_HANDLE_MSC_REQUESTS)
            /* MSC requests are handled by the component. */
            requestHandled = DEBUGPRINT_DispatchMSCClassRqst();
        #elif defined(DEBUGPRINT_DISPATCH_MSC_CLASS_RQST_CALLBACK)
            /* MSC requests are handled by user defined callbcak. */
            requestHandled = DEBUGPRINT_DispatchMSCClassRqst_Callback();
        #else
            /* MSC requests are not handled. */
            requestHandled = DEBUGPRINT_FALSE;
        #endif /* (DEBUGPRINT_HANDLE_MSC_REQUESTS) */
            break;
    #endif /* (DEBUGPRINT_ENABLE_MSC_CLASS) */
        
        default:
            /* Request is not handled: unknown class request type. */
            requestHandled = DEBUGPRINT_FALSE;
            break;
    }
#else /*No class is defined*/
    if (0u != interfaceNumber)
    {
        /* Suppress warning message */
    }
    requestHandled = DEBUGPRINT_FALSE;
#endif /*HID or AUDIO or MSC or CDC class enabled*/

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

#ifdef DEBUGPRINT_DISPATCH_CLASS_RQST_CALLBACK
    if (DEBUGPRINT_FALSE == requestHandled)
    {
        requestHandled = DEBUGPRINT_DispatchClassRqst_Callback(interfaceNumber);
    }
#endif /* (DEBUGPRINT_DISPATCH_CLASS_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* DEBUGPRINT_EXTERN_CLS */


/* [] END OF FILE */
