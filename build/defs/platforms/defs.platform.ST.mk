# ST platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/STM/STLinux-2.2/devkit/sources/kernel/linux0039
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/STM/STLinux-2.2/devkit/sh4/bin/sh4-linux-

ARCH := sh

# Surely this looks questionable at best ending with "-o". Prior to
# this commit, the relevant CFLAGS in os/linux/config.mk ended with
# "-o $(WFLAGS-y}". Net result: no change in (likely busted) behavior
CFLAGS_${PLATFORM} := -D__KERNEL__                                 \
                      -I$(LINUX_SRC)/include                       \
                      -Wall -O2 -Wundef -Wstrict-prototypes        \
                      -Wno-trigraphs -Wdeclaration-after-statement \
                      -Wno-pointer-sign -fno-strict-aliasing       \
                      -fno-common -fomit-frame-pointer             \
                      -ffreestanding -m4-nofpu -o

export ARCH
