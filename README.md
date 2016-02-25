# mt7610u-linksys-ae6000-wifi-fixes
Trying to fix the MT7610U chipset driver by MediaTek so it's usable on modern Linux kernels and with nl80211/NetworkManager (and not completely breaking on old ones, maybe...).

Based on the driver from the HPRATH site (thank you!)
http://hprath.com/2014/06/cisco-linksys-ae6000-ac580-media-tek-mt7610u-mt7630u-mt7650u-linux-x64-driver-patch/

Some of the issues, such as a WPA supplicant issue, are fixable by comparing MT7610U and MT7612U code from MediaTek.

# Features
- Works with 2.4/5GHz networks out of the box
- Works with NetworkManager and nl80211 interface out of the box
- Works with WPA2-Personal and WPA supplicant/NetworkManager without extra configuration

# Building
- sudo apt-get install build-essential linux-headers-$(uname -r)
- make clean
- make
- sudo make install

# Major bugs fixed in original driver
## If you have these issues, then this driver might fix the problem.
- Keeps getting Disassociation with ReasonCode=1(Unspecified) while connecting to WPA2 AP
- wpa_supplicant debug mode error:  No wpa_ie set - cannot generate msg 2/4

# TODO
- Remove excessive logging
- Lots of cleanup and testing
- Add other dev ids
- Try to get AP mode working (huge project?)
- Test other encryption modes like WEP, WPA2-Enterprise, etc.
- Using -Dwext with wpa_supplicant seems to reveal a warning (WARN_ON(!bss) kernel 3.11 ~net/wireless/sme.c:658 __cfg80211_connect_result+0x24f/0x346) in the driver, which was probably there originally

# Other
- Please submit patches or let me know of anything missing or not working
- I also don't know the code very well, but have been working on comparing MT7610U and MT7612U code to find out-of-date portions in the MT7610U driver
