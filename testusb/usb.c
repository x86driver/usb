#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include "function.h"

//#define USB_NODE "/dev/skel0"
//#define USB_NODE "/dev/garmin"

int main(int argc, char **argv)
{
	printf("Build on %s %s\n", __DATE__, __TIME__);
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [node] [read_total_size]\n", argv[0]);
		exit(1);
	}

	fd_set read_fd;
	int fd = open(argv[1], O_RDWR);
	int size = atoi(argv[2]);
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

	while (size > 0) {
		FD_ZERO(&read_fd);
		FD_SET(fd, &read_fd);
		printf("We select.....\n");
		ret = select(fd+1, &read_fd, NULL, NULL, NULL);
		if (ret == -1) {
			perror("select");
			exit(1);
		}
		printf("select ret: %d\n", ret);
		if (FD_ISSET(fd, &read_fd)) {
			printf("We'll read %d bytes\n", size);
			ret = read(fd, (void*)&buf[0], size);
			printf("Read %d bytes\n", ret);
			dump(buf, 0, ret);
			size -= ret;
		}
	}

	close(fd);
	return 0;
}

