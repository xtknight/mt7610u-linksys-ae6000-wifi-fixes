# RALINK_3052 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/peter/ap_soc/SDK_3_3_0_0/RT288x_SDK/source/linux-2.6.21.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/buildroot-gcc342/bin/mipsel-linux-uclibc-

CFLAGS_${PLATFORM} := -D__KERNEL__                                          \
                      -I${LINUX_SRC}/include/asm-mips/mach-generic          \
                      -I${LINUX_SRC}/include -Wall -Wstrict-prototypes      \
                      -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common   \
                      -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic      \
                      -pipe  -finline-limit=100000 -march=mips2 -mabi=32    \
                      -Wa,--trap -DLINUX -nostdinc -iwithprefix include
