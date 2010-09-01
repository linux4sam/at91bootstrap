AT91SAM9G45EKES ROM Code Replacement

Procedure to install AT91SAM9G45-ES ROM code replacement:
Prior to any operation, the user needs to 
* install AT91-ISP.exe 1.13
* unzip AT91SAM9G45_RomCode_Replacement_13.zip file 
  that contains a version of ROM binary code with USB issue fixed. 


Programming the ROMCode_Replacement into EEPROM
===============================================
Once done the following steps are necessary to store this version of ROM code in DataFlash.

PREPARE THE BOARD
1. unplug power supply
2. unplug usb device cable
3. remove jumper JP10 (NandFlash Chip Select) & JP12 (DataFlash Chip Select)
4. plug-in power supply

PROGRAM THE BOOTROM REPLACEMENT
5. Close EEPROM chip select jumper
5. launch SAM-BA (Choose right COM port and AT91SAM9G45-EKES)
6. Choose EEPROM media tab in the SAM-BA GUI interface
7. In the Scripts dropdown menu
7.1	Choose the "Enable EEPROM AT24C512x"  and press Execute to initialize the EEPROM
7.2.1	Choose the "Send Foot File", press Execute
7.2.2	Select AT91SAM9G45_RomCode_Replacement_13.bin binary file and press Open; 
	The media is written down to EEPROM
8. Close SAM-BA

On Reset, the faulty ROM code will copy the fixed ROM code into SRAM and launch it. 
The connection to the SAM-BA monitor over the USB interface will now work.

PROGRAM USER CODE
1. close jumper JP10 (NandFlash Chip Select) and/or JP12 (DataFlash® Chip Select)
2. Start SAMBA as usual

FURTHER USE
As long as the NAND/DATA flash connectors are closed,
the CPU will try to boot, first from the dataflash,
and then from the dataflash.
Before SAMBA is started, these connectors should be removed.
If the EEPROM connector is closed, the USB interface will work.
Otherwise it will not work.



Programming the ROMCode_Replacement into Dataflash
==================================================
Once done the following steps are necessary to store this version of ROM code in DataFlash.
1. unplug power supply
2. unplug usb device cable
3. remove jumper JP10 (NandFlash Chip Select) & JP12 (DataFlash Chip Select)
4. plug-in power supply
5. close jumper JP12 (DataFlash® Chip Select)
6. launch SAM-BA (Choose right COM port and AT91SAM9G45-EKES)
7. choose DataFlash media tab in the SAM-BA GUI interface
8. initialize DataFlash, choosing the Enable action in the Scripts rolling menu and press Execute
9. choose Send boot file, press Execute
10. select AT91SAM9G45_RomCode_Replacement.bin binary file and press Open; the media is written down
11. close SAM-BA

On Reset, the faulty ROM code will copy the fixed ROM code in SRAM and launch it. The connexion
through USB to the SAM-BA monitor will work.
Note: Boot from DataFlash media will no longer be available for other purpose.


WORKAROUND if SAMBA does not connect when you try to apply RomCodeReplacement
====================================
1. unplug power supply
2. unplug usb device cable
3. remove jumper JP10 (NandFlash Chip Select) & JP12 (DataFlash Chip Select) & EEPROM Chip Select
4. plug-in power supply
5. plug serial cable
6. launch hyper terminal (115200 bauds, 8 bits, parity none, 1 stop bit, no flow control)
7. type on hyper terminal : "Alt-0128 Alt-0128 #"
   ALT-0128 is the '€' (Euro) sign for people lucky enough to 
   have a European Keyboard.
   Otherwise you press the ALT button, and then press 0128 in a sequence before releasing the ALT button
   V#
8. AT91SAM9G45-EKES returns ">"
9. close hyper terminal
10. Start SAMBA using serial port
