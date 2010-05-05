#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "function.h"

//#define USB_NODE "/dev/skel0"
//#define USB_NODE "/dev/garmin"

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [node] [read_total_size]\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDWR);
	int size = atoi(argv[1]);
	int ret = 0;
	char *buf;

	if (!fd) {
		printf("Open: %s error!\n", argv[1]);
		perror("open");
		exit(1);
	}
	buf = (char*)malloc(size);
	if (buf == NULL) {
		perror("malloc");
		exit(1);
	}

	printf("Open %s OK\n", argv[1]);

	memset((void*)&buf[0], 0, size);
	ret = read(fd, (void*)&buf[0], size);

	printf("Read %d bytes\n", ret);
	dump(buf, 0, size);

	close(fd);
	return 0;
}

