# rt3572 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    WFLAGS_${CHIPSET}_${RT28xx_MODE}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRT2870 -DRT28xx  \
                      -DRT30xx -DRT35xx -DRT3572 -DRTMP_TIMER_TASK_SUPPORT \
                      -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT            \
                      -DA_BAND_SUPPORT -DVCORECAL_SUPPORT                  \
                      -DCONFIG_M8051_SUPPORT

WFLAGS_${CHIPSET}_AP-${HAS_CS_SUPPORT} += -DCARRIER_DETECTION_FIRMWARE_SUPPORT

CHIPSET_DAT_${CHIPSET} = 2870
