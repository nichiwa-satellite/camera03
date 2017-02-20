/***************************************************************************//**
* \file DEBUGPRINT_cdc.c
* \version 3.10
*
* \brief
*  This file contains the USB CDC class request handler.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUGPRINT_cdc.h"
#include "DEBUGPRINT_pvt.h"
#include "cyapicallbacks.h"

#if defined(DEBUGPRINT_ENABLE_CDC_CLASS)

/*******************************************************************************
*    CDC Variables
*******************************************************************************/

/*PUBLIC*/
/** Contains the current line coding structure. The host sets it using a
 * SET_LINE_CODING request and returns it to the user code using the
 * DEBUGPRINT_GetDTERate(), DEBUGPRINT_GetCharFormat(),
 * DEBUGPRINT_GetParityType(), and DEBUGPRINT_GetDataBits() APIs.
 * It is an array of 2 elements for COM port 1 and COM port 2 for MultiCOM port
 * support. In case of 1 COM port, data is in 0 element.*/
volatile uint8 DEBUGPRINT_linesCoding[DEBUGPRINT_MAX_MULTI_COM_NUM][DEBUGPRINT_LINE_CODING_SIZE] =
{
    /*COM Port 1*/
    {
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
    },
    /*COM Port 2*/
    {
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
    }
};

/**Used as a flag for the DEBUGPRINT_IsLineChanged() API, to inform it that the
 * host has been sent a request to change line coding or control bitmap. It is 
 * an array of 2 elements for COM port 1 and COM port 2 for MultiCOM port 
 * support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  DEBUGPRINT_linesChanged[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** Contains the current control-signal bitmap. The host sets it using a
 * SET_CONTROL_LINE request and returns it to the user code using the 
 * DEBUGPRINT_GetLineControl() API. It is an array of 2 elements for COM 
 * port 1 and COM port 2 for MultiCOM port support. In case of 1 COM port, data 
 * is in 0 element.*/
volatile uint16 DEBUGPRINT_linesControlBitmap[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** Contains the 16-bit serial state value that was sent using the 
 * \ref DEBUGPRINT_SendSerialState() API. . It is an array of 2 elements 
 * for COM port 1 and COM port 2 for MultiCOM port support. In case of 1 COM 
 * port, data is in 0 element.*/
volatile uint16 DEBUGPRINT_serialStateBitmap[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** Contains the data IN endpoint number. It is initialized after a 
 * SET_CONFIGURATION request based on a user descriptor. It is used in CDC APIs 
 * to send data to the PC. It is an array of 2 elements for COM port 1 and COM 
 * port 2 for MultiCOM port support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  DEBUGPRINT_cdcDataInEp[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** Contains the data OUT endpoint number. It is initialized after a 
 * SET_CONFIGURATION request based on user descriptor. It is used in CDC APIs to 
 * receive data from the PC. It is an array of 2 elements for COM port 1 and COM  
 * port 2 for MultiCOM port support. In case of 1 COM port, data is in 0 element.*/
volatile uint8  DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_MAX_MULTI_COM_NUM];
/** Contains the data IN endpoint number for COMMUNICATION interface. It is 
 * initialized after a SET_CONFIGURATION request based on a user descriptor. It 
 * is used in CDC APIs to send data to the PC. It is an array of 2 elements for 
 * COM port 1 and COM port 2 for MultiCOM port support. In case of 1 COM port, 
 * data is in 0 element.*/
volatile uint8  DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_MAX_MULTI_COM_NUM];

/*PRIVATE*/

#define DEBUGPRINT_CDC_IN_EP      (0u)
#define DEBUGPRINT_CDC_OUT_EP     (1u)
#define DEBUGPRINT_CDC_NOTE_EP    (2u)

#define DEBUGPRINT_CDC_EP_MASK    (0x01u)

#define DEBUGPRINT_GET_EP_COM_NUM(cdcComNums, epType) (((cdcComNums) >> (epType)) & DEBUGPRINT_CDC_EP_MASK)


/***************************************
*     Static Function Prototypes
***************************************/
#if (DEBUGPRINT_ENABLE_CDC_CLASS_API != 0u)
    static uint16 DEBUGPRINT_StrLen(const char8 string[]) ;
    static t_DEBUGPRINT_cdc_notification DEBUGPRINT_serialStateNotification =
    {

        DEBUGPRINT_SERIAL_STATE_REQUEST_TYPE, /* bRequestType    */
        DEBUGPRINT_SERIAL_STATE,              /* bNotification   */
        0u,                                         /* wValue          */
        0u,                                         /* wValueMSB       */
        0u,                                         /* wIndex          */
        0u,                                         /* wIndexMSB       */
        DEBUGPRINT_SERIAL_STATE_LENGTH,       /* wLength         */
        0u,                                         /* wLengthMSB      */
        0u,                                         /* wSerialState    */
        0u,                                         /* wSerialStateMSB */
    };
    static uint8 DEBUGPRINT_activeCom = 0u;
#endif /* (DEBUGPRINT_ENABLE_CDC_CLASS_API != 0u) */


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: DEBUGPRINT_DispatchCDCClassRqst
****************************************************************************//**
*
*  This routine dispatches CDC class requests.
*
* \return
*  requestHandled
*
* \globalvars
*   DEBUGPRINT_linesCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   DEBUGPRINT_linesControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   DEBUGPRINT_linesChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_DispatchCDCClassRqst(void) 
{
    uint8 requestHandled = DEBUGPRINT_FALSE;
    uint8 comPort;

    comPort = DEBUGPRINT_GetInterfaceComPort((uint8)DEBUGPRINT_wIndexLoReg);

    /* Check request direction: D2H or H2D. */
    if (0u != (DEBUGPRINT_bmRequestTypeReg & DEBUGPRINT_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */

        switch (DEBUGPRINT_bRequestReg)
        {
            case DEBUGPRINT_CDC_GET_LINE_CODING:
                DEBUGPRINT_currentTD.count = DEBUGPRINT_LINE_CODING_SIZE;
                DEBUGPRINT_currentTD.pData = DEBUGPRINT_linesCoding[comPort];
                requestHandled  = DEBUGPRINT_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:
            /* Do not handle this request unless callback is defined. */
            #ifdef DEBUGPRINT_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK
                requestHandled = DEBUGPRINT_DispatchCDCClass_CDC_READ_REQUESTS_Callback();
            #endif /* (DEBUGPRINT_DISPATCH_CDC_CLASS_CDC_READ_REQUESTS_CALLBACK) */
                break;
        }
    }
    else
    {
        /* Handle direction from host to device. */

        switch (DEBUGPRINT_bRequestReg)
        {
            case DEBUGPRINT_CDC_SET_LINE_CODING:
                DEBUGPRINT_currentTD.count  = DEBUGPRINT_LINE_CODING_SIZE;
                DEBUGPRINT_currentTD.pData  = DEBUGPRINT_linesCoding[comPort];
                DEBUGPRINT_linesChanged[comPort] |= DEBUGPRINT_LINE_CODING_CHANGED;

                requestHandled = DEBUGPRINT_InitControlWrite();
                break;

            case DEBUGPRINT_CDC_SET_CONTROL_LINE_STATE:
                DEBUGPRINT_linesControlBitmap[comPort] = (uint8) DEBUGPRINT_wValueLoReg;
                DEBUGPRINT_linesChanged[comPort]      |= DEBUGPRINT_LINE_CONTROL_CHANGED;

                requestHandled = DEBUGPRINT_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:
                /* Do not handle this request unless callback is defined. */
            #ifdef DEBUGPRINT_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK
                requestHandled = DEBUGPRINT_DispatchCDCClass_CDC_WRITE_REQUESTS_Callback();
            #endif /* (DEBUGPRINT_DISPATCH_CDC_CLASS_CDC_WRITE_REQUESTS_CALLBACK) */
                break;
        }
    }

    return(requestHandled);
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetInterfaceComPort
************************************************************************//**
*   \internal
*  Internal function which gets number of COM port by specified interface
*   number.
*
* \param uint8 interface
*  Interface number
*
* \return
*  COM port number (0 or 1) or error 0xFF
*
***************************************************************************/
uint8 DEBUGPRINT_GetInterfaceComPort(uint8 interface) 
{
    uint8 comPort = 0u;
    uint8 res = 0xFFu;
    uint8 notEp;

    while (comPort < DEBUGPRINT_MAX_MULTI_COM_NUM)
    {
        notEp = DEBUGPRINT_cdcCommInInterruptEp[comPort];

        if (DEBUGPRINT_EP[notEp].interface == interface)
        {
            res = comPort;
            comPort = DEBUGPRINT_MAX_MULTI_COM_NUM;
        }

        comPort++;
    }
    return (res);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (DEBUGPRINT_ENABLE_CDC_CLASS_API != 0u)
/***************************************************************************
* Function Name: DEBUGPRINT_CDC_Init
************************************************************************//**
*
*  This function initializes the CDC interface to be ready to receive data
*  from the PC. The API set active communication port to 0 in the case of 
*  multiple communication port support.This API should be called after the 
*  device has been started and configured using USBUART_Start() API to 
*  initialize and start the USBFS component operation. Then call the 
*  USBUART_GetConfiguration() API to wait until the host has enumerated and 
*  configured the device. For example:
*
*  \snippet /USBFS_sut_02.cydsn/main.c wait for enumeration
*
* \return
*  cystatus:
*   Return Value    Description
*   DEBUGPRINT_SUCCESS   CDC interface was initialized correctly
*   DEBUGPRINT_FAILURE   CDC interface was not initialized
*
* \globalvars
*   DEBUGPRINT_linesChanged: Initialized to zero.
*   DEBUGPRINT_cdcDataOutEp: Used as an OUT endpoint number.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 DEBUGPRINT_CDC_Init(void) 
{
    uint8 comPort;
    uint8 outEp;
    uint8 ret = DEBUGPRINT_SUCCESS;

    DEBUGPRINT_activeCom = 0u;
    DEBUGPRINT_linesChanged[DEBUGPRINT_COM_PORT1] = 0u;
    DEBUGPRINT_linesChanged[DEBUGPRINT_COM_PORT2] = 0u;

    for(comPort = 0u; comPort<DEBUGPRINT_MAX_MULTI_COM_NUM; comPort++)
    {
        outEp = DEBUGPRINT_cdcDataOutEp[comPort];
        if((0u != outEp) && (DEBUGPRINT_MAX_EP > outEp))
        {
            DEBUGPRINT_EnableOutEP(outEp);
        }

    }

    /* COM Port 1 should be correct to proceed. */
    if ((0u == DEBUGPRINT_cdcDataInEp[DEBUGPRINT_COM_PORT1]) \
            || (0u == DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_COM_PORT1]) \
            || (0u ==  DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_COM_PORT1])
            || (DEBUGPRINT_cdcDataInEp[DEBUGPRINT_COM_PORT1] >= DEBUGPRINT_MAX_EP)
            || (DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_COM_PORT1] >= DEBUGPRINT_MAX_EP)
            || (DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_COM_PORT1] >= DEBUGPRINT_MAX_EP))
    {
        ret = DEBUGPRINT_FAILURE;
    }

    return (ret);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_PutData
****************************************************************************//**
*
*  This function sends a specified number of bytes from the location specified
*  by a pointer to the PC. The DEBUGPRINT_CDCIsReady() function should be
*  called before sending new data, to be sure that the previous data has
*  finished sending.
*  If the last sent packet is less than maximum packet size the USB transfer
*  of this short packet will identify the end of the segment. If the last sent
*  packet is exactly maximum packet size, it shall be followed by a zero-length
*  packet (which is a short packet) to assure the end of segment is properly
*  identified. To send zero-length packet, use DEBUGPRINT_PutData() API
*  with length parameter set to zero.
*
*  \param pData: pointer to the buffer containing data to be sent.
*  \param length: Specifies the number of bytes to send from the pData
*  buffer. Maximum length will be limited by the maximum packet
*  size for the endpoint. Data will be lost if length is greater than Max
*  Packet Size.
*
* \globalvars
*
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_PutData(const uint8* pData, uint16 length) 
{
    uint8 epNumber = DEBUGPRINT_cdcDataInEp[DEBUGPRINT_activeCom];

    /* Limit length to maximum packet size for endpoint. */
    if (length > DEBUGPRINT_EP[epNumber].bufferSize)
    {
        /* Caution: Data will be lost if length is greater than Max Packet Size. */
        length = DEBUGPRINT_EP[epNumber].bufferSize;

        /* Halt CPU in debug mode */
        CYASSERT(0u != 0u);
    }

    DEBUGPRINT_LoadInEP(epNumber, pData, length);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_StrLen
****************************************************************************//**
*
*  Calculates length of a null terminated string.
*
*  \param string: pointer to the string.
*
* \return
*  Length of the string
*
*******************************************************************************/
static uint16 DEBUGPRINT_StrLen(const char8 string[]) 
{
    uint16 len = 0u;

    while (string[len] != (char8)0)
    {
        len++;
    }

    return ((uint16) len);
}


/***************************************************************************
* Function Name: DEBUGPRINT_PutString
************************************************************************//**
*
*  This function sends a null terminated string to the PC. This function will
*  block if there is not enough memory to place the whole string. It will block
*  until the entire string has been written to the transmit buffer.
*  The DEBUGPRINT_CDCIsReady() function should be called before
*  sending data with a new call to DEBUGPRINT_PutString(), to be sure
*  that the previous data has finished sending. This function sends
*  zero-length packet automatically, if the length of the last packet, sent
*  by this API, is equal to Max Packet Size
*
*  \param string: pointer to the string to be sent to the PC.
*
* \globalvars
*
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
***************************************************************************/
void DEBUGPRINT_PutString(const char8 string[]) 
{
    uint16 strLength;
    uint16 sendLength;
    uint16 bufIndex = 0u;

    uint8  epNumber = DEBUGPRINT_cdcDataInEp[DEBUGPRINT_activeCom];

    /* Get length string length (it is terminated with zero). */
    strLength = DEBUGPRINT_StrLen(string);

    do
    {
        /* Limit length to maximum packet size of endpoint. */
        sendLength = (strLength > DEBUGPRINT_EP[epNumber].bufferSize) ?
                                  DEBUGPRINT_EP[epNumber].bufferSize : strLength;

        /* Load IN endpoint and expose it to host. */
        DEBUGPRINT_LoadInEP(epNumber, (const uint8 *)&string[bufIndex], sendLength);
        strLength -= sendLength;

        /* If more data are present to send or full packet was sent */
        if ((strLength > 0u) || (sendLength == DEBUGPRINT_EP[epNumber].bufferSize))
        {
            bufIndex += sendLength;

            /* Wait until host read data from IN endpoint buffer. */
            while (DEBUGPRINT_IN_BUFFER_FULL == DEBUGPRINT_EP[epNumber].apiEpState)
            {
            }

            /* If last packet is exactly maximum packet size, it shall be followed
            * by a zero-length packet to assure the end of segment is properly
            * identified by the terminal.
            */
            if (0u == strLength)
            {
                DEBUGPRINT_LoadInEP(epNumber, NULL, 0u);
            }
        }
    }
    while (strLength > 0u);
}


/***************************************************************************
* Function Name: DEBUGPRINT_PutChar
************************************************************************//**
*
*  This function writes a single character to the PC at a time. This is an
*  inefficient way to send large amounts of data.
*
*  \param txDataByte: Character to be sent to the PC.
*
*  \globalvars
*
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
*  \reentrant
*  No.
*
***************************************************************************/
void DEBUGPRINT_PutChar(char8 txDataByte) 
{
    uint8 dataByte;
    dataByte = (uint8) txDataByte;

    DEBUGPRINT_LoadInEP(DEBUGPRINT_cdcDataInEp[DEBUGPRINT_activeCom], &dataByte, 1u);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_PutCRLF
****************************************************************************//**
*
*  This function sends a carriage return (0x0D) and line feed (0x0A) to the
*  PC. This APIis provided to mimic API provided by our other UART components
*
* \globalvars
*
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used for sending
*     data.
*
* \reentrant
*  No.
*
*******************************************************************************/
void DEBUGPRINT_PutCRLF(void) 
{
    const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

    DEBUGPRINT_LoadInEP(DEBUGPRINT_cdcDataInEp[DEBUGPRINT_activeCom], (const uint8 *)txData, 2u);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetCount
****************************************************************************//**
*
*  This function returns the number of bytes that were received from the PC.
*  The returned length value should be passed to DEBUGPRINT_GetData() as
*  a parameter to read all received data. If all of the received data is not
*  read at one time by the DEBUGPRINT_GetData() API, the unread data will
*  be lost.
*
* \return
*  Returns the number of received bytes. The maximum amount of received data at
*  a time is limited by the maximum packet size for the endpoint.
*
* \globalvars
*   DEBUGPRINT_cdcDataOutEp: CDC OUT endpoint number used.
*
*******************************************************************************/
uint16 DEBUGPRINT_GetCount(void) 
{
    uint16 bytesCount;

    uint8  epNumber = DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_activeCom];

    if (DEBUGPRINT_OUT_BUFFER_FULL == DEBUGPRINT_EP[epNumber].apiEpState)
    {
        bytesCount = DEBUGPRINT_GetEPCount(epNumber);
    }
    else
    {
        bytesCount = 0u;
    }

    return (bytesCount);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_DataIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the component received data or
*  received zero-length packet. The DEBUGPRINT_GetAll() or
*  DEBUGPRINT_GetData() API should be called to read data from the buffer
*  and reinitialize the OUT endpoint even when a zero-length packet is
*  received. These APIs will return zero value when zero-length packet is
*  received.
*
* \return
*  If the OUT packet is received, this function returns a non-zero value.
*  Otherwise, it returns zero.
*
* \globalvars
*   DEBUGPRINT_cdcDataOutEp: CDC OUT endpoint number used.
*
*******************************************************************************/
uint8 DEBUGPRINT_DataIsReady(void) 
{
    return (DEBUGPRINT_GetEPState(DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_activeCom]));
}


/*******************************************************************************
* Function Name: DEBUGPRINT_CDCIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the component is ready to send more
*  data to the PC; otherwise, it returns zero. The function should be called
*  before sending new data when using any of the following APIs:
*  DEBUGPRINT_PutData(),DEBUGPRINT_PutString(),
*  DEBUGPRINT_PutChar or DEBUGPRINT_PutCRLF(),
*  to be sure that the previous data has finished sending.
*
* \return
*  If the buffer can accept new data, this function returns a non-zero value.
*  Otherwise, it returns zero.
*
* \globalvars
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used.
*
*******************************************************************************/
uint8 DEBUGPRINT_CDCIsReady(void) 
{
    return (DEBUGPRINT_GetEPState(DEBUGPRINT_cdcDataInEp[DEBUGPRINT_activeCom]));
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetData
************************************************************************//**
*
*  This function gets a specified number of bytes from the input buffer and
*  places them in a data array specified by the passed pointer.
*  The DEBUGPRINT_DataIsReady() API should be called first, to be sure
*  that data is received from the host. If all received data will not be read at
*  once, the unread data will be lost. The DEBUGPRINT_GetData() API should
*  be called to get the number of bytes that were received.
*
*  \param pData: Pointer to the data array where data will be placed.
*  \param Length: Number of bytes to read into the data array from the RX buffer.
*          Maximum length is limited by the the number of received bytes
*          or 64 bytes.
*
* \return
*         Number of bytes which function moves from endpoint RAM into the
*         data array. The function moves fewer than the requested number
*         of bytes if the host sends fewer bytes than requested or sends
*         zero-length packet.
*
* \globalvars
*   DEBUGPRINT_cdcDataOutEp: CDC OUT endpoint number used.
*
* \reentrant
*  No.
*
***************************************************************************/
uint16 DEBUGPRINT_GetData(uint8* pData, uint16 length) 
{
    uint8 epNumber = DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_activeCom];

    /* Read data from OUT endpoint buffer. */
    length = DEBUGPRINT_ReadOutEP(epNumber, pData, length);

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (DEBUGPRINT_OUT_BUFFER_FULL == DEBUGPRINT_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    DEBUGPRINT_EnableOutEP(epNumber);
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) */

    return (length);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetAll
****************************************************************************//**
*
*  This function gets all bytes of received data from the input buffer and
*  places them into a specified data array. The
*  DEBUGPRINT_DataIsReady() API should be called first, to be sure
*  that data is received from the host.
*
*  \param pData: Pointer to the data array where data will be placed.
*
* \return
*  Number of bytes received. The maximum amount of the received at a time
*  data is 64 bytes.
*
* \globalvars
*   - \ref DEBUGPRINT_cdcDataOutEp: CDC OUT endpoint number used.
*   - \ref DEBUGPRINT_EP[].bufferSize: EP max packet size is used as a
*     length to read all data from the EP buffer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint16 DEBUGPRINT_GetAll(uint8* pData) 
{
    uint8 epNumber = DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_activeCom];
    uint16 dataLength;

    /* Read data from OUT endpoint buffer. */
    dataLength = DEBUGPRINT_ReadOutEP(epNumber, pData, DEBUGPRINT_EP[epNumber].bufferSize);

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (DEBUGPRINT_OUT_BUFFER_FULL == DEBUGPRINT_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    DEBUGPRINT_EnableOutEP(epNumber);
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) */

    return (dataLength);
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetChar
************************************************************************//**
*
*  This function reads one byte of received data from the buffer. If more than
*  one byte has been received from the host, the rest of the data will be lost.
*
* \return
*  Received one character.
*
* \globalvars
*   DEBUGPRINT_cdcDataOutEp: CDC OUT endpoint number used.
*
* \reentrant
*  No.
*
***************************************************************************/
uint8 DEBUGPRINT_GetChar(void) 
{
     uint8 rxData;
     uint8 epNumber = DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_activeCom];

    (void) DEBUGPRINT_ReadOutEP(epNumber, &rxData, 1u);

#if (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL)
    /* Wait until DMA complete transferring data from OUT endpoint buffer. */
    while (DEBUGPRINT_OUT_BUFFER_FULL == DEBUGPRINT_GetEPState(epNumber))
    {
    }

    /* Enable OUT endpoint to communicate with host. */
    DEBUGPRINT_EnableOutEP(epNumber);
#endif /* (DEBUGPRINT_EP_MANAGEMENT_DMA_MANUAL) */

    return (rxData);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_IsLineChanged
****************************************************************************//**
*
*  This function returns clear on read status of the line. It returns not zero
*  value when the host sends updated coding or control information to the
*  device. The DEBUGPRINT_GetDTERate(), DEBUGPRINT_GetCharFormat()
*  or DEBUGPRINT_GetParityType() or DEBUGPRINT_GetDataBits() API
*  should be called to read data coding information.
*  The DEBUGPRINT_GetLineControl() API should be called to read line
*  control information.
*
* \return
*  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE requests are received, it
*  returns a non-zero value. Otherwise, it returns zero.
*  Return Value                 | Description
*  -----------------------------|--------------------------
*  USBUART_LINE_CODING_CHANGED  | Line coding changed
*  USBUART_LINE_CONTROL_CHANGED |   Line control changed
*
* \globalvars
*  - \ref DEBUGPRINT_transferState: it is checked to be sure then OUT
*    data phase has been complete, and data written to the lineCoding or
*    Control Bitmap buffer.
*  - \ref DEBUGPRINT_linesChanged: used as a flag to be aware that
*    Host has been sent request for changing Line Coding or Control Bitmap.
*
*******************************************************************************/
uint8 DEBUGPRINT_IsLineChanged(void) 
{
    uint8 state = 0u;

    /* transferState is checked to be sure then OUT data phase has been complete */
    if (DEBUGPRINT_transferState == DEBUGPRINT_TRANS_STATE_IDLE)
    {
        if (DEBUGPRINT_linesChanged[DEBUGPRINT_activeCom] != 0u)
        {
            state = DEBUGPRINT_linesChanged[DEBUGPRINT_activeCom];
            DEBUGPRINT_linesChanged[DEBUGPRINT_activeCom] = 0u;
        }
    }

    return (state);
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetDTERate
************************************************************************//**
*
*  This function returns the data terminal rate set for this port in bits
*  per second.
*
* \return
*  Returns a uint32 value of the data rate in bits per second.
*
* \globalvars
*  DEBUGPRINT_linesCoding: First four bytes converted to uint32
*    depend on compiler, and returned as a data rate.
*
*******************************************************************************/
uint32 DEBUGPRINT_GetDTERate(void) 
{
    uint32 rate;

    rate = DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_RATE + 3u];
    rate = (rate << 8u) | DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_RATE + 2u];
    rate = (rate << 8u) | DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_RATE + 1u];
    rate = (rate << 8u) | DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_RATE];

    return (rate);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetCharFormat
****************************************************************************//**
*
*  Returns the number of stop bits.
*
* \return
*  Returns the number of stop bits.
*  Return               |Value Description
*  ---------------------|-------------------
*  USBUART_1_STOPBIT    | 1 stop bit
*  USBUART_1_5_STOPBITS | 1,5 stop bits
*  USBUART_2_STOPBITS   | 2 stop bits
*
*
* \globalvars
*  DEBUGPRINT_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 DEBUGPRINT_GetCharFormat(void) 
{
    return (DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_STOP_BITS]);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetParityType
****************************************************************************//**
*
*  This function returns the parity type for the CDC port.
*
* \return
*  Returns the parity type.
*   Return               | Value Description
*  ----------------------|-------------------
*  USBUART_PARITY_NONE   | 1 stop bit
*  USBUART_PARITY_ODD    | 1,5 stop bits
*  USBUART_PARITY_EVEN   | 2 stop bits
*  USBUART_PARITY_MARK   | Mark
*  USBUART_PARITY_SPACE  | Space
*
* \globalvars
*  DEBUGPRINT_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 DEBUGPRINT_GetParityType(void) 
{
    return (DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_PARITY]);
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetDataBits
************************************************************************//**
*
*  This function returns the number of data bits for the CDC port.
*
* \return
*  Returns the number of data bits.
*  The number of data bits can be 5, 6, 7, 8 or 16.
*
* \globalvars
*  DEBUGPRINT_linesCoding: used to get a parameter.
*
*******************************************************************************/
uint8 DEBUGPRINT_GetDataBits(void) 
{
    return (DEBUGPRINT_linesCoding[DEBUGPRINT_activeCom][DEBUGPRINT_LINE_CODING_DATA_BITS]);
}


/***************************************************************************
* Function Name: DEBUGPRINT_GetLineControl
************************************************************************//**
*
*  This function returns Line control bitmap that the host sends to the
*  device.
*
* \return
*  Returns Line control bitmap.
*  Return                   |Value Notes
*  -------------------------|-----------------------------------------------
*  USBUART_LINE_CONTROL_DTR |Indicates that a DTR signal is present. This signal corresponds to V.24 signal 108/2 and RS232 signal DTR.
*  USBUART_LINE_CONTROL_RTS |Carrier control for half-duplex modems. This signal corresponds to V.24 signal 105 and RS232 signal RTS.
*  RESERVED                 |The rest of the bits are reserved.
*
*  *Note* Some terminal emulation programs do not properly handle these
*  control signals. They update information about DTR and RTS state only
*  when the RTS signal changes the state.
*
* \globalvars
*  DEBUGPRINT_linesControlBitmap: used to get a parameter.
*
*******************************************************************************/
uint16 DEBUGPRINT_GetLineControl(void) 
{
    return (DEBUGPRINT_linesControlBitmap[DEBUGPRINT_activeCom]);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_SendSerialState
****************************************************************************//**
*
*  Sends the serial state notification to the host using the interrupt
*  endpoint for the COM port selected using the API SetComPort().The
*  DEBUGPRINT_NotificationIsReady() API must be called to check if the
*  Component is ready to send more serial state to the host. The API will
*  not send the notification data if the interrupt endpoint Max Packet Size
*  is less than the required 10 bytes.
*
* \param uint16 serialState
*  16-bit value that will be sent from the device to the
*  host as SERIAL_STATE notification using the IN interrupt endpoint. Refer
*  to revision 1.2 of the CDC PSTN Subclass specification for bit field
*  definitions of the 16-bit serial state value.
*
*******************************************************************************/
void DEBUGPRINT_SendSerialState (uint16 serialState) 
{
    uint8 epNumber = DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_activeCom];

    if(DEBUGPRINT_SERIAL_STATE_SIZE <= DEBUGPRINT_EP[epNumber].bufferSize)
    {
        /* Save current SERIAL_STATE bitmap. */
        DEBUGPRINT_serialStateBitmap[DEBUGPRINT_activeCom] = serialState;

        /* Add interface number */
        DEBUGPRINT_serialStateNotification.wIndex = DEBUGPRINT_EP[epNumber].interface;

        /*Form SERIAL_STATE data*/
        DEBUGPRINT_serialStateNotification.wSerialState =    LO8(DEBUGPRINT_serialStateBitmap[DEBUGPRINT_activeCom]);
        DEBUGPRINT_serialStateNotification.wSerialStateMSB = HI8(DEBUGPRINT_serialStateBitmap[DEBUGPRINT_activeCom]);

        DEBUGPRINT_LoadInEP(epNumber, (uint8 *) &DEBUGPRINT_serialStateNotification, sizeof(DEBUGPRINT_serialStateNotification));
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetSerialState
****************************************************************************//**
*
*  This function returns the current serial state value for the COM port
*  selected using the API SetComPort().
*
* \return
*  16-bit serial state value. Refer to revision 1.2 of the CDC PSTN Subclass
*  specification for bit field definitions of the 16-bit serial state value.
*
*******************************************************************************/
uint16 DEBUGPRINT_GetSerialState(void) 
{
    return DEBUGPRINT_serialStateBitmap[DEBUGPRINT_activeCom];
}


/*******************************************************************************
* Function Name: DEBUGPRINT_NotificationIsReady
****************************************************************************//**
*
*  This function returns a non-zero value if the Component is ready to send
*  more notifications to the host; otherwise, it returns zero. The function
*  should be called before sending new notifications when using
*  DEBUGPRINT_SendSerialState() to ensure that any previous
*  notification data has been already sent to the host.
*
* \return
*  If the buffer can accept new data(endpoint buffer not full), this
*  function returns a non-zero value. Otherwise, it returns zero.
*
* \globalvars
*   DEBUGPRINT_cdcDataInEp: CDC IN endpoint number used.
*
*******************************************************************************/
uint8 DEBUGPRINT_NotificationIsReady(void) 
{
    return (DEBUGPRINT_EP[DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_activeCom]].apiEpState);
}


/*******************************************************************************
* Function Name: DEBUGPRINT_SetComPort
****************************************************************************//**
*
*  This function allows the user to select from one of the two COM ports
*  they wish to address in the instance of having multiple COM ports
*  instantiated though the use of a composite device. Once set, all future
*  function calls related to the USBUART will be affected. This addressed
*  COM port can be changed during run time.
*
* \param comNumber
*  Contains the COM interface the user wishes to address. Value can either
*  be 0 or 1 since a maximum of only 2 COM ports can be supported. Note that
*  this COM port number is not the COM port number assigned on the PC side
*  for the UART communication. If a value greater than 1 is passed, the
*  function returns without performing any action.
*
*******************************************************************************/
void DEBUGPRINT_SetComPort(uint8 comNumber) 
{
    if ((DEBUGPRINT_activeCom != comNumber) && \
            (comNumber < DEBUGPRINT_MAX_MULTI_COM_NUM ))
    {
        DEBUGPRINT_activeCom = comNumber;
    }
}


/*******************************************************************************
* Function Name: DEBUGPRINT_GetComPort
****************************************************************************//**
*
*  This function returns the current selected COM port that the user is
*  currently addressing in the instance of having multiple COM ports
*  instantiated though the use of a composite device.
*
* \return
*  Returns the currently selected COM port. Value can either be 0 or 1 since
*  a maximum of only 2 COM ports can be supported. . Note that this COM port
*  number is not the COM port number assigned on the PC side for the UART
*  communication.
*
*******************************************************************************/
uint8 DEBUGPRINT_GetComPort(void) 
{
    return (DEBUGPRINT_activeCom);
}


#endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS_API) */


/***************************************************************************
* Function Name: DEBUGPRINT_Cdc_EpInit
************************************************************************//**
*
*  \internal
*  This routine decide type of endpoint (IN, OUT, Notification) and same to
*   appropriate global variables  according to COM port number.
*   DEBUGPRINT_cdcDataInEp[], DEBUGPRINT_cdcCommInInterruptEp[],
*   DEBUGPRINT_cdcDataOutEp[]
*
* \param pEP: Pointer to structure with current EP description.
* \param epNum: EP number
* \param cdcComNums: Bit array of current COM ports for CDC IN, OUT,
*        and notification EPs(0 - COM port 1, 1- COM port 2)
*
* \return
*  Updated cdcComNums
*
* \reentrant
*  No.
*
***************************************************************************/
uint8 DEBUGPRINT_Cdc_EpInit(const T_DEBUGPRINT_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) 
{
    uint8 epType;

    epType = pEP->attributes & DEBUGPRINT_EP_TYPE_MASK;

    if (0u != (pEP->addr & DEBUGPRINT_DIR_IN))
    {
        if (epType != DEBUGPRINT_EP_TYPE_INT)
        {
            DEBUGPRINT_cdcDataInEp[DEBUGPRINT_GET_EP_COM_NUM(cdcComNums, DEBUGPRINT_CDC_IN_EP)] = epNum;
            cdcComNums |= (uint8)(DEBUGPRINT_COM_PORT2 << DEBUGPRINT_CDC_IN_EP);
        }
        else
        {

            DEBUGPRINT_cdcCommInInterruptEp[DEBUGPRINT_GET_EP_COM_NUM(cdcComNums, DEBUGPRINT_CDC_NOTE_EP)] = epNum;
            cdcComNums |= (uint8)(DEBUGPRINT_COM_PORT2 << DEBUGPRINT_CDC_NOTE_EP);
        }
    }
    else
    {
        if (epType != DEBUGPRINT_EP_TYPE_INT)
        {
            DEBUGPRINT_cdcDataOutEp[DEBUGPRINT_GET_EP_COM_NUM(cdcComNums, DEBUGPRINT_CDC_OUT_EP)] = epNum;
            cdcComNums |= (uint8)(DEBUGPRINT_COM_PORT2 << DEBUGPRINT_CDC_OUT_EP);
        }
    }
    return (cdcComNums);
}


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (DEBUGPRINT_ENABLE_CDC_CLASS) */


/* [] END OF FILE */
