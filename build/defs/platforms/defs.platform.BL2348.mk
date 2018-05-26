# BL2348 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_BL2348
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/sample/Customers/BroadLight/bl234x-linux-2.6.21-small-v29
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-wrs-linux-gnu-
CFLAGS_BL2348 := -D__KERNEL__ -I${LINUX_SRC}/include                     \
                 -I${LINUX_SRC}/include/asm/gcc                          \
                 -I$(LINUX_SRC)/include/asm-mips/mach-tango2             \
                 -I$(LINUX_SRC)/include/asm-mips/mach-generic            \
                 -I$(RT2860_DIR)/include                                 \
                 -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2 -DEM86XX_REVISION=6  \
                 -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs        \
                 -fno-strict-aliasing -fno-common -ffreestanding -O2     \
                 -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic -pipe  \
                 -mabi=32 -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2    \
                 -Wa,-mips32r2 -Wa,--trap                                \
                 -DMODULE -DSIGMA863X_PLATFORM -DEXPORT_SYMTAB           \
                 -DPLATFORM_BL2348

