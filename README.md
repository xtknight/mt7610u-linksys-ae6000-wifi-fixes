# mt7610u-linksys-ae6000-wifi-fixes
Trying to fix the MT7610U chipset driver by MediaTek so it's usable on modern Linux kernels and with nl80211/NetworkManager (and not completely breaking on old ones, maybe...).

Some of the issues, such as a WPA supplicant issue, are "simple" to fix by comparing MT7610U and MT7612U code from MediaTek.

# Features
- Works with 2.4/5GHz networks out of the box
- Works with NetworkManager and nl80211 interface out of the box
- Works with WPA2 and WPA supplicant/NetworkManager without extra configuration

# TODO
- Remove excessive logging
- Lots of cleanup and testing
- Add other dev ids
