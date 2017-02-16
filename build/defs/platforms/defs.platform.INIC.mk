# INIC platform definitions file
#
# Defines the following variables:
#    UCOS_SRC
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: This uses UCOS_SRC instead of LINUX_SRC. It is not currently known
# if this refers to TARGET=UCOS. If so, then this file can be deleted as
# there is no support for TARGET=UCOS.

UCOS_SRC ?= /opt/uCOS/iNIC_rt2880
CROSS_COMPILE ?= /usr/bin/mipsel-linux-
