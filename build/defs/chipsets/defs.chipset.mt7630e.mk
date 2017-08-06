# mt7630e chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DMT76x0 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_MAC_PCI  \
                      -DRTMP_PCI_SUPPORT -DA_BAND_SUPPORT -DRX_DMA_SCATTER \
                      -DNEW_MBSSID_MODE -DRTMP_EFUSE_SUPPORT               \
                      -DCONFIG_ANDES_SUPPORT -DMT7630
CHIPSET_DAT_${CHIPSET} = 2860
