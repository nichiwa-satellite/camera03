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
#include "project.h"
#include "PSC_MAIN.h"
#include "PSC_Types.h"
#include "PSC_Communicate.h"
#include "PSC_CMD_API.h"
#include "PSC_Proc_Common.h"
#include "PSC_Proc_CameraShot.h"
#include "Debugs.h"

//Prototypes
//-------------------------------------------------//

int main(void)
{
    PSC_CHAR[40] retCommand;

    PSC_Initialize();

    while(1)
    {
        PSC_Comm_GetCommand(&retCommand, sizeof(retCommand));
        if( PSC_CmdIsValid(retCommand) )
        {
            PSC_CmdExecute(retCommand);
        }
    }
    exit(0);
}

 