/***************************************************************************//**
* \file DEBUGPRINT_vnd.c
* \version 3.10
*
* \brief
*  This file contains the  USB vendor request handler.
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

#if(DEBUGPRINT_EXTERN_VND == DEBUGPRINT_FALSE)

/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: DEBUGPRINT_HandleVendorRqst
****************************************************************************//**
*
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_HandleVendorRqst(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;

    /* Check request direction: D2H or H2D. */
    if (0u != (DEBUGPRINT_bmRequestTypeReg & DEBUGPRINT_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (DEBUGPRINT_bRequestReg)
        {
            case DEBUGPRINT_GET_EXTENDED_CONFIG_DESCRIPTOR:
            #if defined(DEBUGPRINT_ENABLE_MSOS_STRING)
                DEBUGPRINT_currentTD.pData = (volatile uint8 *) &DEBUGPRINT_MSOS_CONFIGURATION_DESCR[0u];
                DEBUGPRINT_currentTD.count = DEBUGPRINT_MSOS_CONFIGURATION_DESCR[0u];
                requestHandled  = DEBUGPRINT_InitControlRead();
            #endif /* (DEBUGPRINT_ENABLE_MSOS_STRING) */
                break;
            
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

#ifdef DEBUGPRINT_HANDLE_VENDOR_RQST_CALLBACK
    if (DEBUGPRINT_FALSE == requestHandled)
    {
        requestHandled = DEBUGPRINT_HandleVendorRqst_Callback();
    }
#endif /* (DEBUGPRINT_HANDLE_VENDOR_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* DEBUGPRINT_EXTERN_VND */


/* [] END OF FILE */
