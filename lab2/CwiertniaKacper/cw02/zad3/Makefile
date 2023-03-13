all:
	gcc -std=gnu11 -O2 -Wall -Wconversion -o scandir scandir.c -lm

test:
	./scandir
	wc -c *

clean:
	rm scandir