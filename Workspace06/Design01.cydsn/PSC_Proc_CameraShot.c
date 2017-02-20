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
    PR_STATE_CS_GET,
    PR_STATE_CS_RESET_CAMERA,
    PR_STATE_CS_BAURATE,
    PR_STATE_CS_CONFIG_DATASIZE,
    PR_STATE_CS_TAKE_PICTURE,
    PR_STATE_CS_LOAD_DATA_SIZE,
    PR_STATE_CS_LOAD_DATA,
    PR_STATE_CS_MAX
}PSC_PROC_STATE_CAMERASHOT;


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
            ret = psc_Proc_CameraShot_Get(pstData);
            break;
        case PR_STATE_CS_GET:
            DBG_printf("TRACE Proc CS Get \n\r");
            ret = psc_Proc_CameraShot_ResetCamera(pstData);
            break;
        case PR_STATE_CS_RESET_CAMERA:
            DBG_printf("TRACE Proc CS Camera \n\r");
            ret = psc_Proc_CameraShot_Baurate(pstData);
            break;
        case PR_STATE_CS_BAURATE:
            DBG_printf("TRACE Proc CS Baurate \n\r");
            ret = psc_Proc_CameraShot_ConfigDataSize(pstData);
            break;
        case PR_STATE_CS_CONFIG_DATASIZE:
            DBG_printf("TRACE Proc CS Datasize \n\r");
            ret = psc_Proc_CameraShot_TakePicture(pstData);
            break;
        case PR_STATE_CS_TAKE_PICTURE:
            DBG_printf("TRACE Proc CS take picture \n\r");
            ret = psc_Proc_CameraShot_LoadDataSize(pstData);
            break;
        case PR_STATE_CS_LOAD_DATA_SIZE:
            DBG_printf("TRACE Proc CS LoadDataSize \n\r");
            ret = psc_Proc_CameraShot_LoadData(pstData);
            break;
        case PR_STATE_CS_LOAD_DATA:
            DBG_printf("TRACE Proc CS Load Data \n\r");
            ret = psc_Proc_CameraShot_Complete();
            break;
        case PR_STATE_CS_MAX:
            break;
        default:
            ret = PSC_RET_INTERNAL_ERROR;
            break;
        
    }
    CyDelay(1500);
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
    PSC_RET ret;
    
  
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,get,get_size);
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
    PSC_RET ret;
    //TODO: Return Value Check from CAM
    //      That is in pstData->
    
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,reset_camera,reset_camera_size);
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
    svPSC_PROC_STATE_CAMERASHOT++;
    return PSC_RET_SUCCESS;
    //ret = PSC_Comm_SndCommand(DEV_ID_CAM,baurate,sizeof(baurate));
    if( ret != PSC_RET_SUCCESS )
    {
        //return ret;
        
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
    PSC_RET ret;
    
    
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,config_datasize,config_datasize_size);
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
    PSC_RET ret;
    
    //TODO: Return Value Check from CAM
    //      That is in pstData->
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,take_picture,tack_picture_size);
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
    PSC_RET ret;
    
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,read_datasize,read_datasize_size);
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
    
    ret = PSC_Comm_SndCommand(DEV_ID_CAM,load_data,load_data_size);
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
