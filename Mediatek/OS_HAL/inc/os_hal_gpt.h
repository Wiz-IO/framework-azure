/*
 * (C) 2005-2019 MediaTek Inc. All rights reserved.
 *
 * Copyright Statement:
 *
 * This MT3620 driver software/firmware and related documentation
 * ("MediaTek Software") are protected under relevant copyright laws.
 * The information contained herein is confidential and proprietary to
 * MediaTek Inc. ("MediaTek"). You may only use, reproduce, modify, or
 * distribute (as applicable) MediaTek Software if you have agreed to and been
 * bound by this Statement and the applicable license agreement with MediaTek
 * ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User"). If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
 * PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS
 * ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO
 * LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED
 * HEREUNDER WILL BE ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
 * RECEIVER TO MEDIATEK DURING THE PRECEDING TWELVE (12) MONTHS FOR SUCH
 * MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __OS_HAL_GPT_H__
#define __OS_HAL_GPT_H__

#include "mhal_osai.h"
#include "mhal_gpt.h"

enum gpt_timer_id {
	GPT_ID_0 = 0,
	GPT_ID_1,
	GPT_ID_2,
	GPT_ID_3,
	GPT_ID_4,
	GPT_ID_MAX_NUM
};

struct os_gpt_int {
	void (*gpt_cb_hdl)(void *);
	void *gpt_cb_data;
};

/**
 * @brief  Start GPT timer count.
 *  @param [in] timer_id: GPT timer id
 *  @return
 *	0: Success.\n
 *	negative: Failure.\n
 */
int mtk_os_hal_gpt_start(unsigned char timer_id);

/**
 * @brief  Stop GPT timer count.
 *  @param [in] timer_id: GPT timer id
 *  @return
 *	0: Success.\n
 *	negative: Failure.\n
 */
int mtk_os_hal_gpt_stop(unsigned char timer_id);

/**
 * @brief  Get GPT timer counter value.
 *  @param [in] timer_id: GPT timer id
 *  @return
 *	32bit counter value
 */
unsigned int mtk_os_hal_gpt_get_cur_count(unsigned char timer_id);

/**
 * @brief  Restart GPT timer count.
 *  @param [in] timer_id: GPT timer id
 *  @return
 *	0: Success.\n
 *	negative: Failure.\n
 */
int mtk_os_hal_gpt_restart(unsigned char timer_id);

/**
 * @brief  Reset GPT timer mode (only works for interrupt-based timer).
 *  @param [in] timer_id: GPT timer id
 *  @param [in] count_val: GPT timeout count value
 *  @param [in] auto_repeat: open repeat mode (only works for GPT0 & GPT1)
 *  @return
 *	0: Success.\n
 *	negative: Failure.\n
 */
int mtk_os_hal_gpt_reset_timer(unsigned char timer_id,
			       unsigned int count_val,
			       bool auto_repeat);

/**
 * @brief  Config GPT timer.
 *  @param [in] timer_id: GPT timer id
 *  @param [in] speed_32us: for GPT0, GPT1 & GPT2, it is used to choose
 *	32kHz(= 1) or 1kHz(= 0); for GPT4, it is used to choose bus_clk(= 1)
 *	or half of bus_clk(= 0); and for GPT3, it has no influence.
 *  @param [in] gpt_int: a pointer of struct os_gpt_int to set interrupt
 *	callback (only works for GPT0, GPT1 & GPT3)
 *  @return
 *	0: Success.\n
 *	negative: Failure.\n
 */
int mtk_os_hal_gpt_config(unsigned char timer_id,
			  unsigned char speed_32us,
			  struct os_gpt_int *gpt_int);

/**
 * @brief  Init GPT device.
 *  @param
 *	None
 *  @return
 *	None
 *  @note
 *	Internal assurance that it will only be executed only one time
 * effectively.
 */
void mtk_os_hal_gpt_init(void);


#endif /* __OS_HAL_GPT_H__ */
