/**
  ******************************************************************************
  * @file    usbd_ctlreq.c
  * @author  MCD Application Team
  * @brief   USB Device standard device requests driver
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
#include "usbd_ctlreq.h"


#define DBG_TAG             "USBD CtrlReq"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @defgroup USBD_CtlReq  USBD Control Request
  * @brief    USBD Control Request
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup USBD_CtlReq_Private_Functions USBD CtlReq Private Functions
  * @brief    USBD Control Request Private Functions
  * @{
  */
//USBD Standard Device Request IN/OUT Process Functions
static USBD_StatusETypeDef USBD_StdDevReqIn(void);
static USBD_StatusETypeDef USBD_StdDevReqOut(void);

//Misc Functions
static USBD_StatusETypeDef USBD_SeekDescToSend(USB_DescTypeETypeDef desc_type);
static USBD_StatusETypeDef USBD_SeekStrDescToSend(uint8_t str_idx);

//USBD Standard Device Request IN Functions
static USBD_StatusETypeDef USBD_GetStatus(void);
static USBD_StatusETypeDef USBD_GetDescriptor(void);
static USBD_StatusETypeDef USBD_GetConfiguration(void);
static USBD_StatusETypeDef USBD_GetInterface(void);
static USBD_StatusETypeDef USBD_SynchFrame(void);

//USBD Standard Device Request OUT Functions
static USBD_StatusETypeDef USBD_ClearFeature(void);
static USBD_StatusETypeDef USBD_SetFeature(void);
static USBD_StatusETypeDef USBD_SetAddress(void);
static USBD_StatusETypeDef USBD_SetDescriptor(void);
static USBD_StatusETypeDef USBD_SetConfiguration(void);
static USBD_StatusETypeDef USBD_SetInterface(void);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup USBD_CtlReq_Exported_Functions USBD CtlReq Exported Functions
  * @brief    USBD Control Request Exported Functions
  * @{
  */

/**
  * @brief  USBD Setup Request Parse
  * @param  req USB_StdDevReqTypeDef Type Pointer
  * @param  pdata Request Data
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_SetupReqParse(USB_StdDevReqTypeDef *req, uint8_t *pdata)
{
    //Assert param
    USBD_ASSERT_PARAM(req != NULL);
    USBD_ASSERT_PARAM(pdata != NULL);

    if (req == NULL || pdata == NULL) {
        return USBD_INVALID;
    }

    //Parse Setup Request
    req->bmRequestType = pdata[0];
    req->bRequest = pdata[1];
    req->wValue  = pdata[2] | ((uint16_t)pdata[3] << 8);
    req->wIndex  = pdata[4] | ((uint16_t)pdata[5] << 8);
    req->wLength = pdata[6] | ((uint16_t)pdata[7] << 8);

    return USBD_OK;
}

/**
  * @brief  USBD Standard Device Request Process
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_StdDevReqProcess(void)
{
    uint8_t req_dir;
    USBD_StatusETypeDef ret = USBD_FAILED;

    req_dir  = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_DIR_BITMASK)  >> USB_STD_DEV_REQ_DIR_BIT;

    if (req_dir == USB_STD_DEV_REQ_DIR_IN) {    //USB Standard Device Request <IN>
        ret = USBD_StdDevReqIn();
    } else {                                    //USB Standard Device Request <OUT>
        ret = USBD_StdDevReqOut();
    }

    return ret;
}

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup USBD_CtlReq_Private_Functions
  * @{
  */

/**
  * @brief  USBD Standard Device Request In Process
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_StdDevReqIn(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    switch (usb_core_ctrl.req.bRequest) {
        case GET_STATUS:                    //<Get Status>
            LOG_D("GET_STATUS.\n");
            ret = USBD_GetStatus();
            break;

        case GET_DESCRIPTOR:                //<Get Descriptor>
            LOG_D("GET_DESCRIPTOR.\n");
            ret = USBD_GetDescriptor();
            break;

        case GET_CONFIGURATION:             //<Get Configulation>
            LOG_D("GET_CONFIGURATION.\n");
            ret = USBD_GetConfiguration();
            break;

        case GET_INTERFACE:                 //<Get Interface>
            LOG_D("GET_INTERFACE.\n");
            ret = USBD_GetInterface();
            break;

        case SYNCH_FRAME:                   //<Synch Frame>
            LOG_D("SYNCH_FRAME.\n");
            ret = USBD_SynchFrame();
            break;

        default:
            LOG_E("Invalid Request Type (%d)!\n", usb_core_ctrl.req.bRequest);
            ret = USBD_FAILED;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Standard Device Request Out Process
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_StdDevReqOut(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    switch (usb_core_ctrl.req.bRequest) {
        case CLEAR_FEATURE:                 //<Clear Feature>
            LOG_D("CLEAR_FEATURE.\n");
            ret = USBD_ClearFeature();
            break;

        case SET_FEATURE:                   //<Set Feature>
            LOG_D("SET_FEATURE.\n");
            ret = USBD_SetFeature();
            break;

        case SET_ADDRESS:                   //<Set Address>
            LOG_D("SET_ADDRESS.\n");
            ret = USBD_SetAddress();
            break;

        case SET_DESCRIPTOR:                //<Set Descriptor>
            LOG_D("SET_DESCRIPTOR.\n");
            ret = USBD_SetDescriptor();
            break;

        case SET_CONFIGURATION:             //<Set Configulation>
            LOG_D("SET_CONFIGURATION.\n");
            ret = USBD_SetConfiguration();
            break;

        case SET_INTERFACE:                 //<Set Interface>
            LOG_D("SET_INTERFACE.\n");
            ret = USBD_SetInterface();
            break;

        default:
            LOG_E("Invalid Request Type (%d)!\n", usb_core_ctrl.req.bRequest);
            usb_core_ctrl.recv_len = 0;
            ret = USBD_FAILED;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Seek Description to Send
  * @param  desc_type Description Type to Seek
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SeekDescToSend(USB_DescTypeETypeDef desc_type)
{
    uint8_t i;
    USB_EnumDescTypeDef *desc_ptr;

    //Assert param
    USBD_ASSERT_PARAM(usb_core_ctrl.enum_desc != NULL);

    if (usb_core_ctrl.enum_desc == NULL) {
        return USBD_INVALID;
    }

    desc_ptr = usb_core_ctrl.enum_desc;

    //Find Descriptor to return
    for (i = 0; i < usb_core_ctrl.enum_desc_nums; i++, desc_ptr++) {
        if (desc_ptr->desc_type == desc_type) {
            usb_core_ctrl.send_ptr = desc_ptr->desc_ptr;
            break;
        }
    }

    //Don't find Descriptor to return
    if (i == usb_core_ctrl.enum_desc_nums || usb_core_ctrl.send_ptr == NULL) {
        LOG_E("Don't find Descriptor Type[%d] to return!\n", desc_type);
        return USBD_ERROR;
    }

    //Config send length and need to send 0 data packet or not
    if (usb_core_ctrl.req.wLength > desc_ptr->desc_len) {
        usb_core_ctrl.send_len = desc_ptr->desc_len;

        if (!(usb_core_ctrl.send_len % USB_EP0_MAX_PL)) {
            usb_core_ctrl.need_zero_pkt = true;
        }
    } else {
        usb_core_ctrl.send_len = usb_core_ctrl.req.wLength;
    }

    //Start send data, remain data will send in Endpoint 0 Interrupt
    USBD_Ep0SendData();

    return USBD_OK;
}

/**
  * @brief  USBD Seek String Description to Send
  * @param  str_idx String Index to Seek
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SeekStrDescToSend(uint8_t str_idx)
{
    uint8_t i;
    USB_EnumStrTypeDef *string_ptr;

    //Assert param
    USBD_ASSERT_PARAM(usb_core_ctrl.enum_str != NULL);

    if (usb_core_ctrl.enum_str == NULL) {
        return USBD_INVALID;
    }

    string_ptr = usb_core_ctrl.enum_str;

    //Find Index[0] String Descriptor to return
    for (i = 0; i < usb_core_ctrl.enum_str_nums; i++, string_ptr++) {
        if (string_ptr->str_idx == str_idx) {
            usb_core_ctrl.send_ptr = string_ptr->str_ptr;
            break;
        }
    }

    //Don't find String Descriptor to return, then return a 0 data packet
    if (i == usb_core_ctrl.enum_str_nums || usb_core_ctrl.send_ptr == NULL) {
        LOG_E("Don't find index[%d] String Descriptor to return!\n", str_idx);
        return USBD_ERROR;
    }

    //Config send length and need to send 0 data packet or not
    if (usb_core_ctrl.req.wLength > string_ptr->str_len) {
        usb_core_ctrl.send_len = string_ptr->str_len;

        if (!(usb_core_ctrl.send_len % USB_EP0_MAX_PL)) {
            usb_core_ctrl.need_zero_pkt = true;
        }
    } else {
        usb_core_ctrl.send_len = usb_core_ctrl.req.wLength;
    }

    //Start send data, remain data will send in Endpoint 0 Interrupt
    USBD_Ep0SendData();

    return USBD_OK;
}

/**
  * @brief  USBD Standard Device Request GetStatus
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_GetStatus(void)
{
    uint8_t req_rcvr;
    USBD_StatusETypeDef ret = USBD_FAILED;

    req_rcvr = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_RCVR_BITMASK) >> USB_STD_DEV_REQ_RCVR_BIT;

    switch (req_rcvr) {
        case USB_STD_DEV_REQ_RCVR_DEV:
            LOG_D("USB_STD_DEV_REQ_RCVR_DEV (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Return Device Status
            break;

        case USB_STD_DEV_REQ_RCVR_IFC:
            LOG_D("USB_STD_DEV_REQ_RCVR_IFC (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Return Interface Status
            break;

        case USB_STD_DEV_REQ_RCVR_EP:
            LOG_D("USB_STD_DEV_REQ_RCVR_EP (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Return Endpoint Status
            break;

        default:
            LOG_E("Invalid Request Receiver (%d)!\n", req_rcvr);
            ret = USBD_ERROR;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Standard Device Request Get Descriptor
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_GetDescriptor(void)
{
    uint8_t str_idx;
    USB_DescTypeETypeDef desc_type;
    USBD_StatusETypeDef ret = USBD_FAILED;

    //Assert param
    USBD_ASSERT_PARAM(usb_core_ctrl.enum_desc != NULL);

    if (usb_core_ctrl.enum_desc == NULL) {
        return USBD_INVALID;
    }

    desc_type = (USB_DescTypeETypeDef)((usb_core_ctrl.req.wValue >> 8) & 0xFF);

    switch (desc_type) {
        case DEVICE_DESCRIPTOR:                     //(Device Descriptor)
            LOG_D("DEVICE_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case CONFIGURATION_DESCRIPTOR:              //(Configulation Descriptor)
            LOG_D("CONFIGURATION_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case DEVICE_QUALIFIER_DESCRIPTOR:           //(Device Qualifier Descriptor)
            LOG_D("DEVICE_QUALIFIER_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case OTHER_SPEED_CONFIGURATION_DESCRIPTOR:  //(Other Speed Configulation Description)
            LOG_D("OTHER_SPEED_CONFIGURATION_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case INTERFACE_POWER_DESCRIPTOR:            //(Interface Power Description)
            LOG_D("INTERFACE_POWER_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case REPORT_DESCRIPTOR:                     //(Report Descriptor)
            LOG_D("REPORT_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case PHYSICAL_DESCRIPTOR:                   //(Physical Descriptor)
            LOG_D("PHYSICAL_DESCRIPTOR.\n");
            ret = USBD_SeekDescToSend(desc_type);
            break;

        case STRING_DESCRIPTOR:                     //(String Descriptor)
            LOG_D("STRING_DESCRIPTOR ");
            USBD_ASSERT_PARAM(usb_core_ctrl.enum_str != NULL);

            if (usb_core_ctrl.enum_str == NULL) {
                return USBD_INVALID;
            }

            str_idx = (uint8_t)(usb_core_ctrl.req.wValue & 0xFF);
            LOG_D("Index[%d].\n", str_idx);

            ret = USBD_SeekStrDescToSend(str_idx);

            if (ret != USBD_OK) {
                ret = USBD_OK;
                USBD_Ep0SendZeroPkt();
            }

            break;

        default:
            LOG_E("-> Invalid Descriptor Type (%d)!\n", desc_type);
            ret = USBD_ERROR;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Standard Device Request Get Configuration
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_GetConfiguration(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    //:TODO: Return Configuration

    return ret;
}

/**
  * @brief  USBD Standard Device Request Get Interface
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_GetInterface(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    //:TODO: Return Interface

    return ret;
}

/**
  * @brief  USBD Standard Device Request Synch Frame
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SynchFrame(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    //:TODO: Return Synch Frame

    return ret;
}

/**
  * @brief  USBD Standard Device Request Clear Feature
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_ClearFeature(void)
{
    uint8_t req_rcvr;
    USBD_StatusETypeDef ret = USBD_FAILED;

    req_rcvr = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_RCVR_BITMASK) >> USB_STD_DEV_REQ_RCVR_BIT;

    switch (req_rcvr) {
        case USB_STD_DEV_REQ_RCVR_DEV:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_DEV (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Clear Device Feature
            break;

        case USB_STD_DEV_REQ_RCVR_IFC:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_IFC (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Clear Interface Feature
            break;

        case USB_STD_DEV_REQ_RCVR_EP:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_EP (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Clear Endpoint Feature
            break;

        default:
            LOG_D("-> Invalid Request Receiver (%d)!\n", req_rcvr);
            usb_core_ctrl.recv_len = 0;
            ret = USBD_ERROR;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Standard Device Request Set Feature
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SetFeature(void)
{
    uint8_t req_rcvr;
    USBD_StatusETypeDef ret = USBD_FAILED;

    req_rcvr = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_RCVR_BITMASK) >> USB_STD_DEV_REQ_RCVR_BIT;

    switch (req_rcvr) {
        case USB_STD_DEV_REQ_RCVR_DEV:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_DEV (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Set Device Feature
            break;

        case USB_STD_DEV_REQ_RCVR_IFC:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_IFC (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Set Interface Feature
            break;

        case USB_STD_DEV_REQ_RCVR_EP:
            LOG_D("-> USB_STD_DEV_REQ_RCVR_EP (%d).\n", usb_core_ctrl.req.wIndex);
            //:TODO: Set Endpoint Feature
            break;

        default:
            LOG_D("-> Invalid Request Receiver (%d)!\n", req_rcvr);
            usb_core_ctrl.recv_len = 0;
            ret = USBD_ERROR;
            break;
    }

    return ret;
}

/**
  * @brief  USBD Standard Device Request Set Address
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SetAddress(void)
{
    usb_core_ctrl.dev_addr = usb_core_ctrl.req.wValue & 0xFF;
    USBD_Ep0SendZeroPkt();

    return USBD_OK;
}

/**
  * @brief  USBD Standard Device Request Set Descriptor
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SetDescriptor(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    //:TODO: Set Descriptor

    return ret;
}

/**
  * @brief  USBD Standard Device Request Set Configuration
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SetConfiguration(void)
{
    uint8_t i;
    USBD_StatusETypeDef ret = USBD_OK;
    USB_EpCfgTypeDef *ep_cfg_ptr = usb_core_ctrl.ep_cfg;

    for (i = 0; i < usb_core_ctrl.ep_cfg_nums; i++) {
        if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->EpCfg) {
            ret = (USBD_StatusETypeDef)usb_core_ctrl.ll_drv->EpCfg(usb_core_ctrl.Instance, ep_cfg_ptr++, true);
        }

        if (ret != USBD_OK) {
            return USBD_FAILED;
        }
    }

    usb_core_ctrl.cur_cfg_val = usb_core_ctrl.req.wValue & 0xFF;
    USBD_Ep0SendZeroPkt();

    return USBD_OK;
}

/**
  * @brief  USBD Standard Device Request Set Interface
  * @param  None
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_SetInterface(void)
{
    USBD_StatusETypeDef ret = USBD_FAILED;

    //:TODO: Set Interface

    return ret;
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

