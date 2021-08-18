#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void mmapcopy(int fd, int size)
{
	/* Ptr to memory mapped area */
 	char *bufp;
 	bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
 	write(1, bufp, size);
 	return;
}

int main(int argc, char **argv)
{
	struct stat stat;
	int fd;
 
	/* Check for required cmd line arg */
 	if (argc != 2) {
 		printf("usage: %s <filename>\n", argv[0]);
 		exit(0);
 	}
 
	/* Copy input file to stdout */
 	fd = open(argv[1], O_RDONLY, 0);
 	fstat(fd, &stat);
 	mmapcopy(fd, stat.st_size);
 	exit(0);
}
