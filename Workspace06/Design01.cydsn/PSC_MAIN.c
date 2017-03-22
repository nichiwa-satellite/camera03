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

#include "PSC_MAIN.h"
#include "PSC_Types.h"
#include "PSC_Communicate.h"
#include "PSC_CMD_API.h"
#include "PSC_Proc_Common.h"
#include "PSC_Proc_CameraShot.h"
#include "Debugs.h"

//Typedef
//-------------------------------------------------//

typedef enum PSC_INTR_STATEtag
{
    PSC_INTR_ST_SLEEP,
    PSC_INTR_ST_ACTIVE,
    PSC_INTR_ST_MAX
    
}PSC_INTR_STATE;

typedef struct PSC_ST_PROCtag
{
    PSC_RET     (*pfInit)();
    PSC_RET     (*pfProc)(PSC_ST_CMD*);
}PSC_ST_PROC;


//Prototypes
//-------------------------------------------------//
void PSC_PROGRAM_START();
PSC_RET psc_Main();
PSC_RET psc_Initialize();

PSC_RET psc_Main_Idle();
//PSC_RET psc_Main_Run();

PSC_RET psc_CmdCheckGo();

//Static
static PSC_STATE        svPSC_PROG_STATE;  //status
static PSC_INTR_STATE   svPSC_INTR_STATE;
static PSC_ST_CMD       sstPSC_COMMAND;
static PSC_RET          (*psfPSC_PROC)(PSC_ST_CMD*);

void PSC_PROGRAM_START()
{
    PSC_RET ret;
    char[] retCommand;
    unsigned char ret;

    unsigned short dataSize = 8;   // get command size(bit)

    // Initialize
    DBG_printf("Initialize.n\r");
    ret = psc_Initialize();
    if( ret != PSC_RET_SUCCESS )
    {
        DBG_printf("Initialize Err.\n\r");
        return;
    }

    // Recv Standby
    DBG_printf("Recv Standby.n\r");
    retCommand = PSC_Comm_GetCommand(dataSize);
    if( retCommand != NULL )
    {
        // Command Check & Go
        DBG_printf("Command Check & Go.\n\r");
        retStatus = psc_CmdCheckGo(retCommand);
        switch( retStatus )
        {
            case 0:
                DBG_printf("Command Check0.\n\r");
                break;
            case 1:
                DBG_printf("Command Check1.\n\r");
                break;
            case 2:
                DBG_printf("Command Check2.\n\r");
                break;
            default:
                DBG_printf("Command Check3.\n\r");
                break;
        }
    }
    return;
}



PSC_RET psc_Initialize()
{
    PSC_RET ret;

    // Debug Print Init
    DBG_Init();

    // sstPSC_COMMAND Init
    ret = PSC_CMD_CREATE_CONTEXT(&sstPSC_COMMAND);
    if( ret != PSC_RET_SUCCESS )
    {
        //Create Context Error
        return ret;
    }

    ret = PSC_Comm_Initialize();
    if( ret != PSC_RET_SUCCESS )
    {
        //Create Context Error
        return ret;
    }

    svPSC_PROG_STATE = PSC_ST_IDLE;
    svPSC_INTR_STATE = PSC_INTR_ST_ACTIVE;
    return PSC_RET_SUCCESS;
}



PSC_RET psc_CmdCheckGo()
{
    PSC_RET ret;
    PSC_COMMAND cmd;

    // 構造体からcmd変数にデータを取得
    ret = PSC_CMD_GET_COMMAND(&sstPSC_COMMAND,&cmd);
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }

    switch( cmd )
    {
        case COMM_REQ_CAMERASHOT:
            ret = PSC_Proc_CameraShot_Init(&psfPSC_PROC);
            if( ret != PSC_RET_SUCCESS )
            {
                return ret;
            }
            break;
        case COMM_REQ_DOWNLOAD_FILE:
            break;
        default:
            svPSC_PROG_STATE = PSC_ST_IDLE;
            break;
    }
    return PSC_RET_SUCCESS;
}



//PSC_RET psc_Main_Run()
//{
//    PSC_RET ret;
//
//    if( psfPSC_PROC == null )
//    {
//        return PSC_RET_SUCCESS;
//    }
//
//    ret = psfPSC_PROC(&sstPSC_COMMAND);
//    if( ret != PSC_RET_SUCCESS )
//    {
//        return ret;
//    }
//
//    if( gsvPSC_PROC_STATE == PSC_PROC_SLEEP )
//    {
//        psfPSC_PROC = null;
//        svPSC_PROG_STATE = PSC_ST_IDLE;
//        return PSC_RET_SUCCESS;
//    }
//
////    ret = PSC_Comm_GetCommand(&sstPSC_COMMAND);
////    if( ret != PSC_RET_SUCCESS )
////    {
////        return ret;
////    }
//
//    return PSC_RET_SUCCESS;
//}
