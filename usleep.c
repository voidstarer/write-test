#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	useconds_t t;

	t = atoi(argv[1]);
	usleep(t);
	exit(0);
}

