# RMI_64 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/rmi/1.7.0/linux_64/src/
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/rmi/1.7.0/mipscross/nptl/bin/mips64-unknown-linux-gnu-
