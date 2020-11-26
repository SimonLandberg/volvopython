/********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * http://www.rt-labs.com
 * Copyright 2019 rt-labs AB, Sweden.
 * See LICENSE file in the project root for full license information.
 ********************************************************************/

/**
 * \addtogroup can_diag_handler CAN diag handler
 * \{
 * Common CAN diagnostic functions used in application.
 */

#ifndef _CAN_DIAG_HANDLER_H_
#define _CAN_DIAG_HANDLER_H_

#include <stdio.h>
#include <stdbool.h>
#include "ecu_unit.h"
#include "pf.h"

/** CAN diag requests */
typedef enum can_diag_cmd_req
{
   DiagReq_CheckActiveFmi = 0,
   DiagReq_ClearAllFmi = 1,
   DiagReq_GetHwPartNo = 2,
   DiagReq_GetHwSerial = 3,
   DiagReq_GetStm8Ver = 4,
   DiagReq_GetBootPartNo = 5,
   DiagReq_GetMswPartNo = 6,
   DiagReq_GetDstPartNo = 7,
   DiagReq_Reserved1 = 8,
   DiagReq_Reserved2 = 9,
   DiagReq_Reserved3 = 10,
   DiagReq_Reserved4 = 11,
   DiagReq_Reserved5 = 12,
   DiagReq_Reserved6 = 13,
   DiagReq_Reserved7 = 14,
   DiagReq_Reserved8 = 15,
} can_diag_cmd_req_t;

/** CAN diag response */
typedef enum can_diag_reply_rsp
{
   DiagRsp_FmiActive = 0,
   DiagRsp_NoActiveFmi = 1,
   DiagRsp_FmiClearOk = 2,
   DiagRsp_HwPartNo = 3,
   DiagRsp_HwSerial = 4,
   DiagRsp_Stm8Ver = 5,
   DiagRsp_BootPartNo = 6,
   DiagRsp_MswPartNo = 7,
   DiagRsp_DstPartNo = 8,
   DiagRsp_Reserved1 = 9,
   DiagRsp_Reserved2 = 10,
   DiagRsp_Reserved3 = 11,
   DiagRsp_Reserved4 = 12,
   DiagRsp_Reserved5 = 13,
   DiagRsp_Error = 14,
   DiagRsp_NotAvailable = 15,
} can_diag_reply_rsp_t;

/** CAN diag reply */
typedef struct __attribute__((__packed__))
{
   unsigned diagrsp:4;           /**< CAN diagreply response */
   uint64_t reserved1:60;        /**< CAN diagreply reserved */
} can_diag_handler_diagreply_t;

/** CAN diag data */
typedef struct __attribute__((__packed__))
{
   uint64_t diagdata;            /**< CAN diag data */
} can_diag_handler_diagdata_t;

/**
 * Handle received CAN diag request.
 *
 * \param req        CAN diag request received.
 */
void can_diag_handler (can_diag_cmd_req_t req);

void can_diag_set_sw_pn_callback(const char * (*callback)(part_number_t pn_type));
void can_diag_set_hw_pn_callback(const char * (*callback)(part_number_t pn_type));
void can_diag_set_reply_callback
   (void (*callback)(can_ecu_id_t can_id, diag_reply_t diag_reply, void * data));

#endif /* _CAN_DIAG_HANDLER_H_ */

/**
 * \}
 */
