/**
  ******************************************************************************
  * @file    usbd_ioreq.c
  * @author  MCD Application Team
  * @brief   USB Device IO requests dirver
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"


#define DBG_TAG             "USBD IOReq"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @defgroup USBD_IOReq USBD IO Request
  * @brief    USBD IO Request
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup USBD_IOReq_Exported_Functions Endpoint 0 Send/Receive Data Functions
  * @brief    USBD IOReq Endpoint 0 Send/Receive Data Functions
  * @{
  */

/**
  * @brief  Endpoint 0 Send Data First/Continue/Last
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_Ep0SendData(void)
{
    //Check LL driver Valid
    if (!usb_core_ctrl.ll_drv || !usb_core_ctrl.ll_drv->EpFIFOWrite) {
        return USBD_INVALID;
    }

    if (usb_core_ctrl.send_len > USB_EP0_MAX_PL) {  //Send Data Length is greater than EP0 Max Payload
        usb_core_ctrl.ll_drv->EpFIFOWrite(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.send_ptr, USB_EP0_MAX_PL);
        usb_core_ctrl.send_len -= USB_EP0_MAX_PL;
        usb_core_ctrl.send_ptr += USB_EP0_MAX_PL;
    } else {                                        //Send Data Length is less than EP0 Max Payload
        if (usb_core_ctrl.send_len) {
            usb_core_ctrl.ll_drv->EpFIFOWrite(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.send_ptr, usb_core_ctrl.send_len);
            USBD_FUNC_ALTER(usb_core_ctrl.ll_drv->SetupDataEndSet, usb_core_ctrl.ll_drv->SetupDataEndSet(usb_core_ctrl.Instance), (void)0U);
            usb_core_ctrl.send_len = 0;
            usb_core_ctrl.send_ptr = NULL;
        } else {                                    //Send Data Length is 0
            if (usb_core_ctrl.need_zero_pkt) {      //Need to Send 0 Data Packet
                usb_core_ctrl.ll_drv->EpFIFOWrite(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.send_ptr, 0);
                usb_core_ctrl.need_zero_pkt = false;
            }

            usb_core_ctrl.send_ptr = NULL;
        }
    }

    return USBD_OK;
}

/**
  * @brief  Endpoint 0 Receive Data First/Continue/Last
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_Ep0ReceiveData(void)
{
    //Check LL driver Valid
    if (!usb_core_ctrl.ll_drv || !usb_core_ctrl.ll_drv->EpFIFORead) {
        return USBD_INVALID;
    }

    if (usb_core_ctrl.recv_len > USB_EP0_MAX_PL) {
        usb_core_ctrl.ll_drv->EpFIFORead(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.recv_buf, USB_EP0_MAX_PL);
        usb_core_ctrl.recv_len -= USB_EP0_MAX_PL;
    } else {
        if (usb_core_ctrl.recv_len) {
            usb_core_ctrl.ll_drv->EpFIFORead(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.recv_buf, usb_core_ctrl.recv_len);
            USBD_FUNC_ALTER(usb_core_ctrl.ll_drv->SetupDataEndSet, usb_core_ctrl.ll_drv->SetupDataEndSet(usb_core_ctrl.Instance), (void)0U);
            usb_core_ctrl.recv_len = 0;
        } else {
            usb_core_ctrl.ll_drv->EpFIFORead(usb_core_ctrl.Instance, EP_NUM_0, usb_core_ctrl.recv_buf, 0);
        }
    }

    //:TODO: Process Receive Data

    return USBD_OK;
}

/**
  * @brief  Endpoint 0 Send Zero Packet
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_Ep0SendZeroPkt(void)
{
    usb_core_ctrl.send_ptr = NULL;
    usb_core_ctrl.send_len = 0;
    usb_core_ctrl.need_zero_pkt = true;

    return USBD_Ep0SendData();
}

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

