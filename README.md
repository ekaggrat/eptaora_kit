# Eptaora Kit

Firmware/code for the **Eptaora Kit**, available on Tindie:
👉 [https://www.tindie.com/products/41973/](https://www.tindie.com/products/41973/)

## Requirements

- [Arduino IDE 1.8.19](https://www.arduino.cc/en/software/OldSoftwareReleases) (available in the *Legacy IDE (1.8.X)* / old software section of arduino.cc)
- [MiniCore](https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json) board package for Arduino
- USBasp programmer

> This setup has been tested using Arduino IDE 1.8.19 from the old software section of [arduino.cc](https://www.arduino.cc).

## Setup Instructions

### 1. Install MiniCore

1. Open Arduino IDE.
2. Go to **File → Preferences**.
3. In **Additional Boards Manager URLs**, add:
   ```
   https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
   ```
4. Go to **Tools → Board → Boards Manager**, search for **MiniCore**, and install it.

### 2. Configure the Board

Under **Tools**, set the following:

- **Board:** ATmega8
- **Clock:** External 16 MHz
- **Programmer:** USBasp

### 3. Burn the Bootloader

With the USBasp connected and the board settings above selected, go to:

**Tools → Burn Bootloader**

### 4. Upload the Code

With the bootloader burned and the USBasp still connected, upload the sketch using:

**Sketch → Upload Using Programmer**

(Do **not** use the regular Upload button, as no bootloader-based serial upload is used here.)

## Notes

- Make sure the USBasp drivers are correctly installed on your system before starting.
- Double-check wiring between the USBasp and the ATmega8 before burning the bootloader or uploading code.

## Support

For questions about the kit itself, visit the product page on Tindie:
[https://www.tindie.com/products/41973/](https://www.tindie.com/products/41973/)
