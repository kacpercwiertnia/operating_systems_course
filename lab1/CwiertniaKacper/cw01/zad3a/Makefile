CC = gcc
CFLAGS = -Wall

test_create:
	echo "init 5" >> test.txt
	echo "count wclibrary.c" >> test.txt
	echo "count wclibrary.h" >> test.txt
	echo "count wclibrarydll.h" >> test.txt
	echo "count wcrepl.c" >> test.txt
	echo "count Makefile" >> test.txt
	echo "show 0" >> test.txt
	echo "show 1" >> test.txt
	echo "show 2" >> test.txt
	echo "show 3" >> test.txt
	echo "show 4" >> test.txt
	echo "delete 0" >> test.txt
	echo "delete 1" >> test.txt
	echo "delete 2" >> test.txt
	echo "delete 3" >> test.txt
	echo "delete 4" >> test.txt
	echo "destroy" >> test.txt
	echo "exit" >> test.txt

test:
	make test_create
	./wcrepl_static < test.txt > results_static.txt
	./wcrepl_shared < test.txt > results_shared.txt
	./wcrepl_dll < test.txt > results_dll.txt

all:
	make static
	make shared
	make dll

static: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -c wclibrary.c
	ar rcs libwclibrary.a wclibrary.o
	$(CC) $(CFLAGS) wcrepl.c -o wcrepl_static -L . -lwclibrary
	
shared: wclibrary.c wcrepl.c
	$(CC) -fPIC $(CFLAGS) -c wclibrary.c
	$(CC) $(CFLAGS) -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) wcrepl.c -o wcrepl_shared -L . -lwclibrary

dll: wclibrary.c wcrepl.c
	$(CC) -fPIC $(CFLAGS) -c wclibrary.c
	$(CC) $(CFLAGS) -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) wcrepl.c -o wcrepl_dll -L . -lwclibrary -ldl -D USE_DLL

clean:
	rm -f *.o *.a *.so *.txtma