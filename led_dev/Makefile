
KERN_DIR = /work/100/100ask_imx6ull-sdk/Linux-4.9.88
#KERN_DIR :=  /lib/modules/$(shell uname -r)/build/
all:
	make -C $(KERN_DIR) M=`pwd` modules 
	$(CROSS_COMPILE)gcc -o ledtest ledtest.c 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
	rm -f ledtest

100ask_led-y := leddrv.o board_100ask_imx6ull-qemu.o
obj-m	+= 100ask_led.o
