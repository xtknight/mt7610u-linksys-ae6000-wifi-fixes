# SIGMA_8622 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CROSS_COMPILE_INCLUDE
#    CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# Note that CROSS_COMPILE_INCLUDE is not expected to be defined in every
# platform definition file; it is used as a custom variable for this platform.

LINUX_SRC ?= /home/snowpin/armutils_2.5.120.1/build_arm/linux-2.4.22-em86xx
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /home/snowpin/armutils_2.5.120.1/toolchain/bin/arm-elf-
CROSS_COMPILE_INCLUDE ?= /home/snowpin/armutils_2.5.120.1/toolchain/lib/gcc-lib/arm-elf/2.95.3
CFLAGS_${PLATFORM} := -D__KERNEL__                                       \
                      -I$(CROSS_COMPILE_INCLUDE)/include                 \
                      -I$(LINUX_SRC)/include                             \
                      -Wall -Wstrict-prototypes -Wno-trigraphs -O2       \
                      -fno-strict-aliasing -fno-common -fno-common -pipe \
                      -fno-builtin -D__linux__ -DNO_MM -mapcs-32         \
                      -march=armv4 -mtune=arm7tdmi -msoft-float          \
                      -DMODULE -mshort-load-bytes -nostdinc              \
                      -iwithprefix -DMODULE
