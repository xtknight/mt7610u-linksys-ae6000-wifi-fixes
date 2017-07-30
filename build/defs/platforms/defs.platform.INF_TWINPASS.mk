# INF_TWINPASS platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

# For Linux 2.6, use ...
# LINUX_SRC = /lib/modules/$(shell uname -r)/build

# For Linux 2.4, change to your local setting
LINUX_SRC ?= /project/stable/twinpass/release/2.0.1/source/kernel/opensource/linux-2.4.31/

LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
CFLAGS_${PLATFORM} := -D__KERNEL__ -DMODULE                             \
                      -I${LINUX_SRC}/include                            \
                      -Wall -Wstrict-prototypes -Wno-trigraphs -O2      \
                      -fomit-frame-pointer -fno-strict-aliasing         \
                      -fno-common -G 0 -mno-abicalls -fno-pic           \
                      -march=4kc -mips32 -Wa,--trap -pipe -mlong-calls
