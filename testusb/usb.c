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

	fd_set read_fd, write_fd;
	int fd = open(argv[1], O_RDWR);
	int size = atoi(argv[2]);
	int ret = 0;
	char *buf;
	struct timeval tv;

	if (!fd) {
		printf("Open: %s error!\n", argv[1]);
		perror("open");
		exit(1);
	}
	buf = (char*)malloc(size+1);
	if (buf == NULL) {
		perror("malloc");
		exit(1);
	}

	printf("Open %s OK\n", argv[1]);

	memset((void*)&buf[0], 0, size);
	strcpy(buf, "Fuck");
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	while (size > 0) {
		FD_ZERO(&read_fd);
		FD_SET(fd, &read_fd);
		FD_ZERO(&write_fd);
		FD_SET(fd, &write_fd);
		printf("We select.....\n");
		ret = select(fd+1, &read_fd, NULL, NULL, NULL);
		if (ret < 0) {
			perror("select");
			exit(1);
		}
		printf("select ret: %d\n", ret);
		if (FD_ISSET(fd, &read_fd)) {
//			printf("We'll read %d bytes\n", size);
//			int i;
//			for (i = 0; i < size; ++i) {
				ret = read(fd, (void*)&buf[0], 1);
				if (ret < 0) {
					perror("read");
					close(fd);
					exit(1);
				}
//				printf("read %d bytes\n", ret);
				printf("%c", buf[0]);
				fflush(NULL);
				size -= ret;
//				dump(buf, 0, ret);
//			}
//			size -= ret;
		}
	}

	close(fd);
	return 0;
}

