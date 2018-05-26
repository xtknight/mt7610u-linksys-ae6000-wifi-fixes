# MT85XX platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: It seems odd that ${CC} is defined in this file as it is also
# defined in os/linux/config.mk in the same way. This makes it a potential
# cleanup item.

LINUX_SRC ?= $(RT28xx_DIR)/../../../../build_linux
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= armv7a-mediatek451_001_vfp-linux-gnueabi-

CC = ${CROSS_COMPILE}gcc
$(warning :::::::::::::::::::::::::::::::::::::::::::::)
$(warning CC=${CC} for wifi driver)
$(warning :::::::::::::::::::::::::::::::::::::::::::::)

ifneq (,$(findstring 2.4,$(LINUX_SRC)))
# Linux 2.4
CFLAGS_${PLATFORM} := -D__KERNEL__                                        \
                      -I${LINUX_SRC}/include                              \
                      -O2 -fomit-frame-pointer -fno-strict-aliasing       \
                      -fno-common -pipe -mpreferred-stack-boundary=2      \
                      -march=i686 -DMODULE -DMODVERSIONS                  \
                      -include ${LINUX_SRC}/include/linux/modversions.h
else
# Linux 2.6
EXTRA_CFLAGS_${PLATFORM} += -DMT85XX
EXTRA_CFLAGS_${PLATFORM} += -D _NO_TYPEDEF_BOOL_    \
                            -D _NO_TYPEDEF_UCHAR_   \
                            -D _NO_TYPEDEF_UINT8_   \
                            -D _NO_TYPEDEF_UINT16_  \
                            -D _NO_TYPEDEF_UINT32_  \
                            -D _NO_TYPEDEF_UINT64_  \
                            -D _NO_TYPEDEF_CHAR_    \
                            -D _NO_TYPEDEF_INT16_   \
                            -D _NO_TYPEDEF_INT32_   \
                            -D _NO_TYPEDEF_INT64_
endif
