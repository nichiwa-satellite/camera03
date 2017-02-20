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

#ifndef _PSC_PROC_COMMON
#define _PSC_PROC_COMMON

   
typedef enum PSC_PROC_STATEtag
{
    PSC_PROC_ACTIVE,
    PSC_PROC_SLEEP
}PSC_PROC_STATE;

extern PSC_PROC_STATE gsvPSC_PROC_STATE;


#endif