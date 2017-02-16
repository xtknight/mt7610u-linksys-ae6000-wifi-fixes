# SIGMA platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /root/sigma/smp86xx_kernel_source_2.7.172.0/linux-2.6.15
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /root/sigma/smp86xx_toolchain_2.7.172.0/build_mipsel_nofpu/staging_dir/bin/mipsel-linux-
