/**
  ******************************************************************************
  * @file    usbd_def.h
  * @author  MCD Application Team
  * @brief   Header file for USB Device
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
#ifndef _USBD_DEF_H_
#define _USBD_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"


/** @addtogroup TAE_USB_DEVICE
  * @{
  */

/** @defgroup USBD_DEF USBD Defines
  * @brief    USB Device General Defines
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup USBD_Exported_Constants USBD Exported Constants
  * @brief    USBD Exported Constants
  * @{
  */

/** @defgroup USBD_Exported_Constants_Group1 USBD Config
  * @brief    USBD Config
  * @{
  */

/**
  * @brief USB Version Num in BCD Code: V2.0
  */
#define USB_VER                 (0x0200)

/**
  * @brief USB VID/PID Config
  */
#define USB_VID                 (0x0483)
#define USB_PID                 (0x5750)

/**
  * @brief Define Endpoint 0 Max Payload: [8, 16, 32, 64]
  * @note  USB Full Speed Can only Config to [8, 16, 32, 64]
  */
#define USB_EP0_MAX_PL          (64)

/**
  * @brief USB Standard Device Request Command Length
  */
#define USB_STD_DEV_REQ_CMD_LEN (8)             /* sizeof(USB_StdDevReqTypeDef)             */

/**
  * @}
  */


/** @defgroup USBD_Exported_Constants_Group2 USBD Descriptor Length Definition
  * @brief    USBD Descriptor Length Definition
  * @{
  */

#define USB_DEV_DESC_LEN        (18)            /*!< USB Device Descriptor Length           */
#define USB_CFG_DESC_LEN        (9)             /*!< USB Configuration Descriptor Length    */
#define USB_IFC_DESC_LEN        (9)             /*!< USB Interface Descriptor Length        */
#define USB_EP_DESC_LEN         (7)             /*!< USB Endpoint Descriptor Length         */
#define USB_DEV_QUAL_DESC_LEN   (10)            /*!< USB Device Qualifier Descriptor Length */

/**
  * @}
  */


/** @defgroup USBD_Exported_Constants_Group3 USB Endpoint Descriptor <bEndpointAddress> Definition
  * @brief    USB Endpoint Descriptor <bEndpointAddress> Definition
  * @{
  */

//Bit7: Direction
#define USB_EP_ADDR_CFG_DIR_IN      (1 << 7)    /*!< IN endpoint                            */
#define USB_EP_ADDR_CFG_DIR_OUT     (0)         /*!< OUT endpoint                           */

//Bit6~4: Reserved
#define USB_EP_ADDR_CFG_RSV_BIT6_4  (0)         /*!< Reserved, reset to zero                */

//Bit3~0: Number
#define USB_EP_ADDR_CFG_NUM_BIT     (0)         /*!< The endpoint number Bit Shift          */
#define USB_EP_ADDR_CFG_NUM_CFG(n)  (((n) & 0xFUL) << (USB_EP_ADDR_CFG_NUM_BIT))

/**
  * @}
  */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup USBD_DEF_Exported_Macros USBD Define Exported Macros
  * @brief    USBD Define Exported Macros
  * @{
  */

/**
  * @brief  Macro for getting U16 LowByte
  * @param  x u16 param to get LowByte
  * @return LowByte of x
  */
#define USBD_U16_LOWBYTE(x)     ((uint8_t)((uint16_t)(x) & 0x00FF))

/**
  * @brief  Macro for getting U16 HighByte
  * @param  x u16 param to get HighByte
  * @return HighByte of x
  */
#define USBD_U16_HIGHBYTE(x)    ((uint8_t)(((uint16_t)(x) & 0xFF00) >> 8))


/**
  * @brief  To avoid gcc/g++ warnings
  * @param  x Any Param
  * @return None
  */
#define USBD_UNUSED(x)          (void)x


/**
  * @brief  Macro for counting the element number of an array
  * @param  a Array to be Counted
  * @return size of Array
  */
#define USBD_ARRAY_SIZE(a)      (sizeof((a)) / sizeof((a)[0]))


/**
  * @brief  USBD Assert Param
  * @param  exp expression
  * @return None
  */
#ifdef USE_FULL_ASSERT
#define USBD_ASSERT_PARAM(exp)                                              \
        do {                                                                \
            if (!(exp)) {                                                   \
                LOG_R("Invalid param at %s:%d\n", __func__, __LINE__);      \
            }                                                               \
        } while (0)
#else
#define USBD_ASSERT_PARAM(exp)
#endif

/**
  * @brief  USBD Function Alternative
  * @param  flag Condition Flag
  * @param  func_t True Funciton
  * @param  func_f False Function
  * @return None
  */
#define USBD_FUNC_ALTER(flag, func_t, func_f)   \
        do{                                     \
            if((flag)) {                        \
                func_t;                         \
            } else {                            \
                func_f;                         \
            }                                   \
        } while(0)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup USBD_DEF_Exported_Types USBD Define Exported Types
  * @brief    USBD Define Exported Types
  * @{
  */

/** @defgroup USBD_DEF_Exported_Types_Group1 USBD Misc Type Definition
  * @brief    USBD Misc Type Definition
  * @{
  */

/**
  * @brief USBD status definition
  */
typedef enum {
    USBD_OK      = 0x00U,   /*!< USBD Status OK         */
    USBD_ERROR   = 0x01U,   /*!< USBD Status ERROR      */
    USBD_BUSY    = 0x02U,   /*!< USBD Status BUSY       */
    USBD_TIMEOUT = 0x03U,   /*!< USBD Status TIMEOUT    */
    USBD_FAILED  = 0x04U,   /*!< USBD Status FAILED     */
    USBD_INVALID = 0x05U,   /*!< USBD Status INVALID    */
} USBD_StatusETypeDef;


/**
  * @brief USB Configuration Descriptor <bmAttributes> Configuration Characteristics Definition
  */
enum {
    USB_CFG_DESC_ATTR_BIT7_RESERVED_1    = (1 << 7),    /*!< Reserved (set to one)      */
    USB_CFG_DESC_ATTR_BIT6_SEFT_POWERED  = (1 << 6),    /*!< Self-powered               */
    USB_CFG_DESC_ATTR_BIT5_REMOTE_WAKEUP = (1 << 5),    /*!< Remote Wakeup              */
    USB_CFG_DESC_ATTR_BIT4_0_RESERVED_0  = 0x00,        /*!< Reserved (reset to zero)   */
};

/**
  * @brief USB Endpoint Descriptor <bmAttributes> Definition
  */
enum {
    USB_EP_DESC_ATT_XFER_TYPE_CTRL    = (0 << 0),       /*!< Endpoint Transfer Type: Control                            */
    USB_EP_DESC_ATT_XFER_TYPE_ISO     = (1 << 0),       /*!< Endpoint Transfer Type: Isochronous                        */
    USB_EP_DESC_ATT_XFER_TYPE_BULK    = (2 << 0),       /*!< Endpoint Transfer Type: Bulk                               */
    USB_EP_DESC_ATT_XFER_TYPE_INT     = (3 << 0),       /*!< Endpoint Transfer Type:  Interrupt                         */

    USB_EP_DESC_ATT_SYNC_TYPE_NOSYNC  = (0 << 2),       /*!< Endpoint Synchronization Type(ISO): No Synchronization     */
    USB_EP_DESC_ATT_SYNC_TYPE_ASYNC   = (1 << 2),       /*!< Endpoint Synchronization Type(ISO): Asynchronous           */
    USB_EP_DESC_ATT_SYNC_TYPE_ADP     = (2 << 2),       /*!< Endpoint Synchronization Type(ISO): Adaptive               */
    USB_EP_DESC_ATT_SYNC_TYPE_SYNC    = (3 << 2),       /*!< Endpoint Synchronization Type(ISO): Synchronous            */

    USB_EP_DESC_ATT_USAGE_TYPE_DATA   = (0 << 4),       /*!< Endpoint Usage Type(ISO): Data endpoint                    */
    USB_EP_DESC_ATT_USAGE_TYPE_FB     = (1 << 4),       /*!< Endpoint Usage Type(ISO): Feedback endpoint                */
    USB_EP_DESC_ATT_USAGE_TYPE_IMP_FB = (2 << 4),       /*!< Endpoint Usage Type(ISO): Implicit feedback Data endpoint  */
    USB_EP_DESC_ATT_USAGE_TYPE_RSV    = (3 << 4),       /*!< Endpoint Usage Type(ISO): Reserved                         */
};

/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_Types_Group2 USB Language ID Definition
  * @brief    USB String Descriptor <wLANGID[n]> Language ID Definition
  * @{
  */
enum {
    USB_LANG_ID_AFRIKAANS                   = 0x0436,   /*!< Language ID AFRIKAANS                  */
    USB_LANG_ID_ALBANIAN                    = 0x041C,   /*!< Language ID ALBANIAN                   */
    USB_LANG_ID_ARABIC_SAUDI_ARABIA         = 0x0401,   /*!< Language ID ARABIC_SAUDI_ARABIA        */
    USB_LANG_ID_ARABIC_IRAQ                 = 0x0801,   /*!< Language ID ARABIC_IRAQ                */
    USB_LANG_ID_ARABIC_EGYPT                = 0x0C01,   /*!< Language ID ARABIC_EGYPT               */
    USB_LANG_ID_ARABIC_LIBYA                = 0x1001,   /*!< Language ID ARABIC_LIBYA               */
    USB_LANG_ID_ARABIC_ALGERIA              = 0x1401,   /*!< Language ID ARABIC_ALGERIA             */
    USB_LANG_ID_ARABIC_MOROCCO              = 0x1801,   /*!< Language ID ARABIC_MOROCCO             */
    USB_LANG_ID_ARABIC_TUNISIA              = 0x1C01,   /*!< Language ID ARABIC_TUNISIA             */
    USB_LANG_ID_ARABIC_OMAN                 = 0x2001,   /*!< Language ID ARABIC_OMAN                */
    USB_LANG_ID_ARABIC_YEMEN                = 0x2401,   /*!< Language ID ARABIC_YEMEN               */
    USB_LANG_ID_ARABIC_SYRIA                = 0x2801,   /*!< Language ID ARABIC_SYRIA               */
    USB_LANG_ID_ARABIC_JORDAN               = 0x2C01,   /*!< Language ID ARABIC_JORDAN              */
    USB_LANG_ID_ARABIC_LEBANON              = 0x3001,   /*!< Language ID ARABIC_LEBANON             */
    USB_LANG_ID_ARABIC_KUWAIT               = 0x3401,   /*!< Language ID ARABIC_KUWAIT              */
    USB_LANG_ID_ARABIC_UAE                  = 0x3801,   /*!< Language ID ARABIC_UAE                 */
    USB_LANG_ID_ARABIC_BAHRAIN              = 0x3C01,   /*!< Language ID ARABIC_BAHRAIN             */
    USB_LANG_ID_ARABIC_QATAR                = 0x4001,   /*!< Language ID ARABIC_QATAR               */
    USB_LANG_ID_ARMENIAN                    = 0x042B,   /*!< Language ID ARMENIAN                   */
    USB_LANG_ID_ASSAMESE                    = 0x044D,   /*!< Language ID ASSAMESE                   */
    USB_LANG_ID_AZERI_LATIN                 = 0x042C,   /*!< Language ID AZERI_LATIN                */
    USB_LANG_ID_AZERI_CYRILLLIC             = 0x082C,   /*!< Language ID AZERI_CYRILLLIC            */
    USB_LANG_ID_BASQUE                      = 0x042D,   /*!< Language ID BASQUE                     */
    USB_LANG_ID_BELARUSSIAN                 = 0x0423,   /*!< Language ID BELARUSSIAN                */
    USB_LANG_ID_BENGALI                     = 0x0445,   /*!< Language ID BENGALI                    */
    USB_LANG_ID_BULGARIAN                   = 0x0402,   /*!< Language ID BULGARIAN                  */
    USB_LANG_ID_BURMESE                     = 0x0455,   /*!< Language ID BURMESE                    */
    USB_LANG_ID_CATALAN                     = 0x0403,   /*!< Language ID CATALAN                    */
    USB_LANG_ID_CHINESE_TAIWAN              = 0x0404,   /*!< Language ID CHINESE_TAIWAN             */
    USB_LANG_ID_CHINESE_PRC                 = 0x0804,   /*!< Language ID CHINESE_PRC                */
    USB_LANG_ID_CHINESE_HONGKONG_SAR_PRC    = 0x0C04,   /*!< Language ID CHINESE_HONGKONG_SAR_PRC   */
    USB_LANG_ID_CHINESE_SINGAPORE           = 0x1004,   /*!< Language ID CHINESE_SINGAPORE          */
    USB_LANG_ID_CHINESE_MACAU_SAR           = 0x1404,   /*!< Language ID CHINESE_MACAU_SAR          */
    USB_LANG_ID_CROATIAN                    = 0x041A,   /*!< Language ID CROATIAN                   */
    USB_LANG_ID_CZECH                       = 0x0405,   /*!< Language ID CZECH                      */
    USB_LANG_ID_DANISH                      = 0x0406,   /*!< Language ID DANISH                     */
    USB_LANG_ID_DUTCH_NETHERLANDS           = 0x0413,   /*!< Language ID DUTCH_NETHERLANDS          */
    USB_LANG_ID_DUTCH_BELGIUM               = 0x0813,   /*!< Language ID DUTCH_BELGIUM              */
    USB_LANG_ID_ENGLISH_UNITED_STATES       = 0x0409,   /*!< Language ID ENGLISH_UNITED_STATES      */   //<Commonly Use>
    USB_LANG_ID_ENGLISH_UNITED_KINGDOM      = 0x0809,   /*!< Language ID ENGLISH_UNITED_KINGDOM     */
    USB_LANG_ID_ENGLISH_AUSTRALIAN          = 0x0C09,   /*!< Language ID ENGLISH_AUSTRALIAN         */
    USB_LANG_ID_ENGLISH_CANADIAN            = 0x1009,   /*!< Language ID ENGLISH_CANADIAN           */
    USB_LANG_ID_ENGLISH_NEW_ZEALAND         = 0x1409,   /*!< Language ID ENGLISH_NEW_ZEALAND        */
    USB_LANG_ID_ENGLISH_IRELAND             = 0x1809,   /*!< Language ID ENGLISH_IRELAND            */
    USB_LANG_ID_ENGLISH_SOUTH_AFRICA        = 0x1C09,   /*!< Language ID ENGLISH_SOUTH_AFRICA       */
    USB_LANG_ID_ENGLISH_JAMAICA             = 0x2009,   /*!< Language ID ENGLISH_JAMAICA            */
    USB_LANG_ID_ENGLISH_CARIBBEAN           = 0x2409,   /*!< Language ID ENGLISH_CARIBBEAN          */
    USB_LANG_ID_ENGLISH_BELIZE              = 0x2809,   /*!< Language ID ENGLISH_BELIZE             */
    USB_LANG_ID_ENGLISH_TRINIDAD            = 0x2C09,   /*!< Language ID ENGLISH_TRINIDAD           */
    USB_LANG_ID_ENGLISH_ZIMBABWE            = 0x3009,   /*!< Language ID ENGLISH_ZIMBABWE           */
    USB_LANG_ID_ENGLISH_PHILIPPINES         = 0x3409,   /*!< Language ID ENGLISH_PHILIPPINES        */
    USB_LANG_ID_ESTONIAN                    = 0x0425,   /*!< Language ID ESTONIAN                   */
    USB_LANG_ID_FAEROESE                    = 0x0438,   /*!< Language ID FAEROESE                   */
    USB_LANG_ID_FARSI                       = 0x0429,   /*!< Language ID FARSI                      */
    USB_LANG_ID_FINNISH                     = 0x040B,   /*!< Language ID FINNISH                    */
    USB_LANG_ID_FRENCH_STANDARD             = 0x040C,   /*!< Language ID FRENCH_STANDARD            */
    USB_LANG_ID_FRENCH_BELGIAN              = 0x080C,   /*!< Language ID FRENCH_BELGIAN             */
    USB_LANG_ID_FRENCH_CANADIAN             = 0x0C0C,   /*!< Language ID FRENCH_CANADIAN            */
    USB_LANG_ID_FRENCH_SWITZERLAND          = 0x100C,   /*!< Language ID FRENCH_SWITZERLAND         */
    USB_LANG_ID_FRENCH_LUXEMBOURG           = 0x140C,   /*!< Language ID FRENCH_LUXEMBOURG          */
    USB_LANG_ID_FRENCH_MONACO               = 0x180C,   /*!< Language ID FRENCH_MONACO              */
    USB_LANG_ID_GEORGIAN                    = 0x0437,   /*!< Language ID GEORGIAN                   */
    USB_LANG_ID_GERMAN_STANDARD             = 0x0407,   /*!< Language ID GERMAN_STANDARD            */
    USB_LANG_ID_GERMAN_SWITZERLAND          = 0x0807,   /*!< Language ID GERMAN_SWITZERLAND         */
    USB_LANG_ID_GERMAN_AUSTRIA              = 0x0C07,   /*!< Language ID GERMAN_AUSTRIA             */
    USB_LANG_ID_GERMAN_LUXEMBOURG           = 0x1007,   /*!< Language ID GERMAN_LUXEMBOURG          */
    USB_LANG_ID_GERMAN_LIECHTENSTEIN        = 0x1407,   /*!< Language ID GERMAN_LIECHTENSTEIN       */
    USB_LANG_ID_GREEK                       = 0x0408,   /*!< Language ID GREEK                      */
    USB_LANG_ID_GUJARATI                    = 0x0447,   /*!< Language ID GUJARATI                   */
    USB_LANG_ID_HEBREW                      = 0x040D,   /*!< Language ID HEBREW                     */
    USB_LANG_ID_HINDI                       = 0x0439,   /*!< Language ID HINDI                      */
    USB_LANG_ID_HUNGARIAN                   = 0x040E,   /*!< Language ID HUNGARIAN                  */
    USB_LANG_ID_ICELANDIC                   = 0x040F,   /*!< Language ID ICELANDIC                  */
    USB_LANG_ID_INDONESIAN                  = 0x0421,   /*!< Language ID INDONESIAN                 */
    USB_LANG_ID_ITALIAN_STANDARD            = 0x0410,   /*!< Language ID ITALIAN_STANDARD           */
    USB_LANG_ID_ITALIAN_SWITZERLAND         = 0x0810,   /*!< Language ID ITALIAN_SWITZERLAND        */
    USB_LANG_ID_JAPANESE                    = 0x0411,   /*!< Language ID JAPANESE                   */
    USB_LANG_ID_KANNADA                     = 0x044B,   /*!< Language ID KANNADA                    */
    USB_LANG_ID_KASHMIRI_INDIA              = 0x0860,   /*!< Language ID KASHMIRI_INDIA             */
    USB_LANG_ID_KAZAKH                      = 0x043F,   /*!< Language ID KAZAKH                     */
    USB_LANG_ID_KONKANI                     = 0x0457,   /*!< Language ID KONKANI                    */
    USB_LANG_ID_KOREAN                      = 0x0412,   /*!< Language ID KOREAN                     */
    USB_LANG_ID_KOREAN_JOHAB                = 0x0812,   /*!< Language ID KOREAN_JOHAB               */
    USB_LANG_ID_LATVIAN                     = 0x0426,   /*!< Language ID LATVIAN                    */
    USB_LANG_ID_LITHUANIAN                  = 0x0427,   /*!< Language ID LITHUANIAN                 */
    USB_LANG_ID_LITHUANIAN_CLASSIC          = 0x0827,   /*!< Language ID LITHUANIAN_CLASSIC         */
    USB_LANG_ID_MACEDONIAN                  = 0x042F,   /*!< Language ID MACEDONIAN                 */
    USB_LANG_ID_MALAY_MALAYSIAN             = 0x043E,   /*!< Language ID MALAY_MALAYSIAN            */
    USB_LANG_ID_MALAY_BRUNEI_DARUSSALAM     = 0x083E,   /*!< Language ID MALAY_BRUNEI_DARUSSALAM    */
    USB_LANG_ID_MALAYALAM                   = 0x044C,   /*!< Language ID MALAYALAM                  */
    USB_LANG_ID_MANIPURI                    = 0x0458,   /*!< Language ID MANIPURI                   */
    USB_LANG_ID_MARATHI                     = 0x044E,   /*!< Language ID MARATHI                    */
    USB_LANG_ID_NEPALI_INDIA                = 0x0861,   /*!< Language ID NEPALI_INDIA               */
    USB_LANG_ID_NOREWGIAN_BOKMAL            = 0x0414,   /*!< Language ID NOREWGIAN_BOKMAL           */
    USB_LANG_ID_NOREWGIAN_NYNORSK           = 0x0814,   /*!< Language ID NOREWGIAN_NYNORSK          */
    USB_LANG_ID_ORIYA                       = 0x0448,   /*!< Language ID ORIYA                      */
    USB_LANG_ID_POLISH                      = 0x0415,   /*!< Language ID POLISH                     */
    USB_LANG_ID_PORTUGUESE_BRAZIL           = 0x0416,   /*!< Language ID PORTUGUESE_BRAZIL          */
    USB_LANG_ID_PORTUGUESE_STANDARD         = 0x0816,   /*!< Language ID PORTUGUESE_STANDARD        */
    USB_LANG_ID_PUNJABI                     = 0x0446,   /*!< Language ID PUNJABI                    */
    USB_LANG_ID_ROMANIAN                    = 0x0418,   /*!< Language ID ROMANIAN                   */
    USB_LANG_ID_RUSSIAN                     = 0x0419,   /*!< Language ID RUSSIAN                    */
    USB_LANG_ID_SANSKRIT                    = 0x044F,   /*!< Language ID SANSKRIT                   */
    USB_LANG_ID_SERBIAN_CYRILLLIC           = 0x0C1A,   /*!< Language ID SERBIAN_CYRILLLIC          */
    USB_LANG_ID_SERBIAN_LATIN               = 0x081A,   /*!< Language ID SERBIAN_LATIN              */
    USB_LANG_ID_SINDHI                      = 0x0459,   /*!< Language ID SINDHI                     */
    USB_LANG_ID_SLOVAK                      = 0x041B,   /*!< Language ID SLOVAK                     */
    USB_LANG_ID_SLOVENIAN                   = 0x0424,   /*!< Language ID SLOVENIAN                  */
    USB_LANG_ID_SPANISH_TRADITIONAL_SORT    = 0x040A,   /*!< Language ID SPANISH_TRADITIONAL_SORT   */
    USB_LANG_ID_SPANISH_MEXICAN             = 0x080A,   /*!< Language ID SPANISH_MEXICAN            */
    USB_LANG_ID_SPANISH_MODERN_SORT         = 0x0C0A,   /*!< Language ID SPANISH_MODERN_SORT        */
    USB_LANG_ID_SPANISH_GUATEMALA           = 0x100A,   /*!< Language ID SPANISH_GUATEMALA          */
    USB_LANG_ID_SPANISH_COSTA_RICA          = 0x140A,   /*!< Language ID SPANISH_COSTA_RICA         */
    USB_LANG_ID_SPANISH_PANAMA              = 0x180A,   /*!< Language ID SPANISH_PANAMA             */
    USB_LANG_ID_SPANISH_DOMINICAN_REPUBLIC  = 0x1C0A,   /*!< Language ID SPANISH_DOMINICAN_REPUBLIC */
    USB_LANG_ID_SPANISH_VENEZUELA           = 0x200A,   /*!< Language ID SPANISH_VENEZUELA          */
    USB_LANG_ID_SPANISH_COLOMBIA            = 0x240A,   /*!< Language ID SPANISH_COLOMBIA           */
    USB_LANG_ID_SPANISH_PERU                = 0x280A,   /*!< Language ID SPANISH_PERU               */
    USB_LANG_ID_SPANISH_ARGENTINA           = 0x2C0A,   /*!< Language ID SPANISH_ARGENTINA          */
    USB_LANG_ID_SPANISH_ECUADOR             = 0x300A,   /*!< Language ID SPANISH_ECUADOR            */
    USB_LANG_ID_SPANISH_CHILE               = 0x340A,   /*!< Language ID SPANISH_CHILE              */
    USB_LANG_ID_SPANISH_URUGUAY             = 0x380A,   /*!< Language ID SPANISH_URUGUAY            */
    USB_LANG_ID_SPANISH_PARAGUAY            = 0x3C0A,   /*!< Language ID SPANISH_PARAGUAY           */
    USB_LANG_ID_SPANISH_BOLIVIA             = 0x400A,   /*!< Language ID SPANISH_BOLIVIA            */
    USB_LANG_ID_SPANISH_EL_SALVADOR         = 0x440A,   /*!< Language ID SPANISH_EL_SALVADOR        */
    USB_LANG_ID_SPANISH_HONDURAS            = 0x480A,   /*!< Language ID SPANISH_HONDURAS           */
    USB_LANG_ID_SPANISH_NICARAGUA           = 0x4C0A,   /*!< Language ID SPANISH_NICARAGUA          */
    USB_LANG_ID_SPANISH_PUERTO_RICO         = 0x500A,   /*!< Language ID SPANISH_PUERTO_RICO        */
    USB_LANG_ID_SUTU                        = 0x0430,   /*!< Language ID SUTU                       */
    USB_LANG_ID_SWAHILI_KENYA               = 0x0441,   /*!< Language ID SWAHILI_KENYA              */
    USB_LANG_ID_SWEDISH                     = 0x041D,   /*!< Language ID SWEDISH                    */
    USB_LANG_ID_SWEDISH_FINLAND             = 0x081D,   /*!< Language ID SWEDISH_FINLAND            */
    USB_LANG_ID_TAMIL                       = 0x0449,   /*!< Language ID TAMIL                      */
    USB_LANG_ID_TATAR_TATARSTAN             = 0x0444,   /*!< Language ID TATAR_TATARSTAN            */
    USB_LANG_ID_TELUGU                      = 0x044A,   /*!< Language ID TELUGU                     */
    USB_LANG_ID_THAI                        = 0x041E,   /*!< Language ID THAI                       */
    USB_LANG_ID_TURKISH                     = 0x041F,   /*!< Language ID TURKISH                    */
    USB_LANG_ID_UKRAINIAN                   = 0x0422,   /*!< Language ID UKRAINIAN                  */
    USB_LANG_ID_URDU_PAKISTAN               = 0x0420,   /*!< Language ID URDU_PAKISTAN              */
    USB_LANG_ID_URDU_INDIA                  = 0x0820,   /*!< Language ID URDU_INDIA                 */
    USB_LANG_ID_UZBEK_LATIN                 = 0x0443,   /*!< Language ID UZBEK_LATIN                */
    USB_LANG_ID_UZBEK_CYRILLLIC             = 0x0843,   /*!< Language ID UZBEK_CYRILLLIC            */
    USB_LANG_ID_VIETNAMESE                  = 0x042A,   /*!< Language ID VIETNAMESE                 */

    USB_LANG_ID_HID_USAGE_DATA_DESCRIPTOR   = 0x04FF,   /*!< Language ID HID_USAGE_DATA_DESCRIPTOR  */
    USB_LANG_ID_HID_VENDOR_DEFINE_1         = 0xF0FF,   /*!< Language ID HID_VENDOR_DEFINE_1        */
    USB_LANG_ID_HID_VENDOR_DEFINE_2         = 0xF4FF,   /*!< Language ID HID_VENDOR_DEFINE_2        */
    USB_LANG_ID_HID_VENDOR_DEFINE_3         = 0xF8FF,   /*!< Language ID HID_VENDOR_DEFINE_3        */
    USB_LANG_ID_HID_VENDOR_DEFINE_4         = 0xFCFF,   /*!< Language ID HID_VENDOR_DEFINE_4        */
};

/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_Types_Group3 USB StdDevReq Region BitFunction Definition
  * @brief    USB Standard Device Request Region BitFunction Definition
  * @{
  */

/**
  * @brief USB Standard Device Request Region <bmRequestType> Requset Direction
  */
enum {
    USB_STD_DEV_REQ_DIR_OUT = 0,            /*!< Requset Direction Out      */
    USB_STD_DEV_REQ_DIR_IN  = 1,            /*!< Requset Direction In       */

    USB_STD_DEV_REQ_DIR_BIT = 7,            /*!< Requset Direction Bit      */
    USB_STD_DEV_REQ_DIR_BITMASK = 0x80,     /*!< Requset Direction BitMask  */
};

/**
  * @brief USB Standard Device Request Region <bmRequestType> Request Type
  */
enum {
    USB_STD_DEV_REQ_TYPE_STD   = 0,         /*!<Request Type Standard       */
    USB_STD_DEV_REQ_TYPE_CLASS = 1,         /*!<Request Type Class          */
    USB_STD_DEV_REQ_TYPE_MAN   = 2,         /*!<Request Type Manufacturer   */
    USB_STD_DEV_REQ_TYPE_RSV   = 3,         /*!<Request Type Reserved       */

    USB_STD_DEV_REQ_TYPE_BIT   = 5,         /*!<Request Type Bit            */
    USB_STD_DEV_REQ_TYPE_BITMASK = 0x60,    /*!<Request Type BitMask        */
    /* OTHER_RESERVED */
};

/**
  * @brief USB Standard Device Request Region <bmRequestType> Request Receiver
  */
enum {
    USB_STD_DEV_REQ_RCVR_DEV = 0,           /*!< Request Receiver Device    */
    USB_STD_DEV_REQ_RCVR_IFC = 1,           /*!< Request Receiver Interface */
    USB_STD_DEV_REQ_RCVR_EP  = 2,           /*!< Request Receiver Endpoint  */
    USB_STD_DEV_REQ_RCVR_OTH = 3,           /*!< Request Receiver Other     */

    USB_STD_DEV_REQ_RCVR_BIT = 0,           /*!< Request Receiver Bit       */
    USB_STD_DEV_REQ_RCVR_BITMASK = 0x1F,    /*!< Request Receiver BitMask   */
};

/**
  * @brief <bRequest> Definition
  */
typedef enum {
    GET_STATUS        = 0,      /*!< This request returns status for the specified recipient                                    */
    CLEAR_FEATURE     = 1,      /*!< This request is used to clear or disable a specific feature                                */
    SET_FEATURE       = 3,      /*!< This request is used to set or enable a specific feature                                   */
    SET_ADDRESS       = 5,      /*!< This request sets the device address for all future device accesses                        */
    GET_DESCRIPTOR    = 6,      /*!< This request returns the specified descriptor if the descriptor exists                     */
    SET_DESCRIPTOR    = 7,      /*!< This request may be used to update existing descriptors or new descriptors may be added    */
    GET_CONFIGURATION = 8,      /*!< This request returns the current device configuration value                                */
    SET_CONFIGURATION = 9,      /*!< This request sets the device configuration                                                 */
    GET_INTERFACE     = 10,     /*!< This request returns the selected alternate setting for the specified interface            */
    SET_INTERFACE     = 11,     /*!< This request allows the host to select an alternate setting for the specified interface    */
    SYNCH_FRAME       = 12,     /*!< This request is used to set and then report an endpoint's synchronization frame           */

    STD_REQ_INVALID   = -1,     /*!< Invalid Standard Device Request                                                            */
} USB_StdDevReqETypeDef;

/**
  * @brief DescriptorType Definition
  */
typedef enum {
    //Standard Descriptor
    DEVICE_DESCRIPTOR                    = 0x01,    /*!< A device descriptor describes general information about a USB device   */
    CONFIGURATION_DESCRIPTOR             = 0x02,    /*!< Describes information about a specific device configuration            */
    STRING_DESCRIPTOR                    = 0x03,    /*!< Each endpoint used for an interface has its own descriptor             */
    INTERFACE_DESCRIPTOR                 = 0x04,    /*!< Describes a specific interface within a configuration                  */
    ENDPOINT_DESCRIPTOR                  = 0x05,    /*!< Contains bandwidth information required by the host                    */
    DEVICE_QUALIFIER_DESCRIPTOR          = 0x06,    /*!< Describes information about a HS capable device operate at other speed */
    OTHER_SPEED_CONFIGURATION_DESCRIPTOR = 0x07,    /*!< Other Speed Configuration Descriptor                                   */
    INTERFACE_POWER_DESCRIPTOR           = 0x08,    /*!< Interface Power Descriptor                                             */

    //HID Class Descriptor
    HID_DESCRIPTOR      = 0x21,                     /*!< HID Class Descriptor           */
    REPORT_DESCRIPTOR   = 0x22,                     /*!< HID Class Report Descriptor    */
    PHYSICAL_DESCRIPTOR = 0x23,                     /*!< HID Class Physical Descriptor  */

    //HUB Class Descriptor
    HUB_DESCRIPTOR      = 0x29,                     /*!< Hub Descriptor                 */

    //Manufacturer Custom Descriptor
    MANUFACTURER_CUSTOM_DESCRIPTOR = 0xFF,          /*!< Manufacturer Custom Descriptor */
} USB_DescTypeETypeDef;

/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_Types_Group4 USBD Class Definition
  * @brief    USBD Class Definition
  * @{
  */

/**
  * @brief USB Device Class Definition
  */
enum {
    USB_DEV_CLS_USE_IN_IFC    = 0x00,           /*!< Use class information in the Interface Descriptors */
    USB_DEV_CLS_COMM_CDC_CTRL = 0x02,           /*!< Communications and CDC Control                     */
    USB_DEV_CLS_HUB           = 0x09,           /*!< Hub                                                */
    USB_DEV_CLS_BILLBOARD     = 0x11,           /*!< Billboard Device Class                             */
    USB_DEV_CLS_DIAGNOSTIC    = 0xDC,           /*!< Diagnostic Device                                  */
    USB_DEV_CLS_MISC          = 0xEF,           /*!< Miscellaneous                                      */
    USB_DEV_CLS_VENDOR        = 0xFF,           /*!< Vendor Specific                                    */
};

/**
  * @brief USB Interface Class Definition
  */
enum {
    USB_IFC_CLS_AUDIO               = 0x01,     /*!< Audio                          */
    USB_IFC_CLS_COMM_CDC_CTRL       = 0x02,     /*!< Communications and CDC Control */
    USB_IFC_CLS_HID                 = 0x03,     /*!< HID (Human Interface Device)   */
    USB_IFC_CLS_PHYSYCAL            = 0x05,     /*!< Physical                       */
    USB_IFC_CLS_IMAGE               = 0x06,     /*!< Image                          */
    USB_IFC_CLS_PRINTER             = 0x07,     /*!< Printer                        */
    USB_IFC_CLS_MASS_STORAGE        = 0x08,     /*!< Mass Storage                   */
    USB_IFC_CLS_CDC_DATA            = 0x0A,     /*!< CDC-Data                       */
    USB_IFC_CLS_SMART_CARD          = 0x0B,     /*!< Smart Card                     */
    USB_IFC_CLS_CONTENT_SECURITY    = 0x0D,     /*!< Content Security               */
    USB_IFC_CLS_VIDEO               = 0x0E,     /*!< Video                          */
    USB_IFC_CLS_PERSONAL_HEALTHCARE = 0x0F,     /*!< Personal Healthcare            */
    USB_IFC_CLS_AUDIO_VIDEO_DEV     = 0x10,     /*!< Audio/Video Devices            */
    USB_IFC_CLS_USB_TYPEC_BRIDGE    = 0x12,     /*!< USB Type-C Bridge Class        */
    USB_IFC_CLS_DIAGNOSTIC          = 0xDC,     /*!< Diagnostic Device              */
    USB_IFC_CLS_WIRELESS_CONTROLER  = 0xE0,     /*!< Wireless Controller            */
    USB_IFC_CLS_MISC                = 0xEF,     /*!< Miscellaneous                  */
    USB_IFC_CLS_APP                 = 0xFE,     /*!< Application Specific           */
    USB_IFC_CLS_VENDOR              = 0xFF,     /*!< Vendor Specific                */
};

/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_Types_Group5  USB Device Descriptor Struct Definition
  * @brief    USB Device Descriptor Struct Definition
  * @{
  */

/**
  * @brief USB Device Descriptor Struct Definition
  */
typedef struct __USB_DevDescTypeDef {
    uint8_t bLength;                /*!< Size of this descriptor in bytes                                   */
    uint8_t bDescriptorType;        /*!< DEVICE Descriptor Type                                             */
    uint8_t bcdUSB[2];              /*!< USB Specification Release Number in Binary-Coded Decima            */
    uint8_t bDeviceClass;           /*!< Device Class Code                                                  */
    uint8_t bDeviceSubClass;        /*!< Device Subclass code                                               */
    uint8_t bDeviceProtocol;        /*!< Device Protocol code                                               */
    uint8_t bMaxPacketSize0;        /*!< Maximum packet size for endpoint 0                                 */
    uint8_t idVendor[2];            /*!< Vendor ID                                                          */
    uint8_t idProduct[2];           /*!< Product ID                                                         */
    uint8_t bcdDevice[2];           /*!< Device release number in binary-coded decimal                      */
    uint8_t iManufacturer;          /*!< Index of string descriptor describing manufacturer                 */
    uint8_t iProduct;               /*!< Index of string descriptor describing product                      */
    uint8_t iSerialNumber;          /*!< Index of string descriptor describing the device's serial number   */
    uint8_t bNumConfigurations;     /*!< Number of possible configurations                                  */
} USB_DevDescTypeDef;

/**
  * @brief USB Configuration Descriptor Struct Definition(the same as USB Other Speed Configuration Descriptor)
  */
typedef struct __USB_CfgDescTypeDef {
    uint8_t bLength;                /*!< Size of this descriptor in bytes                                   */
    uint8_t bDescriptorType;        /*!< CONFIGURATION Descriptor Type                                      */
    uint8_t wTotalLength[2];        /*!< Total length of data returned for this configuration               */
    uint8_t bNumInterfaces;         /*!< Number of interfaces supported by this configuration               */
    uint8_t bConfigurationValue;    /*!< Value to select this configuration                                 */
    uint8_t iConfiguration;         /*!< Index of string descriptor describing this configuration           */
    uint8_t bmAttributes;           /*!< Configuration characteristics                                      */
    uint8_t bMaxPower;              /*!< Maximum power consumption of the USB device from the bus           */
} USB_CfgDescTypeDef, USB_OtherSpeedCfgDescTypeDef;

/**
  * @brief USB Interface Descriptor Struct Definition
  */
typedef struct __USB_IfcDescTypeDef {
    uint8_t bLength;                /*!< Size of this descriptor in bytes                                   */
    uint8_t bDescriptorType;        /*!< INTERFACE Descriptor Type                                          */
    uint8_t bInterfaceNumber;       /*!< Number of this interface <Zero-based>                              */
    uint8_t bAlternateSetting;      /*!< Alternate Number of this interface                                 */
    uint8_t bNumEndpoints;          /*!< Number of endpoints used by this interface(excluding endpoint 0)   */
    uint8_t bInterfaceClass;        /*!< Interface Class Code                                               */
    uint8_t bInterfaceSubClass;     /*!< Interface Subclass Code                                            */
    uint8_t bInterfaceProtocol;     /*!< Interface Protocol Code                                            */
    uint8_t iInterface;             /*!< Index of string descriptor describing this interface               */
} USB_IfcDescTypeDef;

/**
  * @brief USB Endpoint Descriptor Struct Definition
  */
typedef struct __USB_EpDescTypeDef {
    uint8_t bLength;                /*!< Size of this descriptor in bytes                                   */
    uint8_t bDescriptorType;        /*!< ENDPOINT Descriptor Type                                           */
    uint8_t bEndpointAddress;       /*!< Address of the EP on the USB device described by this descriptor   */
    uint8_t bmAttributes;           /*!< This field describes the endpoint's attributes                     */
    uint8_t wMaxPacketSize[2];      /*!< Maximum packet size endpoint is capable of sending or receiving    */
    uint8_t bInterval;              /*!< Interval for polling EP for data transfers(FRMs or MicroFRMs)      */
} USB_EpDescTypeDef;

/**
  * @brief USB Device Qualifier Descriptor Struct Definition
  */
typedef struct __USB_DevQualDescTypeDef {
    uint8_t bLength;                /*!< Size of descriptor                                                 */
    uint8_t bDescriptorType;        /*!< Device Qualifier Type                                              */
    uint8_t bcdUSB[2];              /*!< USB specification version number                                   */
    uint8_t bDeviceClass;           /*!< Device Class Code                                                  */
    uint8_t bDeviceSubClass;        /*!< Device SubClass Code                                               */
    uint8_t bDeviceProtocol;        /*!< Device Protocol Code                                               */
    uint8_t bMaxPacketSize0;        /*!< Maximum packet size for other speed(EP0)                           */
    uint8_t bNumConfigurations;     /*!< Number of Other-speed Configurations                               */
    uint8_t bReserved;              /*!< Reserved for future use, must be zero                              */
} USB_DevQualDescTypeDef;

/**
  * @}
  */


/** @defgroup USBD_DEF_Exported_Types_Group6  USB Enum EP0 Control struct Definition
  * @brief    USB Enum EP0 Control struct Definition
  * @{
  */

/**
  * @brief USB Standard Device Request Struct Definition
  */
typedef struct __USB_StdDevReqTypeDef {
    uint8_t  bmRequestType; /*!< This bitmapped field identifies the characteristics of the specific request                    */
    uint8_t  bRequest;      /*!< This field specifies the particular request                                                    */
    uint16_t wValue;        /*!< The contents of this field vary according to the request                                       */
    uint16_t wIndex;        /*!< The contents of this field vary according to the request                                       */
    uint16_t wLength;       /*!< This field specify the length of the data transferred during the 2nd phase of the CTRL transfer*/
} USB_StdDevReqTypeDef;

/**
  * @brief USB Enum Descriptor Type Definition
  */
typedef struct __USB_EnumDescTypeDef {
    USB_DescTypeETypeDef desc_type; /*!< Enum Descriptor Type       */
    uint8_t  *desc_ptr;             /*!< Enum Descriptor Pointer    */
    uint16_t desc_len;              /*!< Enum Descriptor Length     */
} USB_EnumDescTypeDef;

/**
  * @brief USB String Descriptor Type Definition
  */
typedef struct __USB_EnumStrTypeDef {
    uint8_t  str_idx;               /*!< String Index               */
    uint8_t  *str_ptr;              /*!< String Descriptor Pointer  */
    uint16_t str_len;               /*!< String Descriptor Length   */
} USB_EnumStrTypeDef;

/**
  * @brief USB Class Function Struct Definition
  */
typedef struct __USB_ClassFuncTypeDef {
    USBD_StatusETypeDef(*Setup)(USB_StdDevReqTypeDef *req);     /*!< USB Class Setup Function       */
    USBD_StatusETypeDef(*DataIn)(USB_EpNumETypeDef ep_num);     /*!< USB Class Data IN Callback     */
    USBD_StatusETypeDef(*DataOut)(USB_EpNumETypeDef ep_num);    /*!< USB Class Data OUT Callback    */
} USB_ClassFuncTypeDef;


/**
  * @brief USB Core Init Struct Definition
  */
typedef struct __USBD_CoreInitTypeDef {
    //USB LL Control
    USB_TypeDef *Instance;              /*!< USB ll Instance                            */
    USB_LL_DrvTypeDef *ll_drv;          /*!< USB LL Driver Interface Pointer            */

    //USB Class Control
    USB_ClassFuncTypeDef *cls_func;     /*!< USB Class Function Pointer                 */

    //Enum Control
    USB_EnumDescTypeDef *enum_desc;     /*!< Usb Enum Descriptor Array pointer          */
    uint8_t enum_desc_nums;             /*!< Usb Enum Descriptor Array element nums     */
    USB_EnumStrTypeDef *enum_str;       /*!< USB String Descriptor Array pointer        */
    uint8_t enum_str_nums;              /*!< USB String Descriptor Array element nums   */
    USB_EpCfgTypeDef *ep_cfg;           /*!< USB Endpoint Config Array pointer          */
    uint8_t ep_cfg_nums;                /*!< USB Endpoint Config Array element nums     */
} USBD_CoreInitTypeDef;

/**
  * @brief USB Enum Ep0 Control Struct Definition
  */
typedef struct __USBD_CoreCtrlTypeDef {
    //USB LL Control
    USB_TypeDef *Instance;              /*!< USB ll Instance                            */
    USB_LL_DrvTypeDef *ll_drv;          /*!< USB LL Driver Interface Pointer            */

    //USB Class Control
    USB_ClassFuncTypeDef *cls_func;     /*!< USB Class Function Pointer                 */

    //Enum Control
    USB_EnumDescTypeDef *enum_desc;     /*!< Usb Enum Descriptor Array pointer          */
    uint8_t enum_desc_nums;             /*!< Usb Enum Descriptor Array element nums     */
    USB_EnumStrTypeDef *enum_str;       /*!< USB String Descriptor Array pointer        */
    uint8_t enum_str_nums;              /*!< USB String Descriptor Array element nums   */
    USB_EpCfgTypeDef *ep_cfg;           /*!< USB Endpoint Config Array pointer          */
    uint8_t ep_cfg_nums;                /*!< USB Endpoint Config Array element nums     */

    //USB Stand Device Request
    USB_StdDevReqTypeDef req;           /*!< USB Standard Device Request Struct         */

    //USB EP0 Send/Receive Buffer
    uint8_t recv_buf[USB_EP0_MAX_PL];   /*!< EP0 Receieve Buffer Array                  */
    uint16_t recv_len;                  /*!< EP0 Receieve Buffer Length                 */
    uint8_t *send_ptr;                  /*!< EP0 Current Send Pointer                   */
    uint16_t send_len;                  /*!< EP0 Current Send Buffer Remain Length      */

    //Misc Control
    bool need_zero_pkt;                 /*!< Need to Send 0 Length Data Packet Or Not   */
    uint8_t dev_addr;                   /*!< USB Device Address                         */
    volatile uint8_t cur_cfg_val;       /*!< USB Device Current Config Value            */
    USB_StdDevReqETypeDef enum_sta;     /*!< USB Enum Status in Standard Device Request */
} USBD_CoreCtrlTypeDef;

/**
  * @}
  */

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USBD_DEF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

