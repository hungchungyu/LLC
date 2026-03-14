/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @brief   USB Device HID class driver
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
#include "usbd_hid.h"


#define DBG_TAG             "USBD HID"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @defgroup USBD_HID USBD HID Class Driver
  * @brief    USBD HID Class Driver
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/** @defgroup USBD_HID_Private_Variables USBD HID Private Variables
  * @brief    USBD HID Private Variables
  * @{
  */

/**
  * @brief USBD HID Control Variable definition
  */
static USBD_HID_CtrlTypeDef usbd_hid_ctrl;

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup USBD_HID_Private_Functions USBD HID Private Functions
  * @brief    USBD HID Private Functions
  * @{
  */
static USBD_StatusETypeDef USBD_HID_Setup(USB_StdDevReqTypeDef *req);
static USBD_StatusETypeDef USBD_HID_DataIn(USB_EpNumETypeDef ep_num);
static USBD_StatusETypeDef USBD_HID_DataOut(USB_EpNumETypeDef ep_num);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @defgroup USBD_HID_Exported_Variables USBD HID Exported Variables
  * @brief    USBD HID Exported Variables
  * @{
  */

/**
  * @brief HID Configulation Descriptor
  */
const USB_HID_CfgDescSetTypeDef hid_cfg_desc_set = {
    /* Configuration Descriptor */
    .cfg_desc = {
        .bLength = USB_CFG_DESC_LEN,                    /*!< Size of this descriptor in bytes                                   */
        .bDescriptorType = CONFIGURATION_DESCRIPTOR,    /*!< CONFIGURATION Descriptor Type                                      */
        .wTotalLength = {                               /*!< Total length of data returned for this configuration               */
            USBD_U16_LOWBYTE(HID_CFG_DESC_SET_LEN),
            USBD_U16_HIGHBYTE(HID_CFG_DESC_SET_LEN),
        },
        .bNumInterfaces = 0x01,                         /*!< Number of interfaces supported by this configuration               */
        .bConfigurationValue = 0x01,                    /*!< Value to select this configuration                                 */
        .iConfiguration = HID_CFG_STR_IDX,              /*!< Index of string descriptor describing this configuration           */
        .bmAttributes =                                 /*!< Configuration characteristics:<SeftPower>                          */
        USB_CFG_DESC_ATTR_BIT7_RESERVED_1 |
        USB_CFG_DESC_ATTR_BIT6_SEFT_POWERED |
        USB_CFG_DESC_ATTR_BIT4_0_RESERVED_0,
        .bMaxPower = 0x32,                              /*!< Maximum power consumption of the USB device from the bus: <100mA>  */
    },

    /* Interface Descriptor */
    .ifc_desc = {
        .bLength = USB_IFC_DESC_LEN,                    /*!< Size of this descriptor in bytes                                   */
        .bDescriptorType = INTERFACE_DESCRIPTOR,        /*!< INTERFACE Descriptor Type                                          */
        .bInterfaceNumber = 0x00,                       /*!< Number of this interface <Zero-based>                              */
        .bAlternateSetting = 0x00,                      /*!< Alternate Number of this interface                                 */
        .bNumEndpoints = HID_EP_NUMS,                   /*!< Number of endpoints used by this interface(excluding endpoint 0)   */
        .bInterfaceClass = USB_IFC_CLS_HID,             /*!< Interface Class Code: <HID>                                        */
        .bInterfaceSubClass = HID_IFC_SUB_CLS_BOOT_IFC, /*!< Interface Subclass Code: <Boot>                                    */
        .bInterfaceProtocol = HID_IFC_PROT_KEYBOARD,    /*!< Interface Protocol Code: <KeyBoard>                                */
        .iInterface = HID_IFC_STR_IDX,                  /*!< Index of string descriptor describing this interface               */
    },

    /* HID Descriptor */
    .hid_desc = {
        .bLength = HID_DESC_LEN,                        /*!< Numeric expression that is the total size of the HID descriptor    */
        .bDescriptorType = HID_DESCRIPTOR,              /*!< Constant name specifying type of HID descriptor                    */
        .bcdHID = {                                     /*!< Numeric expression identifying the HIDClass Specification release  */
            USBD_U16_LOWBYTE(HID_PTOT_VER),
            USBD_U16_HIGHBYTE(HID_PTOT_VER),
        },
        .bCountryCode = HID_CY_US,                      /*!< Numeric expression identifying country code of the localized HW    */
        .bNumDescriptors = HID_SUB_DESC_NUMS,           /*!< Numeric expression specifying the number of class descriptors      */
        .sub_desc = {
            {
                .bDescriptorType = REPORT_DESCRIPTOR,   /*!< Constant name identifying type of class descriptor                 */
                .wDescriptorLength = {                  /*!< Numeric expression that is the total size of the Report descriptor */
                    USBD_U16_LOWBYTE(HID_REPROT_DESC_LEN),
                    USBD_U16_HIGHBYTE(HID_REPROT_DESC_LEN),
                },
            },
        },
    },

    /* Endpoint Descriptor */
    .ep_desc = {
        //ep_desc[0]: Endpoint IN
        {
            .bLength = USB_EP_DESC_LEN,                 /*!< Size of this descriptor in bytes                                   */
            .bDescriptorType = ENDPOINT_DESCRIPTOR,     /*!< ENDPOINT Descriptor Type                                           */

            .bEndpointAddress = USB_EP_ADDR_CFG_DIR_IN  /*!< Address of the EP on the USB device described by this descriptor   */
            | USB_EP_ADDR_CFG_NUM_CFG(HID_EP_IN_NUM),
            .bmAttributes =                             /*!< This field describes the endpoint's attributes                    */
            USB_EP_DESC_ATT_XFER_TYPE_INT,
            .wMaxPacketSize = {                         /*!< Maximum packet size endpoint is capable of sending or receiving    */
                USBD_U16_LOWBYTE(HID_EP_IN_MAX_PL),
                USBD_U16_HIGHBYTE(HID_EP_IN_MAX_PL),
            },
            .bInterval = HID_EP_INTERVAL,               /*!< Interval for polling EP for data transfers(FRMs or MicroFRMs)      */
        },

        //ep_desc[1]: Endpoint OUT
        {
            .bLength = USB_EP_DESC_LEN,                 /*!< Size of this descriptor in bytes                                   */
            .bDescriptorType = ENDPOINT_DESCRIPTOR,     /*!< ENDPOINT Descriptor Type                                           */
            .bEndpointAddress = USB_EP_ADDR_CFG_DIR_OUT /*!< Address of the EP on the USB device described by this descriptor   */
            | USB_EP_ADDR_CFG_NUM_CFG(HID_EP_OUT_NUM),
            .bmAttributes =                             /*!< This field describes the endpoint's attributes                    */
            USB_EP_DESC_ATT_XFER_TYPE_INT,
            .wMaxPacketSize = {                         /*!< Maximum packet size endpoint is capable of sending or receiving    */
                USBD_U16_LOWBYTE(HID_EP_OUT_MAX_PL),
                USBD_U16_HIGHBYTE(HID_EP_OUT_MAX_PL),
            },
            .bInterval = HID_EP_INTERVAL,               /*!< Interval for polling EP for data transfers(FRMs or MicroFRMs)      */
        },
    },
};

/**
 * @brief USB HID Class Function
 */
const USB_ClassFuncTypeDef hid_class_func = {
    .Setup    = USBD_HID_Setup,     /*!< USBD HID Class Setup   */
    .DataIn   = USBD_HID_DataIn,    /*!< USBD HID Data IN       */
    .DataOut  = USBD_HID_DataOut,   /*!< USBD HID Data OUT      */
};

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup USBD_HID_Exported_Functions USBD HID Exported Functions
  * @brief    USBD HID Exported Functions
  * @{
  */

/**
  * @brief  USB HID Init
  * @param  dataout_callback User HID dataout Callback Pointer
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_HID_Init(void (*dataout_callback)(USB_TypeDef *Instance))
{
    usbd_hid_ctrl.datain_busy_flag = false;
    usbd_hid_ctrl.dataout_callback = dataout_callback;

    return USBD_OK;
}

/**
  * @brief  USB HID DeInit
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_HID_DeInit(void)
{
    usbd_hid_ctrl.datain_busy_flag = false;
    usbd_hid_ctrl.dataout_callback = NULL;

    return USBD_OK;
}

/**
  * @brief  USB HID Data Send
  * @param  buf Send data buffer pointer
  * @param  len Send data length
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_HID_DataSend(uint8_t *buf, uint32_t len)
{
    //Assert param
    USBD_ASSERT_PARAM(buf != NULL);

    if (buf == NULL) {
        return USBD_INVALID;
    }

    //Check data in busy flag
    if (usbd_hid_ctrl.datain_busy_flag) {
        return USBD_BUSY;
    }

    //Check LL driver Valid
    if (!usb_core_ctrl.ll_drv || !usb_core_ctrl.ll_drv->EpFIFOWrite) {
        return USBD_FAILED;
    }

    //Send data
    usb_core_ctrl.ll_drv->EpFIFOWrite(usb_core_ctrl.Instance, HID_EP_IN_NUM, buf, len);
    usbd_hid_ctrl.datain_busy_flag = true;

    return USBD_OK;
}

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup USBD_HID_Private_Functions
  * @{
  */

/**
  * @brief  USBD HID Class Request Process
  * @param  req USB_StdDevReqTypeDef Request Poinetr
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_HID_Setup(USB_StdDevReqTypeDef *req)
{
    uint8_t req_dir;
    USBD_StatusETypeDef ret = USBD_FAILED;

    //Assert param
    USBD_ASSERT_PARAM(req != NULL);

    if (req == NULL) {
        return USBD_INVALID;
    }

    req_dir = (req->bmRequestType & USB_STD_DEV_REQ_DIR_BITMASK)  >> USB_STD_DEV_REQ_DIR_BIT;

    if (req_dir == USB_STD_DEV_REQ_DIR_IN) {
        switch (req->bRequest) {
            case HID_GET_REPORT:
                LOG_D("HID_GET_REPORT\n");
                break;

            case HID_GET_IDLE:
                LOG_D("HID_GET_IDLE\n");
                break;

            case HID_GET_PROTOCOL:
                LOG_D("HID_GET_PROTOCOL");
                break;

            default:
                LOG_E("Unknow USB HID Class IN request[%d]!\n", req->bRequest);
                ret = USBD_ERROR;
                break;
        }
    } else {
        switch (req->bRequest) {
            case HID_SET_REPORT:
                LOG_D("HID_SET_REPORT");
                break;

            case HID_SET_IDLE:
                LOG_D("HID_SET_IDLE");
                USBD_Ep0SendZeroPkt();
                ret = USBD_OK;
                break;

            case HID_SET_PROTOCOL:
                LOG_D("HID_SET_PROTOCOL");
                break;

            default:
                LOG_E("Unknow USB HID Class OUT request[%d]!\n", req->bRequest);
                ret = USBD_ERROR;
                break;
        }
    }

    return ret;
}

/**
  * @brief  USBD HID Endpoint IN Interrupt
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_HID_DataIn(USB_EpNumETypeDef ep_num)
{
    if (ep_num == HID_EP_IN_NUM) {
        usbd_hid_ctrl.datain_busy_flag = false;
        return USBD_OK;
    }

    return USBD_FAILED;
}

/**
  * @brief  USBD HID Endpoint OUT Interrupt
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return USBD_StatusETypeDef
  */
static USBD_StatusETypeDef USBD_HID_DataOut(USB_EpNumETypeDef ep_num)
{
    if (ep_num == HID_EP_OUT_NUM) {
        if (usbd_hid_ctrl.dataout_callback) {
            usbd_hid_ctrl.dataout_callback(usb_core_ctrl.Instance);
            return USBD_OK;
        }
    }

    return USBD_FAILED;
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

