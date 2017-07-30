# BL23570 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    ARCH
#    EXTRA_CFLAGS_BL23570
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/FIBERHOME/linux-2.6.34.8
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-wrs-linux-gnu-mips_74k_softfp-glibc_small-
ARCH := mips
EXTRA_CFLAGS_BL23570 := -D__KERNEL__                                        \
                        -I$(LINUX_SRC)/include                              \
                        -I$(LINUX_SRC)/include/asm/gcc                      \
                        -I$(LINUX_SRC)/include/asm-mips/mach-tango2         \
                        -I$(LINUX_SRC)/include/asm-mips/mach-generic        \
                        -I$(RT2860_DIR)/include                             \
                        -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2                  \
                        -DEM86XX_REVISION=6                                 \
                        -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs    \
                        -fno-strict-aliasing -fno-common -ffreestanding -O2 \
                        -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic    \
                        -pipe -mabi=32 -march=74kc -Wa,-32                  \
                        -Wa,-march=mips32r2 -Wa,-mips32r2 -Wa,--trap        \
                        -DMODULE -DSIGMA863X_PLATFORM -DEXPORT_SYMTAB       \
                        -DPLATFORM_BL23570

export ARCH
