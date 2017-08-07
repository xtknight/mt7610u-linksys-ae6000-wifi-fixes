# rt5572 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    WFLAGS_${CHIPSET}_${RT28xx_MODE}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_USB -DRTMP_USB_SUPPORT -DRT30xx -DRT5572  \
                      -DRT5592 -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT   \
                      -DNEW_MBSSID_MODE -DRTMP_TIMER_TASK_SUPPORT          \
                      -DA_BAND_SUPPORT -DIQ_CAL_SUPPORT -DVCORECAL_SUPPORT \
                      -DRTMP_TEMPERATURE_COMPENSATION -DCONFIG_M8051_SUPPORT

WFLAGS_${CHIPSET}-${HAS_CSO_SUPPORT} += -DCONFIG_CSO_SUPPORT

WFLAGS_${CHIPSET}_AP_-${HAS_CS_SUPPORT} += -DCARRIER_DETECTION_FIRMWARE_SUPPORT
WFLAGS_${CHIPSET}_APSTA_-y += -DRTMP_FREQ_CALIBRATION_SUPPORT
WFLAGS_${CHIPSET}_STA_-y += -DRTMP_FREQ_CALIBRATION_SUPPORT

CHIPSET_DAT_${CHIPSET} = 2870
