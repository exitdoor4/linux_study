CROSS_COMPILE=/home/r/external-toolchain/bin/arrch64-linux-gnu-

obj-m:=driver.o
KDIR:=/home/r/linux-3.10
PWD:=$(shell pwd)

defalut:
	$(MAKE)ARCH=arm64 -C $(KDIR)M=$(PWD)modules CROSS_COMPILE=${CROSS_COMPILE}
clean:
rm-f*.ko
rm -f *.o
rm -f *.mod.*
rm -f .*.cmd
