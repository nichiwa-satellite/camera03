/***************************************************************************//**
* \file DEBUGPRINT_boot.c
* \version 3.10
*
* \brief
*  This file contains the Bootloader API for USBFS Component.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_pvt.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUGPRINT) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))   

/***************************************
*    Bootloader Variables
***************************************/
    

static uint8  DEBUGPRINT_started = 0u;


/*******************************************************************************
* Function Name: DEBUGPRINT_CyBtldrCommStart
****************************************************************************//**
*
*  This function performs all required initialization for the USBFS component, 
*  waits on enumeration, and enables communication.
*
* \sideeffect
*  This function starts the USB with 3V or 5V operation.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_CyBtldrCommStart(void) 
{
    /* Enable Global Interrupts. Interrupts are mandatory for USBFS component operation. */
    CyGlobalIntEnable;

    /* Start USBFS Operation: device 0 and with 5V or 3V operation depend on Voltage Configuration in DWR. */
    DEBUGPRINT_Start(0u, DEBUGPRINT_DWR_POWER_OPERATION);

    /* USB component started, the correct enumeration will be checked in the first Read operation. */
    DEBUGPRINT_started = 1u;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_CyBtldrCommStop.
****************************************************************************//**
*
*  This function performs all necessary shutdown tasks required for the USBFS 
*  component.
*  
*  \sideeffect
*   Calls the USBFS_Stop() function.
*
*******************************************************************************/
void DEBUGPRINT_CyBtldrCommStop(void) 
{
    DEBUGPRINT_Stop();
}


/*******************************************************************************
* Function Name: DEBUGPRINT_CyBtldrCommReset.
****************************************************************************//**
*
*  This function resets receive and transmit communication buffers.
*
* \reentrant
*  No
*
*******************************************************************************/
void DEBUGPRINT_CyBtldrCommReset(void) 
{
    DEBUGPRINT_EnableOutEP(DEBUGPRINT_BTLDR_OUT_EP); 
}


/*******************************************************************************
* Function Name: DEBUGPRINT_CyBtldrCommWrite.
****************************************************************************//**
*
*  This function allows the caller to write data to the bootloader host. It 
*  handles polling to allow a block of data to be completely sent to the host 
*  device.
*
*  \param pData    A pointer to the block of data to send to the device
*  \param size     The number of bytes to write.
*  \param count    Pointer to an unsigned short variable to write the number of
*                  bytes actually written.
*  \param timeOut  Number of units to wait before returning because of a timeout.
*
* \return
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value that 
*  best describes the problem. For more information, see the gReturn Codesh 
*  section of the System Reference Guide.
*
* \reentrant
*  No
*
*******************************************************************************/
cystatus DEBUGPRINT_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus retCode;
    uint16 timeoutMs;

    /* Convert 10mS checks into 1mS checks. */
    timeoutMs = ((uint16) 10u * timeOut);

    /* Load data into IN endpoint to be read by host. */
    DEBUGPRINT_LoadInEP(DEBUGPRINT_BTLDR_IN_EP, pData, DEBUGPRINT_BTLDR_SIZEOF_READ_BUFFER);

    /* Wait unitl host reads data from IN endpoint. */
    while ((DEBUGPRINT_GetEPState(DEBUGPRINT_BTLDR_IN_EP) == DEBUGPRINT_IN_BUFFER_FULL) &&
           (0u != timeoutMs))
    {
        CyDelay(DEBUGPRINT_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    if (DEBUGPRINT_GetEPState(DEBUGPRINT_BTLDR_IN_EP) == DEBUGPRINT_IN_BUFFER_FULL)
    {
        retCode = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        retCode = CYRET_SUCCESS;
    }

    return (retCode);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_CyBtldrCommRead.
****************************************************************************//**
*
*  This function allows the caller to read data from the bootloader host. It 
*  handles polling to allow a block of data to be completely received from the 
*  host device.
*
*  \param pData    A pointer to the area to store the block of data received
*                  from the device.
*  \param size     The number of bytes to read.
*  \param count    Pointer to an unsigned short variable to write the number
*                  of bytes actually read.
*  \param timeOut  Number of units to wait before returning because of a timeOut.
*                  Timeout is measured in 10s of ms.
*
* \return
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value that 
*  best describes the problem. For more information, see the gReturn Codesh 
*  section of the System Reference Guide.
*
* \reentrant
*  No
*
*******************************************************************************/
cystatus DEBUGPRINT_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus retCode;
    uint16 timeoutMs;

    /* Convert 10mS checks into 1mS checks. */
    timeoutMs = ((uint16) 10u * timeOut);

    if (size > DEBUGPRINT_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = DEBUGPRINT_BTLDR_SIZEOF_WRITE_BUFFER;
    }

    /* Wait for enumeration first time. */
    if (0u != DEBUGPRINT_started)
    {
        /* Wait for device enumeration. */
        while ((0u == DEBUGPRINT_GetConfiguration()) && (0u != timeoutMs))
        {
            CyDelay(DEBUGPRINT_BTLDR_WAIT_1_MS);
            timeoutMs--;
        }

        /* Enable OUT after enumeration. */
        if (0u != DEBUGPRINT_GetConfiguration())
        {
            (void) DEBUGPRINT_IsConfigurationChanged();  /* Clear configuration changes state status. */
            DEBUGPRINT_CyBtldrCommReset();
            
            DEBUGPRINT_started = 0u;
        }
    }
    else /* Check for configuration changes, has been done by Host. */
    {
        if (0u != DEBUGPRINT_IsConfigurationChanged()) /* Host could send double SET_INTERFACE request or RESET. */
        {
            if (0u != DEBUGPRINT_GetConfiguration())   /* Init OUT endpoints when device reconfigured. */
            {
                DEBUGPRINT_CyBtldrCommReset();
            }
        }
    }

    timeoutMs = ((uint16) 10u * timeOut); /* Re-arm timeout */

    /* Wait unitl host writes data into OUT endpoint. */
    while ((DEBUGPRINT_GetEPState(DEBUGPRINT_BTLDR_OUT_EP) != DEBUGPRINT_OUT_BUFFER_FULL) && \
           (0u != timeoutMs))
    {
        CyDelay(DEBUGPRINT_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    /* Read data from OUT endpoint if host wrote data into it. */
    if (DEBUGPRINT_GetEPState(DEBUGPRINT_BTLDR_OUT_EP) == DEBUGPRINT_OUT_BUFFER_FULL)
    {
        *count = DEBUGPRINT_ReadOutEP(DEBUGPRINT_BTLDR_OUT_EP, pData, size);
        retCode = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        retCode = CYRET_TIMEOUT;
    }

    return (retCode);
}

#endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUGPRINT) */


/* [] END OF FILE */
