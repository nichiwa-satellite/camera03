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

#ifndef _interrpt
#define _interrpt
#include "PSC_Types.h"

#define RECVDATASIZE        ( 500 )

   
typedef enum tgPSC_INTR_TIKET
{
    PSC_INTR_TIKET_NO1,
    PSC_INTR_TIKET_MAX,
} PSC_INTR_TIKET;

typedef enum tgPSC_INTR_RECV_STATE
{
    PSC_INTR_STATE_RECV_OFF,
    PSC_INTR_STATE_RECV_ON,
    PSC_INTR_STATE_RECV_MAX,
} PSC_INTR_RECV_STATE;

extern PSC_RET PSC_Interrupt_Initialize();
extern PSC_RET PSC_Interrupt_RecvStateIsOff();
extern PSC_RET PSC_Interrupt_GetTicket( PSC_INTR_TIKET *pTicket, int max );
extern PSC_RET PSC_Interrupt_Registration( PSC_INTR_TIKET Ticket,int Retry );
extern PSC_RET PSC_Interrupt_Invalidation( PSC_INTR_TIKET Ticket );
extern PSC_RET PSC_Interrupt_GetData( PSC_INTR_TIKET Ticket, PSC_CHAR Data[], int size, int *pSize );
extern PSC_RET PSC_Interrupt_TicketFree( PSC_INTR_TIKET Ticket );
extern void PSC_Interrupt_ReciveON();
extern void PSC_Interrupt_ReciveOFF();

#endif