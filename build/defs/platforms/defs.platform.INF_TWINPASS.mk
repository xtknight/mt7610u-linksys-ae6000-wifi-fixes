# INF_TWINPASS platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

# For Linux 2.6, use ...
# LINUX_SRC = /lib/modules/$(shell uname -r)/build

# For Linux 2.4, change to your local setting
LINUX_SRC ?= /project/stable/twinpass/release/2.0.1/source/kernel/opensource/linux-2.4.31/

LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
