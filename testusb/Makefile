TARGET = testusb
CFLAGS =

ARCH = x86
#ARCH = arm

ifeq ($(ARCH), x86)
CC = gcc
else
CC = arm-none-linux-gnueabi-gcc
endif

all:$(TARGET)

usb.o:usb.c
	$(CC) $(CFLAGS) -c -Wall -o $@ $<

function.o:function.c
	$(CC) $(CFLAGS) -c -Wall -o $@ $<

testusb:usb.o function.o
	$(CC) $(CFLAGS) -Wall -o $@ usb.o function.o

clean:
	rm -rf $(TARGET) *.o

