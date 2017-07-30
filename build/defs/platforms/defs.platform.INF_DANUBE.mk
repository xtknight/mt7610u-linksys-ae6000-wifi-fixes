# INF_DANUBE platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    ROOTDIR
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: At the time this file was created, ROOTDIR was not used anywhere
# in the build system.

LINUX_SRC ?= /opt/danube/sdk/linux-2.6.16.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
ROOTDIR ?= /opt/danube/sdk

# These __MARCHxxx variables are local to this file
__MARCH_2.4 = -march=mips32
__MARCH_ = -march=mips32r2
__MARCH = ${__MARCH_$(findstring 2.4,${LINUX_SRC})}

CFLAGS_${PLATFORM} := -Wundef -fno-strict-aliasing -fno-common       \
                      -ffreestanding -Os -fomit-frame-pointer -G 0   \
                      -mno-abicalls -fno-pic -pipe -msoft-float      \
                      -mabi=32 ${__MARCH} -Wa,-32 -Wa,${__MARCH}     \
                      -Wa,-mips32 -Wa,--trap                         \
                      -I${LINUX_SRC}/include/asm-mips/mach-generic

export ROOTDIR
