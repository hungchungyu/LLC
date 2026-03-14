/**
  ******************************************************************************
  * @file    usbd_core.c
  * @author  MCD Application Team
  * @brief   USB Device Core driver
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
#include <string.h>
#include "usbd_core.h"


#define DBG_TAG             "USBD CORE"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @defgroup TAE_USB_DEVICE TAE USB Device
  * @brief    TAE USB Device
  * @{
  */

/** @defgroup USBD_Core USBD Core
  * @brief    USBD Core
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup USBD_Core_Private_Functions USBD Core Private Functions
  * @brief    USBD Core Private Functions
  * @{
  */
static void USBD_SetupReset(void);
__STATIC_INLINE void USBD_SetupReqProcess(void);

static void USBD_PowerSuspendCallback(USB_TypeDef *Instance);
static void USBD_PowerResumeCallback(USB_TypeDef *Instance);
static void USBD_PowerResetCallback(USB_TypeDef *Instance);
static void USBD_PowerSOFCallback(USB_TypeDef *Instance);
static void USBD_PowerDisconnCallback(USB_TypeDef *Instance);

static void USBD_DetInsertCallback(USB_TypeDef *Instance);
static void USBD_DetUnplugCallback(USB_TypeDef *Instance);

static void USBD_Ep0SetupCallback(USB_TypeDef *Instance);
static void USBD_Ep0InCallback(USB_TypeDef *Instance);
static void USBD_Ep0OutCallback(USB_TypeDef *Instance);
static void USBD_Ep1InCallback(USB_TypeDef *Instance);
static void USBD_Ep1OutCallback(USB_TypeDef *Instance);
static void USBD_Ep2InCallback(USB_TypeDef *Instance);
static void USBD_Ep2OutCallback(USB_TypeDef *Instance);

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @defgroup USBD_Core_Exported_Variables USBD Core Exported Variables
  * @brief    USBD Core Exported Variables
  * @{
  */

/**
  * @brief USBD Core USB LL Interrupt Callback Interface const Definition
  */
const USB_LL_IRQCbTypeDef usbd_core_irq_cb = {
    //Power Interrupt Callback
    .PowerSuspend = USBD_PowerSuspendCallback,
    .PowerResume  = USBD_PowerResumeCallback,
    .PowerReset   = USBD_PowerResetCallback,
    .PowerSOF     = USBD_PowerSOFCallback,
    .PowerDisconn = USBD_PowerDisconnCallback,

    //Detect Interrupt Callback
    .DetInsert = USBD_DetInsertCallback,
    .DetUnplug = USBD_DetUnplugCallback,

    //Endpoint Interrupt Callback
    .Ep0Setup  = USBD_Ep0SetupCallback,
    .EpxIn[0]  = USBD_Ep0InCallback,
    .EpxOut[0] = USBD_Ep0OutCallback,

    .EpxIn[1]  = USBD_Ep1InCallback,
    .EpxOut[1] = USBD_Ep1OutCallback,

    .EpxIn[2]  = USBD_Ep2InCallback,
    .EpxOut[2] = USBD_Ep2OutCallback,
};

/**
  * @brief USBD Core Control Global Struct Variable
  */
USBD_CoreCtrlTypeDef usb_core_ctrl;

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup USBD_Core_Exported_Functions USBD Core Exported Functions
  * @brief    USBD Core Exported Functions
  * @{
  */

/** @defgroup USBD_Core_Exported_Functions_Group1 USBD Core Init and DeInit Functions
  * @brief    USBD Core Init and DeInit Functions
  * @{
  */

/**
  * @brief  USBD Init
  * @param  core_init USBD Core Init Pointer
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_Init(USBD_CoreInitTypeDef *core_init)
{
    //Assert param
    USBD_ASSERT_PARAM(core_init != NULL);
    USBD_ASSERT_PARAM(core_init->Instance != NULL);
    USBD_ASSERT_PARAM(core_init->ll_drv != NULL);
    USBD_ASSERT_PARAM(core_init->ll_drv->EpFIFORead != NULL);
    USBD_ASSERT_PARAM(core_init->ll_drv->EpFIFOWrite != NULL);
    USBD_ASSERT_PARAM(core_init->ll_drv->SetupAddrSet != NULL);

    if (!core_init || !core_init->Instance || !core_init->ll_drv ||
        !core_init->ll_drv->EpFIFORead || !core_init->ll_drv->EpFIFOWrite || !core_init->ll_drv->SetupAddrSet) {
        return USBD_INVALID;
    }

    LOG_D("--->%s\n\n", __FUNCTION__);

    //USB Core Init
    usb_core_ctrl.Instance = core_init->Instance;
    usb_core_ctrl.ll_drv = core_init->ll_drv;

    usb_core_ctrl.cls_func = core_init->cls_func;

    usb_core_ctrl.enum_desc = core_init->enum_desc;
    usb_core_ctrl.enum_desc_nums = core_init->enum_desc_nums;
    usb_core_ctrl.enum_str = core_init->enum_str;
    usb_core_ctrl.enum_str_nums = core_init->enum_str_nums;
    usb_core_ctrl.ep_cfg = core_init->ep_cfg;
    usb_core_ctrl.ep_cfg_nums = core_init->ep_cfg_nums;

    //USB Setup Reset
    USBD_SetupReset();

    return USBD_OK;
}

/**
  * @brief  USBD DeInit
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_DeInit(void)
{
    LOG_D("--->%s\n\n", __FUNCTION__);

    //USB Setup Reset
    USBD_SetupReset();

    //USB Core DeInit
    usb_core_ctrl.Instance = NULL;
    usb_core_ctrl.ll_drv = NULL;

    usb_core_ctrl.cls_func = NULL;

    usb_core_ctrl.enum_desc = NULL;
    usb_core_ctrl.enum_desc_nums = 0;
    usb_core_ctrl.enum_str = NULL;
    usb_core_ctrl.enum_str_nums = 0;
    usb_core_ctrl.ep_cfg = NULL;
    usb_core_ctrl.ep_cfg_nums = 0;

    return USBD_OK;
}

/**
  * @}
  */


/** @defgroup USBD_Core_Exported_Functions_Group2 USBD Core Misc Functions
  * @brief    USBD Core Misc Functions
  * @{
  */

/**
  * @brief  USBD All Endpoint Disable except Endpoint 0
  * @param  None
  * @return USBD_StatusETypeDef
  */
USBD_StatusETypeDef USBD_AllEpDis(void)
{
    USB_EpCfgTypeDef ep_cfg;

    if (!usb_core_ctrl.ll_drv || !usb_core_ctrl.ll_drv->EpCfg) {
        LOG_E("USB [Invalid] Device Request.\n");
        return USBD_FAILED;
    }

    //All Endpoint Disable
    for (uint8_t i = 0; i < EP_NUMS; i++) {
        if (i == EP_NUM_0) {
            continue;
        }

        ep_cfg.ep_num = (USB_EpNumETypeDef)i;
        ep_cfg.ep_dir = EP_DIR_IN;
        usb_core_ctrl.ll_drv->EpCfg(usb_core_ctrl.Instance, &ep_cfg, false);
        ep_cfg.ep_dir = EP_DIR_OUT;
        usb_core_ctrl.ll_drv->EpCfg(usb_core_ctrl.Instance, &ep_cfg, false);
    }

    return USBD_OK;
}

/**
  * @brief  Judge is USBD Core Enum Finish or not
  * @param  None
  * @retval False Enum isn't Finished
  * @retval True  Enum is Finished
  */
bool USBD_IsEnumFinish(void)
{
    return (bool)usb_core_ctrl.cur_cfg_val;
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup USBD_Core_Private_Functions
  * @{
  */

/** @defgroup USBD_Core_Private_Functions_Group1 USBD Core Private Misc Functions
  * @brief    USBD Core Private Misc Functions
  * @{
  */

/**
  * @brief  USBD Setup Reset
  * @param  None
  * @return None
  */
static void USBD_SetupReset(void)
{
    //All Endpoint Disable and Address reset to 0
    USBD_AllEpDis();

    if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupAddrSet) {
        usb_core_ctrl.ll_drv->SetupAddrSet(usb_core_ctrl.Instance, 0x00);
    }

    //Setup Process Relative Control Variables Reset
    memset((void *)&usb_core_ctrl.req, 0, sizeof(usb_core_ctrl.req));
    memset((void *)usb_core_ctrl.recv_buf, 0, sizeof(usb_core_ctrl.recv_buf));
    usb_core_ctrl.recv_len = 0;
    usb_core_ctrl.send_ptr = NULL;
    usb_core_ctrl.send_len = 0;

    usb_core_ctrl.need_zero_pkt = false;
    usb_core_ctrl.dev_addr = 0x00;
    usb_core_ctrl.cur_cfg_val = 0;
    usb_core_ctrl.enum_sta = STD_REQ_INVALID;
}

/**
  * @brief  USBD Setup Request Process
  * @param  None
  * @return None
  */
__STATIC_INLINE void USBD_SetupReqProcess(void)
{
    uint8_t req_dir, req_type;
    USBD_StatusETypeDef ret = USBD_FAILED;

    req_dir  = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_DIR_BITMASK)  >> USB_STD_DEV_REQ_DIR_BIT;
    req_type = (usb_core_ctrl.req.bmRequestType & USB_STD_DEV_REQ_TYPE_BITMASK) >> USB_STD_DEV_REQ_TYPE_BIT;

    if (req_dir == USB_STD_DEV_REQ_DIR_OUT) {
        usb_core_ctrl.recv_len = usb_core_ctrl.req.wLength;
    }

    switch (req_type) {
        case USB_STD_DEV_REQ_TYPE_STD:      //Request Type: [Standard]
            LOG_D("USB [Standard] Device Request.\n");
            usb_core_ctrl.enum_sta = (USB_StdDevReqETypeDef)usb_core_ctrl.req.bRequest;
            ret = USBD_StdDevReqProcess();
            break;

        case USB_STD_DEV_REQ_TYPE_CLASS:    //Request Type: [Class]
            LOG_D("USB [Class] Device Request.\n");

            if (usb_core_ctrl.cls_func && usb_core_ctrl.cls_func->Setup) {
                ret = usb_core_ctrl.cls_func->Setup(&usb_core_ctrl.req);
            }

            break;

        case USB_STD_DEV_REQ_TYPE_MAN:      //Request Type: [Manufacturer]
            LOG_D("USB [Manufacturer] Device Request.\n");
            //:TODO: Manufacturer Request Process
            break;

        case USB_STD_DEV_REQ_TYPE_RSV:      //Request Type: [Reserved]
            LOG_D("USB [Reserved] Device Request.\n");
            break;

        default:
            LOG_E("USB [Invalid] Device Request.\n");
            ret = USBD_ERROR;
            break;
    }

    if (ret != USBD_OK) {
        if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupStallSet) {
            usb_core_ctrl.ll_drv->SetupStallSet(usb_core_ctrl.Instance);
        }

        usb_core_ctrl.enum_sta = STD_REQ_INVALID;
    }
}

/**
  * @}
  */


/** @defgroup USBD_Core_Private_Functions_Group2 USBD Core Power Interrupt Callback Functions
  * @brief    USBD Core Power Interrupt Callback Functions
  * @{
  */

/**
  * @brief  USBD Power Suspend Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_PowerSuspendCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD-POWER [Suspend] INT\n");
}

/**
  * @brief  USBD Power Resume Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_PowerResumeCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD-POWER [Resume] INT\n");
}

/**
  * @brief  USBD Power Reset Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_PowerResetCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_R("USBD-POWER [Reset] INT\n");
    USBD_SetupReset();
}

/**
  * @brief  USBD Power SOF Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_PowerSOFCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD-POWER [SOF] INT\n");
}

/**
  * @brief  USBD Power Peripheral Disconnect Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_PowerDisconnCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD-POWER [Disconnect] INT\n");
}

/**
  * @}
  */


/** @defgroup USBD_Core_Private_Functions_Group3 USBD Core Detect Interrupt Callback Functions
  * @brief    USBD Core Detect Interrupt Callback Functions
  * @{
  */

/**
  * @brief  USBD Detect Insert Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_DetInsertCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_R("USBD-Detect [Insert] INT\n");
}

/**
  * @brief  USBD Detect Unplug Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_DetUnplugCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_R("USBD-Detect [Unplug] INT\n");

    if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupAddrSet) {
        usb_core_ctrl.ll_drv->SetupAddrSet(usb_core_ctrl.Instance, 0x00);
    }

    USBD_AllEpDis();
    USBD_SetupReset();
}

/**
  * @}
  */


/** @defgroup USBD_Core_Private_Functions_Group4 USBD Core Endpoint Interrupt Callback Functions
  * @brief    USBD Core Endpoint Interrupt Callback Functions
  * @{
  */

/**
  * @brief  USBD Endpoint 0 Setup Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep0SetupCallback(USB_TypeDef *Instance)
{
    uint8_t ep0_req_cmd_buf[USB_STD_DEV_REQ_CMD_LEN];

    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance && usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->EpFIFORead, (void)0U, return);
    LOG_D("USBD EP0 [Setup] INT\n");

    usb_core_ctrl.ll_drv->EpFIFORead(usb_core_ctrl.Instance, EP_NUM_0, ep0_req_cmd_buf, USB_STD_DEV_REQ_CMD_LEN);
    USBD_SetupReqParse(&usb_core_ctrl.req, ep0_req_cmd_buf);

    //USB Standard Device Request Process
    USBD_SetupReqProcess();
}

/**
  * @brief  USBD Endpoint 0 In Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep0InCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD EP0 [IN] INT\n");

    if (usb_core_ctrl.enum_sta == SET_ADDRESS) {
        if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupAddrSet) {
            usb_core_ctrl.ll_drv->SetupAddrSet(usb_core_ctrl.Instance, usb_core_ctrl.dev_addr);
        }
    } else if (usb_core_ctrl.enum_sta == STD_REQ_INVALID) {
        if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupStallClr) {
            usb_core_ctrl.ll_drv->SetupStallClr(usb_core_ctrl.Instance);
        }
    } else {
        //Send remain data in Ep0 IN Interrupt
        USBD_Ep0SendData();
    }
}

/**
  * @brief  USBD Endpoint 0 Out Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep0OutCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);
    LOG_D("USBD EP0 [Out] INT\n");

    if (usb_core_ctrl.enum_sta == STD_REQ_INVALID) {
        if (usb_core_ctrl.ll_drv && usb_core_ctrl.ll_drv->SetupStallClr) {
            usb_core_ctrl.ll_drv->SetupStallClr(usb_core_ctrl.Instance);
        }
    } else {
        //Receive data in Ep0 OUT Interrupt
        USBD_Ep0ReceiveData();
    }
}

/**
  * @brief  USBD Endpoint 1 In Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep1InCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);

    LOG_D("USBD EP1 [IN] INT\n");
    USBD_FUNC_ALTER(usb_core_ctrl.cls_func && usb_core_ctrl.cls_func->DataIn, usb_core_ctrl.cls_func->DataIn(EP_NUM_1), (void)0U);
}

/**
  * @brief  USBD Endpoint 1 Out Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep1OutCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);

    LOG_D("USBD EP1 [OUT] INT\n");
    USBD_FUNC_ALTER(usb_core_ctrl.cls_func && usb_core_ctrl.cls_func->DataOut, usb_core_ctrl.cls_func->DataOut(EP_NUM_1), (void)0U);
}

/**
  * @brief  USBD Endpoint 2 In Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep2InCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);

    LOG_D("USBD EP2 [IN] INT\n");
    USBD_FUNC_ALTER(usb_core_ctrl.cls_func && usb_core_ctrl.cls_func->DataIn, usb_core_ctrl.cls_func->DataIn(EP_NUM_2), (void)0U);
}

/**
  * @brief  USBD Endpoint 2 Out Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
static void USBD_Ep2OutCallback(USB_TypeDef *Instance)
{
    USBD_FUNC_ALTER(Instance == usb_core_ctrl.Instance, (void)0U, return);

    LOG_D("USBD EP2 [OUT] INT\n");
    USBD_FUNC_ALTER(usb_core_ctrl.cls_func && usb_core_ctrl.cls_func->DataOut, usb_core_ctrl.cls_func->DataOut(EP_NUM_2), (void)0U);
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

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

