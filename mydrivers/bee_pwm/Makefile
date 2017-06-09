ifeq ($(KERNELRELEASE), )
#KERNELDIR ?= /lib/modules/$(shell uname -r)/build/
KERNELDIR ?= /home/teamviewer/newHQYJ/linux-3.14.25
PWD ?= $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
app:
	arm-none-linux-gnueabi-gcc pwm_test.c -o pwm_test
	sudo cp pwm_test /rootfs/
.PHONY: modules clean
else
	obj-m += pwmdriver.o
endif

