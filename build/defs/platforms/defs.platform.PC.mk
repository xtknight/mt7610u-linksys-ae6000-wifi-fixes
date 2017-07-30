# PC platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED

# Linux 2.6 and later
LINUX_SRC ?= /lib/modules/$(shell uname -r)/build
# For Linux 2.4, change to your local setting.
# LINUX_SRC = /usr/src/linux-2.4

LINUX_SRC_MODULE ?= /lib/modules/$(shell uname -r)/kernel/drivers/net/wireless/
CROSS_COMPILE ?=
PLATFORM_SUPPORTED = y

ifneq (,$(findstring 2.4,$(LINUX_SRC)))
# Linux 2.4
CFLAGS_${PLATFORM} := -D__KERNEL__                                        \
                      -I${LINUX_SRC}/include -O2                          \
                      -fomit-frame-pointer -fno-strict-aliasing           \
                      -fno-common -pipe -mpreferred-stack-boundary=2      \
                      -march=i686 -DMODULE -DMODVERSIONS                  \
                      -include $(LINUX_SRC)/include/linux/modversions.h
else
# Linux 2.6
EXTRA_CFLAGS_${PLATFORM} :=
endif

