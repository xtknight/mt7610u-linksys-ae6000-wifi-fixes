# SIGMA platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /root/sigma/smp86xx_kernel_source_2.7.172.0/linux-2.6.15
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /root/sigma/smp86xx_toolchain_2.7.172.0/build_mipsel_nofpu/staging_dir/bin/mipsel-linux-
CFLAGS_${PLATFORM} := -D__KERNEL__                                           \
                      -I$(LINUX_SRC)/include                                 \
                      -I$(LINUX_SRC)/include/asm/gcc                         \
                      -I$(LINUX_SRC)/include/asm-mips/mach-tango2            \
                      -I$(LINUX_SRC)/include/asm-mips/mach-tango2            \
                      -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2 -DEM86XX_REVISION=6 \
                      -I$(LINUX_SRC)/include/asm-mips/mach-generic           \
                      -I$(RT2860_DIR)/include                                \
                      -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs       \
                      -fno-strict-aliasing -fno-common -ffreestanding -O2    \
                      -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic -pipe \
                      -mabi=32 -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2   \
                      -Wa,-mips32r2 -Wa,--trap -DMODULE -DSIGMA863X_PLATFORM
