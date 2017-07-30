# RALINK_2880 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /project/stable/RT288x/RT288x_SDK/source/linux-2.4.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/buildroot-gdb/bin/mipsel-linux-

CFLAGS_${PLATFORM} := -D__KERNEL__                                           \
                      -I${LINUX_SRC}/include                                 \
                      -Wall -Wstrict-prototypes -Wno-trigraphs -O2           \
                      -fno-strict-aliasing -fno-common -fomit-frame-pointer  \
                      -G 0 -mno-abicalls -fno-pic -pipe                      \
                      -finline-limit=100000 -march=mips2 -mabi=32            \
                      -Wa,--trap -DLINUX -nostdinc -iwithprefix include
