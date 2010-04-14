#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

#define USB_NODE "/dev/skel0"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s [read_size]\n", argv[0]);
		exit(1);
	}

	int fd = open(USB_NODE, O_RDWR);
	int size = atoi(argv[1]);
	int ret;
	char buf[512];

	if (!fd) {
		perror("open");
		exit(1);
	}
	printf("Open %s OK\n", USB_NODE);

	memset(&buf[0], 0, sizeof(buf));
	ret = read(fd, buf, size);
	printf("Read %d bytes\n", ret);
	dump(buf, 0, size);

	close(fd);
	return 0;
}

