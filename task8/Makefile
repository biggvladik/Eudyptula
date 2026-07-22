obj-m += task8.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: all clean load unload reload logs

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load:
	sudo insmod task8.ko

unload:
	sudo rmmod task8

reload:
	-sudo rmmod task8
	sudo insmod task8.ko

logs:
	sudo dmesg | tail -n 30
