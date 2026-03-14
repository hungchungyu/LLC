/**
  ******************************************************************************
  * @file    usbd_hid.h
  * @author  MCD Application Team
  * @brief   Header file for USB Device HID class driver
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
#ifndef _USBD_HID_H_
#define _USBD_HID_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @addtogroup USBD_HID
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup USBD_HID_Exported_Constants USBD HID Exported Constants
  * @brief    USBD HID Exported Constants
  * @{
  */

/**
  * @brief HID Protocol Version in BCD Code: V1.1
  */
#define HID_PTOT_VER                (0x0110)

/**
  * @brief HID Product Serial Number in BCD Code
  */
#define HID_PROD_SN                 (0x0100)


/**
  * @brief HID Endpoint Numbers
  * @verbatim
           the endpoint numbers to be used in HID Configulation: 1 IN + 1 OUT
  * @endverbatim
  */
#define HID_EP_NUMS                 (2)

/**
  * @brief HID Input Endpoint Number
  */
#define HID_EP_IN_NUM               (EP_NUM_1)

/**
  * @brief HID Output Endpoint Number
  */
#define HID_EP_OUT_NUM              (EP_NUM_1)

/**
  * @brief HID Endpoint IN Max Payload
  */
#define HID_EP_IN_MAX_PL            (0x40)

/**
  * @brief HID Endpoint OUT Max Payload
  */
#define HID_EP_OUT_MAX_PL           (0x40)

/**
  * @brief HID Endpoint Interval
  * @note  10 Frames
  */
#define HID_EP_INTERVAL             (0xA)


/**
  * @brief HID Language ID String Index
  * @note  fixed 0x00 according to USB protocol, don't modify
  */
#define HID_LANG_ID_STR_IDX         (0x00)

/**
  * @brief HID Manufacture String Index
  */
#define HID_MAN_STR_IDX             (0x01)

/**
  * @brief HID Product String Index
  */
#define HID_PROD_STR_IDX            (0x02)

/**
  * @brief HID Serial Number String Index
  */
#define HID_SN_STR_IDX              (0x03)

/**
  * @brief HID Configuration String Index
  */
#define HID_CFG_STR_IDX             (0x04)

/**
  * @brief HID Interface String Index
  */
#define HID_IFC_STR_IDX             (0x05)


/**
  * @brief HID IFC-Class Subordinate Descriptor Numbers
  * @note  Always at least one i.e. Report Descriptor
  * @verbatim
           REPORT_DESCRIPTOR + PHYSICAL_DESCRIPTOR
  * @endverbatim
  */
#define HID_SUB_DESC_NUMS           (1)

/**
  * @brief HID Report Descriptor Length in Byte
  */
#define HID_REPROT_DESC_LEN         (33)

/**
  * @brief HID Descriptor Length in Byte
  */
#define HID_DESC_LEN                (sizeof(USB_HID_DescTypeDef))

/**
  * @brief HID Configuration Descriptor Set Length in Byte
  */
#define HID_CFG_DESC_SET_LEN        (sizeof(USB_HID_CfgDescSetTypeDef))

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/** @defgroup USBD_HID_Exported_Types USBD HID Exported Types
  * @brief    USBD HID Exported Types
  * @{
  */

/**
  * @brief HID Interface Class <Subclass Codes> Definition
  */
enum {
    HID_IFC_SUB_CLS_NONE     = 0x00,    /*!< No Subclass                */
    HID_IFC_SUB_CLS_BOOT_IFC = 0x01,    /*!< Boot Interface Subclass    */
    /* OTHER_RESERVED */
};

/**
  * @brief HID Interface Class <Protocol Codes> Definition
  */
enum {
    HID_IFC_PROT_NONE     = 0x00,       /*!< None Protocol              */
    HID_IFC_PROT_KEYBOARD = 0x01,       /*!< Keyboard Protocol          */
    HID_IFC_PROT_MOUSE    = 0x02,       /*!< Mouse Protocol             */
    /* OTHER_RESERVED */
};

/**
  * @brief HID Descriptor <bCountryCode> Definition
  * @note  Numeric expression identifying the HID Class Specification release
  */
enum {
    HID_CY_NOT_SUPPORTED      = 0,      /*!< Not Supported Country Code         */
    HID_CY_ARABIC             = 1,      /*!< Arabic Country Code                */
    HID_CY_BELGIAN            = 2,      /*!< Belgian Country Code               */
    HID_CY_CANADIAN_BILINGUAL = 3,      /*!< Canadian-Bilingual Country Code    */
    HID_CY_CANADIAN_FRENCH    = 4,      /*!< Canadian-French Country Code       */
    HID_CY_CZECH_REPUBLIC     = 5,      /*!< Czech Republic Country Code        */
    HID_CY_DANISH             = 6,      /*!< Danish Country Code                */
    HID_CY_FINNISH            = 7,      /*!< Finnish Country Code               */
    HID_CY_FRENCH             = 8,      /*!< French Country Code                */
    HID_CY_GERMAN             = 9,      /*!< German Country Code                */
    HID_CY_GREEK              = 10,     /*!< Greek Country Code                 */
    HID_CY_HEBREW             = 11,     /*!< Hebrew Country Code                */
    HID_CY_HUNGARY            = 12,     /*!< Hungary Country Code               */
    HID_CY_INTERNATIONAL      = 13,     /*!< International (ISO) Country Code   */
    HID_CY_ITALIAN            = 14,     /*!< Italian Country Code               */
    HID_CY_JAPAN              = 15,     /*!< Japan (Katakana) Country Code      */
    HID_CY_KOREAN             = 16,     /*!< Korean Country Code                */
    HID_CY_LATIN_AMERICAN     = 17,     /*!< Latin American Country Code        */
    HID_CY_NETHERLANDS_DUTCH  = 18,     /*!< Netherlands/Dutch Country Code     */
    HID_CY_NORWEGIAN          = 19,     /*!< Norwegian Country Code             */
    HID_CY_PERSIAN            = 20,     /*!< Persian (Farsi) Country Code       */
    HID_CY_POLAND             = 21,     /*!< Poland Country Code                */
    HID_CY_PORTUGUESE         = 22,     /*!< Portuguese Country Code            */
    HID_CY_RUSSIA             = 23,     /*!< Russia Country Code                */
    HID_CY_SLOVAKIA           = 24,     /*!< Slovakia Country Code              */
    HID_CY_SPANISH            = 25,     /*!< Spanish Country Code               */
    HID_CY_SWEDISH            = 26,     /*!< Swedish Country Code               */
    HID_CY_SWISS_FRENCH       = 27,     /*!< Swiss/French Country Code          */
    HID_CY_SWISS_GERMAN       = 28,     /*!< Swiss/German Country Code          */
    HID_CY_SWITZERLAND        = 29,     /*!< Switzerland Country Code           */
    HID_CY_TAIWAN             = 30,     /*!< Taiwan Code                        */
    HID_CY_TURKISH_Q          = 31,     /*!< Turkish-Q Country Code             */
    HID_CY_UK                 = 32,     /*!< UK Country Code                    */
    HID_CY_US                 = 33,     /*!< US Country Code ##Commonly Use##   */
    HID_CY_YUGOSLAVIA         = 34,     /*!< Yugoslavia Country Code            */
    HID_CY_TURKISH_F          = 35,     /*!< Turkish-F Country Code             */
    /* OTHER_RESERVED */
};

/**
  * @brief HID Class Request
  */
enum {
    HID_GET_REPORT   = 0x01,        /*!< The Get_Report request allows the host to receive a report via the Control pipe    */
    HID_GET_IDLE     = 0x02,        /*!< The Get_Idle request reads the current idle rate for a particular Input report     */
    HID_GET_PROTOCOL = 0x03,        /*!< The Get_Protocol request reads which protocol is currently active                  */
    HID_SET_REPORT   = 0x09,        /*!< The Set_Report request allows the host to send a report to the device              */
    HID_SET_IDLE     = 0x0A,        /*!< The Set_Idle request silences a particular report on the Interrupt In pipe         */
    HID_SET_PROTOCOL = 0x0B,        /*!< The Set_Protocol switches between the boot protocol and the report protocol        */
};


/**
  * @brief HID IFC-Class Subordinate Descriptor Definition
  */
typedef struct __HID_DescSubsetTypeDef {
    uint8_t bDescriptorType;        /*!< Constant name identifying type of class descriptor                     */
    uint8_t wDescriptorLength[2];   /*!< Numeric expression that is the total size of the Report descriptor     */
} HID_DescSubsetTypeDef;

/**
  * @brief USB IFC-Class HID Descriptor Struct Definition
  */
typedef struct __USB_HID_DescTypeDef {
    uint8_t bLength;                /*!< Numeric expression that is the total size of the HID descriptor        */
    uint8_t bDescriptorType;        /*!< Constant name specifying type of HID descriptor                        */
    uint8_t bcdHID[2];              /*!< Numeric expression identifying the HIDClass Specification release      */
    uint8_t bCountryCode;           /*!< Numeric expression identifying country code of the localized hardware  */
    uint8_t bNumDescriptors;        /*!< Numeric expression specifying the number of class descriptors          */
    HID_DescSubsetTypeDef sub_desc[HID_SUB_DESC_NUMS];
} USB_HID_DescTypeDef;

/**
  * @brief USB IFC-Class HID Configuration Descriptor Set Struct Definition
  */
typedef struct __USB_HID_CfgDescSetTypeDef {
    USB_CfgDescTypeDef  cfg_desc;                       /*!< Configuration Descriptor   */
    USB_IfcDescTypeDef  ifc_desc;                       /*!< Interface Descriptor       */
    USB_HID_DescTypeDef hid_desc;                       /*!< HID Descriptor             */
    USB_EpDescTypeDef   ep_desc[HID_EP_NUMS];           /*!< Endpoint Descriptor        */
} USB_HID_CfgDescSetTypeDef;

/**
  * @brief USBD HID Control struct type definition
  */
typedef struct __USBD_HID_CtrlTypeDef {
    volatile bool datain_busy_flag;                     /*!< data in busy flag          */
    void (*dataout_callback)(USB_TypeDef *Instance);    /*!< data out callback          */
} USBD_HID_CtrlTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @addtogroup USBD_HID_Exported_Variables
  * @{
  */
extern const USB_ClassFuncTypeDef hid_class_func;
extern const USB_HID_CfgDescSetTypeDef hid_cfg_desc_set;
/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @addtogroup USBD_HID_Exported_Functions
  * @{
  */
USBD_StatusETypeDef USBD_HID_Init(void (*dataout_callback)(USB_TypeDef *Instance));
USBD_StatusETypeDef USBD_HID_DeInit(void);
USBD_StatusETypeDef USBD_HID_DataSend(uint8_t *buf, uint32_t len);
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

#endif /* _USBD_HID_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

