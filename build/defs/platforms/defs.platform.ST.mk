# ST platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/STM/STLinux-2.2/devkit/sources/kernel/linux0039
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/STM/STLinux-2.2/devkit/sh4/bin/sh4-linux-

ARCH := sh

export ARCH
