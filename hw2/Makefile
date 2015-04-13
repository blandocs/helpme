obj-m += msrdrv.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	rm test
	gcc -o test ioctl2.c
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

