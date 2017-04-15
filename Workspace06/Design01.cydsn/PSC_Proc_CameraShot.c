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


#include "PSC_Types.h"
#include "PSC_Interrupt.h"
#include "PSC_CMD_API.h"
#include "PSC_Camera.h"
#include "PSC_Communicate.h"
#include "PSC_Proc_Common.h"
#include "PSC_Proc_CameraShot.h"
#include "project.h"
#include "Debugs.h"

typedef enum PSC_PROC_STATE_CAMERASHOTtag
{
    PR_STATE_CS_INIT,
    PR_STATE_CS_STOP_CURRENT_FRAME,
    PR_STATE_CS_GET_FRAMEDATA_LENGTH,
    PR_STATE_CS_BLUE_INDICATE_VALUE,
    PR_STATE_CS_COMPLETE,
    PR_STATE_CS_RESET_CAMERA,
    PR_STATE_CS_CONFIG_DATASIZE,
    PR_STATE_CS_TAKE_PICTURE,
    PR_STATE_CS_LOAD_DATA_SIZE,
    PR_STATE_CS_LOAD_DATA,
    PR_STATE_CS_GET,
    PR_STATE_CS_BAURATE,
    PR_STATE_CS_MAX
}PSC_PROC_STATE_CAMERASHOT;

static     PSC_CHAR    RecvData[RECVDATASIZE];
static PSC_PROC_STATE_CAMERASHOT svPSC_PROC_STATE_CAMERASHOT;
PSC_PROC_STATE gsvPSC_PROC_STATE;

PSC_RET PSC_Proc_CameraShot_Init(PSC_RET (**)(PSC_ST_CMD*));
PSC_RET PSC_Proc_CameraShot_Main(PSC_ST_CMD*);

PSC_RET psc_Proc_CameraShot_Complete();
PSC_RET psc_Proc_CameraShot_Get(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_ResetCamera(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_Baurate(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_ConfigDataSize(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_TakePicture(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_LoadData(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_LoadDataSize(PSC_ST_CMD*);

PSC_RET psc_Proc_CameraShot_StopCurrentFrame(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_GetFrameDataLength(PSC_ST_CMD*);
PSC_RET psc_Proc_CameraShot_BlueIndicateValue(PSC_ST_CMD*);

PSC_RET psc_Proc_CameraShot_SndCommand( PSC_CHAR [], PSC_CHAR [], int, int, int );

PSC_RET PSC_Proc_CameraShot_Init(PSC_RET (**pFunc)(PSC_ST_CMD*))
{
    gsvPSC_PROC_STATE = PSC_PROC_ACTIVE;
    svPSC_PROC_STATE_CAMERASHOT = PR_STATE_CS_INIT;
    *pFunc = &PSC_Proc_CameraShot_Main;
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_Proc_CameraShot_Main(PSC_ST_CMD* pstData)
{
    PSC_RET ret;

    ret = PSC_RET_SUCCESS;
    
    switch(svPSC_PROC_STATE_CAMERASHOT)
    {
        case PR_STATE_CS_INIT:
            DBG_printf("TRACE Proc CS Init \n\r");
            svPSC_PROC_STATE_CAMERASHOT++;
            break;
        case PR_STATE_CS_GET:
            DBG_printf("TRACE Proc CS Get \n\r");
            ret = psc_Proc_CameraShot_Get(pstData);            
            break;
        case PR_STATE_CS_RESET_CAMERA:
            DBG_printf("TRACE Proc CS Camera \n\r");
            ret = psc_Proc_CameraShot_ResetCamera(pstData);
            break;
        case PR_STATE_CS_BAURATE:
            DBG_printf("TRACE Proc CS Baurate \n\r");
            ret = psc_Proc_CameraShot_Baurate(pstData);
            break;
        case PR_STATE_CS_CONFIG_DATASIZE:
            DBG_printf("TRACE Proc CS Datasize \n\r");
            ret = psc_Proc_CameraShot_ConfigDataSize(pstData);
            break;
        case PR_STATE_CS_TAKE_PICTURE:
            DBG_printf("TRACE Proc CS take picture \n\r");
            ret = psc_Proc_CameraShot_TakePicture(pstData);
            break;
        case PR_STATE_CS_LOAD_DATA_SIZE:
            DBG_printf("TRACE Proc CS LoadDataSize \n\r");
            ret = psc_Proc_CameraShot_LoadDataSize(pstData);
            break;
        case PR_STATE_CS_LOAD_DATA:
            DBG_printf("TRACE Proc CS Load Data \n\r");
            ret = psc_Proc_CameraShot_LoadData(pstData);
            break;
        case PR_STATE_CS_STOP_CURRENT_FRAME:
            ret = psc_Proc_CameraShot_StopCurrentFrame(pstData);
            break;
        
        case PR_STATE_CS_GET_FRAMEDATA_LENGTH:
            ret = psc_Proc_CameraShot_GetFrameDataLength(pstData);
            break;
        
        case PR_STATE_CS_BLUE_INDICATE_VALUE:
            ret = psc_Proc_CameraShot_BlueIndicateValue(pstData);
            break;
            
        case PR_STATE_CS_COMPLETE:
            ret = psc_Proc_CameraShot_Complete();
            break;
        case PR_STATE_CS_MAX:
            break;
        default:
            ret = PSC_RET_INTERNAL_ERROR;
            break;
        
    }
    CyDelay(150);
//    if( ret == PSC_RET_SUCCESS )
//    {
//        svPSC_PROC_STATE_CAMERASHOT++;
//    }
    
    return ret;
}



PSC_RET psc_Proc_CameraShot_Complete()
{
    
    svPSC_PROC_STATE_CAMERASHOT++;
    gsvPSC_PROC_STATE = PSC_PROC_SLEEP;
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Proc_CameraShot_Get(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    
    ret = psc_Proc_CameraShot_SndCommand(get,RecvData,get_size,get_size,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
     
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }

    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Proc_CameraShot_ResetCamera(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    //TODO: Return Value Check from CAM
    //      That is in pstData->
    ret = psc_Proc_CameraShot_SndCommand(reset_camera,RecvData,reset_camera_size,reset_camera_size,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_Baurate(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
    //TODO: Return Value Check from CAM
    //      That is in pstData->
 
    ret = psc_Proc_CameraShot_SndCommand(baurate,RecvData,sizeof(baurate),sizeof(baurate),100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_ConfigDataSize(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    ret = psc_Proc_CameraShot_SndCommand(config_datasize,RecvData,config_datasize_size,config_datasize_size,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_TakePicture(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    //TODO: Return Value Check from CAM
    //      That is in pstData->
    
    ret = psc_Proc_CameraShot_SndCommand(take_picture,RecvData,tack_picture_size,tack_picture_size ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }

    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_LoadDataSize(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    
    ret = psc_Proc_CameraShot_SndCommand(read_datasize,RecvData,read_datasize_size,read_datasize_size ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }    

    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_LoadData(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
    
    ret = psc_Proc_CameraShot_SndCommand(load_data,RecvData,load_data_size,500 ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }    
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Proc_CameraShot_StopCurrentFrame(PSC_ST_CMD* pstData)
{
    PSC_RET     ret;
    PSC_CHAR    SendData[] = {0x56, 0x00, 0x36, 0x01, 0x00};
    
    ret = psc_Proc_CameraShot_SndCommand(SendData,RecvData,sizeof( SendData ),5 ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }    
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Proc_CameraShot_GetFrameDataLength(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
    PSC_CHAR    SendData[] = {0x56, 0x00, 0x34, 0x01, 0x00};

    
   ret = psc_Proc_CameraShot_SndCommand(SendData,RecvData,sizeof( SendData ), 9 ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }    
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}

PSC_RET psc_Proc_CameraShot_BlueIndicateValue(PSC_ST_CMD* pstData)
{
    PSC_RET ret;
     PSC_CHAR    SendData[] = {0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5, 0xF8, 0x10, 0x00};
    
   ret = psc_Proc_CameraShot_SndCommand(SendData,RecvData,sizeof( SendData ),200 ,100);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }    
    
    ret = PSC_CMD_SET_DEVICE_ID(pstData,DEV_ID_CAM);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
}



PSC_RET psc_Proc_CameraShot_SndCommand( PSC_CHAR SendData[], PSC_CHAR RecvDatas[], int SendSize, int RecvSize, int TimeOut )
{
    PSC_RET ret;
    PSC_CHAR data[RECVDATASIZE];
    PSC_INTR_TIKET ticket;

    memset(data, 0x00, sizeof( data ) );
    
    (void)PSC_Interrupt_GetTicket( &ticket, RecvSize );
    (void)PSC_Interrupt_Registration( ticket, 1 );
    (void)PSC_Interrupt_ReciveON();
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,SendData,SendSize);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    while( PSC_Interrupt_RecvStateIsOff() != PSC_RET_SUCCESS ){  }
    (void)PSC_Interrupt_ReciveOFF();
    (void)PSC_Interrupt_Invalidation( ticket );
    (void)PSC_Interrupt_GetData( ticket, data, RecvSize, &RecvSize );
    (void)PSC_Interrupt_TicketFree( ticket );
    
    ret = PSC_Comm_SndCommand(DEV_ID_COMM,data,RecvSize);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    memcpy(RecvDatas,data,RECVDATASIZE);
    
    return PSC_RET_SUCCESS;
}