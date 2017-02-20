/***************************************************************************//**
* \file DEBUGPRINT_episr.c
* \version 3.10
*
* \brief
*  This file contains the Data endpoint Interrupt Service Routines.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_pvt.h"
#include "DEBUGPRINT_cydmac.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if (DEBUGPRINT_EP1_ISR_ACTIVE)
    /******************************************************************************
    * Function Name: DEBUGPRINT_EP_1_ISR
    ***************************************************************************//**
    *
    *  Endpoint 1 Interrupt Service Routine
    *
    ******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_1_ISR)
    {

    #ifdef DEBUGPRINT_EP_1_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_1_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_1_ISR_ENTRY_CALLBACK) */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    
        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP1_INTR);
            
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP1].addr & DEBUGPRINT_DIR_IN))
    #endif /* (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP1].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP1) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP1].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP1].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP1)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */
    
        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_1_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_1_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_1_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }

#endif /* (DEBUGPRINT_EP1_ISR_ACTIVE) */


#if (DEBUGPRINT_EP2_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_2_ISR
    ****************************************************************************//**
    *
    *  Endpoint 2 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_2_ISR)
    {
    #ifdef DEBUGPRINT_EP_2_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_2_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_2_ISR_ENTRY_CALLBACK) */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP2_INTR);

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP2].addr & DEBUGPRINT_DIR_IN))
    #endif /* (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP2].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP2) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP2].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP2].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP2)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */        
    
        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_2_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_2_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_2_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP2_ISR_ACTIVE) */


#if (DEBUGPRINT_EP3_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_3_ISR
    ****************************************************************************//**
    *
    *  Endpoint 3 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_3_ISR)
    {
    #ifdef DEBUGPRINT_EP_3_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_3_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_3_ISR_ENTRY_CALLBACK) */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP3_INTR);    

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP3].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP3].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP3) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP3].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP3].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP3)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_3_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_3_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_3_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP3_ISR_ACTIVE) */


#if (DEBUGPRINT_EP4_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_4_ISR
    ****************************************************************************//**
    *
    *  Endpoint 4 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_4_ISR)
    {
    #ifdef DEBUGPRINT_EP_4_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_4_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_4_ISR_ENTRY_CALLBACK) */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP4_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP4].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP4].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP4) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP4].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP4].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if(DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP4)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_4_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_4_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_4_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP4_ISR_ACTIVE) */


#if (DEBUGPRINT_EP5_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_5_ISR
    ****************************************************************************//**
    *
    *  Endpoint 5 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_5_ISR)
    {
    #ifdef DEBUGPRINT_EP_5_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_5_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_5_ISR_ENTRY_CALLBACK) */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

    #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && \
                 DEBUGPRINT_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP5_INTR);
    
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP5].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP5].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP5) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP5].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP5].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))        
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP5)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_5_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_5_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_5_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP5_ISR_ACTIVE) */


#if (DEBUGPRINT_EP6_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_6_ISR
    ****************************************************************************//**
    *
    *  Endpoint 6 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_6_ISR)
    {
    #ifdef DEBUGPRINT_EP_6_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_6_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_6_ISR_ENTRY_CALLBACK) */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP6_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP6].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP6].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP6) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP6].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP6].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP6)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_6_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_6_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_6_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP6_ISR_ACTIVE) */


#if (DEBUGPRINT_EP7_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_7_ISR
    ****************************************************************************//**
    *
    *  Endpoint 7 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_7_ISR)
    {
    #ifdef DEBUGPRINT_EP_7_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_7_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_7_ISR_ENTRY_CALLBACK) */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    
        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP7_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP7].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {           
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP7].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP7) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP7].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP7].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }


    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if(DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP7)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_7_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_7_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_7_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP7_ISR_ACTIVE) */


#if (DEBUGPRINT_EP8_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_EP_8_ISR
    ****************************************************************************//**
    *
    *  Endpoint 8 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_EP_8_ISR)
    {
    #ifdef DEBUGPRINT_EP_8_ISR_ENTRY_CALLBACK
        DEBUGPRINT_EP_8_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_EP_8_ISR_ENTRY_CALLBACK) */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */

        DEBUGPRINT_ClearSieEpInterruptSource(DEBUGPRINT_SIE_INT_EP8_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (DEBUGPRINT_EP[DEBUGPRINT_EP8].addr & DEBUGPRINT_DIR_IN))
    #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) DEBUGPRINT_SIE_EP_BASE.sieEp[DEBUGPRINT_EP8].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (DEBUGPRINT_GET_EP_TYPE(DEBUGPRINT_EP8) != DEBUGPRINT_EP_TYPE_ISOC)
            {
                DEBUGPRINT_EP[DEBUGPRINT_EP8].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            DEBUGPRINT_EP[DEBUGPRINT_EP8].apiEpState = DEBUGPRINT_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
            !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
            if (DEBUGPRINT_midi_out_ep == DEBUGPRINT_EP8)
            {
                DEBUGPRINT_MIDI_OUT_Service();
            }
        #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_EP_8_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_8_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_8_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
        !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (DEBUGPRINT_EP8_ISR_ACTIVE) */


#if (DEBUGPRINT_SOF_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: DEBUGPRINT_SOF_ISR
    ****************************************************************************//**
    *
    *  Start of Frame Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(DEBUGPRINT_SOF_ISR)
    {
    #ifdef DEBUGPRINT_SOF_ISR_ENTRY_CALLBACK
        DEBUGPRINT_SOF_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_SOF_ISR_ENTRY_CALLBACK) */

        /* `#START SOF_USER_CODE` Place your code here */

        /* `#END` */

        DEBUGPRINT_ClearSieInterruptSource(DEBUGPRINT_INTR_SIE_SOF_INTR);

    #ifdef DEBUGPRINT_SOF_ISR_EXIT_CALLBACK
        DEBUGPRINT_SOF_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_SOF_ISR_EXIT_CALLBACK) */
    }
#endif /* (DEBUGPRINT_SOF_ISR_ACTIVE) */


#if (DEBUGPRINT_BUS_RESET_ISR_ACTIVE)
/*******************************************************************************
* Function Name: DEBUGPRINT_BUS_RESET_ISR
****************************************************************************//**
*
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
*
*******************************************************************************/
CY_ISR(DEBUGPRINT_BUS_RESET_ISR)
{
#ifdef DEBUGPRINT_BUS_RESET_ISR_ENTRY_CALLBACK
    DEBUGPRINT_BUS_RESET_ISR_EntryCallback();
#endif /* (DEBUGPRINT_BUS_RESET_ISR_ENTRY_CALLBACK) */

    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    DEBUGPRINT_ClearSieInterruptSource(DEBUGPRINT_INTR_SIE_BUS_RESET_INTR);

    DEBUGPRINT_ReInitComponent();

#ifdef DEBUGPRINT_BUS_RESET_ISR_EXIT_CALLBACK
    DEBUGPRINT_BUS_RESET_ISR_ExitCallback();
#endif /* (DEBUGPRINT_BUS_RESET_ISR_EXIT_CALLBACK) */
}
#endif /* (DEBUGPRINT_BUS_RESET_ISR_ACTIVE) */


#if (DEBUGPRINT_LPM_ACTIVE)
/***************************************************************************
* Function Name: DEBUGPRINT_INTR_LPM_ISR
************************************************************************//**
*
*   Interrupt Service Routine for LPM of the interrupt sources.
*
*
***************************************************************************/
CY_ISR(DEBUGPRINT_LPM_ISR)
{
#ifdef DEBUGPRINT_LPM_ISR_ENTRY_CALLBACK
    DEBUGPRINT_LPM_ISR_EntryCallback();
#endif /* (DEBUGPRINT_LPM_ISR_ENTRY_CALLBACK) */

    /* `#START LPM_BEGIN_USER_CODE` Place your code here */

    /* `#END` */

    DEBUGPRINT_ClearSieInterruptSource(DEBUGPRINT_INTR_SIE_LPM_INTR);

    /* `#START LPM_END_USER_CODE` Place your code here */

    /* `#END` */

#ifdef DEBUGPRINT_LPM_ISR_EXIT_CALLBACK
    DEBUGPRINT_LPM_ISR_ExitCallback();
#endif /* (DEBUGPRINT_LPM_ISR_EXIT_CALLBACK) */
}
#endif /* (DEBUGPRINT_LPM_ACTIVE) */


#if (DEBUGPRINT_EP_MANAGEMENT_DMA && DEBUGPRINT_ARB_ISR_ACTIVE)
    /***************************************************************************
    * Function Name: DEBUGPRINT_ARB_ISR
    ************************************************************************//**
    *
    *  Arbiter Interrupt Service Routine.
    *
    *
    ***************************************************************************/
    CY_ISR(DEBUGPRINT_ARB_ISR)
    {
        uint8 arbIntrStatus;
        uint8 epStatus;
        uint8 ep = DEBUGPRINT_EP1;

    #ifdef DEBUGPRINT_ARB_ISR_ENTRY_CALLBACK
        DEBUGPRINT_ARB_ISR_EntryCallback();
    #endif /* (DEBUGPRINT_ARB_ISR_ENTRY_CALLBACK) */

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Get pending ARB interrupt sources. */
        arbIntrStatus = DEBUGPRINT_ARB_INT_SR_REG;

        while (0u != arbIntrStatus)
        {
            /* Check which EP is interrupt source. */
            if (0u != (arbIntrStatus & 0x01u))
            {
                /* Get endpoint enable interrupt sources. */
                epStatus = (DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epSr & DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epIntEn);

                /* Handle IN endpoint buffer full event: happens only once when endpoint buffer is loaded. */
                if (0u != (epStatus & DEBUGPRINT_ARB_EPX_INT_IN_BUF_FULL))
                {
                    if (0u != (DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN))
                    {
                        /* Clear data ready status. */
                        DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epCfg &= (uint8) ~DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY;

                    #if (CY_PSOC3 || CY_PSOC5LP)
                        #if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u))
                            /* Set up common area DMA with rest of data. */
                            if(DEBUGPRINT_inLength[ep] > DEBUGPRINT_DMA_BYTES_PER_BURST)
                            {
                                DEBUGPRINT_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                DEBUGPRINT_inBufFull[ep] = 1u;
                            }
                        #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO && (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)) */
                    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

                        /* Arm IN endpoint. */
                        DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0 = DEBUGPRINT_EP[ep].epMode;

                    #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && DEBUGPRINT_ISR_SERVICE_MIDI_IN)
                        if (ep == DEBUGPRINT_midi_in_ep)
                        {
                            /* Clear MIDI input pointer. */
                            DEBUGPRINT_midiInPointer = 0u;
                        }
                    #endif /* (DEBUGPRINT_ENABLE_MIDI_STREAMING) */
                    }
                }

            #if (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & DEBUGPRINT_ARB_EPX_SR_DMA_GNT))
                {
                    if (0u == (DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN))
                    {
                        /* Notify user that data has been copied from endpoint buffer. */
                        DEBUGPRINT_EP[ep].apiEpState = DEBUGPRINT_NO_EVENT_PENDING;

                        /* DMA done coping data: OUT endpoint has to be re-armed by user. */
                    }
                }
            #endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) */

            #if (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & DEBUGPRINT_ARB_EPX_INT_DMA_TERMIN))
                {
                    uint32 channelNum = DEBUGPRINT_DmaChan[ep];

                    /* Restore burst counter for endpoint. */
                    DEBUGPRINT_DmaEpBurstCnt[ep] = DEBUGPRINT_DMA_GET_BURST_CNT(DEBUGPRINT_DmaEpBurstCntBackup[ep]);

                    /* Disable DMA channel to restore descriptor configuration. The on-going transfer is aborted. */
                    DEBUGPRINT_CyDmaChDisable(channelNum);

                    /* Generate DMA tr_out signal to notify USB IP that DMA is done. This signal is not generated
                    * when transfer was aborted (it occurs when host writes less bytes than buffer size).
                    */
                    DEBUGPRINT_CyDmaTriggerOut(DEBUGPRINT_DmaBurstEndOut[ep]);

                    /* Restore destination address for output endpoint. */
                    DEBUGPRINT_CyDmaSetDstAddress(channelNum, DEBUGPRINT_DMA_DESCR0, (void*) ((uint32) DEBUGPRINT_DmaEpBufferAddrBackup[ep]));
                    DEBUGPRINT_CyDmaSetDstAddress(channelNum, DEBUGPRINT_DMA_DESCR1, (void*) ((uint32) DEBUGPRINT_DmaEpBufferAddrBackup[ep] +
                                                                                                                   DEBUGPRINT_DMA_BYTES_PER_BURST));

                    /* Restore number of data elements to transfer which was adjusted for last burst. */
                    if (0u != (DEBUGPRINT_DmaEpLastBurstEl[ep] & DEBUGPRINT_DMA_DESCR_REVERT))
                    {
                        DEBUGPRINT_CyDmaSetNumDataElements(channelNum, (DEBUGPRINT_DmaEpLastBurstEl[ep] >> DEBUGPRINT_DMA_DESCR_SHIFT),
                                                                             DEBUGPRINT_DMA_GET_MAX_ELEM_PER_BURST(DEBUGPRINT_DmaEpLastBurstEl[ep]));
                    }

                    /* Validate descriptor 0 and 1 (also reset current state). Command to start with descriptor 0. */
                    DEBUGPRINT_CyDmaValidateDescriptor(channelNum, DEBUGPRINT_DMA_DESCR0);
                    if (DEBUGPRINT_DmaEpBurstCntBackup[ep] > 1u)
                    {
                        DEBUGPRINT_CyDmaValidateDescriptor(channelNum, DEBUGPRINT_DMA_DESCR1);
                    }
                    DEBUGPRINT_CyDmaSetDescriptor0Next(channelNum);

                    /* Enable DMA channel: configuration complete. */
                    DEBUGPRINT_CyDmaChEnable(channelNum);
                    
                    
                    /* Read CR0 register to clear SIE lock. */
                    (void) DEBUGPRINT_SIE_EP_BASE.sieEp[ep].epCr0;
                    
                    /* Toggle all endpoint types except ISOC. */
                    if (DEBUGPRINT_GET_EP_TYPE(ep) != DEBUGPRINT_EP_TYPE_ISOC)
                    {
                        DEBUGPRINT_EP[ep].epToggle ^= DEBUGPRINT_EPX_CNT_DATA_TOGGLE;
                    }
            
                    /* Notify user that data has been copied from endpoint buffer. */
                    DEBUGPRINT_EP[ep].apiEpState = DEBUGPRINT_EVENT_PENDING;
                    
                #if (defined(DEBUGPRINT_ENABLE_MIDI_STREAMING) && \
                    !defined(DEBUGPRINT_MAIN_SERVICE_MIDI_OUT) && DEBUGPRINT_ISR_SERVICE_MIDI_OUT)
                    if (DEBUGPRINT_midi_out_ep == ep)
                    {
                        DEBUGPRINT_MIDI_OUT_Service();
                    }
                #endif /* (DEBUGPRINT_ISR_SERVICE_MIDI_OUT) */
                }
            #endif /* (CY_PSOC4 && DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */


                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

            #ifdef DEBUGPRINT_ARB_ISR_CALLBACK
                DEBUGPRINT_ARB_ISR_Callback(ep, epStatus);
            #endif /* (DEBUGPRINT_ARB_ISR_CALLBACK) */

                /* Clear serviced endpoint interrupt sources. */
                DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epSr = epStatus;
            }

            ++ep;
            arbIntrStatus >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef DEBUGPRINT_ARB_ISR_EXIT_CALLBACK
        DEBUGPRINT_ARB_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_ARB_ISR_EXIT_CALLBACK) */
    }

#endif /*  (DEBUGPRINT_ARB_ISR_ACTIVE && DEBUGPRINT_EP_MANAGEMENT_DMA) */


#if (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)

    /******************************************************************************
    * Function Name: DEBUGPRINT_EPxDmaDone
    ***************************************************************************//**
    *
    * \internal
    *  Endpoint  DMA Done Interrupt Service Routine basic function .
    *  
    *  \param dmaCh
    *  number of DMA channel
    *  
    *  \param ep
    *  number of USB end point
    *  
    *  \param dmaDone
    *  transfer completion flag
    *  
    *  \return
    *   updated transfer completion flag
    *
    ******************************************************************************/
    CY_INLINE static void DEBUGPRINT_EPxDmaDone(uint8 dmaCh, uint8 ep)
    {
        uint32 nextAddr;

        /* Manage data elements which remain to transfer. */
        if (0u != DEBUGPRINT_DmaEpBurstCnt[ep])
        {
            if(DEBUGPRINT_DmaEpBurstCnt[ep] <= 2u)
            {
                /* Adjust length of last burst. */
                DEBUGPRINT_CyDmaSetNumDataElements(dmaCh,
                                                    ((uint32) DEBUGPRINT_DmaEpLastBurstEl[ep] >> DEBUGPRINT_DMA_DESCR_SHIFT),
                                                    ((uint32) DEBUGPRINT_DmaEpLastBurstEl[ep] &  DEBUGPRINT_DMA_BURST_BYTES_MASK));
            }
            

            /* Advance source for input endpoint or destination for output endpoint. */
            if (0u != (DEBUGPRINT_EP[ep].addr & DEBUGPRINT_DIR_IN))
            {
                /* Change source for descriptor 0. */
                nextAddr = (uint32) DEBUGPRINT_CyDmaGetSrcAddress(dmaCh, DEBUGPRINT_DMA_DESCR0);
                nextAddr += (2u * DEBUGPRINT_DMA_BYTES_PER_BURST);
                DEBUGPRINT_CyDmaSetSrcAddress(dmaCh, DEBUGPRINT_DMA_DESCR0, (void *) nextAddr);

                /* Change source for descriptor 1. */
                nextAddr += DEBUGPRINT_DMA_BYTES_PER_BURST;
                DEBUGPRINT_CyDmaSetSrcAddress(dmaCh, DEBUGPRINT_DMA_DESCR1, (void *) nextAddr);
            }
            else
            {
                /* Change destination for descriptor 0. */
                nextAddr  = (uint32) DEBUGPRINT_CyDmaGetDstAddress(dmaCh, DEBUGPRINT_DMA_DESCR0);
                nextAddr += (2u * DEBUGPRINT_DMA_BYTES_PER_BURST);
                DEBUGPRINT_CyDmaSetDstAddress(dmaCh, DEBUGPRINT_DMA_DESCR0, (void *) nextAddr);

                /* Change destination for descriptor 1. */
                nextAddr += DEBUGPRINT_DMA_BYTES_PER_BURST;
                DEBUGPRINT_CyDmaSetDstAddress(dmaCh, DEBUGPRINT_DMA_DESCR1, (void *) nextAddr);
            }

            /* Enable DMA to execute transfer as it was disabled because there were no valid descriptor. */
            DEBUGPRINT_CyDmaValidateDescriptor(dmaCh, DEBUGPRINT_DMA_DESCR0);
            
            --DEBUGPRINT_DmaEpBurstCnt[ep];
            if (0u != DEBUGPRINT_DmaEpBurstCnt[ep])
            {
                DEBUGPRINT_CyDmaValidateDescriptor(dmaCh, DEBUGPRINT_DMA_DESCR1);
                --DEBUGPRINT_DmaEpBurstCnt[ep];
            }
            
            DEBUGPRINT_CyDmaChEnable (dmaCh);
            DEBUGPRINT_CyDmaTriggerIn(DEBUGPRINT_DmaReqOut[ep]);
        }
        else
        {
            /* No data to transfer. False DMA trig. Ignore.  */
        }

    }

    #if (DEBUGPRINT_DMA1_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP1_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 1 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP1_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP1_DMA_CH,
                                                  DEBUGPRINT_EP1);
                
        }
    #endif /* (DEBUGPRINT_DMA1_ACTIVE) */


    #if (DEBUGPRINT_DMA2_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP2_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 2 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP2_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP2_DMA_CH,
                                                  DEBUGPRINT_EP2);
        }
    #endif /* (DEBUGPRINT_DMA2_ACTIVE) */


    #if (DEBUGPRINT_DMA3_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP3_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 3 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP3_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP3_DMA_CH,
                                                  DEBUGPRINT_EP3);
        }
    #endif /* (DEBUGPRINT_DMA3_ACTIVE) */


    #if (DEBUGPRINT_DMA4_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP4_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 4 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP4_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP4_DMA_CH,
                                                  DEBUGPRINT_EP4);
        }
    #endif /* (DEBUGPRINT_DMA4_ACTIVE) */


    #if (DEBUGPRINT_DMA5_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP5_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 5 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP5_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP5_DMA_CH,
                                                  DEBUGPRINT_EP5);
        }
    #endif /* (DEBUGPRINT_DMA5_ACTIVE) */


    #if (DEBUGPRINT_DMA6_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP6_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 6 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP6_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP6_DMA_CH,
                                                  DEBUGPRINT_EP6);
        }
    #endif /* (DEBUGPRINT_DMA6_ACTIVE) */


    #if (DEBUGPRINT_DMA7_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP7_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 7 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP7_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP7_DMA_CH,
                                                  DEBUGPRINT_EP7);
        }
    #endif /* (DEBUGPRINT_DMA7_ACTIVE) */


    #if (DEBUGPRINT_DMA8_ACTIVE)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP8_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 8 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void DEBUGPRINT_EP8_DMA_DONE_ISR(void)
        {

            DEBUGPRINT_EPxDmaDone((uint8)DEBUGPRINT_EP8_DMA_CH,
                                                  DEBUGPRINT_EP8);
        }
    #endif /* (DEBUGPRINT_DMA8_ACTIVE) */


#else
    #if (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u)
        /******************************************************************************
        * Function Name: DEBUGPRINT_EP_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        CY_ISR(DEBUGPRINT_EP_DMA_DONE_ISR)
        {
            uint8 int8Status;
            uint8 int17Status;
            uint8 ep_status;
            uint8 ep = DEBUGPRINT_EP1;

        #ifdef DEBUGPRINT_EP_DMA_DONE_ISR_ENTRY_CALLBACK
            DEBUGPRINT_EP_DMA_DONE_ISR_EntryCallback();
        #endif /* (DEBUGPRINT_EP_DMA_DONE_ISR_ENTRY_CALLBACK) */

            /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

            /* `#END` */

            /* Read clear on read status register with EP source of interrupt. */
            int17Status = DEBUGPRINT_EP17_DMA_Done_SR_Read() & DEBUGPRINT_EP17_SR_MASK;
            int8Status  = DEBUGPRINT_EP8_DMA_Done_SR_Read()  & DEBUGPRINT_EP8_SR_MASK;

            while (int8Status != 0u)
            {
                while (int17Status != 0u)
                {
                    if ((int17Status & 1u) != 0u)  /* If EpX interrupt present. */
                    {
                        /* Read Endpoint Status Register. */
                        ep_status = DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epSr;

                        if ((0u == (ep_status & DEBUGPRINT_ARB_EPX_SR_IN_BUF_FULL)) &&
                            (0u ==DEBUGPRINT_inBufFull[ep]))
                        {
                            /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                            /* `#END` */

                        #ifdef DEBUGPRINT_EP_DMA_DONE_ISR_CALLBACK
                            DEBUGPRINT_EP_DMA_DONE_ISR_Callback();
                        #endif /* (DEBUGPRINT_EP_DMA_DONE_ISR_CALLBACK) */

                            /* Transfer again 2 last bytes into pre-fetch endpoint area. */
                            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwWaMsb = 0u;
                            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].rwWa = (DEBUGPRINT_DMA_BYTES_PER_BURST * ep) - DEBUGPRINT_DMA_BYTES_REPEAT;
                            DEBUGPRINT_LoadNextInEP(ep, 1u);

                            /* Set Data ready status to generate DMA request. */
                            DEBUGPRINT_ARB_EP_BASE.arbEp[ep].epCfg |= DEBUGPRINT_ARB_EPX_CFG_IN_DATA_RDY;
                        }
                    }

                    ep++;
                    int17Status >>= 1u;
                }

                int8Status >>= 1u;

                if (int8Status != 0u)
                {
                    /* Prepare pointer for EP8. */
                    ep = DEBUGPRINT_EP8;
                    int17Status = int8Status & 0x01u;
                }
            }

            /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

            /* `#END` */

    #ifdef DEBUGPRINT_EP_DMA_DONE_ISR_EXIT_CALLBACK
        DEBUGPRINT_EP_DMA_DONE_ISR_ExitCallback();
    #endif /* (DEBUGPRINT_EP_DMA_DONE_ISR_EXIT_CALLBACK) */
        }
    #endif /* (DEBUGPRINT_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_AUTO) */


#if (CY_PSOC4)
    /***************************************************************************
    * Function Name: DEBUGPRINT_IntrHandler
    ************************************************************************//**
    *
    *   Interrupt handler for Hi/Mid/Low ISRs.
    *
    *  regCause - The cause register of interrupt. One of the three variants:
    *       DEBUGPRINT_INTR_CAUSE_LO_REG - Low interrupts.
    *       DEBUGPRINT_INTR_CAUSE_MED_REG - Med interrupts.
    *       DEBUGPRINT_INTR_CAUSE_HI_REG - - High interrupts.
    *
    *
    ***************************************************************************/
    CY_INLINE static void DEBUGPRINT_IntrHandler(uint32 intrCause)
    {
        /* Array of pointers to component interrupt handlers. */
        static const cyisraddress DEBUGPRINT_isrCallbacks[] =
        {

        };

        uint32 cbIdx = 0u;

        /* Check arbiter interrupt source first. */
        if (0u != (intrCause & DEBUGPRINT_INTR_CAUSE_ARB_INTR))
        {
            DEBUGPRINT_isrCallbacks[DEBUGPRINT_ARB_EP_INTR_NUM]();
        }

        /* Check all other interrupt sources (except arbiter and resume). */
        intrCause = (intrCause  & DEBUGPRINT_INTR_CAUSE_CTRL_INTR_MASK) |
                    ((intrCause & DEBUGPRINT_INTR_CAUSE_EP1_8_INTR_MASK) >>
                                  DEBUGPRINT_INTR_CAUSE_EP_INTR_SHIFT);

        /* Call interrupt handlers for active interrupt sources. */
        while (0u != intrCause)
        {
            if (0u != (intrCause & 0x1u))
            {
                 DEBUGPRINT_isrCallbacks[cbIdx]();
            }

            intrCause >>= 1u;
            ++cbIdx;
        }
    }


    /***************************************************************************
    * Function Name: DEBUGPRINT_INTR_HI_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the high group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(DEBUGPRINT_INTR_HI_ISR)
    {
        DEBUGPRINT_IntrHandler(DEBUGPRINT_INTR_CAUSE_HI_REG);
    }

    /***************************************************************************
    * Function Name: DEBUGPRINT_INTR_MED_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the medium group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(DEBUGPRINT_INTR_MED_ISR)
    {
       DEBUGPRINT_IntrHandler(DEBUGPRINT_INTR_CAUSE_MED_REG);
    }

    /***************************************************************************
    * Function Name: DEBUGPRINT_INTR_LO_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the low group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(DEBUGPRINT_INTR_LO_ISR)
    {
        DEBUGPRINT_IntrHandler(DEBUGPRINT_INTR_CAUSE_LO_REG);
    }
#endif /* (CY_PSOC4) */


/* [] END OF FILE */
