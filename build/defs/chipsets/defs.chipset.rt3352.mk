# rt3352 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_RBUS_SUPPORT -DRT3352 -DRT305x \
                      -DRTMP_RF_RW_SUPPORT -DVCORECAL_SUPPORT              \
                      -DCONFIG_SWMCU_SUPPORT -DRTMP_INTERNAL_TX_ALC        \
                      -DNEW_MBSSID_MODE
CHIPSET_DAT_${CHIPSET} = 2860
