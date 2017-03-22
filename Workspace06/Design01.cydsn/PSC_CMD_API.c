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

#include "PSC_CMD_API.h"
#include "PSC_Types.h"

typedef struct PSC_CMD_RCV_PROCtag
{
    unsigned    char    StartIndex;       //WriteIndex
    unsigned    char    EndIndex;
    PSC_RET            (*pfProc)(PSC_ST_CMD*,PSC_CHAR*);
}PSC_CMD_RCV_PROC;

PSC_RET PSC_CMD_CREATE_CONTEXT(PSC_ST_CMD*);
PSC_RET PSC_CMD_SET_UPDATE_FLG(PSC_ST_CMD*,PSC_BOOL);
PSC_RET PSC_CMD_SET_DEVICE_ID(PSC_ST_CMD*,DEV_ID);
PSC_RET PSC_CMD_SET_COMMAND(PSC_ST_CMD*,PSC_COMMAND*);
PSC_RET PSC_CMD_GET_DEVICE_ID(PSC_ST_CMD*,DEV_ID*);
PSC_RET PSC_CMD_GET_COMMAND(PSC_ST_CMD*,PSC_COMMAND*);
PSC_RET PSC_CMD_GET_UPDATE_FLG(PSC_ST_CMD*,PSC_BOOL*);
PSC_RET PSC_CMD_RECV_SETUP(PSC_ST_CMD*);
PSC_RET PSC_CMD_SET_RECV_DATA(PSC_ST_CMD*,PSC_CHAR*);

PSC_RET psc_cmd_StateUpdate(PSC_ST_CMD*,PSC_CHAR*);

PSC_RET psc_cmd_Set_Recv_Header(PSC_ST_CMD*,PSC_CHAR*);
PSC_RET psc_cmd_Set_Recv_Body(PSC_ST_CMD*,PSC_CHAR*);
PSC_RET psc_cmd_Set_Recv_End(PSC_ST_CMD*,PSC_CHAR*);

PSC_RET psc_cmd_Set_Recv_Data(PSC_ST_CMD*,PSC_CHAR*);

PSC_CMD_RCV_STATE svPSC_CMD_RCV_STATE;

static PSC_CMD_RCV_PROC ssaPSC_CMD_RCV_PROC[PSC_CMD_RCV_ST_MAX] = 
{
    {   0                                                           ,
        0                                                           ,
        0                                                       }   ,
    {   0                                                           ,
        SZ_COMMAND_HEADER                                           ,
        &psc_cmd_Set_Recv_Header                                }   ,
    {   SZ_COMMAND_HEADER                                           ,
        SZ_COMMAND_HEADER  +   SZ_COMMAND_BODY                      ,
        &psc_cmd_Set_Recv_Body                                  }   ,
    {   SZ_COMMAND_HEADER  +   SZ_COMMAND_BODY                      ,
        SZ_COMMAND_HEADER  +   SZ_COMMAND_BODY +   SZ_COMMAND_END   ,
        &psc_cmd_Set_Recv_End                                   }   ,
    {   SZ_COMMAND_FULL                                             ,
        SZ_COMMAND_FULL                                             ,
        0                                                       }
};



PSC_RET PSC_CMD_CREATE_CONTEXT(PSC_ST_CMD* pstData)
{
    memset(pstData,0x00,sizeof(PSC_ST_CMD));
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_CMD_RECV_SETUP(PSC_ST_CMD* pstRecvData, unsigned short pstRecvDataSize)
{
    svPSC_CMD_RCV_STATE = PSC_CMD_RCV_ST_INIT;
    memset(pstRecvData, 0x00, pstRecvDataSize);
    return PSC_RET_SUCCESS;
}

PSC_CMD_RCV_STATE PSC_CMD_GET_RCV_STATE()
{
    return svPSC_CMD_RCV_STATE;
}

PSC_RET PSC_CMD_PARSE_COMMAND(PSC_ST_CMD* pstData)
{
    pstData->Data.command = COMM_REQ_CAMERASHOT;
    return PSC_RET_SUCCESS;
}
PSC_RET PSC_CMD_GET_COMMAND(PSC_ST_CMD* pstData,PSC_COMMAND* pStr)
{
    memcpy(pStr,&pstData->Data.command,sizeof(PSC_COMMAND));
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_CMD_GET_DEVICE_ID(PSC_ST_CMD* pstData,DEV_ID* pID)
{
    *pID = pstData->dev_id;
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_CMD_SET_DEVICE_ID(PSC_ST_CMD* pstData,DEV_ID ID)
{
    pstData->dev_id = ID;
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_CMD_SET_COMMAND(PSC_ST_CMD* pstData,PSC_COMMAND* pStr)
{
    memcpy(&pstData->Data.command,&pStr,sizeof(PSC_COMMAND));
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_CMD_SET_RECV_DATA(PSC_ST_CMD* pstData, PSC_CHAR* pChar)
{
    PSC_RET ret;

    if( *pChar != TX_COMMAND_NONE )
    {
        ret = PSC_RET_INVALID_PARAM;
    }

    // Size Over
    if( pstData->Data > pstData->Data.RecvDataSize )
    {
        ret = PSC_CMD_RCV_ST_COMPLETE;
    }
    return ret;
}

PSC_RET psc_cmd_Set_Recv_Header(PSC_ST_CMD* pstData,PSC_CHAR* pChar)
{
    PSC_RET ret;
    ret = psc_cmd_Set_Recv_Data(pstData,pChar);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    return  PSC_RET_SUCCESS;
}

PSC_RET psc_cmd_Set_Recv_Body(PSC_ST_CMD* pstData,PSC_CHAR* pChar)
{
    PSC_RET ret;
    ret = psc_cmd_Set_Recv_Data(pstData,pChar);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    return  PSC_RET_SUCCESS;
}


PSC_RET psc_cmd_Set_Recv_End(PSC_ST_CMD* pstData,PSC_CHAR* pChar)
{
    PSC_RET ret;
    ret = psc_cmd_Set_Recv_Data(pstData,pChar);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    return  PSC_RET_SUCCESS;
}

PSC_RET psc_cmd_Set_Recv_Data(PSC_ST_CMD* pstData,PSC_CHAR* pChar)
{
    if( *pChar != 0x00 )
    {
        pstData->Data.recv_data[pstData->Data.RecvDataSize++] = *pChar;
    }
    
    return PSC_RET_SUCCESS;
}