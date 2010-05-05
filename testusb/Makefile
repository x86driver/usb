TARGET = testusb
CFLAGS =

all:$(TARGET)

usb.o:usb.c
	gcc $(CFLAGS) -c -Wall -o $@ $<

function.o:function.c
	gcc $(CFLAGS) -c -Wall -o $@ $<

testusb:usb.o function.o
	gcc $(CFLAGS) -Wall -o $@ usb.o function.o

clean:
	rm -rf $(TARGET)

