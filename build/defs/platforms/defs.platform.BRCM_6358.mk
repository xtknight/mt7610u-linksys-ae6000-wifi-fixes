# BRCM_6358 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_BRCM_6358
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?=
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?=
CFLAGS_BRCM_6358 := -nostdinc -iwithprefix include                          \
                    -D__KERNEL__ -Wall -Wstrict-prototypes -Wno-trigraphs   \
                    -fno-strict-aliasing -fno-common                        \
                    -I $(LINUX_SRC)/include/asm/gcc                         \
                    -G 0 -mno-abicalls -fno-pic -pipe                       \
                    -finline-limit=100000 -mabi=32 -march=mips32            \
                    -Wa,-32 -Wa,-march=mips32 -Wa,-mips32 -Wa,--trap        \
                    -I$(LINUX_SRC)/include/asm-mips/mach-bcm963xx           \
                    -I$(LINUX_SRC)/include/asm-mips/mach-generic            \
                    -Os -fomit-frame-pointer -Wdeclaration-after-statement  \
                    -DMODULE -mlong-calls

