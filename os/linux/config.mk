HAS_RSSI_FEEDBACK=n

# Support XLINK mode
HAS_XLINK=n

# Support WDS function
HAS_WDS=n

# Support AP-Client function
HAS_APCLI=n

#Support IGMP-Snooping function.
HAS_IGMP_SNOOP_SUPPORT=n

#Support DFS function
HAS_DFS_SUPPORT=n

#Support Carrier-Sense function
HAS_CS_SUPPORT=n

#Support WEPAUTO mode try Open first then shared
HAS_WEPAUTO_OPEN_FIRST_SUPPORT=n

# Support for Multiple Cards
HAS_MC_SUPPORT=n

#Support for PCI-MSI
HAS_MSI_SUPPORT=n


#Support for IEEE802.11e DLS
HAS_QOS_DLS_SUPPORT=n

#Support for EXT_CHANNEL
HAS_EXT_BUILD_CHANNEL_LIST=n

#Support for IDS 
HAS_IDS_SUPPORT=n


#Support for Net-SNMP
HAS_SNMP_SUPPORT=n

#Support features of 802.11n Draft3
HAS_DOT11N_DRAFT3_SUPPORT=y

#Support features of Single SKU. 
HAS_SINGLE_SKU_SUPPORT=n

#Support features of 802.11n
HAS_DOT11_N_SUPPORT=y

#Support for 802.11ac VHT
HAS_DOT11_VHT_SUPPORT=y



#Support for 2860/2880 co-exist 
HAS_RT2880_RT2860_COEXIST=n

HAS_KTHREAD_SUPPORT=n





#Support for WiFi Display
HAS_WFD_SUPPORT=n

#Support for Auto channel select enhance
HAS_AUTO_CH_SELECT_ENHANCE=n

#Support statistics count
HAS_STATS_COUNT=y

#Support TSSI Antenna Variation
HAS_TSSI_ANTENNA_VARIATION=n

#Support USB_BULK_BUF_ALIGMENT
HAS_USB_BULK_BUF_ALIGMENT=n

#Support for USB_SUPPORT_SELECTIVE_SUSPEND
HAS_USB_SUPPORT_SELECTIVE_SUSPEND=n

#Support USB load firmware by multibyte
HAS_USB_FIRMWARE_MULTIBYTE_WRITE=n


#Support ANDROID_SUPPORT
HAS_ANDROID_SUPPORT=n

#HAS_IFUP_IN_PROBE_SUPPORT
HAS_IFUP_IN_PROBE_SUPPORT=n




#Support TXRX SW Antenna Diversity
HAS_TXRX_SW_ANTDIV_SUPPORT=n

#Client support WDS function
HAS_CLIENT_WDS_SUPPORT=n

#Support for Bridge Fast Path & Bridge Fast Path function open to other module
HAS_BGFP_SUPPORT=n
HAS_BGFP_OPEN_SUPPORT=n

# Support HOSTAPD function
HAS_HOSTAPD_SUPPORT=n

#Support GreenAP function
HAS_GREENAP_SUPPORT=n

#Support RFKILL hardware block/unblock LINUX-only function
HAS_RFKILL_HW_SUPPORT=n



HAS_APCLI_WPA_SUPPLICANT=n

HAS_RTMP_FLASH_SUPPORT=n


HAS_LED_CONTROL_SUPPORT=y


#Support WIDI feature
#Must enable HAS_WSC at the same time.

HAS_TXBF_SUPPORT=n

HAS_STREAM_MODE_SUPPORT=n

HAS_RATE_ADAPT_AGS_SUPPORT=n





HAS_TEMPERATURE_TX_ALC=y

HAS_WOW_SUPPORT=n
HAS_WOW_IFDOWN_SUPPORT=n

HAS_HDR_TRANS_SUPPORT=n

HAS_MAC_REPEATER_SUPPORT=n

HAS_FPGA_MODE=n

HAS_WIFI_TEST=n

HAS_WIFI_P2P_CONCURRENT_FAST_SCAN=n

STA_DRIVER_BUILD := 20141022-1327

#################################################

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld

ifndef $(WFLAGS)
WFLAGS := -DSTA_DRIVER_BUILD="\"${STA_DRIVER_BUILD}\""
else
WFLAGS += -DSTA_DRIVER_BUILD="\"${STA_DRIVER_BUILD}\""
endif

WFLAGS += -g -DAGGREGATION_SUPPORT -DPIGGYBACK_SUPPORT -DWMM_SUPPORT  -DLINUX -Wall -Wstrict-prototypes -Wno-trigraphs
WFLAGS += -DSYSTEM_LOG_SUPPORT -DRT28xx_MODE=$(RT28xx_MODE) -DCHIPSET=$(MODULE) -DRESOURCE_PRE_ALLOC -DENHANCED_STAT_DISPLAY
#WFLAGS += -DFPGA_MODE
WFLAGS += -I$(RT28xx_DIR)/include





ifeq ($(HAS_WIFI_P2P_CONCURRENT_FAST_SCAN),y)
WFLAGS += -DWIFI_P2P_CONCURRENT_FAST_SCAN
endif

ifeq ($(HAS_WEPAUTO_OPEN_FIRST_SUPPORT),y)
WFLAGS += -DWEPAUTO_OPEN_FIRST
endif

ifeq ($(HAS_KTHREAD_SUPPORT),y)
WFLAGS += -DKTHREAD_SUPPORT
endif

ifeq ($(HAS_RTMP_FLASH_SUPPORT),y)
WFLAGS += -DRTMP_FLASH_SUPPORT
endif

ifeq ($(HAS_STREAM_MODE_SUPPORT),y)
WFLAGS += -DSTREAM_MODE_SUPPORT
endif

ifeq ($(HAS_SINGLE_SKU_SUPPORT),y)
WFLAGS += -DSINGLE_SKU_V2
endif

ifeq ($(HAS_HDR_TRANS_SUPPORT),y)
WFLAGS += -DHDR_TRANS_SUPPORT
endif

ifeq ($(HAS_DOT11_VHT_SUPPORT),y)
WFLAGS += -DDOT11_VHT_AC
endif


ifeq ($(HAS_MAC_REPEATER_SUPPORT),y)
WFLAGS += -DMAC_REPEATER_SUPPORT
endif


#################################################

# config for STA mode

ifeq ($(RT28xx_MODE),STA)
WFLAGS += -DCONFIG_STA_SUPPORT -DSCAN_SUPPORT -DDBG

ifeq ($(HAS_HDR_TRANS_SUPPORT),y)
WFLAGS += -DHDR_TRANS_TX_SUPPORT
endif

ifeq ($(HAS_XLINK),y)
WFLAGS += -DXLINK_SUPPORT
endif

ifeq ($(HAS_SNMP_SUPPORT),y)
WFLAGS += -DSNMP_SUPPORT
endif

ifeq ($(HAS_QOS_DLS_SUPPORT),y)
WFLAGS += -DQOS_DLS_SUPPORT
endif

ifeq ($(HAS_DOT11_N_SUPPORT),y)
WFLAGS += -DDOT11_N_SUPPORT

ifeq ($(HAS_DOT11N_DRAFT3_SUPPORT),y)
WFLAGS += -DDOT11N_DRAFT3
endif

ifeq ($(HAS_TXBF_SUPPORT),y)
WFLAGS += -DTXBF_SUPPORT
endif

endif


ifeq ($(HAS_WFD_SUPPORT),y)
HAS_P2P_SUPPORT=y
HAS_P2P_SPECIFIC_WIRELESS_EVENT=y
WFLAGS += -DWFD_SUPPORT
endif


ifeq ($(HAS_CS_SUPPORT),y)
WFLAGS += -DCARRIER_DETECTION_SUPPORT
endif

ifeq ($(HAS_STATS_COUNT),y)
WFLAGS += -DSTATS_COUNT_SUPPORT
endif

ifeq ($(HAS_TSSI_ANTENNA_VARIATION),y)
WFLAGS += -DTSSI_ANTENNA_VARIATION
endif

ifeq ($(HAS_ANDROID_SUPPORT),y)
WFLAGS += -DANDROID_SUPPORT
endif


ifeq ($(HAS_IFUP_IN_PROBE_SUPPORT),y)
WFLAGS += -DIFUP_IN_PROBE
endif

ifeq ($(HAS_USB_SUPPORT_SELECTIVE_SUSPEND),y)
WFLAGS += -DUSB_SUPPORT_SELECTIVE_SUSPEND
endif

ifeq ($(HAS_USB_FIRMWARE_MULTIBYTE_WRITE),y)
WFLAGS += -DUSB_FIRMWARE_MULTIBYTE_WRITE -DMULTIWRITE_BYTES=4
endif

ifeq ($(HAS_RFKILL_HW_SUPPORT),y)
WFLAGS += -DRFKILL_HW_SUPPORT
endif

ifeq ($(HAS_TXRX_SW_ANTDIV_SUPPORT),y)
WFLAGS += -DTXRX_SW_ANTDIV_SUPPORT
endif


ifeq ($(HAS_WIDI_SUPPORT),y)
WFLAGS += -DWIDI_SUPPORT

ifeq ($(HAS_P2P_SUPPORT),y)
ifeq ($(HAS_INTEL_WFD_SUPPORT),y)
WFLAGS += -DINTEL_WFD_SUPPORT
endif

ifeq ($(HAS_WFA_WFD_SUPPORT),y)
WFLAGS += -DWFA_WFD_SUPPORT
endif
endif

endif

ifeq ($(HAS_WOW_SUPPORT),y)
WFLAGS += -DWOW_SUPPORT
endif

ifeq ($(HAS_WOW_IFDOWN_SUPPORT),y)
WFLAGS += -DWOW_IFDOWN_SUPPORT
endif

endif
# endif of ifeq ($(RT28xx_MODE),STA)

#################################################

#################################################

#
# Common compiler flag
#






ifeq ($(HAS_EXT_BUILD_CHANNEL_LIST),y)
WFLAGS += -DEXT_BUILD_CHANNEL_LIST
endif

ifeq ($(HAS_IDS_SUPPORT),y)
WFLAGS += -DIDS_SUPPORT
endif


ifeq ($(HAS_CLIENT_WDS_SUPPORT),y)
WFLAGS += -DCLIENT_WDS
endif

ifeq ($(HAS_BGFP_SUPPORT),y)
WFLAGS += -DBG_FT_SUPPORT
endif

ifeq ($(HAS_BGFP_OPEN_SUPPORT),y)
WFLAGS += -DBG_FT_OPEN_SUPPORT
endif


ifeq ($(HAS_LED_CONTROL_SUPPORT),y)
WFLAGS += -DLED_CONTROL_SUPPORT
endif

ifeq ($(HAS_FPGA_MODE),y)
WFLAGS += -DCONFIG_FPGA_MODE
endif

ifeq ($(HAS_WIFI_TEST),y)
WFLAGS += -DCONFIG_WIFI_TEST
endif


ifeq ($(HAS_TEMPERATURE_TX_ALC),y)
WFLAGS += -DRTMP_TEMPERATURE_TX_ALC
endif

#################################################
# ChipSet specific definitions.
#

ifneq ($(or $(findstring mt7650u,$(CHIPSET)),$(findstring mt7630u,$(CHIPSET)),$(findstring mt7610u,$(CHIPSET))),)
WFLAGS += -DMT76x0 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DA_BAND_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE -DCONFIG_ANDES_SUPPORT
ifneq ($(findstring mt7650u,$(CHIPSET)),)
WFLAGS += -DMT7650
endif

ifneq ($(findstring mt7630u,$(CHIPSET)),)
WFLAGS += -DMT7630
endif

ifneq ($(findstring mt7610u,$(CHIPSET)),)
WFLAGS += -DMT7610
endif

ifeq ($(HAS_CSO_SUPPORT), y)
WFLAGS += -DCONFIG_CSO_SUPPORT -DCONFIG_TSO_SUPPORT
endif

CHIPSET_DAT = 2870
endif

#################################################


ifeq ($(PLATFORM),5VT)
#WFLAGS += -DCONFIG_5VT_ENHANCE
endif

ifeq ($(HAS_DFS_SUPPORT),y)
WFLAGS += -DDFS_SUPPORT
endif

ifeq ($(HAS_MC_SUPPORT),y)
WFLAGS += -DMULTIPLE_CARD_SUPPORT
endif

#kernel build options for 2.4
# move to Makefile outside LINUX_SRC := /opt/star/kernel/linux-2.4.27-star

ifeq ($(PLATFORM),PC)
    ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	# Linux 2.4
	CFLAGS := -D__KERNEL__ -I$(LINUX_SRC)/include -O2 -fomit-frame-pointer -fno-strict-aliasing -fno-common -pipe -mpreferred-stack-boundary=2 -march=i686 -DMODULE -DMODVERSIONS -include $(LINUX_SRC)/include/linux/modversions.h $(WFLAGS)
	export CFLAGS
    else
	# Linux 2.6
	EXTRA_CFLAGS := $(WFLAGS) 
    endif
endif
