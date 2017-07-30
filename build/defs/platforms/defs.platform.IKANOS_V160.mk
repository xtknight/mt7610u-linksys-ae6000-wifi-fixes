# IKANOS_V160 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_IKANOS_V160
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: The CFLAGS_IKANOS_V160 line seems fishy as the "-Wa," is followed
# by a space and then -DMODULE.

LINUX_SRC ?= /home/sample/projects/LX_2618_RG_5_3_00r4_SRC/linux-2.6.18
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
CFLAGS_IKANOS_V160 := -D__KERNEL__                                          \
                      -I$(LINUX_SRC)/include                                \
                      -I$(LINUX_SRC)/include/asm/gcc                        \
                      -I$(LINUX_SRC)/include/asm-mips/mach-tango2           \
                      -I$(LINUX_SRC)/include/asm-mips/mach-generic          \
                      -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs      \
                      -fno-strict-aliasing -fno-common -ffreestanding -O2   \
                      -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic      \
                      -pipe -march=lx4189 -Wa, -DMODULE
