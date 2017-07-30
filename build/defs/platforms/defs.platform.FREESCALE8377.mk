# FREESCALE8377 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    EXTRA_CFLAGS_FREESCALE8377
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/ltib-mpc8377_rds-20090309/rpm/BUILD/linux-2.6.25
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/freescale/usr/local/gcc-4.2.187-eglibc-2.5.187/powerpc-linux-gnu/bin/powerpc-linux-gnu-
EXTRA_CFLAGS_FREESCALE8377 :=  -I$(RT28xx_DIR)/include
