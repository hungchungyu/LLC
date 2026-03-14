/**
  ******************************************************************************
  * @file    usbd_core.h
  * @author  MCD Application Team
  * @brief   Header file for USB Device Core driver
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USBD_CORE_H_
#define _USBD_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"
#include "usbd_ioreq.h"
#include "usbd_ctlreq.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @addtogroup USBD_Core
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/** @addtogroup USBD_Core_Exported_Variables
  * @{
  */
extern USBD_CoreCtrlTypeDef usb_core_ctrl;
extern const USB_LL_IRQCbTypeDef usbd_core_irq_cb;
/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @addtogroup USBD_Core_Exported_Functions
  * @{
  */

/** @addtogroup USBD_Core_Exported_Functions_Group1
  * @{
  */
USBD_StatusETypeDef USBD_Init(USBD_CoreInitTypeDef *core_init);
USBD_StatusETypeDef USBD_DeInit(void);
/**
  * @}
  */


/** @addtogroup USBD_Core_Exported_Functions_Group2
  * @{
  */
USBD_StatusETypeDef USBD_AllEpDis(void);
bool USBD_IsEnumFinish(void);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USBD_CORE_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

