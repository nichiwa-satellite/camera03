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


#ifndef _PSC_PROC_CAMERASHOT
#define _PSC_PROC_CAMERASHOT
    
#include "PSC_Types.h"
#include "PSC_CMD_API.h"

extern PSC_RET PSC_Proc_CameraShot_Init(PSC_RET (**)(PSC_ST_CMD*));
extern PSC_RET PSC_Proc_CameraShot_Main(PSC_ST_CMD*);
    
#endif