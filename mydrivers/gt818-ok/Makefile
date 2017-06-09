ifeq ($(KERNELRELEASE), )
#KERNELDIR ?= /lib/modules/$(shell uname -r)/build/
KERNELDIR ?= /home/teamviewer/newHQYJ/linux-3.14.25
PWD ?= $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
.PHONY: modules clean
else
	obj-m += gt818_ts.o
        gt818_ts-objs := goodix_tool.o gt818_update.o gt818.o
endif

