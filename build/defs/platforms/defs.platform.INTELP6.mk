# INTELP6 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /tftpboot/IntelCE-20.0.11052.243193/project_build_i686/IntelCE/kernel-20.0.11024.238456/linux-2.6.35
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /tftpboot/IntelCE-20.0.11052.243193/build_i686/i686-linux-elf/bin/i686-cm-linux-
