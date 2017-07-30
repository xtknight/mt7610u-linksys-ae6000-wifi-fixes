# INF_AR9 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /root/ar9/xR9_BSP1.2.2.0/source/kernel/opensource/linux-2.6.20/
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /root/ar9/ifx-lxdb26-1.0.2/gcc-3.4.4/toolchain-mips/bin/
CFLAGS_${PLATFORM} := -Wundef -fno-strict-aliasing -fno-common             \
                      -fno-pic -ffreestanding -Os -fomit-frame-pointer     \
                      -G 0 -mno-abicalls -fno-pic -pipe -msoft-float       \
                      -mabi=32 -mlong-calls -march=mips32r2 -mtune=34kc    \
                      -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2          \
                      -Wa,-mips32r2 -Wa,--trap                             \
                      -I$(LINUX_SRC)/include/asm-mips/mach-generic
