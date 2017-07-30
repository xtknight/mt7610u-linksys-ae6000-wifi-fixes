# IXP platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    EXTRA_CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /project/stable/Gmtek/snapgear-uclibc/linux-2.6.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= arm-linux-

CFLAGS_${PLATFORM} := -v -D__KERNEL__ -DMODULE                            \
                      -I$(LINUX_SRC)/include                              \
                      -mbig-endian -Wall -Wstrict-prototypes              \
                      -Wno-trigraphs -O2 -fno-strict-aliasing             \
                      -fno-common -Uarm -fno-common -pipe -mapcs-32       \
                      -D__LINUX_ARM_ARCH__=5 -mcpu=xscale -mtune=xscale   \
                      -malignment-traps -msoft-float

EXTRA_CFLAGS_${PLATFORM} := -v -mbig-endian
