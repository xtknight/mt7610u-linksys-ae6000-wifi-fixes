/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bin2h(char *infname, char *outfname, char *fw_name)
{
	int ret = 0;
    FILE *infile, *outfile;	
    unsigned char c;
    int i=0;

    infile = fopen(infname,"r");

    if (infile == (FILE *) NULL) {
		printf("Can't read file %s \n",infname);
		return -1;
    }

    outfile = fopen(outfname,"w");
    
    if (outfile == (FILE *) NULL) {
		printf("Can't open write file %s \n",outfname);
       	return -1;
    }
    
    fputs("/* AUTO GEN PLEASE DO NOT MODIFY IT */ \n",outfile);
    fputs("/* AUTO GEN PLEASE DO NOT MODIFY IT */ \n",outfile);
    fputs("\n",outfile);
    fputs("\n",outfile);

	fprintf(outfile, "UCHAR %s[] = {\n", fw_name);

    while(1) {
		char cc[3];    

		c = getc(infile);
	
		if (feof(infile))
	   		break;
	
		memset(cc,0,2);
	
		if (i >= 16) {	
	   		fputs("\n", outfile);	
	   		i = 0;
		}
    
		fputs("0x", outfile); 
		sprintf(cc,"%02x",c);
		fputs(cc, outfile);
		fputs(", ", outfile);
		i++;
    } 
    
    fputs("} ;\n", outfile);
    fclose(infile);
    fclose(outfile);
}	

int main(int argc ,char *argv[])
{
    char infname[1024], ine2pname[1024];
    char outfname[1024], oute2pname[1024];
	char chipsets[1024];
	char fw_name[128], e2p_name[128];
    char *rt28xxdir;
    char *chipset, *token;
	char *wow, *rt28xx_mode;
   
    rt28xxdir = (char *)getenv("RT28xx_DIR");
    chipset = (char *)getenv("CHIPSET");
	memcpy(chipsets, chipset, strlen(chipset));
	wow = (char *)getenv("HAS_WOW_SUPPORT");
	rt28xx_mode = (char *)getenv("RT28xx_MODE");

    if(!rt28xxdir) {
		printf("Environment value \"RT28xx_DIR\" not export \n");
	 	return -1;
    }

    if(!chipset) {
		printf("Environment value \"CHIPSET\" not export \n");
		return -1;
    }	    
	
	if (strlen(rt28xxdir) > (sizeof(infname)-100)) {
		printf("Environment value \"RT28xx_DIR\" is too long!\n");
		return -1;
	}
    
	chipset = strtok(chipsets, " ");

	while (chipset != NULL) {
		printf("chipset = %s\n", chipset);
    	memset(infname, 0,1024);
		memset(ine2pname, 0, 1024);
    	memset(outfname, 0, 1024);
		memset(oute2pname, 0, 1024);
		memset(fw_name, 0, 128);
		memset(e2p_name, 0, 128);
    	strcat(infname,rt28xxdir);
		strcat(ine2pname, rt28xxdir);
    	strcat(outfname,rt28xxdir);
		strcat(oute2pname, rt28xxdir);
		if (strncmp(chipset, "2860",4) == 0) {
			strcat(infname,"/mcu/bin/rt2860.bin");
    		strcat(outfname,"/include/mcu/rt2860_firmware.h");
			strcat(fw_name, "RT2860_FirmwareImage");
		} else if (strncmp(chipset, "2870",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "3090",4) == 0) {
	    	strcat(infname,"/mcu/bin/rt2860.bin");
    		strcat(outfname,"/include/mcu/rt2860_firmware.h");
			strcat(fw_name, "RT2860_FirmwareImage");
		} else if (strncmp(chipset, "2070",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "3070",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "3572",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "3573",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "3370",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "5370",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
	    		strcat(infname,"/mcu/bin/rt2870_wow.bin");
    			strcat(outfname,"/include/mcu/rt2870_wow_firmware.h");
				strcat(fw_name, "RT2870_WOW_FirmwareImage");
			} else {
	    		strcat(infname,"/mcu/bin/rt2870.bin");
    			strcat(outfname,"/include/mcu/rt2870_firmware.h");
				strcat(fw_name, "RT2870_FirmwareImage");
			}
		} else if (strncmp(chipset, "5572",4) == 0) {
			strcat(infname,"/mcu/bin/rt2870.bin");
    		strcat(outfname,"/include/mcu/rt2870_firmware.h");
			strcat(fw_name, "RT2870_FirmwareImage");
		} else if (strncmp(chipset, "5592",4) == 0) {
			strcat(infname,"/mcu/bin/rt2860.bin");
    		strcat(outfname,"/include/mcu/rt2860_firmware.h");
			strcat(fw_name, "RT2860_FirmwareImage");
		} else if ((strncmp(chipset, "mt7650e", 7) == 0)
				|| (strncmp(chipset, "mt7650u", 7) == 0)
				|| (strncmp(chipset, "mt7630e", 7) == 0)
				|| (strncmp(chipset, "mt7630u", 7) == 0)) {
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.modify.USB.flow.bin"); // pmu
			strcat(infname, "/mcu/bin/MT7610_formal_2.4.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.starck.USB.fix.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210302000.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_10292045.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.for.PMU.print.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_20121029.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210231140.bin"); // atomic bw
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210180939.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151438.bin"); // led
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210171346.bin");
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151547.bin");
			//strcat(infname, "/mcu/bin/MT7650_1012.bin");
			//strcat(infname,"/mcu/bin/MT7610.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_201210031435.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210021430.bin"); // turn on debug log same as 10020138.bin
			//strcat(infname,"/mcu/bin/MT7610_201210020138.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_10021442.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_1002.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_shang_1001.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv5.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv4.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_20120919.bin"); // wifi
			//strcat(infname,"/mcu/bin/MT7650E2_V01007870_20120921.bin"); // bt
			//strcat(infname,"/mcu/bin/MT7650.bin");
    		strcat(outfname,"/include/mcu/mt7650_firmware.h");
			strcat(fw_name, "MT7650_FirmwareImage");
		} else if ((strncmp(chipset, "mt7610e", 7) == 0)
				|| (strncmp(chipset, "mt7610u", 7) == 0)) {
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.modify.USB.flow.bin"); // pmu
			strcat(infname, "/mcu/bin/MT7610_formal_2.6.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210302000.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_10292045.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.for.PMU.print.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_20121029.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210231140.bin"); // atomic bw
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210180939.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151438.bin"); // led
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210171346.bin");
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151547.bin");
			//strcat(infname, "/mcu/bin/MT7650_1012.bin");
			//strcat(infname,"/mcu/bin/MT7610.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_201210031435.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210021430.bin"); // turn on debug log same as 10020138.bin
			//strcat(infname,"/mcu/bin/MT7610_201210031425.bin"); 
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_10021442.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_shang_1001.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_1002.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv5.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210020138.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv4.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_20120919.bin");
    		strcat(outfname, "/include/mcu/mt7610_firmware.h");
			strcat(fw_name, "MT7610_FirmwareImage");

			if ((strncmp(chipset, "mt7610e", 7) == 0)) {
				strcat(ine2pname, "/eeprom/MT7610U_FEM_V1_1.bin");
				strcat(oute2pname, "/include/eeprom/mt7610e_e2p.h");
				strcat(e2p_name, "MT7610E_E2PImage");
			} else if ((strncmp(chipset, "mt7610u", 7) == 0)) {
				strcat(ine2pname, "/eeprom/MT7610U_FEM_V1_1.bin");
				strcat(oute2pname, "/include/eeprom/mt7610u_e2p.h");
				strcat(e2p_name, "MT7610U_E2PImage");
			}
		} else if ((strncmp(chipset, "mt7662e", 7) == 0)
				|| (strncmp(chipset, "mt7662u", 7) == 0)) {
			strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121119.bin");
			//strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121116.bin");
			//strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121115.bin");
			//strcat(infname,"/mcu/bin/MT7662_E1_hdr_20121115.bin");
			//strcat(infname,"/mcu/bin/MT7662_E1_hdr_20121109.bin");
			//strcat(infname,"/mcu/bin/MT7662.bin");
    		strcat(outfname,"/include/mcu/mt7662_firmware.h");
			strcat(fw_name, "MT7662_FirmwareImage");
		} else if ((strncmp(chipset, "mt7612e", 7) == 0)
				|| (strncmp(chipset, "mt7612u", 7) == 0)) {
			strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121119.bin");
			//strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121116.bin");
			//strcat(infname,"/mcu/bin/WIFI_RAM_CODE_ALL_20121115.bin");
			//strcat(infname,"/mcu/bin/MT7662_E1_hdr_20121115.bin");
			//strcat(infname,"/mcu/bin/MT7662_E1_hdr_20121109.bin");
			//strcat(infname,"/mcu/bin/MT7612.bin");
    		strcat(outfname,"/include/mcu/mt7612_firmware.h");
			strcat(fw_name, "MT7612_FirmwareImage");
		} else {
			printf("unknown chipset = %s\n", chipset);
		}

     	bin2h(infname, outfname, fw_name);

		chipset = strtok(NULL, " ");
	}

    exit(0);
}	
