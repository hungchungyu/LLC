/**
  ******************************************************************************
  * @file    usbd_ctlreq.h
  * @author  MCD Application Team
  * @brief   Header file for USB Device standard device requests driver
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
#ifndef _USBD_CTLREQ_H_
#define _USBD_CTLREQ_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @addtogroup USBD_CtlReq
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup USBD_CtlReq_Exported_Functions
  * @{
  */
USBD_StatusETypeDef USBD_SetupReqParse(USB_StdDevReqTypeDef *req, uint8_t *pdata);
USBD_StatusETypeDef USBD_StdDevReqProcess(void);
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

#endif /* _USBD_CTLREQ_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

