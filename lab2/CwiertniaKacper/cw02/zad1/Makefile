all:
	gcc -std=gnu11 -O2 -Wall -Wconversion -o swapchars swapchars.c -lm

test:
	./swapchars a b test.txt res.txt > pomiar_zad_1.txt
	tr a b < test.txt > tmp
	diff -s tmp res.txt

clean:
	rm -f res.txt tmp swapchars