# STAR platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/star/kernel/linux-2.4.27-star
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/star/tools/arm-linux/bin/arm-linux-
