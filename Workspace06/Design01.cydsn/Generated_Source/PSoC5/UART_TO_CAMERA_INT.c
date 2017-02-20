/*******************************************************************************
* File Name: UART_TO_CAMERAINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_TO_CAMERA.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART_TO_CAMERA_RX_INTERRUPT_ENABLED && (UART_TO_CAMERA_RX_ENABLED || UART_TO_CAMERA_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART_TO_CAMERA_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_TO_CAMERA_rxBuffer - RAM buffer pointer for save received data.
    *  UART_TO_CAMERA_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_TO_CAMERA_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_TO_CAMERA_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_TO_CAMERA_rxBufferWrite index overtakes
    *     UART_TO_CAMERA_rxBufferRead index.
    *  UART_TO_CAMERA_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_TO_CAMERA_rxBufferWrite is equal to
    *    UART_TO_CAMERA_rxBufferRead
    *  UART_TO_CAMERA_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_TO_CAMERA_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_TO_CAMERA_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART_TO_CAMERA_RXISR_ENTRY_CALLBACK
        UART_TO_CAMERA_RXISR_EntryCallback();
    #endif /* UART_TO_CAMERA_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART_TO_CAMERA_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = UART_TO_CAMERA_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in UART_TO_CAMERA_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (UART_TO_CAMERA_RX_STS_BREAK | 
                            UART_TO_CAMERA_RX_STS_PAR_ERROR |
                            UART_TO_CAMERA_RX_STS_STOP_ERROR | 
                            UART_TO_CAMERA_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                UART_TO_CAMERA_errorStatus |= readStatus & ( UART_TO_CAMERA_RX_STS_BREAK | 
                                                            UART_TO_CAMERA_RX_STS_PAR_ERROR | 
                                                            UART_TO_CAMERA_RX_STS_STOP_ERROR | 
                                                            UART_TO_CAMERA_RX_STS_OVERRUN);
                /* `#START UART_TO_CAMERA_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef UART_TO_CAMERA_RXISR_ERROR_CALLBACK
                UART_TO_CAMERA_RXISR_ERROR_Callback();
            #endif /* UART_TO_CAMERA_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & UART_TO_CAMERA_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = UART_TO_CAMERA_RXDATA_REG;
            #if (UART_TO_CAMERA_RXHW_ADDRESS_ENABLED)
                if(UART_TO_CAMERA_rxAddressMode == (uint8)UART_TO_CAMERA__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & UART_TO_CAMERA_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & UART_TO_CAMERA_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UART_TO_CAMERA_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UART_TO_CAMERA_rxAddressDetected = 0u;
                        }
                    }
                    if(UART_TO_CAMERA_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        UART_TO_CAMERA_rxBuffer[UART_TO_CAMERA_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    UART_TO_CAMERA_rxBuffer[UART_TO_CAMERA_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                UART_TO_CAMERA_rxBuffer[UART_TO_CAMERA_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (UART_TO_CAMERA_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(UART_TO_CAMERA_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        UART_TO_CAMERA_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    UART_TO_CAMERA_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(UART_TO_CAMERA_rxBufferWrite >= UART_TO_CAMERA_RX_BUFFER_SIZE)
                    {
                        UART_TO_CAMERA_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(UART_TO_CAMERA_rxBufferWrite == UART_TO_CAMERA_rxBufferRead)
                    {
                        UART_TO_CAMERA_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (UART_TO_CAMERA_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            UART_TO_CAMERA_RXSTATUS_MASK_REG  &= (uint8)~UART_TO_CAMERA_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(UART_TO_CAMERA_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (UART_TO_CAMERA_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & UART_TO_CAMERA_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START UART_TO_CAMERA_RXISR_END` */

        /* `#END` */

    #ifdef UART_TO_CAMERA_RXISR_EXIT_CALLBACK
        UART_TO_CAMERA_RXISR_ExitCallback();
    #endif /* UART_TO_CAMERA_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (UART_TO_CAMERA_RX_INTERRUPT_ENABLED && (UART_TO_CAMERA_RX_ENABLED || UART_TO_CAMERA_HD_ENABLED)) */


#if (UART_TO_CAMERA_TX_INTERRUPT_ENABLED && UART_TO_CAMERA_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART_TO_CAMERA_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_TO_CAMERA_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_TO_CAMERA_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART_TO_CAMERA_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_TO_CAMERA_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART_TO_CAMERA_TXISR_ENTRY_CALLBACK
        UART_TO_CAMERA_TXISR_EntryCallback();
    #endif /* UART_TO_CAMERA_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART_TO_CAMERA_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART_TO_CAMERA_txBufferRead != UART_TO_CAMERA_txBufferWrite) &&
             ((UART_TO_CAMERA_TXSTATUS_REG & UART_TO_CAMERA_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART_TO_CAMERA_txBufferRead >= UART_TO_CAMERA_TX_BUFFER_SIZE)
            {
                UART_TO_CAMERA_txBufferRead = 0u;
            }

            UART_TO_CAMERA_TXDATA_REG = UART_TO_CAMERA_txBuffer[UART_TO_CAMERA_txBufferRead];

            /* Set next pointer */
            UART_TO_CAMERA_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_TO_CAMERA_TXISR_END` */

        /* `#END` */

    #ifdef UART_TO_CAMERA_TXISR_EXIT_CALLBACK
        UART_TO_CAMERA_TXISR_ExitCallback();
    #endif /* UART_TO_CAMERA_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (UART_TO_CAMERA_TX_INTERRUPT_ENABLED && UART_TO_CAMERA_TX_ENABLED) */


/* [] END OF FILE */
