#!/bin/bash

srcfile=/tmp/file1.txt
dstfile=/tmp/file2.txt

make clean
make

if [ ! -f $srcfile ]; then
	seq 1 80000000 > /tmp/file1.txt
fi

interrupt_test()
{
	sig=$1
	rm -f $dstfile
	sync
	./copy_file $srcfile $dstfile &
	PID=$!

	./usleep 400000
	echo sending $sig signal
	kill $sig $PID
	md5sum $srcfile $dstfile
	wanted=$(wc -c "$srcfile")
	written=$(wc -c "$dstfile")
	echo $written out of $wanted written
}


interrupt_test -TERM
interrupt_test -KILL
