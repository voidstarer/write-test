

all: copy_file

copy_file: copy_file.c
	gcc -Wall copy_file.c -o copy_file

clean:
	rm -f copy_file
