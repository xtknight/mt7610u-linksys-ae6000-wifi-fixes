/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#ifndef __MCU_AND_H__
#define __MCU_AND_H__

#include "mcu.h"

struct _RTMP_ADAPTER;

#define MCU_WAIT_ACK_CMD_THRESHOLD 0x0f
#define MCU_RX_CMD_THRESHOLD 0x0f


#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _TXINFO_NMAC_CMD_PKT{
	UINT32 info_type:2;
	UINT32 d_port:3;
	UINT32 cmd_type:7;
	UINT32 cmd_seq:4;
	UINT32 pkt_len:16;
}TXINFO_NMAC_CMD_PKT;
#else
typedef struct GNU_PACKED _TXINFO_NMAC_CMD_PKT {
	UINT32 pkt_len:16;
	UINT32 cmd_seq:4;
	UINT32 cmd_type:7;
	UINT32 d_port:3;
	UINT32 info_type:2;
}TXINFO_NMAC_CMD_PKT;
#endif /* RT_BIG_ENDIAN */

enum cmd_msg_state {
	illegal,
	tx_start,
	tx_kickout_fail,
	tx_timeout_fail,
	tx_retransmit,
	tx_done,
	wait_cmd_out,
	wait_cmd_out_and_ack,
	wait_ack,
	rx_start,
	rx_receive_fail,
	rx_done,
};

enum {
	MCU_INIT,
	MCU_TX_HALT,
	MCU_RX_HALT,
};

enum cmd_msg_error_type {
	error_tx_kickout_fail,
	error_tx_timeout_fail,
	error_rx_receive_fail,
};

struct MCU_CTRL {
	u8 cmd_seq;
	unsigned long flags;
	RTMP_NET_TASK_STRUCT cmd_msg_task;
	NDIS_SPIN_LOCK txq_lock;
	DL_LIST txq;
	NDIS_SPIN_LOCK rxq_lock;
	DL_LIST rxq;
	NDIS_SPIN_LOCK ackq_lock;
	DL_LIST ackq;
	NDIS_SPIN_LOCK kickq_lock;
	DL_LIST kickq;
	NDIS_SPIN_LOCK tx_doneq_lock;
	DL_LIST tx_doneq;
	NDIS_SPIN_LOCK rx_doneq_lock;
	DL_LIST rx_doneq;
	unsigned long tx_kickout_fail_count;
	unsigned long tx_timeout_fail_count;
	unsigned long rx_receive_fail_count;
	unsigned long alloc_cmd_msg;
	unsigned long free_cmd_msg;
};


struct cmd_msg;
typedef void (*MSG_RSP_HANDLER)(struct cmd_msg *msg, char *payload, u16 payload_len);
typedef void (*MSG_EVENT_HANDLER)(struct _RTMP_ADAPTER *ad, char *payload, u16 payload_len);

struct cmd_msg_cb {
	struct cmd_msg *msg;
};

#define USB_END_PADDING 4
#define FW_INFO_SIZE 32
#define GET_SEMAPHORE_RETRY_MAX 600
#define UPLOAD_FW_UNIT 14592
#define UPLOAD_FW_TIMEOUT 1000
#define CMD_MSG_CB(pkt) ((struct cmd_msg_cb *)(GET_OS_PKT_CB(pkt)))
#define CMD_MSG_RETRANSMIT_TIMES 3
#define CMD_MSG_TIMEOUT 500

struct cmd_msg {
	DL_LIST list;
	u8 type;
	u8 seq;
	u16 timeout;
	u16 rsp_payload_len;
	BOOLEAN need_wait;
	BOOLEAN need_rsp;
	BOOLEAN need_retransmit;
	RTMP_OS_COMPLETION ack_done; 
	char *rsp_payload;
	MSG_RSP_HANDLER rsp_handler;
	enum cmd_msg_state state;
	void *priv;
	PNDIS_PACKET net_pkt;
#ifdef RTMP_USB_SUPPORT
	PURB urb;
#endif
	int retransmit_times;
};

/*
 * Calibration ID
 */
enum CALIBRATION_ID {
	R_CALIBRATION = 1,
	RXDCOC_CALIBRATION,
	LC_CALIBRATION,
	LOFT_CALIBRATION,
	TXIQ_CALIBRATION,
	BW_CALIBRATION,
	DPD_CALIBRATION,
	RXIQ_CALIBRATION,
	TXDCOC_CALIBRATION,
	RX_GROUP_DELAY_CALIBRATION,
	TX_GROUP_DELAY_CALIBRATION,
};

enum CALIBRATION_TYPE {
	FULL_CALIBRATION,
	PARTIAL_CALIBRATION,
};

enum SWITCH_CHANNEL_STAGE {
	NORMAL_OPERATING = 0x01,
	SCANNING = 0x02,
	TEMPERATURE_CHANGE = 0x04,
};

/*
 * Function set ID
 */
enum FUN_ID {
	Q_SELECT = 1,
	BW_SETTING = 2,
};

/*
 * Command response RX Ring selection
 */
enum RX_RING_ID {
	RX_RING0,
	RX_RING1,
};

enum BW_SETTING {
	BW20 = 1,
	BW40 = 2,
	BW10 = 4,
	BW80 = 8,
};

/*
 * Command type table 
 */
enum CMD_TYPE {
	CMD_FUN_SET_OP = 1,
	CMD_BURST_WRITE = 8,
	CMD_READ_MODIFY_WRITE,
	CMD_RANDOM_READ,
	CMD_BURST_READ,
	CMD_RANDOM_WRITE = 12,
	CMD_LED_MODE_OP = 16,
	CMD_POWER_SAVING_OP = 20,
	CMD_WOW_ENTRY,
	CMD_WOW_QUERY,
	CMD_CARRIER_DETECT_OP = 28,
	CMD_RADOR_DETECT_OP,
	CMD_SWITCH_CHANNEL_OP,
	CMD_CALIBRATION_OP,
	CMD_BEACON_OP,
	CMD_ANTENNA_OP
};

/*
 * Event type table
 */
enum EVENT_TYPE {
	CMD_DONE,
	CMD_ERROR,
	CMD_RETRY,
	EVENT_PWR_RSP,
	EVENT_WOW_RSP,
	EVENT_CARRIER_DETECT_RSP,
	EVENT_DFS_DETECT_RSP,
};

enum mcu_skb_state {
	ILLEAGAL = 0,
	MCU_CMD_START,
	MCU_CMD_DONE,
	MCU_RSP_START,
	MCU_RSP_DONE,
	MCU_RSP_CLEANUP,
	UNLINK_START,
};

struct mcu_skb_data {
	enum mcu_skb_state state;
};

#ifdef RTMP_MAC_USB
NDIS_STATUS andes_usb_loadfw(struct _RTMP_ADAPTER *ad);
#endif /* RTMP_MAC_USB */
void andes_ctrl_init(struct _RTMP_ADAPTER *ad);
void andes_ctrl_enable(struct _RTMP_ADAPTER *ad);
void andes_ctrl_disable(struct _RTMP_ADAPTER *ad);
void andes_ctrl_exit(struct _RTMP_ADAPTER *ad);
int andes_send_cmd_msg(struct _RTMP_ADAPTER *ad, struct cmd_msg *msg);
int andes_burst_write(struct _RTMP_ADAPTER *ad, u32 offset, u32 *data, u32 cnt);
int andes_burst_read(struct _RTMP_ADAPTER *ad, u32 offset, u32 cnt, u32 *data);
int andes_random_read(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num);
int andes_rf_random_read(struct _RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *reg_pair, u32 num);
int andes_read_modify_write(struct _RTMP_ADAPTER *ad, R_M_W_REG *reg_pair, u32 num);
int andes_rf_read_modify_write(struct _RTMP_ADAPTER *ad, RF_R_M_W_REG *reg_pair, u32 num);
int andes_random_write(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num);
int andes_rf_random_write(struct _RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *reg_pair, u32 num);
int andes_fun_set(struct _RTMP_ADAPTER *ad, u32 fun_id, u32 param);
int andes_pwr_saving(struct _RTMP_ADAPTER *ad, u32 op, u32 level, 
					 u32 listen_interval, u32 pre_tbtt_lead_time,
					 u8 tim_byte_offset, u8 tim_byte_pattern);
int andes_calibration(struct _RTMP_ADAPTER *ad, u32 cal_id, u32 param);
int andes_led_op(struct _RTMP_ADAPTER *ad, u32 led_idx, u32 link_status);
BOOLEAN is_inband_cmd_processing(struct _RTMP_ADAPTER *ad);
void andes_cmd_msg_bh(unsigned long param);
int usb_rx_cmd_msg_submit(struct _RTMP_ADAPTER *ad);
int usb_rx_cmd_msgs_receive(struct _RTMP_ADAPTER *ad);
void andes_bh_schedule(struct _RTMP_ADAPTER *ad);
#endif
