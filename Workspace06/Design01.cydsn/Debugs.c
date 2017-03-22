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


#include "Debugs.h"
#include "project.h"

void DBG_Init();
void DBG_printf(char str[]);

void DBG_Init()
{
    UART_TO_DEBUG_Init();
    UART_TO_DEBUG_Start();
}

void DBG_printf(char str[])
{
    //UART_TO_DEBUG_PutString(str);
}
