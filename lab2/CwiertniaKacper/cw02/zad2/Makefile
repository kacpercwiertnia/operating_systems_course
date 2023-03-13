all:
	gcc -std=gnu11 -O2 -Wall -Wconversion -o reversefile reversefile.c -lm

test:
	./reversefile test.txt res.txt > pomiar_zad_2.txt
	./reversefile res.txt res2.txt > /dev/null
	diff -s test.txt res2.txt

clean:
	rm res.txt res2.txt reversefile