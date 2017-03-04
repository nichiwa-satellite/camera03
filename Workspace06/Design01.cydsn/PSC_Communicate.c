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

PSC_RET PSC_Comm_GetCommand(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
    
    ret = psc_Comm_GetRecvLine(pstData);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Comm_GetRecvLine(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
    PSC_CHAR recv_data;

    ret = PSC_CMD_RECV_SETUP(pstData);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    /* Debug */
    DBG_printf("TRACE Start Get Command \n\r");
    while(1)
    {   
        ret = psc_Comm_GetRecvChar(pstData->dev_id,&recv_data);
        if( ret != PSC_RET_SUCCESS )
        {
            return ret;
        }
        
        ret = PSC_CMD_SET_RECV_DATA(pstData,&recv_data);
        if( ret != PSC_RET_SUCCESS )
        {
            return ret;
        }
        
        if(PSC_CMD_GET_RCV_STATE() == PSC_CMD_RCV_ST_COMPLETE)
        {
            break;
        }
    }
    /* Debug */
    DBG_printf("TRACE Complete Get Command \n\r");
    ret = PSC_CMD_PARSE_COMMAND(pstData);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    


    return PSC_RET_SUCCESS;
}


PSC_RET psc_Comm_GetRecvChar(DEV_ID dev_id,PSC_CHAR*  pvData)
{
    PSC_CHAR    tmpData;
    int         i;
    
    switch(dev_id)
    {
        case DEV_ID_CAM:
            tmpData = UART_TO_CAMERA_GetChar();
            break;
        case DEV_ID_COMM:
            tmpData = UART_TO_COMM_GetChar();
        default:
            break;
    }
    
    *pvData = tmpData;
    return PSC_RET_SUCCESS;
}


PSC_RET PSC_Comm_SndCommand(DEV_ID dev_id,PSC_CHAR pChar[],uint8 ucSize)
{
    char    tmpData[SZ_COMMAND];
    uint8   utmpData[SZ_COMMAND];
    uint8 bufIndex = 0u;
    int i;
    /* debug */
    DBG_printf("TRACE Send Command Start \n\r");
    switch(dev_id)
    {
        case DEV_ID_CAM:
            /* If not Initialized then skip this function */
            if(UART_TO_CAMERA_initVar != 0u)
            {
                while(bufIndex < ucSize)
                {
                    UART_TO_CAMERA_PutChar(pChar[bufIndex]);
                    bufIndex++;
                    CyDelay(1);
                }
            }
//            UART_TO_CAMERA_PutArray(pChar, ucSize);
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