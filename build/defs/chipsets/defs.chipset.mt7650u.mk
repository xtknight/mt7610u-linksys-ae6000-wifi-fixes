# mt7650u chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DMT76x0 -DRT65xx -DRLT_MAC -DRLT_RF -DRTMP_MAC_USB     \
                      -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT            \
                      -DA_BAND_SUPPORT -DRTMP_EFUSE_SUPPORT -DNEW_MBSSID_MODE \
                      -DCONFIG_ANDES_SUPPORT -DMT7650

WFLAGS_${CHIPSET}-${HAS_CSO_SUPPORT} += -DCONFIG_CSO_SUPPORT  \
                                        -DCONFIG_TSO_SUPPORT

CHIPSET_DAT_${CHIPSET} = 2870
