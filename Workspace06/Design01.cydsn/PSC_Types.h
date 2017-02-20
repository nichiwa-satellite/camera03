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

#ifndef _PSC_TYPES
#define _PSC_TYPES


#define SZ_COMMAND_FULL 36
#define SZ_COMMAND_HEADER 12
#define SZ_COMMAND_BODY 22
#define SZ_COMMAND_END  2
#define SZ_COMMAND      16

#define TX_COMMAND_END 
#define TX_COMMAND_NONE 0x00

#define COMM_REQ_CAMERASHOT             0x0000000000000001
#define COMM_REQ_DOWNLOAD_FILE          0x0000000000000002
    
#define null                            0x00


typedef unsigned       int  PSC_COMMAND;
typedef unsigned       char PSC_CHAR;
  
typedef enum PSC_BOOLtag
{
    PSC_BOOL_FALSE,
    PSC_BOOL_TRUE
}PSC_BOOL;
    
typedef enum DEV_IDtag
{
    DEV_ID_COMM,
    DEV_ID_CAM,
    DEV_ID_MAX,
}DEV_ID;

typedef enum PSC_RETtag
{
    PSC_RET_SUCCESS,
    PSC_RET_INTERNAL_ERROR,
    PSC_RET_INVALID_PARAM,
    PSC_RET_RECV_FAILD,
    PSC_RET_PARTY_ERROR,
    PSC_RET_TIMEOUT,
}PSC_RET;

typedef enum PSC_CMD_ID_FROM_COMMtag
{
    PSC_CMD_ID_FROM_COMM_REQ_CAMERASHOT,
    PSC_CMD_ID_FROM_COMM_REQ_DOWNLOAD_FILE,
    PSC_CMD_ID_FROM_COMM_MAX
}PSC_CMD_ID_FROM_COMM;


#endif