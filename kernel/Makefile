obj-m:=module1.o

CURRENT_PATH:=$(shell pwd)

LNUX_KERNEL_PATH:=/usr/src/kernels/$(shell uname -r)

all:
	make -C /usr/src/kernels/3.10.0-693.2.2.el7.x86_64   M=$(CURRENT_PATH)  modules

clean:
	make -C /usr/src/kernels/3.10.0-693.2.2.el7.x86_64   M=$(CURRENT_PATH)  clean
