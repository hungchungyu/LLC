/**
  ******************************************************************************
  * @file    usbd_ioreq.h
  * @author  MCD Application Team
  * @brief   Header file for USB Device IO requests dirver
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
#ifndef _USBD_IOREQ_H_
#define _USBD_IOREQ_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @addtogroup USBD_IOReq
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup USBD_IOReq_Exported_Functions USBD IOReq Exported Functions
  * @brief    USBD IOReq Exported Functions
  * @{
  */
USBD_StatusETypeDef USBD_Ep0SendData(void);
USBD_StatusETypeDef USBD_Ep0ReceiveData(void);
USBD_StatusETypeDef USBD_Ep0SendZeroPkt(void);
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

#endif /* _USBD_IOREQ_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

