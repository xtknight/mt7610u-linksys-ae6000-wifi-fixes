# DM6446 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_DM6446
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: CFLAGS_DM646 appears to be fishy as "-o" is last flag/option.

LINUX_SRC ?= /home/fonchi/work/soc/ti-davinci
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= arm_v5t_le-
CFLAGS_DM6446 := -nostdinc -iwithprefix include                           \
                 -D__KERNEL__                                             \
                 -I$(LINUX_SRC)/include                                   \
                 -Wall -Wstrict-prototypes -Wno-trigraphs                 \
                 -fno-strict-aliasing -fno-common -Os                     \
                 -fno-omit-frame-pointer -fno-omit-frame-pointer          \
                 -mapcs -mno-sched-prolog -mlittle-endian -mabi=apcs-gnu  \
                 -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi    \
                 -msoft-float -Uarm -Wdeclaration-after-statement         \
                 -c -o
