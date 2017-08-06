# rt2880 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRT2880 -DRT28xx -DRTMP_MAC_PCI               \
                      -DCONFIG_RALINK_RT2880_MP -DRTMP_RBUS_SUPPORT  \
                      -DMERGE_ARCH_TEAM -DA_BAND_SUPPORT -DCONFIG_SWMCU_SUPPORT

# What should this be set to?
CHIPSET_DAT_${CHIPSET} =
