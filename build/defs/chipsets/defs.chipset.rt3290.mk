# rt3290 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_PCI_SUPPORT -DRTMP_RF_RW_SUPPORT \
                      -DRTMP_EFUSE_SUPPORT -DRTMP_FREQ_CALIBRATION_SUPPORT   \
                      -DRTMP_INTERNAL_TX_ALC -DRT30xx -DRT3290               \
                      -DVCORECAL_SUPPORT -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2860
