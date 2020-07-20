#/bin/bash
dfu-util -a 0 -s 0x08000000:leave -D build/tng-ao-4u-4i-usb.bin
