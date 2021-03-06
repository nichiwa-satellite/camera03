/*******************************************************************************
* File Name: DEBUGPRINT_Dp.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DEBUGPRINT_Dp_H) /* Pins DEBUGPRINT_Dp_H */
#define CY_PINS_DEBUGPRINT_Dp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DEBUGPRINT_Dp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DEBUGPRINT_Dp__PORT == 15 && ((DEBUGPRINT_Dp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DEBUGPRINT_Dp_Write(uint8 value);
void    DEBUGPRINT_Dp_SetDriveMode(uint8 mode);
uint8   DEBUGPRINT_Dp_ReadDataReg(void);
uint8   DEBUGPRINT_Dp_Read(void);
void    DEBUGPRINT_Dp_SetInterruptMode(uint16 position, uint16 mode);
uint8   DEBUGPRINT_Dp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DEBUGPRINT_Dp_SetDriveMode() function.
     *  @{
     */
        #define DEBUGPRINT_Dp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DEBUGPRINT_Dp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DEBUGPRINT_Dp_DM_RES_UP          PIN_DM_RES_UP
        #define DEBUGPRINT_Dp_DM_RES_DWN         PIN_DM_RES_DWN
        #define DEBUGPRINT_Dp_DM_OD_LO           PIN_DM_OD_LO
        #define DEBUGPRINT_Dp_DM_OD_HI           PIN_DM_OD_HI
        #define DEBUGPRINT_Dp_DM_STRONG          PIN_DM_STRONG
        #define DEBUGPRINT_Dp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DEBUGPRINT_Dp_MASK               DEBUGPRINT_Dp__MASK
#define DEBUGPRINT_Dp_SHIFT              DEBUGPRINT_Dp__SHIFT
#define DEBUGPRINT_Dp_WIDTH              1u

/* Interrupt constants */
#if defined(DEBUGPRINT_Dp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DEBUGPRINT_Dp_SetInterruptMode() function.
     *  @{
     */
        #define DEBUGPRINT_Dp_INTR_NONE      (uint16)(0x0000u)
        #define DEBUGPRINT_Dp_INTR_RISING    (uint16)(0x0001u)
        #define DEBUGPRINT_Dp_INTR_FALLING   (uint16)(0x0002u)
        #define DEBUGPRINT_Dp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DEBUGPRINT_Dp_INTR_MASK      (0x01u) 
#endif /* (DEBUGPRINT_Dp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DEBUGPRINT_Dp_PS                     (* (reg8 *) DEBUGPRINT_Dp__PS)
/* Data Register */
#define DEBUGPRINT_Dp_DR                     (* (reg8 *) DEBUGPRINT_Dp__DR)
/* Port Number */
#define DEBUGPRINT_Dp_PRT_NUM                (* (reg8 *) DEBUGPRINT_Dp__PRT) 
/* Connect to Analog Globals */                                                  
#define DEBUGPRINT_Dp_AG                     (* (reg8 *) DEBUGPRINT_Dp__AG)                       
/* Analog MUX bux enable */
#define DEBUGPRINT_Dp_AMUX                   (* (reg8 *) DEBUGPRINT_Dp__AMUX) 
/* Bidirectional Enable */                                                        
#define DEBUGPRINT_Dp_BIE                    (* (reg8 *) DEBUGPRINT_Dp__BIE)
/* Bit-mask for Aliased Register Access */
#define DEBUGPRINT_Dp_BIT_MASK               (* (reg8 *) DEBUGPRINT_Dp__BIT_MASK)
/* Bypass Enable */
#define DEBUGPRINT_Dp_BYP                    (* (reg8 *) DEBUGPRINT_Dp__BYP)
/* Port wide control signals */                                                   
#define DEBUGPRINT_Dp_CTL                    (* (reg8 *) DEBUGPRINT_Dp__CTL)
/* Drive Modes */
#define DEBUGPRINT_Dp_DM0                    (* (reg8 *) DEBUGPRINT_Dp__DM0) 
#define DEBUGPRINT_Dp_DM1                    (* (reg8 *) DEBUGPRINT_Dp__DM1)
#define DEBUGPRINT_Dp_DM2                    (* (reg8 *) DEBUGPRINT_Dp__DM2) 
/* Input Buffer Disable Override */
#define DEBUGPRINT_Dp_INP_DIS                (* (reg8 *) DEBUGPRINT_Dp__INP_DIS)
/* LCD Common or Segment Drive */
#define DEBUGPRINT_Dp_LCD_COM_SEG            (* (reg8 *) DEBUGPRINT_Dp__LCD_COM_SEG)
/* Enable Segment LCD */
#define DEBUGPRINT_Dp_LCD_EN                 (* (reg8 *) DEBUGPRINT_Dp__LCD_EN)
/* Slew Rate Control */
#define DEBUGPRINT_Dp_SLW                    (* (reg8 *) DEBUGPRINT_Dp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DEBUGPRINT_Dp_PRTDSI__CAPS_SEL       (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DEBUGPRINT_Dp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DEBUGPRINT_Dp_PRTDSI__OE_SEL0        (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__OE_SEL0) 
#define DEBUGPRINT_Dp_PRTDSI__OE_SEL1        (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DEBUGPRINT_Dp_PRTDSI__OUT_SEL0       (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__OUT_SEL0) 
#define DEBUGPRINT_Dp_PRTDSI__OUT_SEL1       (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DEBUGPRINT_Dp_PRTDSI__SYNC_OUT       (* (reg8 *) DEBUGPRINT_Dp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DEBUGPRINT_Dp__SIO_CFG)
    #define DEBUGPRINT_Dp_SIO_HYST_EN        (* (reg8 *) DEBUGPRINT_Dp__SIO_HYST_EN)
    #define DEBUGPRINT_Dp_SIO_REG_HIFREQ     (* (reg8 *) DEBUGPRINT_Dp__SIO_REG_HIFREQ)
    #define DEBUGPRINT_Dp_SIO_CFG            (* (reg8 *) DEBUGPRINT_Dp__SIO_CFG)
    #define DEBUGPRINT_Dp_SIO_DIFF           (* (reg8 *) DEBUGPRINT_Dp__SIO_DIFF)
#endif /* (DEBUGPRINT_Dp__SIO_CFG) */

/* Interrupt Registers */
#if defined(DEBUGPRINT_Dp__INTSTAT)
    #define DEBUGPRINT_Dp_INTSTAT            (* (reg8 *) DEBUGPRINT_Dp__INTSTAT)
    #define DEBUGPRINT_Dp_SNAP               (* (reg8 *) DEBUGPRINT_Dp__SNAP)
    
	#define DEBUGPRINT_Dp_0_INTTYPE_REG 		(* (reg8 *) DEBUGPRINT_Dp__0__INTTYPE)
#endif /* (DEBUGPRINT_Dp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DEBUGPRINT_Dp_H */


/* [] END OF FILE */
