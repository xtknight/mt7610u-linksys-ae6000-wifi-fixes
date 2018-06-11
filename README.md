# mt7610u-linksys-ae6000-wifi-fixes
Trying to fix the MT7610U chipset driver by MediaTek so it's usable on modern Linux kernels and with nl80211/NetworkManager (and not completely breaking on old ones, maybe...).

Based on the driver from the HPRATH site (thank you!)
http://hprath.com/2014/06/cisco-linksys-ae6000-ac580-media-tek-mt7610u-mt7630u-mt7650u-linux-x64-driver-patch/

Some of the issues, such as a WPA supplicant issue, are fixable by comparing MT7610U and MT7612U code from MediaTek.

# Note
- Regretfully I have moved and didn't bring this adapter with me, so I have not been able to handle the issues. The 'configless' branch contains a version that works without using the conf file but may not compile right now.
- The good news is that 'master' branch should be working with kernel 4.7 now. Thank you for the pull request.

# Features
- Linux kernel 4.7 support
- Works with 2.4/5GHz networks out of the box
- Works with NetworkManager and nl80211 interface out of the box
- Works with WPA2-Personal and WPA supplicant/NetworkManager without extra configuration
- rmmod isn't locked while driver is running and clean-up is better (work in progress)

# Building
- sudo apt-get install build-essential linux-headers-$(uname -r)
- make clean
- make
- sudo make install

# Building with DKMS
```bash
$ sudo apt-get install dkms  # if you've already installed dkms, skip this step.
$ sudo cp -R . /usr/src/mt7610u_sta-1.0
$ sudo dkms add mt7610u_sta/1.0
$ sudo dkms build mt7610u_sta/1.0
$ sudo dkms install mt7610u_sta/1.0
```

# ARMv7 platform notes (e.g. Raspberry PI)

On ARMv7 platforms, there could be a problem with loading module. You'll see something like that in your dmesg output:

```
raspberrypi kernel: [   11.825048] <-- ERROR in Alloc Bulk buffer for RxContext!
raspberrypi kernel: [   11.825112] ERROR mt7610u_sta:
raspberrypi kernel: [   11.825119] Failed to allocate memory - TxRxRing
```

Modify file `/boot/boot.cmd`:

Find the string `setenv bootargs` and add `coherent_pool=4M` in the end of the line.

Then run the command and reboot the device:

```
mkimage -C none -A arm -T script -d /boot/boot.cmd /boot/boot.scr
```

In dmesg output you should see an increased value of DMA atomic allocations:

```
[    0.439464] DMA: preallocated 4096 KiB pool for atomic coherent allocations
```

# Devices recognized by module
- {USB_DEVICE(0x148F,0x7610)}, /* MT7610U Ralink VID */
- {USB_DEVICE(0x0E8D,0x7610)}, /* MT7610U MediaTek VID / Sabrent NTWLAC */
- {USB_DEVICE(0x13B1,0x003E)}, /* Cisco Linksys AE6000 */
- {USB_DEVICE(0x7392,0xA711)}, /* Edimax 7711ULC/7711MAC */
- {USB_DEVICE(0x7392,0xB711)}, /* Elecom WDC-433SU2M */
- {USB_DEVICE(0x148F,0x761A)}, /* TP-LINK Archer T2UH */
- {USB_DEVICE(0x2357,0x010b)}, /* TP-LINK Archer T2UHP AC600 rev0.1 */
- {USB_DEVICE(0x148F,0x760A)}, /* TP-LINK */
- {USB_DEVICE(0x0B05,0x17D1)}, /* ASUS USB-AC51 */
- {USB_DEVICE(0x0B05,0x17DB)}, /* ASUS USB-AC50 */
- {USB_DEVICE(0x0DF6,0x0075)}, /* Edimax EW-7811UTC AC600 / Sitecom WLA-3100 */
- {USB_DEVICE(0x2001,0x3D02)}, /* D-Link DWA-171 rev B1 */
- {USB_DEVICE(0x0586,0x3425)}, /* ZyXEL NWD6505 */
- {USB_DEVICE(0x07B8,0x7610)}, /* AboCom AU7212 */
- {USB_DEVICE(0x04BB,0x0951)}, /* IO DATA WN-AC433UK */
- {USB_DEVICE(0x057C,0x8502)}, /* AVM FRITZ!WLAN USB Stick AC 430 */
- {USB_DEVICE(0x293C,0x5702)}, /* Comcast Xfinity KXW02AAA */
- {USB_DEVICE(0x2019,0xAB31)}, /* Planex GW-450D/GW-450D-KATANA */
- {USB_DEVICE(0x20F4,0x806B)}, /* TRENDnet TEW-806UBH AC600 */
- {USB_DEVICE(0x7392,0xC711)}, /* Devolo Wifi Stick ac */

I have added all the devices from here, but it doesn't necessarily mean they will all work
https://wikidevi.com/wiki/MediaTek_MT7610U

# Major bugs fixed in original driver
#### If you have these issues, then this driver might fix the problem.
- Keeps getting Disassociation with ReasonCode=1(Unspecified) while connecting to WPA2 AP
- NetworkManager keeps asking for password even though password is correct
- wpa_supplicant debug mode error:  No wpa_ie set - cannot generate msg 2/4
- Nothing works if /etc is on BTRFS (because DAT file could not be read)

# TODO
- Remove excessive logging
- Allow operation without DAT file
- Add other dev ids
- Try to get AP mode working (huge project?)
- Test other encryption modes like WEP, WPA2-Enterprise, etc.
- Using -Dwext with wpa_supplicant seems to reveal a warning (WARN_ON(!bss) kernel 3.11 ~net/wireless/sme.c:658 __cfg80211_connect_result+0x24f/0x346) in the driver, which was probably there originally

# Other
- Please submit patches or let me know of anything missing or not working
- I also don't know the code very well, but have been working on comparing MT7610U and MT7612U code to find out-of-date portions in the MT7610U driver
