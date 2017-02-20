/***************************************************************************//**
* \file DEBUGPRINT_drv.c
* \version 3.10
*
* \brief
*  This file contains the Endpoint 0 Driver for the USBFS Component.  
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


/***************************************
* Global data allocation
***************************************/

volatile T_DEBUGPRINT_EP_CTL_BLOCK DEBUGPRINT_EP[DEBUGPRINT_MAX_EP];

/** Contains the current configuration number, which is set by the host using a 
 * SET_CONFIGURATION request. This variable is initialized to zero in 
 * USBFS_InitComponent() API and can be read by the USBFS_GetConfiguration() 
 * API.*/
volatile uint8 DEBUGPRINT_configuration;

/** Contains the current interface number.*/
volatile uint8 DEBUGPRINT_interfaceNumber;

/** This variable is set to one after SET_CONFIGURATION and SET_INTERFACE 
 *requests. It can be read by the USBFS_IsConfigurationChanged() API */
volatile uint8 DEBUGPRINT_configurationChanged;

/** Contains the current device address.*/
volatile uint8 DEBUGPRINT_deviceAddress;

/** This is a two-bit variable that contains power status in the bit 0 
 * (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote wakeup 
 * status (DEVICE_STATUS_REMOTE_WAKEUP) in the bit 1. This variable is 
 * initialized to zero in USBFS_InitComponent() API, configured by the 
 * USBFS_SetPowerStatus() API. The remote wakeup status cannot be set using the 
 * API SetPowerStatus(). */
volatile uint8 DEBUGPRINT_deviceStatus;

volatile uint8 DEBUGPRINT_interfaceSetting[DEBUGPRINT_MAX_INTERFACES_NUMBER];
volatile uint8 DEBUGPRINT_interfaceSetting_last[DEBUGPRINT_MAX_INTERFACES_NUMBER];
volatile uint8 DEBUGPRINT_interfaceStatus[DEBUGPRINT_MAX_INTERFACES_NUMBER];

/** Contains the started device number. This variable is set by the 
 * USBFS_Start() or USBFS_InitComponent() APIs.*/
volatile uint8 DEBUGPRINT_device;

/** Initialized class array for each interface. It is used for handling Class 
 * specific requests depend on interface class. Different classes in multiple 
 * alternate settings are not supported.*/
const uint8 CYCODE *DEBUGPRINT_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8  DEBUGPRINT_ep0Toggle;
volatile uint8  DEBUGPRINT_lastPacketSize;

/** This variable is used by the communication functions to handle the current 
* transfer state.
* Initialized to TRANS_STATE_IDLE in the USBFS_InitComponent() API and after a 
* complete transfer in the status stage.
* Changed to the TRANS_STATE_CONTROL_READ or TRANS_STATE_CONTROL_WRITE in setup 
* transaction depending on the request type.
*/
volatile uint8  DEBUGPRINT_transferState;
volatile T_DEBUGPRINT_TD DEBUGPRINT_currentTD;
volatile uint8  DEBUGPRINT_ep0Mode;
volatile uint8  DEBUGPRINT_ep0Count;
volatile uint16 DEBUGPRINT_transferByteCount;


/*******************************************************************************
* Function Name: DEBUGPRINT_ep_0_Interrupt
****************************************************************************//**
*
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
*
*******************************************************************************/
CY_ISR(DEBUGPRINT_EP_0_ISR)
{
    uint8 tempReg;
    uint8 modifyReg;

#ifdef DEBUGPRINT_EP_0_ISR_ENTRY_CALLBACK
    DEBUGPRINT_EP_0_ISR_EntryCallback();
#endif /* (DEBUGPRINT_EP_0_ISR_ENTRY_CALLBACK) */
    
    tempReg = DEBUGPRINT_EP0_CR_REG;
    if ((tempReg & DEBUGPRINT_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((tempReg & DEBUGPRINT_MODE_SETUP_RCVD) != 0u)
        {
            if ((tempReg & DEBUGPRINT_MODE_MASK) != DEBUGPRINT_MODE_NAK_IN_OUT)
            {
                /* Mode not equal to NAK_IN_OUT: invalid setup */
                modifyReg = 0u;
            }
            else
            {
                DEBUGPRINT_HandleSetup();
                
                if ((DEBUGPRINT_ep0Mode & DEBUGPRINT_MODE_SETUP_RCVD) != 0u)
                {
                    /* SETUP bit set: exit without mode modificaiton */
                    modifyReg = 0u;
                }
            }
        }
        else if ((tempReg & DEBUGPRINT_MODE_IN_RCVD) != 0u)
        {
            DEBUGPRINT_HandleIN();
        }
        else if ((tempReg & DEBUGPRINT_MODE_OUT_RCVD) != 0u)
        {
            DEBUGPRINT_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        
        /* Modify the EP0_CR register */
        if (modifyReg != 0u)
        {
            
            tempReg = DEBUGPRINT_EP0_CR_REG;
            
            /* Make sure that SETUP bit is cleared before modification */
            if ((tempReg & DEBUGPRINT_MODE_SETUP_RCVD) == 0u)
            {
                /* Update count register */
                tempReg = (uint8) DEBUGPRINT_ep0Toggle | DEBUGPRINT_ep0Count;
                DEBUGPRINT_EP0_CNT_REG = tempReg;
               
                /* Make sure that previous write operaiton was successful */
                if (tempReg == DEBUGPRINT_EP0_CNT_REG)
                {
                    /* Repeat until next successful write operation */
                    do
                    {
                        /* Init temporary variable */
                        modifyReg = DEBUGPRINT_ep0Mode;
                        
                        /* Unlock register */
                        tempReg = (uint8) (DEBUGPRINT_EP0_CR_REG & DEBUGPRINT_MODE_SETUP_RCVD);
                        
                        /* Check if SETUP bit is not set */
                        if (0u == tempReg)
                        {
                            /* Set the Mode Register  */
                            DEBUGPRINT_EP0_CR_REG = DEBUGPRINT_ep0Mode;
                            
                            /* Writing check */
                            modifyReg = DEBUGPRINT_EP0_CR_REG & DEBUGPRINT_MODE_MASK;
                        }
                    }
                    while (modifyReg != DEBUGPRINT_ep0Mode);
                }
            }
        }
    }

    DEBUGPRINT_ClearSieInterruptSource(DEBUGPRINT_INTR_SIE_EP0_INTR);
	
#ifdef DEBUGPRINT_EP_0_ISR_EXIT_CALLBACK
    DEBUGPRINT_EP_0_ISR_ExitCallback();
#endif /* (DEBUGPRINT_EP_0_ISR_EXIT_CALLBACK) */
}


/*******************************************************************************
* Function Name: DEBUGPRINT_HandleSetup
****************************************************************************//**
*
*  This Routine dispatches requests for the four USB request types
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_HandleSetup(void) 
{
    uint8 requestHandled;
    
    /* Clear register lock by SIE (read register) and clear setup bit 
    * (write any value in register).
    */
    requestHandled = (uint8) DEBUGPRINT_EP0_CR_REG;
    DEBUGPRINT_EP0_CR_REG = (uint8) requestHandled;
    requestHandled = (uint8) DEBUGPRINT_EP0_CR_REG;

    if ((requestHandled & DEBUGPRINT_MODE_SETUP_RCVD) != 0u)
    {
        /* SETUP bit is set: exit without mode modification. */
        DEBUGPRINT_ep0Mode = requestHandled;
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        DEBUGPRINT_UpdateStatusBlock(DEBUGPRINT_XFER_PREMATURE);

        /* Check request type. */
        switch (DEBUGPRINT_bmRequestTypeReg & DEBUGPRINT_RQST_TYPE_MASK)
        {
            case DEBUGPRINT_RQST_TYPE_STD:
                requestHandled = DEBUGPRINT_HandleStandardRqst();
                break;
                
            case DEBUGPRINT_RQST_TYPE_CLS:
                requestHandled = DEBUGPRINT_DispatchClassRqst();
                break;
                
            case DEBUGPRINT_RQST_TYPE_VND:
                requestHandled = DEBUGPRINT_HandleVendorRqst();
                break;
                
            default:
                requestHandled = DEBUGPRINT_FALSE;
                break;
        }
        
        /* If request is not recognized. Stall endpoint 0 IN and OUT. */
        if (requestHandled == DEBUGPRINT_FALSE)
        {
            DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_HandleIN
****************************************************************************//**
*
*  This routine handles EP0 IN transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_HandleIN(void) 
{
    switch (DEBUGPRINT_transferState)
    {
        case DEBUGPRINT_TRANS_STATE_IDLE:
            break;
        
        case DEBUGPRINT_TRANS_STATE_CONTROL_READ:
            DEBUGPRINT_ControlReadDataStage();
            break;
            
        case DEBUGPRINT_TRANS_STATE_CONTROL_WRITE:
            DEBUGPRINT_ControlWriteStatusStage();
            break;
            
        case DEBUGPRINT_TRANS_STATE_NO_DATA_CONTROL:
            DEBUGPRINT_NoDataControlStatusStage();
            break;
            
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_HandleOUT
****************************************************************************//**
*
*  This routine handles EP0 OUT transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_HandleOUT(void) 
{
    switch (DEBUGPRINT_transferState)
    {
        case DEBUGPRINT_TRANS_STATE_IDLE:
            break;
        
        case DEBUGPRINT_TRANS_STATE_CONTROL_READ:
            DEBUGPRINT_ControlReadStatusStage();
            break;
            
        case DEBUGPRINT_TRANS_STATE_CONTROL_WRITE:
            DEBUGPRINT_ControlWriteDataStage();
            break;
            
        case DEBUGPRINT_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            DEBUGPRINT_UpdateStatusBlock(DEBUGPRINT_XFER_ERROR);
            
            /* We expect no more data, so stall INs and OUTs */
            DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STALL_IN_OUT;
            break;
            
        default:    
            /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_LoadEP0
****************************************************************************//**
*
*  This routine loads the EP0 data registers for OUT transfers. It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
*
* \globalvars
*  DEBUGPRINT_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  DEBUGPRINT_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  DEBUGPRINT_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  DEBUGPRINT_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  DEBUGPRINT_ep0Toggle - inverted
*  DEBUGPRINT_ep0Mode  - prepare for mode register content.
*  DEBUGPRINT_transferState - set to TRANS_STATE_CONTROL_READ
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    DEBUGPRINT_transferByteCount += DEBUGPRINT_lastPacketSize;

    /* Now load the next transaction */
    while ((DEBUGPRINT_currentTD.count > 0u) && (ep0Count < 8u))
    {
        DEBUGPRINT_EP0_DR_BASE.epData[ep0Count] = (uint8) *DEBUGPRINT_currentTD.pData;
        DEBUGPRINT_currentTD.pData = &DEBUGPRINT_currentTD.pData[1u];
        ep0Count++;
        DEBUGPRINT_currentTD.count--;
    }

    /* Support zero-length packet */
    if ((DEBUGPRINT_lastPacketSize == 8u) || (ep0Count > 0u))
    {
        /* Update the data toggle */
        DEBUGPRINT_ep0Toggle ^= DEBUGPRINT_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    DEBUGPRINT_ep0Count =       (uint8) ep0Count;
    DEBUGPRINT_lastPacketSize = (uint8) ep0Count;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_InitControlRead
****************************************************************************//**
*
*  Initialize a control read transaction. It is used to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
*
* \return
*  requestHandled state.
*
* \globalvars
*  DEBUGPRINT_currentTD.count - counts of data to be sent.
*  DEBUGPRINT_currentTD.pData - data pointer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_InitControlRead(void) 
{
    uint16 xferCount;

    if (DEBUGPRINT_currentTD.count == 0u)
    {
        (void) DEBUGPRINT_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_CONTROL_READ;
        
        /* Set the toggle, it gets updated in LoadEP */
        DEBUGPRINT_ep0Toggle = 0u;
        
        /* Initialize the Status Block */
        DEBUGPRINT_InitializeStatusBlock();
        
        xferCount = ((uint16)((uint16) DEBUGPRINT_lengthHiReg << 8u) | ((uint16) DEBUGPRINT_lengthLoReg));

        if (DEBUGPRINT_currentTD.count > xferCount)
        {
            DEBUGPRINT_currentTD.count = xferCount;
        }
        
        DEBUGPRINT_LoadEP0();
    }

    return (DEBUGPRINT_TRUE);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_InitZeroLengthControlTransfer
****************************************************************************//**
*
*  Initialize a zero length data IN transfer.
*
* \return
*  requestHandled state.
*
* \globalvars
*  DEBUGPRINT_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  DEBUGPRINT_ep0Mode  - prepare for mode register content.
*  DEBUGPRINT_transferState - set to TRANS_STATE_CONTROL_READ
*  DEBUGPRINT_ep0Count - cleared, means the zero-length packet.
*  DEBUGPRINT_lastPacketSize - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_CONTROL_READ;
    
    /* Set the data toggle */
    DEBUGPRINT_ep0Toggle = DEBUGPRINT_EP0_CNT_DATA_TOGGLE;
    
    /* Set the Mode Register  */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_ACK_IN_STATUS_OUT;
    
    /* Save the packet size for next time */
    DEBUGPRINT_lastPacketSize = 0u;
    
    DEBUGPRINT_ep0Count = 0u;

    return (DEBUGPRINT_TRUE);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ControlReadDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control read transfer.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_ControlReadDataStage(void) 

{
    DEBUGPRINT_LoadEP0();
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ControlReadStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control read transfer.
*
*
* \globalvars
*  DEBUGPRINT_USBFS_transferByteCount - updated with last packet size.
*  DEBUGPRINT_transferState - set to TRANS_STATE_IDLE.
*  DEBUGPRINT_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    DEBUGPRINT_transferByteCount += DEBUGPRINT_lastPacketSize;
    
    /* Go Idle */
    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_IDLE;
    
    /* Update the completion block */
    DEBUGPRINT_UpdateStatusBlock(DEBUGPRINT_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_InitControlWrite
****************************************************************************//**
*
*  Initialize a control write transaction
*
* \return
*  requestHandled state.
*
* \globalvars
*  DEBUGPRINT_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  DEBUGPRINT_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  DEBUGPRINT_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_CONTROL_WRITE;
    
    /* This might not be necessary */
    DEBUGPRINT_ep0Toggle = DEBUGPRINT_EP0_CNT_DATA_TOGGLE;
    
    /* Initialize the Status Block */
    DEBUGPRINT_InitializeStatusBlock();

    xferCount = ((uint16)((uint16) DEBUGPRINT_lengthHiReg << 8u) | ((uint16) DEBUGPRINT_lengthLoReg));

    if (DEBUGPRINT_currentTD.count > xferCount)
    {
        DEBUGPRINT_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_ACK_OUT_STATUS_IN;

    return(DEBUGPRINT_TRUE);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ControlWriteDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
*
* \globalvars
*  DEBUGPRINT_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  DEBUGPRINT_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  DEBUGPRINT_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  DEBUGPRINT_ep0Toggle - inverted
*  DEBUGPRINT_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (DEBUGPRINT_EP0_CNT_REG & DEBUGPRINT_EPX_CNT0_MASK) - DEBUGPRINT_EPX_CNTX_CRC_COUNT;

    DEBUGPRINT_transferByteCount += (uint8)ep0Count;

    while ((DEBUGPRINT_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *DEBUGPRINT_currentTD.pData = (uint8) DEBUGPRINT_EP0_DR_BASE.epData[regIndex];
        DEBUGPRINT_currentTD.pData = &DEBUGPRINT_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        DEBUGPRINT_currentTD.count--;
    }
    
    DEBUGPRINT_ep0Count = (uint8)ep0Count;
    
    /* Update the data toggle */
    DEBUGPRINT_ep0Toggle ^= DEBUGPRINT_EP0_CNT_DATA_TOGGLE;
    
    /* Expect Data or Status Stage */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_ControlWriteStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control write transfer
*
* \globalvars
*  DEBUGPRINT_transferState - set to TRANS_STATE_IDLE.
*  DEBUGPRINT_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_IDLE;
    
    /* Update the completion block */    
    DEBUGPRINT_UpdateStatusBlock(DEBUGPRINT_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_InitNoDataControlTransfer
****************************************************************************//**
*
*  Initialize a no data control transfer
*
* \return
*  requestHandled state.
*
* \globalvars
*  DEBUGPRINT_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  DEBUGPRINT_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  DEBUGPRINT_ep0Count - cleared.
*  DEBUGPRINT_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_InitNoDataControlTransfer(void) 
{
    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_NO_DATA_CONTROL;
    DEBUGPRINT_ep0Mode       = DEBUGPRINT_MODE_STATUS_IN_ONLY;
    DEBUGPRINT_ep0Toggle     = DEBUGPRINT_EP0_CNT_DATA_TOGGLE;
    DEBUGPRINT_ep0Count      = 0u;

    return (DEBUGPRINT_TRUE);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_NoDataControlStatusStage
****************************************************************************//**
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* \globalvars
*  DEBUGPRINT_transferState - set to TRANS_STATE_IDLE.
*  DEBUGPRINT_ep0Mode  - set to MODE_STALL_IN_OUT.
*  DEBUGPRINT_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  DEBUGPRINT_deviceAddress - used to set new address and cleared
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_NoDataControlStatusStage(void) 
{
    if (0u != DEBUGPRINT_deviceAddress)
    {
        /* Update device address if we got new address. */
        DEBUGPRINT_CR0_REG = (uint8) DEBUGPRINT_deviceAddress | DEBUGPRINT_CR0_ENABLE;
        DEBUGPRINT_deviceAddress = 0u;
    }

    DEBUGPRINT_transferState = DEBUGPRINT_TRANS_STATE_IDLE;
    
    /* Update the completion block. */
    DEBUGPRINT_UpdateStatusBlock(DEBUGPRINT_XFER_STATUS_ACK);
    
    /* Stall IN and OUT, no more data is expected. */
    DEBUGPRINT_ep0Mode = DEBUGPRINT_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: DEBUGPRINT_UpdateStatusBlock
****************************************************************************//**
*
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the DEBUGPRINT_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
*  completionCode - status.
*
*
* \globalvars
*  DEBUGPRINT_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  DEBUGPRINT_currentTD.pStatusBlock->length - updated.
*  DEBUGPRINT_currentTD.pStatusBlock - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_UpdateStatusBlock(uint8 completionCode) 
{
    if (DEBUGPRINT_currentTD.pStatusBlock != NULL)
    {
        DEBUGPRINT_currentTD.pStatusBlock->status = completionCode;
        DEBUGPRINT_currentTD.pStatusBlock->length = DEBUGPRINT_transferByteCount;
        DEBUGPRINT_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_InitializeStatusBlock
****************************************************************************//**
*
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes DEBUGPRINT_transferByteCount.  Save some space,
*  this is the only consumer.
*
* \globalvars
*  DEBUGPRINT_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  DEBUGPRINT_currentTD.pStatusBlock->length - cleared.
*  DEBUGPRINT_transferByteCount - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_InitializeStatusBlock(void) 
{
    DEBUGPRINT_transferByteCount = 0u;
    
    if (DEBUGPRINT_currentTD.pStatusBlock != NULL)
    {
        DEBUGPRINT_currentTD.pStatusBlock->status = DEBUGPRINT_XFER_IDLE;
        DEBUGPRINT_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
