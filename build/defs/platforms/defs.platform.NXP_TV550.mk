# NXP_TV550 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /data/tv550/kernel/linux-2.6.28.9
LINUX_SRC_MODULE ?= /data/tv550/kernel/linux-2.6.28.9/drivers/net/wireless
CROSS_COMPILE ?= /opt/embeddedalley/nxp_tv550/bin/mipsel-linux-
