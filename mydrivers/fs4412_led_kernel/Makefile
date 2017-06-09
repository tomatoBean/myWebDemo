KERNELDIR:=/home/teamviewer/newHQYJ/linux-3.14.25-fs4412
#KERNELDIR:=/home/fengxianl/hqyj-board/cross-kernel/linux-3.14.2
module:
	make   -C  $(KERNELDIR)  M=$(shell  pwd)  modules 

clean:
	rm  -rf  *.ko  *.mod.*  *.o   modules*  Mo*

obj-m = fs4412_led_drv.o

