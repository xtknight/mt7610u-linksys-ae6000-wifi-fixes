# rt3370 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_USB -DRT30xx -DRT33xx -DRT3070 -DRT3370 \
                      -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT       \
                      -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT          \
                      -DRTMP_INTERNAL_TX_ALC -DVCORECAL_SUPPORT          \
                      -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2870
