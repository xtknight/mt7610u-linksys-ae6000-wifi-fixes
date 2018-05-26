# KODAK_DC platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)
#
# NOTE: SKD_SRC is not referenced anywhere, and there also does not appear
# to be a corresponding TARGET=SKD. Furthermore, ${cc} is not defined anywhere
# either. The content is presented in this way so as not to lose information
# that was in the previous build system.
#
# This file is non-functional in its present form.

SKD_SRC ?= C:/SigmaTel/DC1250_SDK_v1-9/sdk
CROSS_COMPILE ?= ${cc}
