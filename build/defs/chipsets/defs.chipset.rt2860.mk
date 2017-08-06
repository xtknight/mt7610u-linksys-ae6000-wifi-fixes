# rt2860 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_{CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_PCI_SUPPORT -DRT2860 -DRT28xx \
                      -DA_BAND_SUPPORT -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2860
