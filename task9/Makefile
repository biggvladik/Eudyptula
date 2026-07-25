obj-m += task9.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: all clean load unload reload logs

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load:
	sudo insmod task9.ko

unload:
	sudo rmmod task9

reload:
	-sudo rmmod task9
	sudo insmod task9.ko

logs:
	sudo dmesg | tail -n 30
