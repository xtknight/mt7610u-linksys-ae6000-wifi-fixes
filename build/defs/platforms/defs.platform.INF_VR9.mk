# INF_VR9 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /home/public/lantiq/VR9/UGW-4.2/build_dir/linux-ifxcpe_platform_vr9/linux-2.6.20.19
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /home/public/lantiq/VR9/UGW-4.2/staging_dir/toolchain-mips_gcc-3.4.6_uClibc-0.9.29/bin/mips-linux-
