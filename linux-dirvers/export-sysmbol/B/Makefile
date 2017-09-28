obj-m := B_func.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

KBUILD_EXTRA_SYMBOLS += /home/hxy/workspace/linux-dirvers/export-sysmbol/A/Module.symvers
export KBUILD_EXTRA_SYMBOLS

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -f *.o *.ko *.mod.c *.order *.symvers
