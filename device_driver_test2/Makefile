CROSS_COMPILE=aarch64-linux-gnu-

obj-m:=test_device.o
KDIR:=/usr/src/linux-headers-4.9.337-tegra-ubuntu18.04_aarch64/kernel-4.9
PWD:=$(shell pwd)

default:
	$(MAKE) ARCH=arm64 -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=${CROSS_COMPILE}
clean:
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f .*.cmd
