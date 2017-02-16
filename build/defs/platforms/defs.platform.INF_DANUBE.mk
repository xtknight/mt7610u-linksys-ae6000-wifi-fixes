# INF_DANUBE platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    ROOTDIR
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: At the time this file was created, ROOTDIR was not used anywhere
# in the build system.

LINUX_SRC ?= /opt/danube/sdk/linux-2.6.16.x
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= mips-linux-
ROOTDIR ?= /opt/danube/sdk

export ROOTDIR
