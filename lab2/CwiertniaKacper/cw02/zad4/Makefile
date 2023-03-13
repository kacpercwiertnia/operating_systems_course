all:
	gcc -std=gnu11 -O2 -Wall -Wconversion -o scandirs scandirs.c -lm

test:
	./scandirs ../../..
	find ../../.. -type f | xargs wc -c

clean:
	rm scandirs