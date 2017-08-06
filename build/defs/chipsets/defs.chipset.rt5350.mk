# rt5350 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DRTMP_RBUS_SUPPORT -DRT5350            \
                      -DRT305x -DRT3050 -DRT3350 -DRTMP_RF_RW_SUPPORT        \
                      -DVCORECAL_SUPPORT -DCONFIG_SWMCU_SUPPORT              \
                      -DRTMP_INTERNAL_TX_ALC -DRTMP_FREQ_CALIBRATION_SUPPORT \
                      -DIQ_CAL_SUPPORT -DNEW_MBSSID_MODE
CHIPSET_DAT_${CHIPSET} = 2860
