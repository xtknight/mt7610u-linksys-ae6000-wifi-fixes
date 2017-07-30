# IKANOS_V180 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_IKANOS_V180
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: The CFLAGS_IKANOS_V180 line seems fishy as the "-Wa," is followed
# by a space and then -DMODULE.

LINUX_SRC ?= /home/sample/projects/LX_BSP_VX180_5_4_0r1_ALPHA_26DEC07/linux-2.6.18
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
CFLAGS_IKANOS_V180 := -D__KERNEL__                                          \
                      -I$(LINUX_SRC)/include                                \
                      -I$(LINUX_SRC)/include/asm/gcc                        \
                      -I$(LINUX_SRC)/include/asm-mips/mach-tango2           \
                      -I$(LINUX_SRC)/include/asm-mips/mach-generic          \
                      -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs      \
                      -fno-strict-aliasing -fno-common -ffreestanding -O2   \
                      -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic      \
                      -pipe -mips32r2 -Wa, -DMODULE
