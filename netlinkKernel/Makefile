ifneq ($(KERNELRELEASE),)
	obj-m := netlinkKernel.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
	
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	
clean:
	rm *.ko *.ko.unsigned *.symvers *.o *.mod.c *.order *.o.cmd *.ko.cmd .*.cmd .tmp_versions/ -rf
	
endif