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

#include <stdio.h>
#include <stdbool.h>
#include "PSC_Types.h"
#include "project.h"
#include "PSC_CMD_API.h"
#include "PSC_Communicate.h"
#include "Debugs.h"



PSC_RET PSC_Comm_Initialize();
PSC_RET PSC_Comm_GetCommand(PSC_ST_CMD*);    //Get Command form Device
PSC_RET PSC_Comm_SndCommand(DEV_ID,PSC_CHAR[],uint8);    //Send Command to Device
PSC_RET psc_Comm_GetRecvLine(PSC_ST_CMD*);
PSC_RET psc_Comm_GetRecvChar(DEV_ID,PSC_CHAR*);
PSC_RET psc_Comm_SndDataLine(PSC_ST_CMD*);

PSC_RET PSC_Comm_Initialize()
{
    UART_TO_COMM_Init();
    UART_TO_COMM_Start();
    
    UART_TO_CAMERA_Init();
    UART_TO_CAMERA_Start();
    
    return PSC_RET_SUCCESS;
}


void PSC_Comm_GetCommand(PSC_CHAR *pstRecvData, unsigned short pstRecvDataSize)
{
    char[] retStr;

    ret = psc_Comm_GetRecvLine(&pstRecvData, pstRecvDataSize);
    if( ret != PSC_RET_SUCCESS )
    {
        sprintf(retStr, "Uart Data Racv Err[%d].n\r", ret);
        DBG_printf(retStr);
        return;
    }

    psc_Comm_ErrorRepair();
    return;
}


PSC_RET psc_Comm_GetRecvLine(PSC_CHAR* pstRecvData, unsigned short pstRecvDataSize)
{
    PSC_RET ret;
    PSC_CHAR recv_data;

    while(1)
    {
        recv_data = UART_TO_COMM_GetChar();

        // Data Get Complete Check
        if(PSC_CMD_SET_RECV_DATA(pstRecvData, &recv_data) == PSC_CMD_RCV_ST_COMPLETE)
        {
            break;
        }
    }
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Comm_ErrorRepair(PSC_CHAR* pstRecvData, unsigned short pstRecvDataSize)
{
    return PSC_RET_SUCCESS;
}

//PSC_RET psc_Comm_GetRecvChar(DEV_ID dev_id,PSC_CHAR* pvData)
//{
//    PSC_CHAR    tmpData;
//    int         i;
//
//    switch(dev_id)
//    {
//        case DEV_ID_CAM:
//            tmpData = UART_TO_CAMERA_GetChar();
//            break;
//        case DEV_ID_COMM:
//            tmpData = UART_TO_COMM_GetChar();
//        default:
//            break;
//    }
//
//    *pvData = tmpData;
//    return PSC_RET_SUCCESS;
//}

PSC_RET PSC_Comm_SndCommand(DEV_ID dev_id,PSC_CHAR pChar[],uint8 ucSize)
{
    char    tmpData[SZ_COMMAND];
    uint8   utmpData[SZ_COMMAND];
    int i;
    /* debug */
    DBG_printf("TRACE Send Command Start \n\r");
    switch(dev_id)
    {
        case DEV_ID_CAM:
            /* If not Initialized then skip this function */
            UART_TO_CAMERA_PutArray(pChar, ucSize);
            break;
        case DEV_ID_COMM:
            sprintf(tmpData,"TXDT %s",pChar);
            UART_TO_COMM_PutString(tmpData);
            break;
        default:
            break;
    }
    DBG_printf("TRACE Send Command END \n\r");
    return PSC_RET_SUCCESS;
}