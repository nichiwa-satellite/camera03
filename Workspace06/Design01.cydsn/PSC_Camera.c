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

#include "PSC_Camera.h"
#include "PSC_Types.h"

/* Typedef */
typedef struct tgPSC_CAMERABUFFER_INDEX
{
    int Layer1;
    int Layer2;
} PSC_CAMERABUFFER_INDEX;


/* Prototype */
PSC_RET PSC_Camera_Buffer_Reset();
PSC_RET PSC_Camera_Buffer_WriteChar( PSC_CHAR WriteData, long int WriteIndex );
PSC_RET PSC_Camera_Buffer_ReadChar( PSC_CHAR* pReadData, long int ReadIndex );
PSC_RET psc_Camera_Buffer_IndexConvertion( const long int Input, PSC_CAMERABUFFER_INDEX* pOutput );


/* Static Variable */
PSC_CHAR Buffer[PHOTO_BUFFER_SCALE_LAYER2][PHOTO_BUFFER_SCALE_LAYER1];



PSC_RET PSC_Camera_Buffer_Reset()
{
    memset(Buffer, 0x00, sizeof( Buffer ) );
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_Camera_Buffer_WriteChar( PSC_CHAR WriteData, long int WriteIndex )
{
    PSC_RET ret;
    PSC_CAMERABUFFER_INDEX index;
    ret = psc_Camera_Buffer_IndexConvertion( WriteIndex, &index );
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    Buffer[index.Layer2][index.Layer1] = WriteData;
    
    return PSC_RET_SUCCESS;
}

PSC_RET PSC_Camera_Buffer_ReadChar( PSC_CHAR* pReadData, long int ReadIndex )
{
    PSC_RET ret;
    PSC_CAMERABUFFER_INDEX index;
    ret = psc_Camera_Buffer_IndexConvertion( ReadIndex, &index );
    if( ret != PSC_RET_SUCCESS )
    {
        return ret;
    }
    
    *pReadData = Buffer[index.Layer2][index.Layer1];
    
    return PSC_RET_SUCCESS;
}


PSC_RET psc_Camera_Buffer_IndexConvertion( const long int Input, PSC_CAMERABUFFER_INDEX* pOutput )
{
    pOutput->Layer2 = Input / PHOTO_BUFFER_SCALE_LAYER1;
    pOutput->Layer1 = Input % PHOTO_BUFFER_SCALE_LAYER1;
    
    if ( pOutput->Layer2 >= PHOTO_BUFFER_SCALE_LAYER2 )
    {
        return PSC_RET_INTERNAL_ERROR;
    }
    
    return PSC_RET_SUCCESS;
}