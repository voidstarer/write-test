#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define LIMIT 1000000

void usage()
{
	fprintf(stdout, "./a.out <src-file> <dst-file>\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int rc, wc;
	int rfd, wfd;
	const char *srcfile, *dstfile;
	char *buffer;

	struct stat st;
	if(argc != 3) {
		usage();
	}
	srcfile = argv[1];
	dstfile = argv[2];

	wfd = open(dstfile, O_RDWR|O_CREAT|O_TRUNC, 0777);
	if(wfd < 0) {
		fprintf(stderr, "open(%s) failed: %s\n", dstfile, strerror(errno));
		exit(1);
	}
	rfd = open(srcfile, O_RDONLY);
	if(rfd < 0) {
		fprintf(stderr, "open(%s) failed: %s\n", srcfile, strerror(errno));
		exit(1);
	}
	
	fstat(rfd, &st);
	fprintf(stdout, "size is %lu\n", st.st_size);
	buffer = malloc(st.st_size);
	if(!buffer) {
		fprintf(stderr, "malloc failed of size %lu\n", st.st_size);
		exit(1);
	}
	rc = read(rfd, buffer, st.st_size);
	if(rc != st.st_size) {
		fprintf(stderr, "failed to read size %lu in one go\n", st.st_size);
		exit(1);
	}
	wc = write(wfd, buffer, st.st_size);
	if(wc != rc) {
		fprintf(stderr, "failed to write size %lu in one go\n", st.st_size);
		exit(1);
	}
	fprintf(stdout, "%s copied to %s: size %lu\n", srcfile, dstfile, st.st_size);

	close(wfd);
	close(rfd);
	return 0;
}
