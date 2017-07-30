# NXP_TV550 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /data/tv550/kernel/linux-2.6.28.9
LINUX_SRC_MODULE ?= /data/tv550/kernel/linux-2.6.28.9/drivers/net/wireless
CROSS_COMPILE ?= /opt/embeddedalley/nxp_tv550/bin/mipsel-linux-

ifneq (,$(findstring 2.4,$(LINUX_SRC)))
# Linux 2.4
CFLAGS_${PLATFORM} := -D__KERNEL__                                       \
                      -I${LINUX_SRC}/include                             \
                      -O2 -fomit-frame-pointer -fno-strict-aliasing      \
                      -fno-common -pipe -mpreferred-stack-boundary=2     \
                      -march=mips -DMODULE -DMODVERSIONS                 \
                      -include ${LINUX_SRC}/include/linux/modversions.h
else
# Linux 2.6
EXTRA_CFLAGS :=
endif

