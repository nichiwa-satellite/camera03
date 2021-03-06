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
#include "PSC_Camera.h"
#include "Debugs.h"

#define  HigherBitsMask  ( 0x0F )
#define  LowerBitsMask   ( 0xF0 )

PSC_RET PSC_Comm_Initialize();
PSC_RET PSC_Comm_GetCommand(PSC_ST_CMD*);    //Get Command form Device
PSC_RET PSC_Comm_SndCommand(DEV_ID,PSC_CHAR[],long int);    //Send Command to Device
PSC_RET psc_Comm_GetRecvLine(PSC_ST_CMD*);
PSC_RET psc_Comm_GetRecvChar(DEV_ID,PSC_CHAR*);
PSC_RET psc_Comm_SndDataLine(PSC_ST_CMD*);
PSC_RET psc_Comm_ConvertHEX(const PSC_CHAR, PSC_CHAR*, PSC_CHAR* );


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


PSC_RET PSC_Comm_SndCommand(DEV_ID dev_id,PSC_CHAR pChar[],long int ucSize)
{
    PSC_CHAR    tmpData[2];
    PSC_CHAR    RecvData;
    long int max = 32;
    long int cnt;
    long int i;
    /* debug */
    DBG_printf("TRACE Send Command Start \n\r");
    switch(dev_id)
    {
        case DEV_ID_CAM:
            /* If not Initialized then skip this function */
            UART_TO_CAMERA_PutArray(pChar, ucSize);
            break;
        case DEV_ID_COMM:
            cnt = 0;
            while( cnt < ucSize )
            {
                UART_TO_COMM_PutString("TXDA ");
                CyDelay(30);
                for( i = 0 + cnt; i < max + cnt; i++ )
                {
                    if( i >= ucSize )
                    {
                        break;
                    }
                    PSC_Camera_Buffer_ReadChar(&RecvData,i);
                    psc_Comm_ConvertHEX(RecvData,&tmpData[0], &tmpData[1]);
                    UART_TO_COMM_PutArray( tmpData,2);
                }
                CyDelay(30);
                UART_TO_COMM_PutString("\n\r");
                CyDelay(30);
                cnt = cnt + max;
            }
            break;
        default:
            break;
    }
    DBG_printf("TRACE Send Command END \n\r");
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Comm_ConvertHEX(const PSC_CHAR Input, PSC_CHAR *pH4Bit, PSC_CHAR *pL4Bit )
{
    *pH4Bit = ( (Input & LowerBitsMask) >> 4 ) + '0';
    *pL4Bit = (Input & HigherBitsMask) + '0';
    return PSC_RET_SUCCESS;
}