# RMI_64 platform definitions file
#
# Defines the following variables:
#    LINUX_SRC
#    LINUX_SRC_MODULE
#    CROSS_COMPILE
#    EXTRA_CFLAGS_${PLATFORM}
#    PLATFORM_SUPPORTED (only if known to be supported)

LINUX_SRC ?= /opt/rmi/1.7.0/linux_64/src/
LINUX_SRC_MODULE ?=
CROSS_COMPILE ?= /opt/rmi/1.7.0/mipscross/nptl/bin/mips64-unknown-linux-gnu-
EXTRA_CFLAGS_${PLATFORM} := -D__KERNEL__ -DMODULE=1                        \
                            -I$(LINUX_SRC)/include                         \
                            -I$(LINUX_SRC)/include/asm-mips/mach-generic   \
                            -Wall -Wstrict-prototypes -Wno-trigraphs       \
                            -O2 -fno-strict-aliasing -fno-common           \
                            -DCONFIG_IFX_ALG_QOS -DCONFIG_WAN_VLAN_SUPPORT \
                            -fomit-frame-pointer -DIFX_PPPOE_FRAME -G 0    \
                            -fno-pic -mno-abicalls -mlong-calls -pipe      \
                            -finline-limit=100000 -mabi=64 -G 0            \
                            -mno-abicalls -fno-pic -pipe -msoft-float      \
                            -march=xlr -ffreestanding  -march=xlr          \
                            -Wa,--trap, -nostdinc -iwithprefix include
