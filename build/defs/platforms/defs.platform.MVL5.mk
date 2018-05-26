# MVL5 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home2/charlestu/AP-VT3426/linux-2.6.18
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/montavista/pro/devkit/arm/v5t_le_mvl5/bin/arm_v5t_le-
CFLAGS_${PLATFORM} := -D__KERNEL__                                          \
                      -I${LINUX_SRC}/include                                \
                      -mlittle-endian -Wall -Wundef -Wstrict-prototypes     \
                      -Wno-trigraphs -fno-strict-aliasing -fno-common -O3   \
                      -fno-omit-frame-pointer -fno-optimize-sibling-calls   \
                      -fno-omit-frame-pointer -mapcs -mno-sched-prolog      \
                      -mno-thumb-interwork -D__LINUX_ARM_ARCH__=5           \
                      -march=armv5te -mtune=arm926ej-s                      \
                      --param max-inline-insns-single=40000                 \
                      -Uarm -Wdeclaration-after-statement                   \
                      -Wno-pointer-sign -DMODULE
