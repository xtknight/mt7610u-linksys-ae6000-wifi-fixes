# rt5390 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    WFLAGS_${CHIPSET}_${RT28xx_MODE}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRT30xx -DRT33xx -DRT3090 -DRT3390   \
                      -DRT5390 -DRTMP_PCI_SUPPORT -DRTMP_RF_RW_SUPPORT     \
                      -DRTMP_EFUSE_SUPPORT -DRTMP_FREQ_CALIBRATION_SUPPORT \
                      -DRTMP_INTERNAL_TX_ALC -DVCORECAL_SUPPORT            \
                      -DIQ_CAL_SUPPORT -DNEW_MBSSID_MODE                   \
                      -DRTMP_TEMPERATURE_COMPENSATION -DCONFIG_M8051_SUPPORT

WFLAGS_${CHIPSET}_AP-y = -DSPECIFIC_BCN_BUF_SUPPORT

CHIPSET_DAT_${CHIPSET} = 2860
