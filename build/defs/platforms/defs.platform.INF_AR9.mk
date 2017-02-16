# INF_AR9 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /root/ar9/xR9_BSP1.2.2.0/source/kernel/opensource/linux-2.6.20/
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /root/ar9/ifx-lxdb26-1.0.2/gcc-3.4.4/toolchain-mips/bin/
