TARGET = enable

#C++ = g++
C++ = arm-none-linux-gnueabi-g++
CFLAGS = -Wall -static

all:$(TARGET)

enable:enable.cpp
	$(C++) $(CFLAGS) -o $@ $<

up:enable
	adb push enable /system

clean:
	rm -rf $(TARGET)

