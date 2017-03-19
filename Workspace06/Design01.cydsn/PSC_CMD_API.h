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


#ifndef _PSC_CMD_API
#define _PSC_CMD_API

#include "PSC_Types.h"

typedef enum PSC_CMD_RCV_STATEtag
{
    PSC_CMD_RCV_ST_INIT,
    PSC_CMD_RCV_ST_HEADER,
    PSC_CMD_RCV_ST_BODY,
    PSC_CMD_RCV_ST_END,
    PSC_CMD_RCV_ST_COMPLETE,
    PSC_CMD_RCV_ST_MAX
}PSC_CMD_RCV_STATE;

typedef struct PSC_CMD_INTEGRITYtag
{
    PSC_BOOL            Result;
    PSC_BOOL            Parity;
    PSC_BOOL            Executable;
    unsigned    char    ErrorCorrection;
    PSC_BOOL            PropertyCorruption[3];      //TODO: Define  ->  Command Property Size;
 
}PSC_CMD_INTEGRITY;

typedef struct PSC_CMD_RCV_DATAtag
{
    unsigned    char    RecvDataSize;                   // Recv data size
    PSC_COMMAND         command;                        // Recv data Conv after Command parts
    PSC_CHAR            recv_data[SZ_COMMAND_FULL];     // Recv data
    PSC_CMD_INTEGRITY   Integrity;                      // parity
}PSC_CMD_RCV_DATA;



typedef struct PSC_CMDtag
{
    DEV_ID  dev_id;
    PSC_CMD_RCV_DATA Data;
}PSC_ST_CMD;



extern PSC_RET PSC_CMD_CREATE_CONTEXT(PSC_ST_CMD*);
extern PSC_RET PSC_CMD_SET_UPDATE_FLG(PSC_ST_CMD*,PSC_BOOL);
extern PSC_RET PSC_CMD_SET_DEVICE_ID(PSC_ST_CMD*,DEV_ID);
extern PSC_RET PSC_CMD_SET_COMMAND(PSC_ST_CMD*,PSC_COMMAND*);

extern PSC_RET PSC_CMD_GET_DEVICE_ID(PSC_ST_CMD*,DEV_ID*);
extern PSC_RET PSC_CMD_GET_COMMAND(PSC_ST_CMD*,PSC_COMMAND*);
extern PSC_RET PSC_CMD_GET_UPDATE_FLG(PSC_ST_CMD*,PSC_BOOL*);

extern PSC_CMD_RCV_STATE PSC_CMD_GET_RCV_STATE();
extern PSC_RET PSC_CMD_RECV_SETUP(PSC_ST_CMD*);
extern PSC_RET PSC_CMD_SET_RECV_DATA(PSC_ST_CMD*,PSC_CHAR*);
extern PSC_RET PSC_CMD_SET_RECV_HEADER(PSC_ST_CMD*,PSC_CHAR*);
extern PSC_RET PSC_CMD_SET_RECV_BODY(PSC_ST_CMD*,PSC_CHAR*);
extern PSC_RET PSC_CMD_PARSE_COMMAND(PSC_ST_CMD*);
#endif