/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "PSC_Types.h"
#include "project.h"
#include "PSC_Interrupt.h"
#include "Debugs.h"

#define RECVDATASIZE        ( 300 )



typedef enum tgPSC_INTR_RESOURCE_STATE
{
    PSC_INTR_RSRC_ST_FREE,
    PSC_INTR_RSRC_ST_HOLD,
    PSC_INTR_RSRC_ST_MAX,
} PSC_INTR_RESOURCE_STATE;

typedef struct tgPSC_INTR_RECVDATA
{
    PSC_INTR_RESOURCE_STATE state;
    PSC_CHAR                data[RECVDATASIZE];
    int                     index;
} PSC_INTR_RECVDATA;

/* function */
PSC_RET PSC_Interrupt_Initialize();
PSC_RET PSC_Interrupt_GetTicket( PSC_INTR_TIKET *pTicket );
PSC_RET PSC_Interrupt_Registration( PSC_INTR_TIKET Ticket, int Retry );
PSC_RET PSC_Interrupt_Invalidation( PSC_INTR_TIKET Ticket );
PSC_RET PSC_Interrupt_GetData( PSC_INTR_TIKET Ticket, PSC_CHAR Data[], int size );
PSC_RET PSC_Interrupt_TicketFree( PSC_INTR_TIKET Ticket );
void PSC_Interrupt_ReciveON();
void PSC_Interrupt_ReciveOFF();

PSC_RET psc_Interrupt_Registration( PSC_INTR_TIKET Ticket );

/* static variable */
static PSC_INTR_RECVDATA PSC_RecvDataList[PSC_INTR_TIKET_MAX];
static PSC_INTR_TIKET PSC_ReciveTicket;
static PSC_INTR_RECV_STATE PSC_ReciveState;

CY_ISR_PROTO(Cam_Rx_Intr);
CY_ISR_PROTO(Cam_Tx_Intr);
CY_ISR_PROTO(Comm_Rx_Intr);
CY_ISR_PROTO(Comm_Tx_Intr);

PSC_RET PSC_Interrupt_Initialize()
{
    Cam_Rx_Intr_StartEx(Cam_Rx_Intr );
    PSC_ReciveTicket = PSC_INTR_TIKET_MAX;
    PSC_ReciveState = PSC_INTR_STATE_RECV_OFF;
    memset(PSC_RecvDataList, 0x00, sizeof( PSC_RecvDataList ) );
    return PSC_RET_SUCCESS;
}


PSC_RET PSC_Interrupt_GetTicket( PSC_INTR_TIKET *pTicket )
{
    PSC_RET ret = PSC_RET_INTERNAL_ERROR;
    int     i;
    
    if( pTicket == NULL )
    {
        return PSC_RET_INVALID_PARAM;
    }
    
    for( i = 0; i < PSC_INTR_TIKET_MAX; i++ )
    {
        if( PSC_RecvDataList[i].state == PSC_INTR_RSRC_ST_FREE )
        {
            memset( &PSC_RecvDataList[i], 0x00, sizeof( PSC_RecvDataList[i] ) );
            PSC_RecvDataList[i].state = PSC_INTR_RSRC_ST_HOLD;
            *pTicket = (PSC_INTR_TIKET)i;
            ret = PSC_RET_SUCCESS;
            break;
        }
    }

    return ret;
}


/* Registration Recive Ticket */
PSC_RET PSC_Interrupt_Registration( PSC_INTR_TIKET Ticket, int Retry )
{
    PSC_RET ret = PSC_RET_TIMEOUT;
    int     i;
    if( Retry < 1 )
    {
        Retry = 1;
    }
    for( i = 0; i < Retry; i++ )
    {
        if( psc_Interrupt_Registration( Ticket ) == PSC_RET_SUCCESS )
        {
            ret = PSC_RET_SUCCESS;
            break;
        }
        CyDelay(100);
    }
    return ret;
}

PSC_RET psc_Interrupt_Registration( PSC_INTR_TIKET Ticket )
{
    PSC_RET ret = PSC_RET_TIMEOUT;

    if( PSC_ReciveTicket != PSC_INTR_TIKET_MAX )
    {
        return PSC_RET_INTERNAL_ERROR;
    }

    PSC_ReciveTicket = Ticket;
    return ret;
}

PSC_RET PSC_Interrupt_Invalidation( PSC_INTR_TIKET Ticket )
{
    if( ( PSC_ReciveTicket != Ticket ) && ( PSC_ReciveTicket != PSC_INTR_TIKET_MAX ) )
    {
        return PSC_RET_INVALID_PARAM;
    }

    PSC_ReciveTicket = PSC_INTR_TIKET_MAX;
    return PSC_RET_SUCCESS;
}


PSC_RET PSC_Interrupt_GetData( PSC_INTR_TIKET Ticket, PSC_CHAR Data[], int size )
{
    PSC_RET ret;
    
    if( ( PSC_ReciveTicket != Ticket ) || ( PSC_ReciveTicket == PSC_INTR_TIKET_MAX ) )
    {
        return PSC_RET_INVALID_PARAM;
    }
    
    if(  RECVDATASIZE < size )
    {
        return PSC_RET_INVALID_PARAM;
    }
    
    memcpy( Data, PSC_RecvDataList[Ticket].data, size );
    
    return PSC_RET_SUCCESS;
}


PSC_RET PSC_Interrupt_TicketFree( PSC_INTR_TIKET Ticket )
{
    if( Ticket >= PSC_INTR_TIKET_MAX )
    {
        return PSC_RET_INVALID_PARAM;
    }
    
    PSC_RecvDataList[Ticket].state = PSC_INTR_RSRC_ST_FREE;
    
    return PSC_RET_SUCCESS;
}


void PSC_Interrupt_ReciveON()
{
    PSC_ReciveState = PSC_INTR_STATE_RECV_ON;
}

void PSC_Interrupt_ReciveOFF()
{
    PSC_ReciveState = PSC_INTR_STATE_RECV_OFF;
}


#pragma interrupt_handler Cam_Rx_Intr

void Cam_Rx_Intr()
{
    int         index;
    PSC_CHAR    recv_data;
    
    recv_data = UART_TO_CAMERA_GetChar();
    UART_TO_DEBUG_PutChar(recv_data);
    if( PSC_ReciveState != PSC_INTR_STATE_RECV_ON )
    {
        return;
    }
    
    if( PSC_ReciveTicket >= PSC_INTR_TIKET_MAX )
    {
        return;
    }
    
    index = PSC_RecvDataList[PSC_ReciveTicket].index;
    PSC_RecvDataList[PSC_ReciveTicket].index++;
    
    PSC_RecvDataList[PSC_ReciveTicket].data[index] = recv_data;
    return;
}
