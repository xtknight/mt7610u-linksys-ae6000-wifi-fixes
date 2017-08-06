# rt3593 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRTMP_MAC_PCI -DDOT11N_SS3_SUPPORT -DRT3593  \
                      -DRT28xx -DRT30xx -DRT35xx -DRTMP_PCI_SUPPORT \
                      -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT     \
                      -DA_BAND_SUPPORT -DNEW_MBSSID_MODE            \
                      -DVCORECAL_SUPPORT -DCONFIG_M8051_SUPPORT
CHIPSET_DAT_${CHIPSET} = 2860
