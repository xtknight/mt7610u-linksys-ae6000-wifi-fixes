# rt8592 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    WFLAGS_${CHIPSET}_${RT28xx_MODE}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRT8592 -DRT65xx -DRLT_MAC -DRTMP_MAC_PCI               \
                      -DRTMP_PCI_SUPPORT -DA_BAND_SUPPORT -DRX_DMA_SCATTER     \
                      -DRTMP_RF_RW_SUPPORT -DIQ_CAL_SUPPORT -DVCORECAL_SUPPORT \
                      -DFIFO_EXT_SUPPORT -DRTMP_TEMPERATURE_COMPENSATION       \
                      -DMCS_LUT_SUPPORT -DFPGA_MODE -DWFA_VHT_PF

# TODO: shiang-6590, need to ask hardware about the
# memory base setting first!!
# WFLAGS_${CHIPSET}_AP-y = -DSPECIFIC_BCN_BUF_SUPPORT

CHIPSET_DAT_${CHIPSET} = 2860
