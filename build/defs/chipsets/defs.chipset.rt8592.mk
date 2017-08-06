# rt8592 chipset definitions file
#
# Defines the following variables:
#    WFLAGS_${CHIPSET}-y
#    CHIPSET_DAT_${CHIPSET}

WFLAGS_${CHIPSET}-y = -DRT8592 -DRT65xx -DRLT_MAC -DRTMP_MAC_PCI               \
                      -DRTMP_PCI_SUPPORT -DA_BAND_SUPPORT -DRX_DMA_SCATTER     \
                      -DRTMP_RF_RW_SUPPORT -DIQ_CAL_SUPPORT -DVCORECAL_SUPPORT \
                      -DFIFO_EXT_SUPPORT -DRTMP_TEMPERATURE_COMPENSATION       \
                      -DMCS_LUT_SUPPORT -DFPGA_MODE -DWFA_VHT_PF
CHIPSET_DAT_${CHIPSET} = 2860
