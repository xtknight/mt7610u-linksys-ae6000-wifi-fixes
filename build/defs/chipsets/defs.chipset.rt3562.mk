# rt3562 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRT2860 -DRT28xx -DRT30xx -DRT35xx  \
                      -DRT3562 -DRTMP_PCI_SUPPORT -DRTMP_RF_RW_SUPPORT    \
                      -DRTMP_EFUSE_SUPPORT -DA_BAND_SUPPORT               \
                      -DVCORECAL_SUPPORT -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2860
