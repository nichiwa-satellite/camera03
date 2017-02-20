/***************************************************************************//**
* \file DEBUGPRINT_audio.h
* \version 3.10
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  Audio class.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_DEBUGPRINT_audio_H)
#define CY_USBFS_DEBUGPRINT_audio_H

#include "DEBUGPRINT.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for DEBUGPRINT_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define DEBUGPRINT_REQUEST_CODE_UNDEFINED     (0x00u)
#define DEBUGPRINT_SET_CUR                    (0x01u)
#define DEBUGPRINT_GET_CUR                    (0x81u)
#define DEBUGPRINT_SET_MIN                    (0x02u)
#define DEBUGPRINT_GET_MIN                    (0x82u)
#define DEBUGPRINT_SET_MAX                    (0x03u)
#define DEBUGPRINT_GET_MAX                    (0x83u)
#define DEBUGPRINT_SET_RES                    (0x04u)
#define DEBUGPRINT_GET_RES                    (0x84u)
#define DEBUGPRINT_SET_MEM                    (0x05u)
#define DEBUGPRINT_GET_MEM                    (0x85u)
#define DEBUGPRINT_GET_STAT                   (0xFFu)

/* point Control Selectors (AUDIO Table A-19) */
#define DEBUGPRINT_EP_CONTROL_UNDEFINED       (0x00u)
#define DEBUGPRINT_SAMPLING_FREQ_CONTROL      (0x01u)
#define DEBUGPRINT_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define DEBUGPRINT_FU_CONTROL_UNDEFINED       (0x00u)
#define DEBUGPRINT_MUTE_CONTROL               (0x01u)
#define DEBUGPRINT_VOLUME_CONTROL             (0x02u)
#define DEBUGPRINT_BASS_CONTROL               (0x03u)
#define DEBUGPRINT_MID_CONTROL                (0x04u)
#define DEBUGPRINT_TREBLE_CONTROL             (0x05u)
#define DEBUGPRINT_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define DEBUGPRINT_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define DEBUGPRINT_DELAY_CONTROL              (0x08u)
#define DEBUGPRINT_BASS_BOOST_CONTROL         (0x09u)
#define DEBUGPRINT_LOUDNESS_CONTROL           (0x0Au)

#define DEBUGPRINT_SAMPLE_FREQ_LEN            (3u)
#define DEBUGPRINT_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define DEBUGPRINT_VOL_MIN_MSB            (0x80u)
    #define DEBUGPRINT_VOL_MIN_LSB            (0x01u)
    #define DEBUGPRINT_VOL_MAX_MSB            (0x7Fu)
    #define DEBUGPRINT_VOL_MAX_LSB            (0xFFu)
    #define DEBUGPRINT_VOL_RES_MSB            (0x00u)
    #define DEBUGPRINT_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/
/**
* \addtogroup group_audio
* @{
*/
extern volatile uint8 DEBUGPRINT_currentSampleFrequency[DEBUGPRINT_MAX_EP][DEBUGPRINT_SAMPLE_FREQ_LEN];
extern volatile uint8 DEBUGPRINT_frequencyChanged;
extern volatile uint8 DEBUGPRINT_currentMute;
extern volatile uint8 DEBUGPRINT_currentVolume[DEBUGPRINT_VOLUME_LEN];
/** @} audio */

extern volatile uint8 DEBUGPRINT_minimumVolume[DEBUGPRINT_VOLUME_LEN];
extern volatile uint8 DEBUGPRINT_maximumVolume[DEBUGPRINT_VOLUME_LEN];
extern volatile uint8 DEBUGPRINT_resolutionVolume[DEBUGPRINT_VOLUME_LEN];

#endif /*  CY_USBFS_DEBUGPRINT_audio_H */


/* [] END OF FILE */
