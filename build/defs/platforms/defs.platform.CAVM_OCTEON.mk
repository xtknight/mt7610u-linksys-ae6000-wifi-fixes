# CAVM_OCTEON platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    EXTRA_CFLAGS_CAVM_OCTEON
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: At the time this file was created, OCTEON_ROOT was only used in this
# file. It is not known if this variable was ever used in previous versions.

OCTEON_ROOT ?= /usr/local/Cavium_Networks/OCTEON-SDK
LINUX_SRC ?= $(OCTEON_ROOT)/linux/kernel_2.6/linux
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips64-octeon-linux-gnu-
EXTRA_CFLAGS_CAVM_OCTEON := -mabi=64
