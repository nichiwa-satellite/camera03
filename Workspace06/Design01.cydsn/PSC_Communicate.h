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
extern PSC_RET PSC_Comm_SndCommand(DEV_ID, PSC_CHAR [],long int);    //Send Command to Device

#endif