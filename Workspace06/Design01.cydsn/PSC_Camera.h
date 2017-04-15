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


#ifndef _camera
#define _camera

#include "PSC_Types.h"
#include "project.h"

// Get Photo Packet Size
#define CAMERA_PHOTO_PACKETSIZE_ID      (    2 )
#define CAMERA_PHOTO_PACKETSIZE_DATA    ( 1282 )
#define CAMERA_PHOTO_PACKETSIZE         ( CAMERA_PHOTO_PACKETSIZE_ID + CAMERA_PHOTO_PACKETSIZE_DATA )

// Photo Size
#define PHOTO_COLOR_LAYER               (    3 )
#define PHOTO_WIDTH                     (  640 )
#define PHOTO_HIGHT                     (  480 )
#define PHOTO_DATASIZE                  ( PHOTO_WIDTH * PHOTO_HIGHT * PHOTO_COLOR_LAYER )

// Photo Buffer Scale
#define PHOTO_BUFFER_SCALE_LAYER1       ( CAMERA_PHOTO_PACKETSIZE )
#define PHOTO_BUFFER_SCALE_LAYER2       ( PHOTO_DATASIZE / CAMERA_PHOTO_PACKETSIZE + 1 )
    
extern PSC_CHAR CameraRecvBuffer[PHOTO_BUFFER_SCALE_LAYER2][PHOTO_BUFFER_SCALE_LAYER1];

static unsigned char get[]             ={0x56, 0x00, 0x11, 0x00};
static uint8         get_size          = 4;
static unsigned char reset_camera[]    =  { 0x56, 0x00, 0x26, 0x00 };
static uint8         reset_camera_size = 4;
static unsigned char baurate[]         =  { 0x56, 0x00, 0x24, 0x16, 0x01, 0x2A, 0xF2 };
static uint8         baurate_size      = 7;
static unsigned char config_datasize[] =  { 0x56, 0x00, 0x31, 0x05, 0x04, 0x01, 0x00, 0x19, 0x00 };    //640×480
static uint8         config_datasize_size = 9;
static unsigned char take_picture[]    =  { 0x56, 0x00, 0x36, 0x01, 0x00 };
static uint8         tack_picture_size = 5;
static unsigned char read_datasize[]   =  { 0x56, 0x00, 0x34, 0x01, 0x00 };
static uint8         read_datasize_size = 5;
static unsigned char load_data[]       =  { 0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCA, 0x6C, 0x00, 0xFF };
static uint8         load_data_size    = 16;
#endif