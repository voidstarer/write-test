

all: copy_file usleep

copy_file: copy_file.c
	gcc -Wall copy_file.c -o copy_file

usleep: usleep.c
	gcc -Wall usleep.c -o usleep

clean:
	rm -f copy_file usleep
