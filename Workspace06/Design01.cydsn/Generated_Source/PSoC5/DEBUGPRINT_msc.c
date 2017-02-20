/***************************************************************************//**
* \file DEBUGPRINT_cdc.c
* \version 3.10
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
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

#include "DEBUGPRINT_msc.h"
#include "DEBUGPRINT_pvt.h"
#include "cyapicallbacks.h"

#if (DEBUGPRINT_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 DEBUGPRINT_lunCount = DEBUGPRINT_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: DEBUGPRINT_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  DEBUGPRINT_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    
    /* Get request data. */
    uint16 value  = DEBUGPRINT_GET_UINT16(DEBUGPRINT_wValueHiReg,  DEBUGPRINT_wValueLoReg);
    uint16 dataLength = DEBUGPRINT_GET_UINT16(DEBUGPRINT_wLengthHiReg, DEBUGPRINT_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (DEBUGPRINT_bmRequestTypeReg & DEBUGPRINT_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (DEBUGPRINT_MSC_GET_MAX_LUN == DEBUGPRINT_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == DEBUGPRINT_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == DEBUGPRINT_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                DEBUGPRINT_currentTD.pData = &DEBUGPRINT_lunCount;
                DEBUGPRINT_currentTD.count =  DEBUGPRINT_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = DEBUGPRINT_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (DEBUGPRINT_MSC_RESET == DEBUGPRINT_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == DEBUGPRINT_MSC_RESET_WVALUE) &&
                (dataLength == DEBUGPRINT_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                DEBUGPRINT_currentTD.count = DEBUGPRINT_MSC_RESET_WLENGTH;
                
            #ifdef DEBUGPRINT_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                DEBUGPRINT_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (DEBUGPRINT_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  DEBUGPRINT_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_MSC_SetLunCount(uint8 lunCount) 
{
    DEBUGPRINT_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  DEBUGPRINT_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_MSC_GetLunCount(void) 
{
    return (DEBUGPRINT_lunCount + 1u);
}   

#endif /* (DEBUGPRINT_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
