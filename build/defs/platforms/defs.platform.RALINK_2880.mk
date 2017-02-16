# RALINK_2880 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /project/stable/RT288x/RT288x_SDK/source/linux-2.4.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/buildroot-gdb/bin/mipsel-linux-
