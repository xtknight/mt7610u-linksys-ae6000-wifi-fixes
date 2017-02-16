# PC platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED

# Linux 2.6 and later
LINUX_SRC ?= /lib/modules/$(shell uname -r)/build
# For Linux 2.4, change to your local setting.
# LINUX_SRC = /usr/src/linux-2.4

LINUX_SRC_MODULE ?= /lib/modules/$(shell uname -r)/kernel/drivers/net/wireless/
CROSS_COMPILE ?=
PLATFORM_SUPPORTED = y
