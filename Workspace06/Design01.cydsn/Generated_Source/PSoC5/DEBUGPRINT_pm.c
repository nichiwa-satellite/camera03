/***************************************************************************//**
* \file DEBUGPRINT_pm.c
* \version 3.10
*
* \brief
*  This file provides Suspend/Resume APIs implementation.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_pvt.h"
#include "DEBUGPRINT_Dp.h"
#include "cyapicallbacks.h"

/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static DEBUGPRINT_BACKUP_STRUCT  DEBUGPRINT_backup;

#if (DEBUGPRINT_DP_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_DP_ISR
    ****************************************************************************//**
    *
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_DP_ISR)
    {
    #ifdef DEBUGPRINT_DP_ISR_ENTRY_CALLBACK
        DEBUGPRINT_DP_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_DP_ISR_ENTRY_CALLBACK) */

        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        (void) DEBUGPRINT_Dp_ClearInterrupt();
		
	#ifdef DEBUGPRINT_DP_ISR_EXIT_CALLBACK
        DEBUGPRINT_DP_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_DP_ISR_EXIT_CALLBACK) */
    }
#endif /* (DEBUGPRINT_DP_ISR_ACTIVE) */


/*******************************************************************************
* Function Name: DEBUGPRINT_SaveConfig
****************************************************************************//**
*
*  Saves the current user configuration.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_SaveConfig(void) 
{
    /* Empty function added for the compatibility purpose. */
}


/*******************************************************************************
* Function Name: DEBUGPRINT_RestoreConfig
****************************************************************************//**
*
*  Restores the current user configuration.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_RestoreConfig(void) 
{
    if (DEBUGPRINT_configuration != 0u)
    {
        DEBUGPRINT_ConfigReg();
        DEBUGPRINT_EpStateInit();
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_Suspend
****************************************************************************//**
*
*  This function prepares the USBFS component to enter low power mode. The 
*  interrupt on falling edge on Dp pin is configured to wakeup device when the 
*  host drives resume condition. The pull-up is enabled on the Dp line while 
*  device is in low power mode. The supported low power modes are Deep Sleep 
*  (PSoC 4200L) and Sleep (PSoC 3/ PSoC 5LP).
*  
*  *Note* For PSoC 4200L devices, this function should not be called before 
*  entering Sleep.
*  
*  *Note* After enter low power mode, the data which is left in the IN or OUT 
*  endpoint buffers is not restored after wakeup and lost. Therefore it should 
*  be stored in the SRAM for OUT endpoint or read by the host for IN endpoint 
*  before enter low power mode.
*
* \globalvars
*  DEBUGPRINT_backup.enable:  modified.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_Suspend(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    if (0u != (DEBUGPRINT_CR0_REG & DEBUGPRINT_CR0_ENABLE))
    {
        /* USB block is enabled. */
        DEBUGPRINT_backup.enableState = 1u;

    #if (DEBUGPRINT_EP_MANAGEMENT_DMA)
        DEBUGPRINT_Stop_DMA(DEBUGPRINT_MAX_EP);
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

    #if (CY_PSOC4)
        /* Suspend enter sequence. */
        DEBUGPRINT_POWER_CTRL_REG |= (DEBUGPRINT_POWER_CTRL_SUSPEND |
                                            DEBUGPRINT_POWER_CTRL_SUSPEND_DEL);

        /* Store state of USB regulator and disable it. */
        DEBUGPRINT_backup.mode = (uint8)  (DEBUGPRINT_CR1_REG & DEBUGPRINT_CR1_REG_ENABLE);
        DEBUGPRINT_CR1_REG    &= (uint32) ~DEBUGPRINT_CR1_REG_ENABLE;
        
        /* Store SIE interrupt sources. Valid bits are 0 - 4. */
        DEBUGPRINT_backup.intrSeiMask = (uint8) DEBUGPRINT_INTR_SIE_MASK_REG;

    #else
        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled. */
        DEBUGPRINT_USBIO_CR0_REG &= (uint8) ~DEBUGPRINT_USBIO_CR0_TEN;
        CyDelayUs(DEBUGPRINT_WAIT_REG_STABILITY_50NS);  /*~50ns delay. */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        DEBUGPRINT_PM_USB_CR0_REG &= (uint8) ~(DEBUGPRINT_PM_USB_CR0_PD_N |
                                                     DEBUGPRINT_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE. */
        DEBUGPRINT_CR0_REG &= (uint8) ~DEBUGPRINT_CR0_ENABLE;

        CyDelayUs(DEBUGPRINT_WAIT_REG_STABILITY_50NS);  /* ~50ns delay. */
        /* Store mode and disable VRegulator. */
        DEBUGPRINT_backup.mode = (uint8) (DEBUGPRINT_CR1_REG & DEBUGPRINT_CR1_REG_ENABLE);
        DEBUGPRINT_CR1_REG    &= (uint8) ~DEBUGPRINT_CR1_REG_ENABLE;

        CyDelayUs(DEBUGPRINT_WAIT_REG_STABILITY_1US); /* min 0.5us delay required. */

        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        DEBUGPRINT_PM_USB_CR0_REG &= (uint8) ~DEBUGPRINT_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pull-up. */
        DEBUGPRINT_USBIO_CR1_REG |= DEBUGPRINT_USBIO_CR1_IOMODE;

        /* Disable USBFS block. */
        /* Clear power active and standby mode templates: disable USB block. */
        DEBUGPRINT_PM_ACT_CFG_REG  &= (uint8) ~DEBUGPRINT_PM_ACT_EN_FSUSB;
        DEBUGPRINT_PM_STBY_CFG_REG &= (uint8) ~DEBUGPRINT_PM_STBY_EN_FSUSB;

        CyDelayUs(DEBUGPRINT_WAIT_REG_STABILITY_1US); /* min 0.5us delay required. */
    #endif /* (CY_PSOC4) */
    }
    else
    {
        DEBUGPRINT_backup.enableState = 0u;
    }

    CyExitCriticalSection(enableInterrupts);

#if (DEBUGPRINT_DP_ISR_ACTIVE)
    /* Clear active mode Dp interrupt source history. */
    (void) DEBUGPRINT_Dp_ClearInterrupt();
    CyIntClearPending(DEBUGPRINT_DP_INTC_VECT_NUM);

    CyIntEnable      (DEBUGPRINT_DP_INTC_VECT_NUM);
#endif /* (DEBUGPRINT_DP_ISR_ACTIVE). */
}


/*******************************************************************************
* Function Name: DEBUGPRINT_Resume
****************************************************************************//**
*
*  This function prepares the USBFS component for active mode operation after 
*  exit low power mode. It restores the component active mode configuration such 
*  as device address assigned previously by the host, endpoints buffer and disables 
*  interrupt on Dp pin.
*  The supported low power modes are Deep Sleep (PSoC 4200L) and Sleep 
*  (PSoC 3/ PSoC 5LP).
*  
*  *Note* For PSoC 4200L devices, this function should not be called after 
*  exiting Sleep.
*  
*  *Note* To resume communication with the host, the data endpoints must be 
*  managed: the OUT endpoints must be enabled and IN endpoints must be loaded 
*  with data. For DMA with Automatic Buffer Management, all endpoints buffers 
*  must be initialized again before making them available to the host.
*
*
* \globalvars
*  DEBUGPRINT_backup - checked.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_Resume(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    if (0u != DEBUGPRINT_backup.enableState)
    {
    #if (DEBUGPRINT_DP_ISR_ACTIVE)
        CyIntDisable(DEBUGPRINT_DP_INTC_VECT_NUM);
    #endif /* (DEBUGPRINT_DP_ISR_ACTIVE) */

    #if (CY_PSOC4)
        /* Enable clock to USB IP. */
        DEBUGPRINT_USB_CLK_EN_REG |= DEBUGPRINT_USB_CLK_CSR_CLK_EN;

        /* Restore arbiter configuration for DMA transfers. */
        #if (DEBUGPRINT_EP_MANAGEMENT_DMA)
            #if (DEBUGPRINT_ARB_ISR_ACTIVE)
                /* Enable ARB EP interrupt sources. */
                DEBUGPRINT_ARB_INT_EN_REG = DEBUGPRINT_DEFAULT_ARB_INT_EN;
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

            /* Configure arbiter for Manual or Auto DMA operation and clear 
            * configuration completion. 
            */
            DEBUGPRINT_ARB_CFG_REG = DEBUGPRINT_DEFAULT_ARB_CFG;
        #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

        /* Restore level (hi, lo, med) for each interrupt source. */
        DEBUGPRINT_INTR_LVL_SEL_REG = DEBUGPRINT_DEFAULT_INTR_LVL_SEL;
        
        /* Store SIE interrupt sources. */
        DEBUGPRINT_INTR_SIE_MASK_REG = (uint32) DEBUGPRINT_backup.intrSeiMask;

        /* Set EP0.CR: ACK Setup, NAK IN/OUT. */
        DEBUGPRINT_EP0_CR_REG = DEBUGPRINT_MODE_NAK_IN_OUT;

        /* Restore data EP1-8 configuration. */
        DEBUGPRINT_RestoreConfig();

        /* Restore state of USB regulator and wait until it supples stable power. */
        DEBUGPRINT_CR1_REG |= DEBUGPRINT_backup.mode;
        CyDelayUs(DEBUGPRINT_WAIT_VREF_STABILITY);

        /* Suspend exit sequence. */
        DEBUGPRINT_POWER_CTRL_REG &= (uint32) ~DEBUGPRINT_POWER_CTRL_SUSPEND;
        CyDelayUs(DEBUGPRINT_WAIT_SUSPEND_DEL_DISABLE);
        DEBUGPRINT_POWER_CTRL_REG &= (uint32) ~DEBUGPRINT_POWER_CTRL_SUSPEND_DEL;

    #else
        /* Set power active and standby mode templates: enable USB block. */
        DEBUGPRINT_PM_ACT_CFG_REG  |= DEBUGPRINT_PM_ACT_EN_FSUSB;
        DEBUGPRINT_PM_STBY_CFG_REG |= DEBUGPRINT_PM_STBY_EN_FSUSB;

        /* Enable core clock. */
        DEBUGPRINT_USB_CLK_EN_REG |= DEBUGPRINT_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        DEBUGPRINT_PM_USB_CR0_REG |= DEBUGPRINT_PM_USB_CR0_REF_EN;

        /* The reference is available ~40us after power restored. */
        CyDelayUs(DEBUGPRINT_WAIT_VREF_RESTORE);
        /* Restore state of USB regulator and wait until it supples stable power. */
        DEBUGPRINT_CR1_REG |= DEBUGPRINT_backup.mode;
        CyDelayUs(DEBUGPRINT_WAIT_VREF_STABILITY);   /*~50ns delay. */

        /* Enable USBIO. */
        DEBUGPRINT_PM_USB_CR0_REG |= DEBUGPRINT_PM_USB_CR0_PD_N;
        CyDelayUs(DEBUGPRINT_WAIT_PD_PULLUP_N_ENABLE);
        /* Set the USBIO pull-up enable. */
        DEBUGPRINT_PM_USB_CR0_REG |= DEBUGPRINT_PM_USB_CR0_PD_PULLUP_N;

        /* Restore arbiter configuration for DMA transfers. */
        #if (DEBUGPRINT_EP_MANAGEMENT_DMA)
            #if (DEBUGPRINT_ARB_ISR_ACTIVE)
                /* Enable ARB EP interrupt sources. */
                DEBUGPRINT_ARB_INT_EN_REG = DEBUGPRINT_DEFAULT_ARB_INT_EN;
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

            /* Configure arbiter for Manual or Auto DMA operation and clear 
            * configuration completion. 
            */
            DEBUGPRINT_ARB_CFG_REG = DEBUGPRINT_DEFAULT_ARB_CFG;
        #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA) */

        /* Set EP0.CR: ACK Setup, STALL IN/OUT. */
        DEBUGPRINT_EP0_CR_REG = DEBUGPRINT_MODE_STALL_IN_OUT;

        /* Enable the USB IP to respond to USB traffic with the last address. */
        DEBUGPRINT_CR0_REG |= DEBUGPRINT_CR0_ENABLE;
        CyDelayCycles(DEBUGPRINT_WAIT_CR0_REG_STABILITY);

        /* Enable D+ pull-up and keep USB control on IO. */
        DEBUGPRINT_USBIO_CR1_REG = DEBUGPRINT_USBIO_CR1_USBPUEN;

        /* Restore data EP1-8 configuration. */
        DEBUGPRINT_RestoreConfig();
    #endif /* (CY_PSOC4) */
    }

    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
