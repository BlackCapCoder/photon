build:
	particle compile photon util.h main.ino

clean:
	rm photon_firmware_*.bin

run: build

upload: build
	particle flash --usb photon_firmware_*.bin
