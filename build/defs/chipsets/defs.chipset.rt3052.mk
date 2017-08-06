# rt3052 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_RBUS_SUPPORT -DRT3052 -DRT305x \
                      -DRTMP_RF_RW_SUPPORT -DCONFIG_SWMCU_SUPPORT          \
                      -DVCORECAL_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2870
