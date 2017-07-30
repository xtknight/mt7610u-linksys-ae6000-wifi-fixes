# STAR platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/star/kernel/linux-2.4.27-star
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/star/tools/arm-linux/bin/arm-linux-
CFLAGS_${PLATFORM} := -D__KERNEL__                                        \
                      -I$(LINUX_SRC)/include                              \
                      -Wall -Wstrict-prototypes -Wno-trigraphs -O2        \
                      -fno-strict-aliasing -fno-common -Uarm              \
                      -fno-common -pipe -mapcs-32 -D__LINUX_ARM_ARCH__=4  \
                      -march=armv4 -mshort-load-bytes -msoft-float        \
                      -Uarm -DMODULE -DMODVERSIONS                        \
                      -include $(LINUX_SRC)/include/linux/modversions.h
