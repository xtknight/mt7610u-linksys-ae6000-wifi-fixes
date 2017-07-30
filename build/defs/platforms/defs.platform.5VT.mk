# 5VT platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_5VT
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/ralink-2860-sdk-5vt-distribution/linux-2.6.17
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/crosstool/uClibc_v5te_le_gcc_4_1_1/bin/arm-linux-
CFLAGS_5VT := -D__KERNEL__ -I${LINUX_SRC}/include -mlittle-endian          \
              -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs             \
              -fno-strict-aliasing -fno-common -O3 -fno-omit-frame-pointer \
              -fno-optimize-sibling-calls -fno-omit-frame-pointer          \
              -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork \
              -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm926ej-s      \
              --param max-inline-insns-single=40000  -Uarm                 \
              -Wdeclaration-after-statement -Wno-pointer-sign -DMODULE
