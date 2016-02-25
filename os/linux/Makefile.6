include $(RT28xx_DIR)/os/linux/config.mk

obj_wsc :=
obj_vht :=
obj_cmm := \
	../../common/crypt_md5.o\
        ../../common/crypt_sha2.o\
        ../../common/crypt_hmac.o\
        ../../common/crypt_aes.o\
        ../../common/crypt_arc4.o\
        ../../common/mlme.o\
        ../../common/cmm_wep.o\
        ../../common/action.o\
        ../../common/cmm_data.o\
	../../common/rtmp_init.o\
        ../../common/rtmp_init_inf.o\
        ../../common/cmm_tkip.o\
        ../../common/cmm_aes.o\
        ../../common/cmm_sync.o\
        ../../common/eeprom.o\
        ../../common/cmm_sanity.o\
        ../../common/cmm_info.o\
        ../../common/cmm_cfg.o\
        ../../common/cmm_wpa.o\
        ../../common/cmm_radar.o\
	../../common/spectrum.o\
        ../../common/rtmp_timer.o\
        ../../common/rt_channel.o\
        ../../common/cmm_profile.o\
        ../../common/cmm_asic.o\
        ../../common/scan.o\
        ../../common/cmm_cmd.o\
        ../../common/uapsd.o\
	../../common/ps.o\
	../../rate_ctrl/ra_ctrl.o\
        ../../rate_ctrl/alg_legacy.o\
        ../../rate_ctrl/alg_ags.o\
	../../chips/rtmp_chip.o\
		../../common/txpower.o\
	../../mac/rtmp_mac.o\
	../../mgmt/mgmt_hw.o\
	../../mgmt/mgmt_entrytb.o\
        ../../phy/rtmp_phy.o\
        ../../phy/rlt_phy.o\
	../../phy/rlt_rf.o

ifeq ($(HAS_BLOCK_NET_IF),y)
obj_cmm += ../../common/netif_block.o
endif

ifeq ($(HAS_NEW_RATE_ADAPT_SUPPORT),y)
obj_cmm += ../../rate_ctrl/alg_grp.o
endif

ifeq ($(HAS_RATE_ADAPT_AGS_SUPPORT),y)
obj_cmm += ../../rate_ctrl/alg_ags.o
endif

ifeq ($(HAS_DFS_SUPPORT),y)
obj_cmm += ../../common/cmm_dfs.o
endif

ifeq ($(HAS_CS_SUPPORT),y)
obj_cmm += ../../common/cmm_cs.o
endif

#ifdef DOT11_N_SUPPORT
ifeq ($(HAS_DOT11_N_SUPPORT),y)
obj_cmm += \
        ../../common/ba_action.o\
        ../../mgmt/mgmt_ht.o

#ifdef TXBF_SUPPORT
ifeq ($(HAS_TXBF_SUPPORT),y)
obj_cmm += \
        ../../common/cmm_txbf.o\
        ../../common/cmm_txbf_cal.o
endif
#endif // TXBF_SUPPORT //
endif
#endif // DOT11_N_SUPPORT //

#ifdef DOT11_VHT_SUPPORT
ifeq ($(HAS_DOT11_VHT_SUPPORT),y)
obj_vht += ../../mgmt/mgmt_vht.o\
	../../common/vht.o
endif
#endif // DOT11_VHT_SUPPORT //




#ifdef CONFIG_STA_SUPPORT
ifeq ($(RT28xx_MODE), STA)
MOD_NAME = $(MODULE)_sta
ifeq ($(PLATFORM),MT85XX)
MOD_NAME = rtsta
endif
ifeq ($(PLATFORM),MT53XX)
MOD_NAME = rtsta
endif
DAT_PATH = /etc/Wireless/RT$(CHIPSET_DAT)STA
DAT_FILE_NAME = conf/RT$(CHIPSET_DAT)STA.dat
endif
#endif // CONFIG_STA_SUPPORT //


obj-m := $(MOD_NAME).o


#ifdef CONFIG_STA_SUPPORT
ifeq ($(RT28xx_MODE), STA)
$(MOD_NAME)-objs := \
	../../os/linux/rt_profile.o\
	../../sta/assoc.o\
	../../sta/auth.o\
	../../sta/auth_rsp.o\
	../../sta/sync.o\
	../../sta/sanity.o\
	../../sta/rtmp_data.o\
	../../sta/connect.o\
	../../sta/wpa.o\
	../../sta/sta_cfg.o\
	$(obj_vht)\
	$(obj_cmm)\
	$(obj_wsc)


ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
	../../common/rt_os_util.o\
	../../os/linux/sta_ioctl.o\
	../../os/linux/rt_linux.o\
	../../os/linux/rt_main_dev.o
else
$(MOD_NAME)-objs += \
	../../os/linux/rt_symb.o
endif

#ifdef ETH_CONVERT
ifeq ($(HAS_ETH_CONVERT_SUPPORT), y)
$(MOD_NAME)-objs += \
	../../common/cmm_mat.o \
	../../common/cmm_mat_iparp.o \
	../../common/cmm_mat_pppoe.o \
	../../common/cmm_mat_ipv6.o
endif
#endif // ETH_CONVERT //




ifeq ($(HAS_QOS_DLS_SUPPORT),y)
$(MOD_NAME)-objs += ../../sta/dls.o
endif


#ifdef WFD_SUPPORT
ifeq ($(HAS_WFD_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../common/wfd.o
endif
#endif // WFD_SUPPORT //


#ifdef LED_CONTROL_SUPPORT
ifeq ($(HAS_LED_CONTROL_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../common/rt_led.o
endif
#endif // LED_CONTROL_SUPPORT //


ifeq ($(HAS_ATE),y)
$(MOD_NAME)-objs += ../../ate/common/rt_ate.o
endif

ifeq ($(HAS_QA_SUPPORT),y)
$(MOD_NAME)-objs += ../../ate/common/rt_qa.o
endif







#ifdef CRDA_SUPPORT
ifeq ($(OSABL),NO)
ifeq ($(HAS_CFG80211_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../os/linux/cfg80211.o \
	../../os/linux/cfg80211drv.o
endif
endif

ifeq ($(OSABL),YES)
ifeq ($(HAS_CFG80211_SUPPORT),y)
$(MOD_NAME)-objs += \
	../../os/linux/cfg80211drv.o
endif
endif
#endif // CRDA_SUPPORT //


endif
#endif // CONFIG_STA_SUPPORT //



#chip releated





















#ifdef RT3290
ifneq ($(findstring rt3290,$(CHIPSET)),)
$(MOD_NAME)-objs += \
	../../common/cmm_mac_pci.o\
	../../common/cmm_data_pci.o\
	../../os/linux/rt_rbus_pci_drv.o\
	../../mcu/mcu.o\
	../../mcu/mcu_51.o\
	../../common/ee_prom.o\
	../../common/ee_efuse.o\
	../../common/rt_rf.o\
	../../chips/rt30xx.o\
	../../chips/rt3290.o

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
        ../../os/linux/rt_pci_rbus.o\
        ../../os/linux/rt_rbus_pci_util.o\
        ../../os/linux/pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
	../../common/frq_cal.o
endif

endif
#endif // RT3290 //

#ifdef RT6592
ifneq ($(findstring rt6592,$(CHIPSET)),)
$(MOD_NAME)-objs += \
        ../../common/cmm_mac_pci.o\
        ../../common/cmm_data_pci.o\
        ../../os/linux/rt_rbus_pci_drv.o\
        ../../mcu/mcu.o\
		../../mcu/rtmp_M51.o\
        ../../common/ee_prom.o\
        ../../common/ee_efuse.o\
        ../../common/rt_rf.o\
        ../../chips/rt6592.o

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
        ../../os/linux/rt_pci_rbus.o\
        ../../os/linux/rt_rbus_pci_util.o\
        ../../os/linux/pci_main_dev.o
endif
endif
#endif // RT6592 //





#ifdef MT76x0
ifneq ($(or $(findstring mt7650e,$(CHIPSET)),$(findstring mt7630e,$(CHIPSET)),$(findstring mt7610e,$(CHIPSET))),)
$(MOD_NAME)-objs += \
                ../../common/cmm_mac_pci.o\
                ../../common/cmm_data_pci.o\
                ../../os/linux/rt_rbus_pci_drv.o\
				../../common/ee_efuse.o\
                ../../common/ee_prom.o\
                ../../common/rt_rf.o\
                ../../chips/rt30xx.o\
				../../chips/rt65xx.o\
                ../../chips/mt76x0.o\
				../../mac/ral_nmac.o\
				../../mcu/mcu.o\
                ../../mcu/mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        ../../common/ee_flash.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../os/linux/rt_pci_rbus.o\
                ../../os/linux/rt_rbus_pci_util.o\
                ../../os/linux/pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        ../../common/frq_cal.o
endif

endif
#endif // MT76x0 //

#ifdef MT76x0
ifneq ($(or $(findstring mt7650u,$(CHIPSET)),$(findstring mt7630u,$(CHIPSET)),$(findstring mt7610u,$(CHIPSET))),)
$(MOD_NAME)-objs += \
                ../../common/cmm_mac_usb.o\
                ../../common/cmm_data_usb.o\
				../../common/rtusb_io.o\
				../../common/rtusb_data.o\
				../../common/rtusb_bulk.o\
                ../../os/linux/rt_usb.o\
                ../../common/ee_prom.o\
				../../common/ee_efuse.o\
                ../../common/rt_rf.o\
				../../chips/rt65xx.o\
                ../../chips/mt76x0.o\
                ../../mac/ral_nmac.o\
				../../mcu/mcu.o\
                ../../mcu/mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        		../../common/ee_flash.o
endif

ifeq ($(HAS_TSO_SUPPORT),y)
$(MOD_NAME)-objs += \
				../../naf/net_acc.o\
				../../naf/cso.o
endif

ifeq ($(HAS_CSO_SUPPORT), y)
$(MOD_NAME)-objs += \
				../../naf/net_acc.o\
				../../naf/cso.o
endif

ifeq ($(HAS_ATE),y)
$(MOD_NAME)-objs += \
	../../ate/chips/mt76x0_ate.o\
	../../ate/common/ate_usb.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../os/linux/rt_usb.o\
                ../../os/linux/rt_usb_util.o\
                ../../os/linux/usb_main_dev.o\
				../../common/rtusb_dev_id.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        ../../common/frq_cal.o
endif

endif
#endif // MT76x0 //


#ifdef RT8592
ifneq ($(findstring rt8592,$(CHIPSET)),)
$(MOD_NAME)-objs += \
                ../../common/cmm_mac_pci.o\
                ../../common/cmm_data_pci.o\
                ../../os/linux/rt_rbus_pci_drv.o\
                ../../common/ee_prom.o\
				../../common/ee_efuse.o\
                ../../common/rt_rf.o\
                ../../chips/rt30xx.o\
				../../chips/rt65xx.o\
				../../chips/rt6592.o\
                ../../chips/rt85592.o\
                ../../mac/ral_nmac.o\
				../../mcu/mcu.o\
                ../../mcu/mcu_and.o

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
$(MOD_NAME)-objs += \
        		../../common/ee_flash.o
endif

ifeq ($(OSABL),NO)
$(MOD_NAME)-objs += \
                ../../os/linux/rt_pci_rbus.o\
                ../../os/linux/rt_rbus_pci_util.o\
                ../../os/linux/pci_main_dev.o
endif

ifneq ($(findstring $(RT28xx_MODE),STA APSTA),)
$(MOD_NAME)-objs += \
        		../../common/frq_cal.o
endif

endif
#endif // RT8592 //


PHONY := clean install uninstall

clean:
	rm -f ../../common/*.o
	rm -f ../../common/.*.{cmd,flags,d}
	rm -f ../../os/linux/*.{o,ko,mod.{o,c}}
	rm -f ../../os/linux/.*.{cmd,flags,d}
	rm -fr ../../os/linux/.tmp_versions
#Must clean Module.symvers; or you will suffer symbol version not match
#when OS_ABL = YES.
	rm -f ../../os/linux/Module.symvers
	rm -f ../../os/linux/Modules.symvers
	rm -f ../../os/linux/Module.markers
	rm -f ../../os/linux/modules.order
	rm -f ../../chips/*.o
	rm -f ../../chips/.*.{cmd,flags,d}
ifeq ($(RT28xx_MODE),AP)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),STA)
	rm -f ../../sta/*.o
	rm -f ../../sta/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),APSTA)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
	rm -f ../../sta/*.o
	rm -f ../../sta/.*.{cmd,flags,d}
endif
endif
endif

install:
	rm -rf $(DAT_PATH)
	$(shell [ ! -f /etc/Wireless ] && mkdir /etc/Wireless)
	mkdir $(DAT_PATH)
	cp $(RT28xx_DIR)/$(DAT_FILE_NAME) $(DAT_PATH)/.
	install -d $(LINUX_SRC_MODULE)
	install -m 644 -c $(addsuffix .ko,$(MOD_NAME)) $(LINUX_SRC_MODULE)
	/sbin/depmod -a ${shell uname -r}

uninstall:
#	rm -rf $(DAT_PATH)
	rm -rf $(addprefix $(LINUX_SRC_MODULE),$(addsuffix .ko,$(MOD_NAME)))
	/sbin/depmod -a ${shell uname -r}

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
