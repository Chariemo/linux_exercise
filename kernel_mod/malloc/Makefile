obj-m := malloc.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_path := /usr/src/kernels/$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_path) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_path) M=$(CURRENT_PATH) clean
