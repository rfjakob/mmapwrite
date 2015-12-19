#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>

int file_size = 50*1024*1024;
int block_size = 1024*1024;

static void *x_malloc(int size)
{
	void *ret = malloc(size);
	if (!ret) {
		fprintf(stderr,"Out of memory for size %d!\n", size);
		exit(1);
	}
	return ret;
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("Usage: mmapwrite FILENAME\n");
		exit(1);
	}

	char *fname = argv[1];

	int fd = open(fname, O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd == -1) {
		perror(fname);
		exit(1);
	}
	
	
	char *p;
	if (ftruncate(fd, file_size) != 0) {
		perror("ftruncate");
		exit(1);
	}

	p = mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == (char *)-1) {
		perror("mmap");
		exit(1);
	}

	long iteration = 1;
	while(1) {
		struct timeval t1, t2;
		gettimeofday(&t1, NULL);
		printf("%3d ", iteration);
		for (int size=0; size<file_size; size += block_size) {
			memset(p + size, 0xfe, block_size);
			printf(".");
			fflush(stdout);
		}
		gettimeofday(&t2, NULL);
		float deltat = ( t2.tv_sec - t1.tv_sec ) + (t2.tv_usec - t1.tv_usec) / 1000000.0;
		printf(" %6.2f MB/s\n", file_size / ( 1024.0 * 1024.0 ) / deltat);
		iteration++;
	}
}
