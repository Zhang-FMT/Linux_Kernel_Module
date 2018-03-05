cc = gcc
CFLAGS = -O2 -DMODULE -D _KERNEL_ -Wall \ -I/usr/src/linux/include

HelloWorldModule.o: HelloWorldModule.c
	$(cc) $(CFLAGS) -c HelloWorldModule.c
install:
	/sbin/insmod HelloWorldModule.o
remove:
	/sbin/remmod HelloWorldModule
clean:
	rm -f HelloWorldModule.o
