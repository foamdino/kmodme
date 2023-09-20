obj-m += kmodme.o
 
PWD := $(CURDIR)/src/kmod
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean