obj-m := hello.o
KDIR := /lib/modules/$(shell name -r) /build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS = $(PWD) modules
clean:
	rm -rf *.ko *.mod.* .*.com *.o
