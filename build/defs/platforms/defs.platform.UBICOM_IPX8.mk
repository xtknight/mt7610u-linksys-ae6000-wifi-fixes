# UBICOM_IPX8 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    EXTRA_CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/sample/Customers/UBICOM/ubicom-linux-dist-2.1.1/linux-2.6.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= ubicom32-elf-
EXTRA_CFLAGS_${PLATFORM} :=
