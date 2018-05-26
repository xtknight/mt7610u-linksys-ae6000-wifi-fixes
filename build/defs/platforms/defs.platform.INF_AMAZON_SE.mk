# INF_AMAZON_SE platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    CFLAGS_INF_AMAZON_SE
#    PLATFORM_SUPPORTED (only if known to be supported)

# Linux 2.6
# LINUX_SRC = /lib/modules/$(shell uname -r)/build

# Linux 2.4 Change to your local setting
LINUX_SRC ?= /backup/ifx/3.6.2.2/source/kernel/opensource/linux-2.4.31

LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/uclibc-toolchain/ifx-lxdb-1-2-3-external/gcc-3.3.6/toolchain-mips/R0208V35/mips-linux-uclibc/bin/
CFLAGS_INF_AMAZON_SE := -D__KERNEL__ -DMODULE=1                           \
                        -I$(LINUX_SRC)/include                            \
                        -Wall -Wstrict-prototypes -Wno-trigraphs -O2      \
                        -fno-strict-aliasing -fno-common                  \
                        -DCONFIG_IFX_ALG_QOS -DCONFIG_WAN_VLAN_SUPPORT    \
                        -fomit-frame-pointer -DIFX_PPPOE_FRAME -G 0       \
                        -fno-pic -mno-abicalls -mlong-calls -pipe         \
                        -finline-limit=100000 -mabi=32 -march=mips32      \
                        -Wa,-32 -Wa,-march=mips32 -Wa,-mips32 -Wa,--trap  \
                        -nostdinc -iwithprefix include
