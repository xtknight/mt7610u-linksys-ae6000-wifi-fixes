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


#include	"rt_config.h"


#ifdef RTMP_MAC_USB
VOID usb_uploadfw_complete(purbb_t urb, pregs *pt_regs)
{
	RTMP_OS_COMPLETION *load_fw_done = (RTMP_OS_COMPLETION *)RTMP_OS_USB_CONTEXT_GET(urb);

	RTMP_OS_COMPLETE(load_fw_done);
}

static NDIS_STATUS usb_load_ivb(RTMP_ADAPTER *ad)
{
	NDIS_STATUS Status = NDIS_STATUS_SUCCESS;
	RTMP_CHIP_CAP *cap = &ad->chipCap;


	if (cap->load_iv) {
		Status = RTUSB_VendorRequest(ad,
									 USBD_TRANSFER_DIRECTION_OUT,
									 DEVICE_VENDOR_REQUEST_OUT,
									 0x01,
									 0x12,
									 0x00,
									 cap->FWImageName + 32,
									 64);
	} else {
		Status = RTUSB_VendorRequest(ad,
									 USBD_TRANSFER_DIRECTION_OUT,
									 DEVICE_VENDOR_REQUEST_OUT,
									 0x01,
									 0x12,
									 0x00,
									 NULL,
									 0x00);

	}

	if (Status)
	{
			DBGPRINT(RT_DEBUG_ERROR, ("Upload IVB Fail\n"));
			return Status;
	}

	return Status;
}

NDIS_STATUS andes_usb_loadfw(RTMP_ADAPTER *ad)
{
	PURB urb;
	POS_COOKIE obj = (POS_COOKIE)ad->OS_Cookie;
	ra_dma_addr_t fw_dma;
	PUCHAR fw_data;
	TXINFO_NMAC_CMD *tx_info;	
	s32 sent_len;
	u32 cur_len = 0;
	u32 mac_value, loop = 0;
	u16 value;
	int ret = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	USB_DMA_CFG_STRUC cfg;
	u32 ilm_len = 0, dlm_len = 0;
	u16 fw_ver, build_ver;
	RTMP_OS_COMPLETION load_fw_done;
	USB_DMA_CFG_STRUC UsbCfg;

	RtmpOsMsDelay(5);

	if (!cap->FWImageName)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s:Please assign a fw image\n", __FUNCTION__));
		return NDIS_STATUS_FAILURE;
	}

	if (cap->IsComboChip)
	{
loadfw_protect:
		RTUSBReadMACRegister(ad, SEMAPHORE_00, &mac_value);
		loop++;

		if (((mac_value & 0x01) == 0) && (loop < GET_SEMAPHORE_RETRY_MAX)) {
			RtmpOsMsDelay(1);
			goto loadfw_protect;
		}

		if (loop >= GET_SEMAPHORE_RETRY_MAX) {
			DBGPRINT(RT_DEBUG_ERROR, ("%s: can not get the hw semaphore\n"));
			return NDIS_STATUS_FAILURE;
		}
	}
	
	RTUSBWriteMACRegister(ad, 0x1004, 0x2c, FALSE);

	/* Enable USB_DMA_CFG */
	USB_CFG_READ(ad, &UsbCfg.word);
	UsbCfg.field.RxBulkAggTOut = 0x20;
	UsbCfg.field.TxBulkEn = 1;
	UsbCfg.field.RxBulkEn = 1;
	USB_CFG_WRITE(ad, UsbCfg.word);
	//USB_CFG_WRITE(ad, 0x00c00020);

	/* Check MCU if ready */
	RTUSBReadMACRegister(ad, COM_REG0, &mac_value);

	if (((mac_value & 0x01) == 0x01) && (cap->IsComboChip)) {
		goto error0;
	}

	RTUSBVenderReset(ad);
	RtmpOsMsDelay(5);

	/* Get FW information */
	ilm_len = (*(cap->FWImageName + 3) << 24) | (*(cap->FWImageName + 2) << 16) |
			 (*(cap->FWImageName + 1) << 8) | (*cap->FWImageName);

	dlm_len = (*(cap->FWImageName + 7) << 24) | (*(cap->FWImageName + 6) << 16) |
			 (*(cap->FWImageName + 5) << 8) | (*(cap->FWImageName + 4));

	fw_ver = (*(cap->FWImageName + 11) << 8) | (*(cap->FWImageName + 10));

	build_ver = (*(cap->FWImageName + 9) << 8) | (*(cap->FWImageName + 8));
	
	DBGPRINT(RT_DEBUG_OFF, ("fw version:%d.%d.%02d ", (fw_ver & 0xf000) >> 8,
						(fw_ver & 0x0f00) >> 8, fw_ver & 0x00ff));
	DBGPRINT(RT_DEBUG_OFF, ("build:%x\n", build_ver));
	DBGPRINT(RT_DEBUG_OFF, ("build time:"));

	for (loop = 0; loop < 16; loop++)
		DBGPRINT(RT_DEBUG_OFF, ("%c", *(cap->FWImageName + 16 + loop)));

	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("ilm length = %d(bytes)\n", ilm_len));
	DBGPRINT(RT_DEBUG_OFF, ("dlm length = %d(bytes)\n", dlm_len));

	/* Enable FCE */
	RTUSBWriteMACRegister(ad, FCE_PSE_CTRL, 0x01, FALSE);

	/* FCE tx_fs_base_ptr */
	RTUSBWriteMACRegister(ad, TX_CPU_PORT_FROM_FCE_BASE_PTR, 0x400230, FALSE);

	/* FCE tx_fs_max_cnt */
	RTUSBWriteMACRegister(ad, TX_CPU_PORT_FROM_FCE_MAX_COUNT, 0x01, FALSE); 

	/* FCE pdma enable */
	RTUSBWriteMACRegister(ad, FCE_PDMA_GLOBAL_CONF, 0x44, FALSE);  

	/* FCE skip_fs_en */
	RTUSBWriteMACRegister(ad, FCE_SKIP_FS, 0x03, FALSE);

	if (IS_MT76x0(ad)) {
		USB_CFG_READ(ad, &cfg.word);

		cfg.field.UDMA_TX_WL_DROP = 1;

		USB_CFG_WRITE(ad, cfg.word);		

		cfg.field.UDMA_TX_WL_DROP = 0;

		USB_CFG_WRITE(ad, cfg.word);
	}
		
	/* Allocate URB */
	urb = RTUSB_ALLOC_URB(0);

	if (!urb)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("can not allocate URB\n"));
		ret = NDIS_STATUS_RESOURCES; 
		goto error0;
	}

	/* Allocate TransferBuffer */
	fw_data = RTUSB_URB_ALLOC_BUFFER(obj->pUsb_Dev, UPLOAD_FW_UNIT, &fw_dma);
		
	if (!fw_data)
	{
		ret = NDIS_STATUS_RESOURCES;
		goto error1;
	}

	DBGPRINT(RT_DEBUG_OFF, ("loading fw"));
	
	RTMP_OS_INIT_COMPLETION(&load_fw_done);

	if (cap->load_iv)
		cur_len = 0x40;
	else
		cur_len = 0x00;

	/* Loading ILM */
	while (1)
	{
		s32 sent_len_max = UPLOAD_FW_UNIT - sizeof(*tx_info) - USB_END_PADDING;	
		sent_len = (ilm_len - cur_len) >=  sent_len_max ? sent_len_max : (ilm_len - cur_len);

		if (sent_len > 0)
		{
			tx_info = (TXINFO_NMAC_CMD *)fw_data;
			tx_info->info_type = CMD_PACKET;
			tx_info->pkt_len = sent_len;
			tx_info->d_port = CPU_TX_PORT;

#ifdef RT_BIG_ENDIAN
			RTMPDescriptorEndianChange((PUCHAR)tx_info, TYPE_TXINFO);
#endif
			NdisMoveMemory(fw_data + sizeof(*tx_info), cap->FWImageName + FW_INFO_SIZE + cur_len, sent_len);

			/* four zero bytes for end padding */	
			NdisZeroMemory(fw_data + sizeof(*tx_info) + sent_len, USB_END_PADDING);

			value = (cur_len + cap->ilm_offset) & 0xFFFF;

			/* Set FCE DMA descriptor */
			ret = RTUSB_VendorRequest(ad,
										 USBD_TRANSFER_DIRECTION_OUT,
										 DEVICE_VENDOR_REQUEST_OUT,
										 0x42,
										 value,
										 0x230,
										 NULL,
										 0);


			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma descriptor fail\n"));
				goto error2;
			}
			
			value = (((cur_len + cap->ilm_offset) & 0xFFFF0000) >> 16);

			/* Set FCE DMA descriptor */
			ret = RTUSB_VendorRequest(ad,
										 USBD_TRANSFER_DIRECTION_OUT,
										 DEVICE_VENDOR_REQUEST_OUT,
										 0x42,
										 value,
										 0x232,
										 NULL,
										 0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma descriptor fail\n"));
				goto error2;
			}

			

			cur_len += sent_len;

			while ((sent_len % 4) != 0)
				sent_len++;

			value = ((sent_len << 16) & 0xFFFF);

			/* Set FCE DMA length */
			ret = RTUSB_VendorRequest(ad,
										 USBD_TRANSFER_DIRECTION_OUT,
										 DEVICE_VENDOR_REQUEST_OUT,
										 0x42,
										 value,
										 0x234,
										 NULL,
										 0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma length fail\n"));
				goto error2;
			}
			
			value = (((sent_len << 16) & 0xFFFF0000) >> 16);

			/* Set FCE DMA length */
			ret = RTUSB_VendorRequest(ad,
										 USBD_TRANSFER_DIRECTION_OUT,
										 DEVICE_VENDOR_REQUEST_OUT,
										 0x42,
										 value,
										 0x236,
										 NULL,
										 0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma length fail\n"));
				goto error2;
			}
		
			/* Initialize URB descriptor */
			RTUSB_FILL_HTTX_BULK_URB(urb,
									 obj->pUsb_Dev,
									 cap->CommandBulkOutAddr,
									 fw_data,
									 sent_len + sizeof(*tx_info) + USB_END_PADDING,
									 (usb_complete_t) usb_uploadfw_complete,
									 &load_fw_done,
									 fw_dma);

			ret = RTUSB_SUBMIT_URB(urb);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("submit urb fail\n"));
				goto error2;
			}

			if (!RTMP_OS_WAIT_FOR_COMPLETION_TIMEOUT(&load_fw_done, RTMPMsecsToJiffies(UPLOAD_FW_TIMEOUT)))
			{
				RTUSB_UNLINK_URB(urb);
				ret = NDIS_STATUS_FAILURE;
				DBGPRINT(RT_DEBUG_ERROR, ("upload fw timeout(%dms)\n", UPLOAD_FW_TIMEOUT));
				DBGPRINT(RT_DEBUG_ERROR, ("%s: submit urb, sent_len = %d, ilm_ilm = %d, cur_len = %d\n", __FUNCTION__, sent_len, ilm_len, cur_len));
	
				goto error2;
			}
			DBGPRINT(RT_DEBUG_OFF, ("."));

			RTUSBReadMACRegister(ad, TX_CPU_PORT_FROM_FCE_CPU_DESC_INDEX, &mac_value);
			mac_value++;
			RTUSBWriteMACRegister(ad, TX_CPU_PORT_FROM_FCE_CPU_DESC_INDEX, mac_value, FALSE);
	
			RtmpOsMsDelay(5);
		}
		else
		{
			break;
		}		

	}
	
	RTMP_OS_EXIT_COMPLETION(&load_fw_done);
	
	/* Re-Initialize completion */
	RTMP_OS_INIT_COMPLETION(&load_fw_done);
	
	cur_len = 0x00;

	/* Loading DLM */
	while (1)
	{
		s32 sent_len_max = UPLOAD_FW_UNIT - sizeof(*tx_info) - USB_END_PADDING;	
		sent_len = (dlm_len - cur_len) >= sent_len_max ? sent_len_max : (dlm_len - cur_len);

		if (sent_len > 0)
		{
			tx_info = (TXINFO_NMAC_CMD *)fw_data;
			tx_info->info_type = CMD_PACKET;
			tx_info->pkt_len = sent_len;
			tx_info->d_port = CPU_TX_PORT;

#ifdef RT_BIG_ENDIAN
			RTMPDescriptorEndianChange((PUCHAR)tx_info, TYPE_TXINFO);
#endif
			NdisMoveMemory(fw_data + sizeof(*tx_info), cap->FWImageName + FW_INFO_SIZE + ilm_len + cur_len, sent_len);
	
			NdisZeroMemory(fw_data + sizeof(*tx_info) + sent_len, USB_END_PADDING);

			value = ((cur_len + cap->dlm_offset) & 0xFFFF);

			/* Set FCE DMA descriptor */
			ret = RTUSB_VendorRequest(ad,
										 USBD_TRANSFER_DIRECTION_OUT,
										 DEVICE_VENDOR_REQUEST_OUT,
										 0x42,
										 value,
										 0x230,
										 NULL,
										 0);


			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma descriptor fail\n"));
				goto error2;
			}
			
			value = (((cur_len + cap->dlm_offset) & 0xFFFF0000) >> 16);

			/* Set FCE DMA descriptor */
			ret = RTUSB_VendorRequest(ad,
									  USBD_TRANSFER_DIRECTION_OUT,
									  DEVICE_VENDOR_REQUEST_OUT,
									  0x42,
									  value,
									  0x232,
									  NULL,
									  0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma descriptor fail\n"));
				goto error2;
			}

			

			cur_len += sent_len;

			while ((sent_len % 4) != 0)
				sent_len++;

			value = ((sent_len << 16) & 0xFFFF);

			/* Set FCE DMA length */
			ret = RTUSB_VendorRequest(ad,
									  USBD_TRANSFER_DIRECTION_OUT,
									  DEVICE_VENDOR_REQUEST_OUT,
									  0x42,
									  value,
									  0x234,
									  NULL,
									  0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma length fail\n"));
				goto error2;
			}
			
			value = (((sent_len << 16) & 0xFFFF0000) >> 16);

			/* Set FCE DMA length */
			ret = RTUSB_VendorRequest(ad,
								  	  USBD_TRANSFER_DIRECTION_OUT,
									  DEVICE_VENDOR_REQUEST_OUT,
									  0x42,
									  value,
									  0x236,
									  NULL,
									  0);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("set fce dma length fail\n"));
				goto error2;
			}
		
			/* Initialize URB descriptor */
			RTUSB_FILL_HTTX_BULK_URB(urb,
									 obj->pUsb_Dev,
									 cap->CommandBulkOutAddr,
									 fw_data,
									 sent_len + sizeof(*tx_info) + USB_END_PADDING,
									 (usb_complete_t) usb_uploadfw_complete,
									 &load_fw_done,
									 fw_dma);

			ret = RTUSB_SUBMIT_URB(urb);

			if (ret)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("submit urb fail\n"));
				goto error2;
			}

			if (!RTMP_OS_WAIT_FOR_COMPLETION_TIMEOUT(&load_fw_done, RTMPMsecsToJiffies(UPLOAD_FW_TIMEOUT)))
			{
				RTUSB_UNLINK_URB(urb);
				ret = NDIS_STATUS_FAILURE;
				DBGPRINT(RT_DEBUG_ERROR, ("upload fw timeout(%dms)\n", UPLOAD_FW_TIMEOUT));
				DBGPRINT(RT_DEBUG_INFO, ("%s: submit urb, sent_len = %d, dlm_len = %d, cur_len = %d\n", __FUNCTION__, sent_len, dlm_len, cur_len));
	
				goto error2;
			}
			DBGPRINT(RT_DEBUG_OFF, ("."));

			RTUSBReadMACRegister(ad, TX_CPU_PORT_FROM_FCE_CPU_DESC_INDEX, &mac_value);
			mac_value++;
			RTUSBWriteMACRegister(ad, TX_CPU_PORT_FROM_FCE_CPU_DESC_INDEX, mac_value, FALSE);
			RtmpOsMsDelay(5);
		}
		else
		{
			break;
		}		

	}

	RTMP_OS_EXIT_COMPLETION(&load_fw_done);

	/* Upload new 64 bytes interrupt vector or reset andes */
	DBGPRINT(RT_DEBUG_OFF, ("\n"));
	usb_load_ivb(ad);

	/* Check MCU if ready */
	loop = 0;
	do
	{
		RTUSBReadMACRegister(ad, COM_REG0, &mac_value);
		if ((mac_value & 0x01) == 0x01)
			break;
		RtmpOsMsDelay(10);
		loop++;
	} while (loop <= 100);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: COM_REG0(0x%x) = 0x%x\n", __FUNCTION__, COM_REG0, mac_value));

	if ((mac_value & 0x01) != 0x01)
		ret = NDIS_STATUS_FAILURE;

error2:
	/* Free TransferBuffer */
	RTUSB_URB_FREE_BUFFER(obj->pUsb_Dev, UPLOAD_FW_UNIT, fw_data, fw_dma);

error1:
	/* Free URB */
	RTUSB_FREE_URB(urb);

error0: 
	if (cap->IsComboChip)
		RTUSBWriteMACRegister(ad, SEMAPHORE_00, 0x1, FALSE);

	RTUSBWriteMACRegister(ad, FCE_PSE_CTRL, 0x01, FALSE);

	return ret;
}
#endif

static struct cmd_msg *andes_alloc_cmd_msg(RTMP_ADAPTER *ad, unsigned int length)
{
	struct cmd_msg *msg = NULL;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
#ifdef RTMP_USB_SUPPORT
	PURB urb = NULL;
#endif

	PNDIS_PACKET net_pkt = RTMP_AllocateFragPacketBuffer(ad, cap->cmd_header_len + length + cap->cmd_padding_len);

	if (!net_pkt) {
		DBGPRINT(RT_DEBUG_ERROR, ("can not allocate net_pkt\n"));
		goto error0;
	}

	OS_PKT_RESERVE(net_pkt, cap->cmd_header_len);

	os_alloc_mem(NULL, (PUCHAR *)&msg, sizeof(*msg));

	if (!msg) {
		DBGPRINT(RT_DEBUG_ERROR, ("can not allocate cmd msg\n"));
		goto error1;
	}

	CMD_MSG_CB(net_pkt)->msg = msg;

	memset(msg, 0x00, sizeof(*msg));
	
#ifdef RTMP_USB_SUPPORT
	urb = RTUSB_ALLOC_URB(0);

	if (!urb) {
		DBGPRINT(RT_DEBUG_ERROR, ("can not allocate urb\n"));
		goto error2;
	}

	msg->urb = urb;
#endif

	msg->priv = (void *)ad;
	msg->net_pkt = net_pkt;

	ctl->alloc_cmd_msg++;
	
	return msg;

error2:
	os_free_mem(NULL, msg);
error1:
	RTMPFreeNdisPacket(ad, net_pkt);
error0:
	return NULL;
}

static void andes_init_cmd_msg(struct cmd_msg *msg, u8 type, BOOLEAN need_wait, u16 timeout, 
							   BOOLEAN need_retransmit, BOOLEAN need_rsp, u16 rsp_payload_len, 
							   char *rsp_payload, MSG_RSP_HANDLER rsp_handler)
{
	msg->type = type;
	msg->need_wait= need_wait;
	msg->timeout = timeout;

	if (need_wait)
		RTMP_OS_INIT_COMPLETION(&msg->ack_done);
	
	msg->need_retransmit = FALSE;

	if (need_retransmit)
		msg->retransmit_times = CMD_MSG_RETRANSMIT_TIMES;
	
	msg->need_rsp = need_rsp;
	msg->rsp_payload_len = rsp_payload_len;
	msg->rsp_payload = rsp_payload;
	msg->rsp_handler = rsp_handler;
}

static void andes_append_cmd_msg(struct cmd_msg *msg, char *data, unsigned int len)
{
	PNDIS_PACKET net_pkt = msg->net_pkt;

	if (data)
		memcpy(OS_PKT_TAIL_BUF_EXTEND(net_pkt, len), data, len);
}

void andes_free_cmd_msg(struct cmd_msg *msg)
{
	PNDIS_PACKET net_pkt = msg->net_pkt;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)(msg->priv);
	struct MCU_CTRL *ctl = &ad->MCUCtrl;

	if (msg->need_wait)
		RTMP_OS_EXIT_COMPLETION(&msg->ack_done);

#ifdef RTMP_USB_SUPPORT
	RTUSB_FREE_URB(msg->urb);
#endif

	os_free_mem(NULL, msg);
	
	RTMPFreeNdisPacket(ad, net_pkt);
	ctl->free_cmd_msg++;
}

BOOLEAN is_inband_cmd_processing(RTMP_ADAPTER *ad)
{
	BOOLEAN ret = 0;

	return ret;
}

UCHAR get_cmd_rsp_num(RTMP_ADAPTER *ad)
{
	UCHAR Num = 0;

	return Num;
}

static inline void andes_inc_error_count(struct MCU_CTRL *ctl, enum cmd_msg_error_type type)
{
	if (OS_TEST_BIT(MCU_INIT, &ctl->flags)) {
		switch (type) {
			case error_tx_kickout_fail:
				ctl->tx_kickout_fail_count++;
			break;
			case error_tx_timeout_fail:
				ctl->tx_timeout_fail_count++;
			break;
			case error_rx_receive_fail:
				ctl->rx_receive_fail_count++;
			break;
			default:
				DBGPRINT(RT_DEBUG_ERROR, ("%s:unknown cmd_msg_error_type(%d)\n", __FUNCTION__, type));
		}
	}
}

static NDIS_SPIN_LOCK *andes_get_spin_lock(struct MCU_CTRL *ctl, DL_LIST *list)
{
	NDIS_SPIN_LOCK *lock = NULL;

	if (list == &ctl->txq)
		lock = &ctl->txq_lock;
	else if (list == &ctl->rxq)
		lock = &ctl->rxq_lock;
	else if (list == &ctl->ackq)
		lock = &ctl->ackq_lock;
	else if (list == &ctl->kickq)
		lock = &ctl->kickq_lock;
	else if (list == &ctl->tx_doneq)
		lock = &ctl->tx_doneq_lock;
	else if (list == &ctl->rx_doneq)
		lock = &ctl->rx_doneq_lock;
	else
		DBGPRINT(RT_DEBUG_ERROR, ("%s:illegal list\n", __FUNCTION__));

	return lock;
} 

static inline UCHAR andes_get_cmd_msg_seq(RTMP_ADAPTER *ad)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	struct cmd_msg *msg;

	RTMP_SPIN_LOCK_IRQ(&ctl->ackq_lock);
get_seq:
	ctl->cmd_seq >= 0xf ? ctl->cmd_seq = 1 : ctl->cmd_seq++;
	DlListForEach(msg, &ctl->ackq, struct cmd_msg, list) {
		if (msg->seq == ctl->cmd_seq) {
			DBGPRINT(RT_DEBUG_ERROR, ("command(seq: %d) is still running\n", ctl->cmd_seq));
			DBGPRINT(RT_DEBUG_ERROR, ("command response nums = %d\n", get_cmd_rsp_num(ad)));
			goto get_seq;
		}
	}
	RTMP_SPIN_UNLOCK_IRQ(&ctl->ackq_lock);

	return ctl->cmd_seq;
}

static void _andes_queue_tail_cmd_msg(DL_LIST *list, struct cmd_msg *msg, 
										enum cmd_msg_state state)
{
	msg->state = state;
	DlListAddTail(list, &msg->list);
}

static void andes_queue_tail_cmd_msg(DL_LIST *list, struct cmd_msg *msg,
										enum cmd_msg_state state)
{
	unsigned long flags;
	NDIS_SPIN_LOCK *lock;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)msg->priv;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	
	lock = andes_get_spin_lock(ctl, list);

	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	_andes_queue_tail_cmd_msg(list, msg, state);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

static void _andes_queue_head_cmd_msg(DL_LIST *list, struct cmd_msg *msg, 
										enum cmd_msg_state state)
{
	msg->state = state;
	DlListAdd(list, &msg->list);
}

static void andes_queue_head_cmd_msg(DL_LIST *list, struct cmd_msg *msg,
										enum cmd_msg_state state)
{
	unsigned long flags;
	NDIS_SPIN_LOCK *lock;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)msg->priv;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	
	lock = andes_get_spin_lock(ctl, list);

	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);	
	_andes_queue_head_cmd_msg(list, msg, state);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

static u32 andes_queue_len(struct MCU_CTRL *ctl, DL_LIST *list)
{
	u32 qlen;
	unsigned long flags;
	NDIS_SPIN_LOCK *lock;
	
	lock = andes_get_spin_lock(ctl, list);
	
	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	qlen = DlListLen(list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);

	return qlen;
}

static int andes_queue_empty(struct MCU_CTRL *ctl, DL_LIST *list)
{
	unsigned long flags;
	int is_empty;
	NDIS_SPIN_LOCK *lock;
	
	lock = andes_get_spin_lock(ctl, list);

	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	is_empty = DlListEmpty(list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);

	return is_empty;
}

static void andes_queue_init(struct MCU_CTRL *ctl, DL_LIST *list)
{

	unsigned long flags;
	NDIS_SPIN_LOCK *lock;
	
	lock = andes_get_spin_lock(ctl, list);
	
	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	DlListInit(list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

static void _andes_unlink_cmd_msg(struct cmd_msg *msg, DL_LIST *list)
{
	if (!msg)
		return;

	DlListDel(&msg->list);		
}

static void andes_unlink_cmd_msg(struct cmd_msg *msg, DL_LIST *list)
{
	unsigned long flags;
	NDIS_SPIN_LOCK *lock;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)msg->priv;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	
	lock = andes_get_spin_lock(ctl, list);
	
	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	_andes_unlink_cmd_msg(msg, list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

static struct cmd_msg *_andes_dequeue_cmd_msg(DL_LIST *list)
{
	struct cmd_msg *msg;

	msg = DlListFirst(list, struct cmd_msg, list);

	_andes_unlink_cmd_msg(msg, list);

	return msg;
}

static struct cmd_msg *andes_dequeue_cmd_msg(struct MCU_CTRL *ctl, DL_LIST *list)
{
	unsigned long flags;
	struct cmd_msg *msg;
	NDIS_SPIN_LOCK *lock;
	
	lock = andes_get_spin_lock(ctl, list);
	
	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	msg = _andes_dequeue_cmd_msg(list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);

	return msg;
}

void andes_rx_process_cmd_msg(RTMP_ADAPTER *ad, struct cmd_msg *rx_msg)
{
	PNDIS_PACKET net_pkt = rx_msg->net_pkt;
	struct cmd_msg *msg, *msg_tmp;
	RXFCE_INFO_CMD *rx_info = (RXFCE_INFO_CMD *)GET_OS_PKT_DATAPTR(net_pkt);
	struct MCU_CTRL *ctl = &ad->MCUCtrl;

#ifdef RT_BIG_ENDIAN
	RTMPDescriptorEndianChange((PUCHAR)rx_info, TYPE_RXINFO);
#endif


	if ((rx_info->info_type != CMD_PACKET)) {
		DBGPRINT(RT_DEBUG_ERROR, ("packet is not command response/self event\n"));
		return;
	} 
	
	if (rx_info->self_gen) {
		/* if have callback function */
		RTEnqueueInternalCmd(ad, CMDTHREAD_RESPONSE_EVENT_CALLBACK, 
								GET_OS_PKT_DATAPTR(net_pkt) + sizeof(*rx_info), rx_info->pkt_len);
	} else {
		RTMP_SPIN_LOCK_IRQ(&ctl->ackq_lock);
		DlListForEachSafe(msg, msg_tmp, &ctl->ackq, struct cmd_msg, list) {
			if (msg->seq == rx_info->cmd_seq)
			{
				_andes_unlink_cmd_msg(msg, &ctl->ackq);
				RTMP_SPIN_UNLOCK_IRQ(&ctl->ackq_lock);
				
				if ((msg->rsp_payload_len == rx_info->pkt_len) && (msg->rsp_payload_len != 0))
				{
					msg->rsp_handler(msg, GET_OS_PKT_DATAPTR(net_pkt) + sizeof(*rx_info), rx_info->pkt_len);
				}
				else if ((msg->rsp_payload_len == 0) && (rx_info->pkt_len == 8))
				{
					DBGPRINT(RT_DEBUG_INFO, ("command response(ack) success\n"));
				}
				else
				{
					DBGPRINT(RT_DEBUG_ERROR, ("expect response len(%d), command response len(%d) invalid\n", msg->rsp_payload_len, rx_info->pkt_len));
					msg->rsp_payload_len = rx_info->pkt_len;
				}

				if (msg->need_wait)
					RTMP_OS_COMPLETE(&msg->ack_done);
				else
					andes_free_cmd_msg(msg);
			
				RTMP_SPIN_LOCK_IRQ(&ctl->ackq_lock);	
				break;
			}
		}
		RTMP_SPIN_UNLOCK_IRQ(&ctl->ackq_lock);
	}
}	

#ifdef RTMP_USB_SUPPORT
static void usb_rx_cmd_msg_complete(PURB urb)
{
	PNDIS_PACKET net_pkt = (PNDIS_PACKET)RTMP_OS_USB_CONTEXT_GET(urb);
	struct cmd_msg *msg = CMD_MSG_CB(net_pkt)->msg;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)msg->priv;
	POS_COOKIE pObj = (POS_COOKIE)ad->OS_Cookie;
	RTMP_CHIP_CAP *pChipCap = &ad->chipCap;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	enum cmd_msg_state state;
	unsigned long flags;
	int ret = 0;

	andes_unlink_cmd_msg(msg, &ctl->rxq);

	OS_PKT_TAIL_BUF_EXTEND(net_pkt, RTMP_USB_URB_LEN_GET(urb));
	
	if (RTMP_USB_URB_STATUS_GET(urb) == 0) {
		state = rx_done;
	} else {
		state = rx_receive_fail;
		andes_inc_error_count(ctl, error_rx_receive_fail);
		DBGPRINT(RT_DEBUG_ERROR, ("receive cmd msg fail(%d)\n", RTMP_USB_URB_STATUS_GET(urb)));
	}

	RTMP_SPIN_LOCK_IRQSAVE(&ctl->rx_doneq_lock, &flags);	
	_andes_queue_tail_cmd_msg(&ctl->rx_doneq, msg, state);
	RTMP_SPIN_UNLOCK_IRQRESTORE(&ctl->rx_doneq_lock, &flags);

	if (OS_TEST_BIT(MCU_INIT, &ctl->flags)) {
		msg = andes_alloc_cmd_msg(ad, 512);
		
		if (!msg) {
			return;
		}

		net_pkt = msg->net_pkt;
	
		RTUSB_FILL_BULK_URB(msg->urb, pObj->pUsb_Dev,
							usb_rcvbulkpipe(pObj->pUsb_Dev, pChipCap->CommandRspBulkInAddr),	
							GET_OS_PKT_DATAPTR(net_pkt), 512, usb_rx_cmd_msg_complete, net_pkt);

		andes_queue_tail_cmd_msg(&ctl->rxq, msg, rx_start);
	
		ret = RTUSB_SUBMIT_URB(msg->urb);
	
		if (ret) {
			andes_unlink_cmd_msg(msg, &ctl->rxq);
			andes_inc_error_count(ctl, error_rx_receive_fail);
			DBGPRINT(RT_DEBUG_ERROR, ("%s:submit urb fail(%d)\n", __FUNCTION__, ret));
			andes_queue_tail_cmd_msg(&ctl->rx_doneq, msg, rx_receive_fail);
		}
		
	}
	
	andes_bh_schedule(ad);
}	

int usb_rx_cmd_msg_submit(RTMP_ADAPTER *ad)
{
	RTMP_CHIP_CAP *pChipCap = &ad->chipCap;
	POS_COOKIE pObj = (POS_COOKIE)ad->OS_Cookie;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	struct cmd_msg *msg = NULL;
	PNDIS_PACKET net_pkt = NULL;
	int ret = 0;
	
	if (!OS_TEST_BIT(MCU_INIT, &ctl->flags))
		return ret;
	
	msg =  andes_alloc_cmd_msg(ad, 512);	
	
	if (!msg) {
		ret = NDIS_STATUS_RESOURCES;
		return ret;
	}

	net_pkt = msg->net_pkt;
		
	RTUSB_FILL_BULK_URB(msg->urb, pObj->pUsb_Dev,
						usb_rcvbulkpipe(pObj->pUsb_Dev, pChipCap->CommandRspBulkInAddr),	
						GET_OS_PKT_DATAPTR(net_pkt), 512, usb_rx_cmd_msg_complete, net_pkt);

	andes_queue_tail_cmd_msg(&ctl->rxq, msg, rx_start);
	
	ret = RTUSB_SUBMIT_URB(msg->urb);
	
	if (ret) {
		andes_unlink_cmd_msg(msg, &ctl->rxq);
		andes_inc_error_count(ctl, error_rx_receive_fail);
		DBGPRINT(RT_DEBUG_ERROR, ("%s:submit urb fail(%d)\n", __FUNCTION__, ret));
		andes_queue_tail_cmd_msg(&ctl->rx_doneq, msg, rx_receive_fail);
	}

	return ret;
}

int usb_rx_cmd_msgs_receive(RTMP_ADAPTER *ad)
{
	int ret = 0;
	int i;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;

	for (i = 0; (i < 1) && (andes_queue_len(ctl, &ctl->rxq) < 1); i++) {
		ret = usb_rx_cmd_msg_submit(ad);
		if (ret)
			break;
	}

	return ret;
}

void andes_cmd_msg_bh(unsigned long param)
{
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)param;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	struct cmd_msg *msg = NULL;

	while ((msg = andes_dequeue_cmd_msg(ctl, &ctl->rx_doneq))) {
		switch (msg->state) {
		case rx_done:
			andes_rx_process_cmd_msg(ad, msg);
			andes_free_cmd_msg(msg);
			continue;
		case rx_receive_fail:
			andes_free_cmd_msg(msg);
			continue;
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("unknow msg state(%d)\n", msg->state));
		}
	}

	while ((msg = andes_dequeue_cmd_msg(ctl, &ctl->tx_doneq))) {
		switch (msg->state) {
		case tx_done:
		case tx_kickout_fail:
		case tx_timeout_fail:
			andes_free_cmd_msg(msg);
			continue;
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("unknow msg state(%d)\n", msg->state));
		}
	}

	if (OS_TEST_BIT(MCU_INIT, &ctl->flags)) {
		andes_bh_schedule(ad);
		usb_rx_cmd_msgs_receive(ad);
	}
}

void andes_bh_schedule(RTMP_ADAPTER *ad)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;

	if (!OS_TEST_BIT(MCU_INIT, &ctl->flags))
		return;

	if (((andes_queue_len(ctl, &ctl->rx_doneq) > 0) 
							|| (andes_queue_len(ctl, &ctl->tx_doneq) > 0)) 
							&& OS_TEST_BIT(MCU_INIT, &ctl->flags)) { 
		RTMP_NET_TASK_DATA_ASSIGN(&ctl->cmd_msg_task, (unsigned long)(ad));	
		RTMP_OS_TASKLET_SCHE(&ctl->cmd_msg_task);
	}
}

static void usb_kick_out_cmd_msg_complete(PURB urb)
{
	PNDIS_PACKET net_pkt = (PNDIS_PACKET)RTMP_OS_USB_CONTEXT_GET(urb);	
	struct cmd_msg *msg = CMD_MSG_CB(net_pkt)->msg;
	RTMP_ADAPTER *ad = (RTMP_ADAPTER *)msg->priv;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;

	if (!OS_TEST_BIT(MCU_INIT, &ctl->flags))
		return;
	
	if (RTMP_USB_URB_STATUS_GET(urb) == 0) {
		if (!msg->need_rsp) {
			andes_unlink_cmd_msg(msg, &ctl->kickq);
			andes_queue_tail_cmd_msg(&ctl->tx_doneq, msg, tx_done);
		} else {
			msg->state = wait_ack;
		}
	} else {
		if (!msg->need_rsp) {
			andes_unlink_cmd_msg(msg, &ctl->kickq);
			andes_queue_tail_cmd_msg(&ctl->tx_doneq, msg, tx_kickout_fail);
			andes_inc_error_count(ctl, error_tx_kickout_fail);
		} else {
			andes_unlink_cmd_msg(msg, &ctl->ackq);
			msg->state = tx_kickout_fail;
			andes_inc_error_count(ctl, error_tx_kickout_fail);
			RTMP_OS_COMPLETE(&msg->ack_done);
		}
		
		DBGPRINT(RT_DEBUG_ERROR, ("kick out cmd msg fail(%d)\n", RTMP_USB_URB_STATUS_GET(urb)));
	}
	
	andes_bh_schedule(ad);
}

int usb_kick_out_cmd_msg(PRTMP_ADAPTER ad, struct cmd_msg *msg)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	POS_COOKIE pObj = (POS_COOKIE)ad->OS_Cookie;
	int ret = 0;
	PNDIS_PACKET net_pkt = msg->net_pkt;
	RTMP_CHIP_CAP *pChipCap = &ad->chipCap;
	
	/* append four zero bytes padding when usb aggregate enable */	
	memset(OS_PKT_TAIL_BUF_EXTEND(net_pkt, 4), 0x00, 4);

	RTUSB_FILL_BULK_URB(msg->urb, pObj->pUsb_Dev,
						usb_sndbulkpipe(pObj->pUsb_Dev, pChipCap->CommandBulkOutAddr),	
						GET_OS_PKT_DATAPTR(net_pkt), GET_OS_PKT_LEN(net_pkt), usb_kick_out_cmd_msg_complete, net_pkt);
	
	if (msg->need_rsp)
		andes_queue_tail_cmd_msg(&ctl->ackq, msg, wait_cmd_out_and_ack);
	else
		andes_queue_tail_cmd_msg(&ctl->kickq, msg, wait_cmd_out);
	
	if (!OS_TEST_BIT(MCU_INIT, &ctl->flags))
		return -1;

	ret = RTUSB_SUBMIT_URB(msg->urb);
	
	if (ret) {
		if (!msg->need_rsp) {
			andes_unlink_cmd_msg(msg, &ctl->kickq);
			andes_queue_tail_cmd_msg(&ctl->tx_doneq, msg, tx_kickout_fail);
			andes_inc_error_count(ctl, error_tx_kickout_fail);
		} else {
			andes_unlink_cmd_msg(msg, &ctl->ackq);
			msg->state = tx_kickout_fail;
			andes_inc_error_count(ctl, error_tx_kickout_fail);
			RTMP_OS_COMPLETE(&msg->ack_done);
		}
			
		DBGPRINT(RT_DEBUG_ERROR, ("%s:submit urb fail(%d)\n", __FUNCTION__, ret));
	}

	return ret;
}

void andes_usb_unlink_urb(RTMP_ADAPTER *ad, DL_LIST *list)
{
	unsigned long flags;
	struct cmd_msg *msg, *msg_tmp;
	NDIS_SPIN_LOCK *lock;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	
	lock = andes_get_spin_lock(ctl, list);

	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	DlListForEachSafe(msg, msg_tmp, list, struct cmd_msg, list) {
		RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
		if ((msg->state == wait_cmd_out_and_ack) || (msg->state == wait_cmd_out) || 
						(msg->state == tx_start) || (msg->state == rx_start) ||
						(msg->state == tx_retransmit))
			RTUSB_UNLINK_URB(msg->urb);
		RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	}
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

#endif

void andes_cleanup_cmd_msg(RTMP_ADAPTER *ad, DL_LIST *list)
{
	unsigned long flags;
	struct cmd_msg *msg, *msg_tmp;
	NDIS_SPIN_LOCK *lock;
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	
	lock = andes_get_spin_lock(ctl, list);

	RTMP_SPIN_LOCK_IRQSAVE(lock, &flags);
	DlListForEachSafe(msg, msg_tmp, list, struct cmd_msg, list) {
		_andes_unlink_cmd_msg(msg, list);
		andes_free_cmd_msg(msg);
	}
	DlListInit(list);
	RTMP_SPIN_UNLOCK_IRQRESTORE(lock, &flags);
}

void andes_ctrl_init(RTMP_ADAPTER *ad)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	int ret = 0;

	RTMP_SEM_EVENT_WAIT(&(ad->mcu_atomic), ret);
	RTMP_CLEAR_FLAG(ad, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD);
	ctl->cmd_seq = 0;
	RTMP_OS_TASKLET_INIT(ad, &ctl->cmd_msg_task, andes_cmd_msg_bh, (unsigned long)ad);
	NdisAllocateSpinLock(ad, &ctl->txq_lock);
	andes_queue_init(ctl, &ctl->txq);
	NdisAllocateSpinLock(ad, &ctl->rxq_lock);
	andes_queue_init(ctl, &ctl->rxq);
	NdisAllocateSpinLock(ad, &ctl->ackq_lock);
	andes_queue_init(ctl, &ctl->ackq);
	NdisAllocateSpinLock(ad, &ctl->kickq_lock);
	andes_queue_init(ctl, &ctl->kickq);
	NdisAllocateSpinLock(ad, &ctl->tx_doneq_lock);
	andes_queue_init(ctl, &ctl->tx_doneq);
	NdisAllocateSpinLock(ad, &ctl->rx_doneq_lock);
	andes_queue_init(ctl, &ctl->rx_doneq);
	ctl->tx_kickout_fail_count = 0;
	ctl->tx_timeout_fail_count = 0;
	ctl->rx_receive_fail_count = 0;	
	ctl->alloc_cmd_msg = 0;
	ctl->free_cmd_msg = 0;
	OS_SET_BIT(MCU_INIT, &ctl->flags);
	usb_rx_cmd_msgs_receive(ad);
	RTMP_SEM_EVENT_UP(&(ad->mcu_atomic));
}

void andes_ctrl_exit(RTMP_ADAPTER *ad)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	int ret = 0;
	
	RTMP_SEM_EVENT_WAIT(&(ad->mcu_atomic), ret);
	RTMP_CLEAR_FLAG(ad, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD);
	OS_CLEAR_BIT(MCU_INIT, &ctl->flags);
	andes_usb_unlink_urb(ad, &ctl->txq);
	andes_usb_unlink_urb(ad, &ctl->kickq);
	andes_usb_unlink_urb(ad, &ctl->ackq);
	andes_usb_unlink_urb(ad, &ctl->rxq);
	RTMP_OS_TASKLET_KILL(&ctl->cmd_msg_task);
	andes_cleanup_cmd_msg(ad, &ctl->txq);
	NdisFreeSpinLock(&ctl->txq_lock);
	andes_cleanup_cmd_msg(ad, &ctl->ackq);
	NdisFreeSpinLock(&ctl->ackq_lock);
	andes_cleanup_cmd_msg(ad, &ctl->rxq);
	NdisFreeSpinLock(&ctl->rxq_lock);
	andes_cleanup_cmd_msg(ad, &ctl->kickq);
	NdisFreeSpinLock(&ctl->kickq_lock);
	andes_cleanup_cmd_msg(ad, &ctl->tx_doneq);
	NdisFreeSpinLock(&ctl->tx_doneq_lock);
	andes_cleanup_cmd_msg(ad, &ctl->rx_doneq);
	NdisFreeSpinLock(&ctl->rx_doneq_lock);
	DBGPRINT(RT_DEBUG_OFF, ("tx_kickout_fail_count = %ld\n", ctl->tx_kickout_fail_count));
	DBGPRINT(RT_DEBUG_OFF, ("tx_timeout_fail_count = %ld\n", ctl->tx_timeout_fail_count));
	DBGPRINT(RT_DEBUG_OFF, ("rx_receive_fail_count = %ld\n", ctl->rx_receive_fail_count));
	DBGPRINT(RT_DEBUG_OFF, ("alloc_cmd_msg = %ld\n", ctl->alloc_cmd_msg));
	DBGPRINT(RT_DEBUG_OFF, ("free_cmd_msg = %ld\n", ctl->free_cmd_msg));
	RTMP_SEM_EVENT_UP(&(ad->mcu_atomic));
}

static int andes_dequeue_and_kick_out_cmd_msgs(RTMP_ADAPTER *ad)
{
	struct cmd_msg *msg = NULL;
	PNDIS_PACKET net_pkt = NULL;	
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	int ret = NDIS_STATUS_SUCCESS;
	TXINFO_NMAC_CMD *tx_info;

	while (msg = andes_dequeue_cmd_msg(ctl, &ctl->txq)) {
		if (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD) 
				|| RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST)
				|| RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_SUSPEND)) { 
			if (!msg->need_rsp)	
				andes_free_cmd_msg(msg);
			continue;
		}

		if (andes_queue_len(ctl, &ctl->ackq) > 0) {
			andes_queue_head_cmd_msg(&ctl->txq, msg, msg->state);
			ret = NDIS_STATUS_FAILURE;
			continue;
		}

		net_pkt = msg->net_pkt;

		if (msg->need_rsp)
			msg->seq = andes_get_cmd_msg_seq(ad);
		else
			msg->seq = 0;

		tx_info = (TXINFO_NMAC_CMD *)OS_PKT_HEAD_BUF_EXTEND(net_pkt, sizeof(*tx_info));
		tx_info->info_type = CMD_PACKET;
		tx_info->d_port = CPU_TX_PORT;
		tx_info->cmd_type = msg->type;
		tx_info->cmd_seq = msg->seq;
		tx_info->pkt_len = GET_OS_PKT_LEN(net_pkt) - sizeof(*tx_info);

#ifdef RT_BIG_ENDIAN
		RTMPDescriptorEndianChange((PUCHAR)tx_info, TYPE_TXINFO);
#endif
	

#ifdef RTMP_USB_SUPPORT	
		ret = usb_kick_out_cmd_msg(ad, msg);
#endif


		if (ret) {
			DBGPRINT(RT_DEBUG_ERROR, ("kick out msg fail\n"));
			break;
		}
	}
	
	andes_bh_schedule(ad);
	
	return ret;
}

int andes_send_cmd_msg(PRTMP_ADAPTER ad, struct cmd_msg *msg)
{
	struct MCU_CTRL *ctl = &ad->MCUCtrl;
	int ret = 0;
	BOOLEAN need_wait = msg->need_wait;
	
	RTMP_SEM_EVENT_WAIT(&(ad->mcu_atomic), ret);

	if (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD) 
				|| RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST) 
				|| RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_SUSPEND)) { 
		andes_free_cmd_msg(msg);
		RTMP_SEM_EVENT_UP(&(ad->mcu_atomic));
		return NDIS_STATUS_FAILURE;
	}

	andes_queue_tail_cmd_msg(&ctl->txq, msg, tx_start);

retransmit:
	andes_dequeue_and_kick_out_cmd_msgs(ad);

	/* Wait for response */
	if (need_wait)
	{
		enum cmd_msg_state state;
		unsigned long expire;
		unsigned long timeout = msg->timeout;
		expire = timeout ? RTMPMsecsToJiffies(timeout) : RTMPMsecsToJiffies(CMD_MSG_TIMEOUT);
		if (!RTMP_OS_WAIT_FOR_COMPLETION_TIMEOUT(&msg->ack_done, expire)) {
			ret = NDIS_STATUS_FAILURE;
			DBGPRINT(RT_DEBUG_ERROR, ("command (%d) timeout(%dms)\n", msg->type, CMD_MSG_TIMEOUT));
			DBGPRINT(RT_DEBUG_ERROR, ("txq qlen = %d\n", andes_queue_len(ctl, &ctl->txq)));
			DBGPRINT(RT_DEBUG_ERROR, ("rxq qlen = %d\n", andes_queue_len(ctl, &ctl->rxq)));
			DBGPRINT(RT_DEBUG_ERROR, ("kickq qlen = %d\n", andes_queue_len(ctl, &ctl->kickq)));
			DBGPRINT(RT_DEBUG_ERROR, ("ackq qlen = %d\n", andes_queue_len(ctl, &ctl->ackq)));
			DBGPRINT(RT_DEBUG_ERROR, ("tx_doneq.qlen = %d\n", andes_queue_len(ctl, &ctl->tx_doneq)));
			DBGPRINT(RT_DEBUG_ERROR, ("rx_done qlen = %d\n", andes_queue_len(ctl, &ctl->rx_doneq)));
			if (OS_TEST_BIT(MCU_INIT, &ctl->flags)) {
				if (msg->state == wait_cmd_out_and_ack) {
					RTUSB_UNLINK_URB(msg->urb);
				} else if (msg->state == wait_ack) {
					andes_unlink_cmd_msg(msg, &ctl->ackq);
				}
			}

			andes_inc_error_count(ctl, error_tx_timeout_fail);
			state = tx_timeout_fail;
			msg->retransmit_times--;
			DBGPRINT(RT_DEBUG_ERROR, ("msg->retransmit_times = %d\n", msg->retransmit_times));
		} else {
			if (msg->state == tx_kickout_fail) {
				state = tx_kickout_fail;
				msg->retransmit_times--;
			} else {
				state = tx_done;
				msg->retransmit_times = 0;
			}
		}
	
		if (OS_TEST_BIT(MCU_INIT, &ctl->flags)) {
			if (msg->need_retransmit && (msg->retransmit_times > 0)) {
				RTMP_OS_EXIT_COMPLETION(&msg->ack_done);
				RTMP_OS_INIT_COMPLETION(&msg->ack_done);
				state = tx_retransmit;
				andes_queue_head_cmd_msg(&ctl->txq, msg, state);
				goto retransmit;
			} else {
				andes_queue_tail_cmd_msg(&ctl->tx_doneq, msg, state);
			}
		} else {
			andes_free_cmd_msg(msg);
		}
	}
	
	RTMP_SEM_EVENT_UP(&(ad->mcu_atomic));

	return ret;
}

static void andes_pwr_event_handler(RTMP_ADAPTER *ad, char *payload, u16 payload_len)
{


}


static void andes_wow_event_handler(RTMP_ADAPTER *ad, char *payload, u16 payload_len)
{


}

static void andes_carrier_detect_event_handler(RTMP_ADAPTER *ad, char *payload, u16 payload_len)
{



}

static void andes_dfs_detect_event_handler(PRTMP_ADAPTER ad, char *payload, u16 payload_len)
{



}

MSG_EVENT_HANDLER msg_event_handler_tb[] =
{
	andes_pwr_event_handler,
	andes_wow_event_handler,
	andes_carrier_detect_event_handler,
	andes_dfs_detect_event_handler,
};


int andes_burst_write(RTMP_ADAPTER *ad, u32 offset, u32 *data, u32 cnt)
{
	struct cmd_msg *msg;
	unsigned int var_len, offset_num, cur_len = 0, sent_len;
	u32 value, i, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;
	BOOLEAN last_packet = FALSE;

	if (!data)
		return -1;

	offset_num = cnt / ((cap->InbandPacketMaxLen - sizeof(offset)) / 4);

	if (cnt % ((cap->InbandPacketMaxLen - sizeof(offset)) / 4))
		var_len = sizeof(offset) * (offset_num + 1) + 4 * cnt;
	else
		var_len = sizeof(offset) * offset_num + 4 * cnt;

	while (cur_len < var_len) {
		sent_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									? cap->InbandPacketMaxLen : (var_len - cur_len);

		if ((sent_len < cap->InbandPacketMaxLen) || ((cur_len + cap->InbandPacketMaxLen) == var_len))
			last_packet = TRUE;

		msg = andes_alloc_cmd_msg(ad, sent_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}

		if (last_packet) {
			andes_init_cmd_msg(msg, CMD_BURST_WRITE, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
		}else {
			andes_init_cmd_msg(msg, CMD_BURST_WRITE, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);
		}
			
	
		value = cpu2le32(offset + cap->WlanMemmapOffset + cur_index * 4);
		andes_append_cmd_msg(msg, (char *)&value, 4);

		for (i = 0; i < ((sent_len - 4) / 4); i++) {
			value = cpu2le32(data[i + cur_index]);
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}
		
		ret = andes_send_cmd_msg(ad, msg);

		
		cur_index += ((sent_len - 4) / 4);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

static void andes_burst_read_callback(struct cmd_msg *msg, char *rsp_payload, u16 rsp_payload_len)
{
	u32 i;
	u32 *data;
	NdisMoveMemory(msg->rsp_payload, rsp_payload + 4, rsp_payload_len - 4);

	for (i = 0; i < (msg->rsp_payload_len - 4) / 4; i++) {
		data = (u32 *)(msg->rsp_payload + i * 4);
		*data = le2cpu32(*data);
	}
}

int andes_burst_read(RTMP_ADAPTER *ad, u32 offset, u32 cnt, u32 *data)
{
	struct cmd_msg *msg;
	unsigned int cur_len = 0, rsp_len, offset_num, receive_len;
	u32 value, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;

	if (!data)
		return -1;

	offset_num = cnt / ((cap->InbandPacketMaxLen - sizeof(offset)) / 4);

	if (cnt % ((cap->InbandPacketMaxLen - sizeof(offset)) / 4))
		rsp_len = sizeof(offset) * (offset_num + 1) + 4 * cnt;
	else
		rsp_len = sizeof(offset) * offset_num + 4 * cnt;

	while (cur_len < rsp_len) {
		receive_len = (rsp_len - cur_len) > cap->InbandPacketMaxLen 
									   ? cap->InbandPacketMaxLen 
									   : (rsp_len - cur_len);

		msg = andes_alloc_cmd_msg(ad, 8);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
	
		andes_init_cmd_msg(msg, CMD_BURST_READ, TRUE, 0, TRUE, TRUE, receive_len, 
									(char *)(&data[cur_index]), andes_burst_read_callback);

		value = cpu2le32(offset + cap->WlanMemmapOffset + cur_index * 4);
		andes_append_cmd_msg(msg, (char *)&value, 4);

		value = cpu2le32((receive_len - 4) / 4);
		andes_append_cmd_msg(msg, (char *)&value, 4);

		ret = andes_send_cmd_msg(ad, msg);

		if (ret) {
			if (cnt == 1)
				*data = 0xffffffff;
		}
		
		cur_index += ((receive_len - 4) / 4);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

static void andes_random_read_callback(struct cmd_msg *msg, char *rsp_payload, u16 rsp_payload_len)
{
	u32 i;
	RTMP_REG_PAIR *reg_pair = (RTMP_REG_PAIR *)msg->rsp_payload;
	
	for (i = 0; i < msg->rsp_payload_len / 8; i++) {
		NdisMoveMemory(&reg_pair[i].Value, rsp_payload + 8 * i + 4, 4);
		reg_pair[i].Value = le2cpu32(reg_pair[i].Value);
	}
}

int andes_random_read(RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 8, cur_len = 0, receive_len;
	u32 i, value, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;

	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		receive_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									   ? cap->InbandPacketMaxLen 
									   : (var_len - cur_len);

		msg = andes_alloc_cmd_msg(ad, receive_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		andes_init_cmd_msg(msg, CMD_RANDOM_READ, TRUE, 0, TRUE, TRUE, receive_len, 
									(char *)&reg_pair[cur_index], andes_random_read_callback);

		for (i = 0; i < receive_len / 8; i++) {
			value = cpu2le32(reg_pair[i + cur_index].Register + cap->WlanMemmapOffset);
			andes_append_cmd_msg(msg, (char *)&value, 4);
			value = 0;
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}
	

		ret = andes_send_cmd_msg(ad, msg);

		
		cur_index += receive_len / 8;
		cur_len += cap->InbandPacketMaxLen;
	}

error:	
	return ret;
}

static void andes_rf_random_read_callback(struct cmd_msg *msg, char *rsp_payload, u16 rsp_payload_len)
{
	u32 i;
	BANK_RF_REG_PAIR *reg_pair = (BANK_RF_REG_PAIR *)msg->rsp_payload;
			
	for (i = 0; i < msg->rsp_payload_len / 8; i++) {
		NdisMoveMemory(&reg_pair[i].Value, rsp_payload + 8 * i + 4, 1);
	}
}

int andes_rf_random_read(RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 8, cur_len = 0, receive_len;
	u32 i, value, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;

	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		receive_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									   ? cap->InbandPacketMaxLen 
									   : (var_len - cur_len);

		msg = andes_alloc_cmd_msg(ad, receive_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		andes_init_cmd_msg(msg, CMD_RANDOM_READ, TRUE, 0, TRUE, TRUE, receive_len, 
									(char *)&reg_pair[cur_index], andes_rf_random_read_callback);

		for (i = 0; i < (receive_len) / 8; i++)
		{
			value = 0;
	
			/* RF selection */
			value = (value & ~0x80000000) | 0x80000000;

			/* RF bank */
			value = (value & ~0x00ff0000) | (reg_pair[i + cur_index].Bank << 16);

			/* RF Index */
			value = (value & ~0x0000ffff) | reg_pair[i + cur_index].Register;

			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
			value = 0;
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}

		ret = andes_send_cmd_msg(ad, msg);
	
	
		cur_index += receive_len / 8;
		cur_len += cap->InbandPacketMaxLen;
	}
	
error:
	return ret;
}

int andes_read_modify_write(RTMP_ADAPTER *ad, R_M_W_REG *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 12, cur_len = 0, sent_len;
	u32 value, i, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;
	BOOLEAN last_packet = FALSE;

	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		sent_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									? cap->InbandPacketMaxLen : (var_len - cur_len);
		
		if ((sent_len < cap->InbandPacketMaxLen) || (cur_len + cap->InbandPacketMaxLen) == var_len)
			last_packet = TRUE;
		
		msg = andes_alloc_cmd_msg(ad, sent_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		if (last_packet)
			andes_init_cmd_msg(msg, CMD_READ_MODIFY_WRITE, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
		else
			andes_init_cmd_msg(msg, CMD_READ_MODIFY_WRITE, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);

		for (i = 0; i < (sent_len / 12); i++)
		{
			/* Address */
			value = cpu2le32(reg_pair[i + cur_index].Register + cap->WlanMemmapOffset);
			andes_append_cmd_msg(msg, (char *)&value, 4);

			/* ClearBitMask */
			value = cpu2le32(reg_pair[i + cur_index].ClearBitMask);
			andes_append_cmd_msg(msg, (char *)&value, 4);

			/* UpdateData */
			value = cpu2le32(reg_pair[i + cur_index].Value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}

		ret = andes_send_cmd_msg(ad, msg);
	
	
		cur_index += (sent_len / 12);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

int andes_rf_read_modify_write(RTMP_ADAPTER *ad, RF_R_M_W_REG *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 12, cur_len = 0, sent_len;
	u32 value, i, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;
	BOOLEAN last_packet = FALSE;
	
	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		sent_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									? cap->InbandPacketMaxLen : (var_len - cur_len);
		
		if ((sent_len < cap->InbandPacketMaxLen) || (cur_len + cap->InbandPacketMaxLen) == var_len)
			last_packet = TRUE;

		msg = andes_alloc_cmd_msg(ad, sent_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		if (last_packet)
			andes_init_cmd_msg(msg, CMD_READ_MODIFY_WRITE, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
		else
			andes_init_cmd_msg(msg, CMD_READ_MODIFY_WRITE, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);
		
		for (i = 0; i < sent_len / 12; i++)
		{
			value = 0;
			/* RF selection */
			value = (value & ~0x80000000) | 0x80000000;

			/* RF bank */
			value = (value & ~0x00ff0000) | (reg_pair[i + cur_index].Bank << 16);

			/* RF Index */
			value = (value & ~0x000000ff) | reg_pair[i + cur_index].Register;
			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
			
			value = 0;
			/* ClearBitMask */
			value = (value & ~0x000000ff) | reg_pair[i + cur_index].ClearBitMask;
			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);

			value = 0;
			/* UpdateData */
			value = (value & ~0x000000ff) | reg_pair[i + cur_index].Value;
			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}
	
		ret = andes_send_cmd_msg(ad, msg);

		
		cur_index += (sent_len / 12);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

int andes_random_write(RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 8, cur_len = 0, sent_len;
	u32 value, i, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;
	BOOLEAN last_packet = FALSE;

	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		sent_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									? cap->InbandPacketMaxLen : (var_len - cur_len);
	
		if ((sent_len < cap->InbandPacketMaxLen) || (cur_len + cap->InbandPacketMaxLen) == var_len)
			last_packet = TRUE;
	
		msg = andes_alloc_cmd_msg(ad, sent_len);
		
		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		if (last_packet)
			andes_init_cmd_msg(msg, CMD_RANDOM_WRITE, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
		else
			andes_init_cmd_msg(msg, CMD_RANDOM_WRITE, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);

		for (i = 0; i < (sent_len / 8); i++)
		{
			/* Address */
			value = cpu2le32(reg_pair[i + cur_index].Register + cap->WlanMemmapOffset);
			andes_append_cmd_msg(msg, (char *)&value, 4);

			/* UpdateData */
			value = cpu2le32(reg_pair[i + cur_index].Value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
		};

		ret = andes_send_cmd_msg(ad, msg);
	

		cur_index += (sent_len / 8);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

int andes_rf_random_write(RTMP_ADAPTER *ad, BANK_RF_REG_PAIR *reg_pair, u32 num)
{
	struct cmd_msg *msg;
	unsigned int var_len = num * 8, cur_len = 0, sent_len;
	u32 value, i, cur_index = 0;
	RTMP_CHIP_CAP *cap = &ad->chipCap;
	int ret = 0;
	BOOLEAN last_packet = FALSE;

	if (!reg_pair)
		return -1;

	while (cur_len < var_len)
	{
		sent_len = (var_len - cur_len) > cap->InbandPacketMaxLen 
									? cap->InbandPacketMaxLen : (var_len - cur_len);
	
		if ((sent_len < cap->InbandPacketMaxLen) || (cur_len + cap->InbandPacketMaxLen) == var_len)
			last_packet = TRUE;

		msg = andes_alloc_cmd_msg(ad, sent_len);

		if (!msg) {
			ret = NDIS_STATUS_RESOURCES;
			goto error;
		}
		
		if (last_packet)
			andes_init_cmd_msg(msg, CMD_RANDOM_WRITE, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
		else
			andes_init_cmd_msg(msg, CMD_RANDOM_WRITE, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);
		
		for (i = 0; i < (sent_len / 8); i++) {
			value = 0;
			/* RF selection */
			value = (value & ~0x80000000) | 0x80000000;

			/* RF bank */
			value = (value & ~0x00ff0000) | (reg_pair[i + cur_index].Bank << 16);

			/* RF Index */
			value = (value & ~0x000000ff) | reg_pair[i + cur_index].Register;
			
			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);

			value = 0;
			/* UpdateData */
			value = (value & ~0x000000ff) | reg_pair[i + cur_index].Value;
			value = cpu2le32(value);
			andes_append_cmd_msg(msg, (char *)&value, 4);
		}

		ret = andes_send_cmd_msg(ad, msg);


		cur_index += (sent_len / 8);
		cur_len += cap->InbandPacketMaxLen;
	}

error:
	return ret;
}

int andes_pwr_saving(RTMP_ADAPTER *ad, u32 op, u32 level, 
					 u32 listen_interval, u32 pre_tbtt_lead_time,
					 u8 tim_byte_offset, u8 tim_byte_pattern)
{
	struct cmd_msg *msg;
	unsigned int var_len;
	u32 value;
	int ret = 0;

	/* Power operation and Power Level */
	var_len = 8;

	if (op == RADIO_OFF_ADVANCE)
	{
		/* Listen interval, Pre-TBTT, TIM info */
		var_len += 12;
	}
	
	msg = andes_alloc_cmd_msg(ad, var_len);

	if (!msg) {
		ret = NDIS_STATUS_RESOURCES;
		goto error;
	}

	andes_init_cmd_msg(msg, CMD_POWER_SAVING_OP, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);
	
	/* Power operation */
	value = cpu2le32(op);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	/* Power Level */
	value = cpu2le32(level);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	if (op == RADIO_OFF_ADVANCE)
	{
		/* Listen interval */
		value = cpu2le32(listen_interval);
		andes_append_cmd_msg(msg, (char *)&value, 4);


		/* Pre TBTT lead time */
		value = cpu2le32(pre_tbtt_lead_time);
		andes_append_cmd_msg(msg, (char*)&value, 4);

		/* TIM Info */
		value = (value & ~0x000000ff) | tim_byte_pattern;
		value = (value & ~0x0000ff00) | (tim_byte_offset << 8);
		value = cpu2le32(value);
		andes_append_cmd_msg(msg, (char *)&value, 4);
	}

	ret = andes_send_cmd_msg(ad, msg);
	
error:
	return ret;
}

int andes_fun_set(RTMP_ADAPTER *ad, u32 fun_id, u32 param)
{
	struct cmd_msg *msg;
	u32 value;
	int ret = 0;

	/* Function ID and Parameter */
	msg = andes_alloc_cmd_msg(ad, 8);

	if (!msg) {
		ret = NDIS_STATUS_RESOURCES;
		goto error;
	}

	if (fun_id != Q_SELECT)
		andes_init_cmd_msg(msg, CMD_FUN_SET_OP, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
	else
		andes_init_cmd_msg(msg, CMD_FUN_SET_OP, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);

	/* Function ID */
	value = cpu2le32(fun_id);
	andes_append_cmd_msg(msg, (char *)&value, 4);
	
	/* Parameter */
	value = cpu2le32(param);
	andes_append_cmd_msg(msg, (char *)&value, 4);	
		
	ret = andes_send_cmd_msg(ad, msg);
	
error:
	return ret;
}

int andes_calibration(RTMP_ADAPTER *ad, u32 cal_id, u32 param)
{
	struct cmd_msg *msg;
	u32 value;
	int ret = 0;

	//DBGPRINT(RT_DEBUG_OFF, ("%s:cal_id(%d)\n", __FUNCTION__, cal_id));

	/* Calibration ID and Parameter */
	msg = andes_alloc_cmd_msg(ad, 8);

	if (!msg) {
		ret = NDIS_STATUS_RESOURCES;
		goto error;
	}
		
	andes_init_cmd_msg(msg, CMD_CALIBRATION_OP, TRUE, 0, TRUE, TRUE, 0, NULL, NULL);
	
	/* Calibration ID */
	value = cpu2le32(cal_id);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	/* Parameter */
	value = cpu2le32(param);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	ret = andes_send_cmd_msg(ad, msg);

error:
	return ret;
}

int andes_led_op(RTMP_ADAPTER *ad, u32 led_idx, u32 link_status)
{
	struct cmd_msg *msg;
	u32 value;
	int ret = 0;

	msg = andes_alloc_cmd_msg(ad, 8);

	if (!msg) {
		ret = NDIS_STATUS_RESOURCES;
		goto error;
	}

	andes_init_cmd_msg(msg, CMD_LED_MODE_OP, FALSE, 0, FALSE, FALSE, 0, NULL, NULL);
	
	/* Led index */
	value = cpu2le32(led_idx);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	/* Link status */
	value = cpu2le32(link_status);
	andes_append_cmd_msg(msg, (char *)&value, 4);

	ret = andes_send_cmd_msg(ad, msg);
	
error:
	return ret;
}
