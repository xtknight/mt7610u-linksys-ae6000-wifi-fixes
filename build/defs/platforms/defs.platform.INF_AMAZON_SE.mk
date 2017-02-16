# INF_AMAZON_SE platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

# Linux 2.6
# LINUX_SRC = /lib/modules/$(shell uname -r)/build

# Linux 2.4 Change to your local setting
LINUX_SRC ?= /backup/ifx/3.6.2.2/source/kernel/opensource/linux-2.4.31

LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/uclibc-toolchain/ifx-lxdb-1-2-3-external/gcc-3.3.6/toolchain-mips/R0208V35/mips-linux-uclibc/bin/
