# rt5592 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_PCI_SUPPORT -DRT30xx -DRT5592 \
                      -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT           \
                      -DA_BAND_SUPPORT -DIQ_CAL_SUPPORT -DRX_DMA_SCATTER  \
                      -DVCORECAL_SUPPORT -DNEW_MBSSID_MODE                \
                      -DRTMP_TEMPERATURE_COMPENSATION -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2860
