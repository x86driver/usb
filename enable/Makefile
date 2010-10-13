TARGET = enable

#C++ = g++
C++ = arm-none-linux-gnueabi-g++
CFLAGS = -Wall -static

all:$(TARGET)

enable:enable.cpp
	$(C++) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)

