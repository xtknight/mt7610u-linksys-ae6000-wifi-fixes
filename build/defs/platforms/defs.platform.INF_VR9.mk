# INF_VR9 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/public/lantiq/VR9/UGW-4.2/build_dir/linux-ifxcpe_platform_vr9/linux-2.6.20.19
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /home/public/lantiq/VR9/UGW-4.2/staging_dir/toolchain-mips_gcc-3.4.6_uClibc-0.9.29/bin/mips-linux-
CFLAGS_${PLATFORM} := -Wundef -fno-strict-aliasing -fno-common           \
                      -fno-pic -ffreestanding -Os -fomit-frame-pointer   \
                      -G 0 -mno-abicalls -fno-pic -pipe -msoft-float     \
                      -mabi=32 -mlong-calls -march=mips32r2              \
                      -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2        \
                      -Wa,-mips32r2 -Wa,--trap                           \
                      -I${LINUX_SRC}/include/asm-mips/mach-generic
