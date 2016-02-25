# mt7610u-linksys-ae6000-wifi-fixes
Trying to fix the MT7610U chipset driver by MediaTek so it's usable on modern Linux kernels and with nl80211/NetworkManager (and not completely breaking on old ones, maybe...).

Some of the issues, such as a WPA supplicant issue, are fixable by comparing MT7610U and MT7612U code from MediaTek.

# Features
- Works with 2.4/5GHz networks out of the box
- Works with NetworkManager and nl80211 interface out of the box
- Works with WPA2-Personal and WPA supplicant/NetworkManager without extra configuration

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

# Other
- Please submit patches or let me know of anything missing or not working
- I also don't know the code very well, but have been working on comparing MT7610U and MT7612U code to find out-of-date portions in the MT7610U driver
