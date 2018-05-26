# Set default value for WIFI_MODE
# STA, AP (not supported?), APSTA (not supported?)
WIFI_MODE ?= STA

RT28xx_MODE = ${WIFI_MODE}

# Set default value for TARGET
# Currently, the only valid TARGET
TARGET ?= LINUX

# Set default value for CHIPSET
# Currently, the only known valid CHIPSET
# Other chipsets listed under 'build/defs/chipsets' might work
CHIPSET ?= mt7610u

MODULE = $(word 1, $(CHIPSET))

#OS ABL - YES or NO
OSABL = NO

#RT28xx_DIR = home directory of RT28xx source code
RT28xx_DIR = $(shell pwd)

# PLATFORM: Target platform
# See build/defs/platforms for the list of possible platforms
# Set the default PLATFORM (unless previously specified)
PLATFORM ?= PC

#APSOC
ifeq ($(MODULE),3050)
PLATFORM = RALINK_3050
endif
ifeq ($(MODULE),3052)
PLATFORM = RALINK_3052
endif
ifeq ($(MODULE),3350)
PLATFORM = RALINK_3050
endif
ifeq ($(MODULE),3352)
PLATFORM = RALINK_3352
endif

include ${RT28xx_DIR}/build/defs/platforms/defs.platform.${PLATFORM}.mk

$(if ${PLATFORM_SUPPORTED}, , $(error "Platform ${PLATFORM} not supported"))

include $(RT28xx_DIR)/os/linux/config.mk

#RELEASE Package
RELEASE = DPO

# It will probably be better in the future to put this in some sort of
# target definitions makefile fragment and then include it. But for now,
# keep it as is.
MAKE_LINUX = make
MAKE = $(if ${MAKE_${TARGET}},${MAKE_${TARGET}},$(error "MAKE not defined"))

export OSABL RT28xx_DIR RT28xx_MODE LINUX_SRC CROSS_COMPILE CROSS_COMPILE_INCLUDE PLATFORM RELEASE CHIPSET MODULE LINUX_SRC_MODULE TARGET HAS_WOW_SUPPORT

# The targets that may be used.
PHONY += all build_tools LINUX clean uninstall install osabl

ifeq ($(TARGET),LINUX)
all: build_tools $(TARGET)
else
all: $(TARGET)
endif 



build_tools:
	$(MAKE) -C tools
	$(RT28xx_DIR)/tools/bin2h

LINUX:
ifneq (,$(findstring 2.4,$(LINUX_SRC)))

ifeq ($(OSABL),YES)
	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4.util
endif

	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4

ifeq ($(OSABL),YES)
	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4.netif
endif

ifeq ($(RT28xx_MODE),AP)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_ap.o /tftpboot
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/rtutil$(MODULE)_ap.o /tftpboot
	cp -f $(RT28xx_DIR)/os/linux/rtnet$(MODULE)_ap.o /tftpboot
endif
ifeq ($(PLATFORM),INF_AMAZON_SE)
	cp -f /tftpboot/rt2870ap.o /backup/ifx/build/root_filesystem/lib/modules/2.4.31-Amazon_SE-3.6.2.2-R0416_Ralink/kernel/drivers/net
endif
else	
ifeq ($(RT28xx_MODE),APSTA)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_apsta.o /tftpboot
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/rtutil$(MODULE)_apsta.o /tftpboot
	cp -f $(RT28xx_DIR)/os/linux/rtnet$(MODULE)_apsta.o /tftpboot
endif
else
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_sta.o /tftpboot
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/rtutil$(MODULE)_sta.o /tftpboot
	cp -f $(RT28xx_DIR)/os/linux/rtnet$(MODULE)_sta.o /tftpboot
endif
endif	
endif	
else

ifeq ($(OSABL),YES)
	cp -f os/linux/Makefile.6.util $(RT28xx_DIR)/os/linux/Makefile
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif

	cp -f os/linux/Makefile.6 $(RT28xx_DIR)/os/linux/Makefile
ifeq ($(PLATFORM),DM6446)
	$(MAKE)  ARCH=arm -C  $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
else
ifeq ($(PLATFORM),FREESCALE8377)
	$(MAKE) ARCH=powerpc CROSS_COMPILE=$(CROSS_COMPILE) -C  $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
else
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif
endif

ifeq ($(OSABL),YES)
	cp -f os/linux/Makefile.6.netif $(RT28xx_DIR)/os/linux/Makefile
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif

ifeq ($(RT28xx_MODE),AP)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_ap.ko /tftpboot
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_ap_util.ko /tftpboot
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_ap_net.ko /tftpboot
endif
	rm -f os/linux/$(MODULE)_ap.ko.lzma
	/root/bin/lzma e os/linux/$(MODULE)_ap.ko os/linux/$(MODULE)_ap.ko.lzma
else	
ifeq ($(RT28xx_MODE),APSTA)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_apsta.ko /tftpboot
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_apsta_util.ko /tftpboot
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_apsta_net.ko /tftpboot
endif
else
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_sta.ko /tftpboot 2>/dev/null || :
ifeq ($(OSABL),YES)
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_sta_util.ko /tftpboot 2>/dev/null || :
	cp -f $(RT28xx_DIR)/os/linux/$(MODULE)_sta_net.ko /tftpboot 2>/dev/null || :
endif
ifeq ($(PLATFORM),MT85XX)
	cp -f $(RT28xx_DIR)/os/linux/rtsta.ko $(RT28xx_DIR)/../../../../../BDP_Generic/build_linux_ko/src/driver/wlan/
endif
endif
endif
endif


clean:
ifeq ($(TARGET), LINUX)
	cp -f os/linux/Makefile.clean os/linux/Makefile
	$(MAKE) -C os/linux clean
	rm -rf os/linux/Makefile
endif	

uninstall:
ifeq ($(TARGET), LINUX)
ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	$(MAKE) -C $(RT28xx_DIR)/os/linux -f Makefile.4 uninstall
else
	$(MAKE) -C $(RT28xx_DIR)/os/linux -f Makefile.6 uninstall
endif
endif

install:
ifeq ($(TARGET), LINUX)
ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	$(MAKE) -C $(RT28xx_DIR)/os/linux -f Makefile.4 install
else
	$(MAKE) -C $(RT28xx_DIR)/os/linux -f Makefile.6 install
endif
endif

osutil:
ifeq ($(OSABL),YES)
ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4.util
else
	cp -f os/linux/Makefile.6.util $(RT28xx_DIR)/os/linux/Makefile
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif
endif

osnet:
ifeq ($(OSABL),YES)
ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4.netif
else
	cp -f os/linux/Makefile.6.netif $(RT28xx_DIR)/os/linux/Makefile
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif
endif

osdrv:
ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	$(MAKE) -C $(RT28xx_DIR)/os/linux/ -f Makefile.4
else
	cp -f os/linux/Makefile.6 $(RT28xx_DIR)/os/linux/Makefile
	$(MAKE) -C $(LINUX_SRC) SUBDIRS=$(RT28xx_DIR)/os/linux modules
endif

# Declare the contents of the .PHONY variable as phony.  We keep that information in a variable
.PHONY: $(PHONY)
