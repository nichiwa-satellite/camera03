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

#ifndef _PSC_Communicate
#define _PSC_Communicate
    
#include "PSC_Types.h"
#include "PSC_CMD_API.h"
#include "project.h"


extern PSC_RET PSC_Comm_Initialize();
extern PSC_RET PSC_Comm_GetCommand(PSC_ST_CMD*);    //Get Command form Device
extern PSC_RET PSC_Comm_SndCommand(DEV_ID, PSC_CHAR [],uint8);    //Send Command to Device
extern PSC_RET psc_Comm_GetRecvCmd_For_Camera(DEV_ID dev_id, PSC_CHAR string[],  int size );
#endif