# MT85XX platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: It seems odd that ${CC} is defined in this file as it is also
# defined in os/linux/config.mk in the same way. This makes it a potential
# cleanup item.

LINUX_SRC ?= $(RT28xx_DIR)/../../../../build_linux
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= armv7a-mediatek451_001_vfp-linux-gnueabi-

CC = ${CROSS_COMPILE}gcc
$(warning :::::::::::::::::::::::::::::::::::::::::::::)
$(warning CC=${CC} for wifi driver)
$(warning :::::::::::::::::::::::::::::::::::::::::::::)
