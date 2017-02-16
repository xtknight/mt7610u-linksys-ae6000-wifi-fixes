# BL23570 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/FIBERHOME/linux-2.6.34.8
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-wrs-linux-gnu-mips_74k_softfp-glibc_small-
ARCH := mips

export ARCH
