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
	./wcrepl_static_o1 < test.txt > results_static_O1.txt
	./wcrepl_shared_o1 < test.txt > results_shared_O1.txt
	./wcrepl_dll_o1 < test.txt > results_dll_O1.txt
	./wcrepl_static_o2 < test.txt > results_static_O2.txt
	./wcrepl_shared_o2 < test.txt > results_shared_O2.txt
	./wcrepl_dll_o2 < test.txt > results_dll_O2.txt
	./wcrepl_static_o3 < test.txt > results_static_O3.txt
	./wcrepl_shared_o3 < test.txt > results_shared_O3.txt
	./wcrepl_dll_o3 < test.txt > results_dll_O3.txt

all:
	make static_O1
	make static_O2
	make static_O3
	make shared_O1
	make shared_O2
	make shared_O3
	make dll_O1
	make dll_O2
	make dll_O3

static_O1: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O1 -c wclibrary.c
	ar rcs libwclibrary_O1.a wclibrary.o
	$(CC) $(CFLAGS) -O1 wcrepl.c -o wcrepl_static_o1 -L . libwclibrary_O1.a

static_O2: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O2 -c wclibrary.c
	ar rcs libwclibrary_O2.a wclibrary.o
	$(CC) $(CFLAGS) -O2 wcrepl.c -o wcrepl_static_o2 -L . libwclibrary_O2.a

static_O3: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O3 -c wclibrary.c
	ar rcs libwclibrary_O3.a wclibrary.o
	$(CC) $(CFLAGS) -O3 wcrepl.c -o wcrepl_static_o3 -L . libwclibrary_O3.a
	
shared_O1: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O1 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O1 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O1 wcrepl.c -o wcrepl_shared_o1 -L . -lwclibrary

shared_O2: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O2 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O2 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O2 wcrepl.c -o wcrepl_shared_o2 -L . -lwclibrary

shared_O3: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O3 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O3 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O3 wcrepl.c -o wcrepl_shared_o3 -L . -lwclibrary

dll_O1: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O1 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O1 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O1 wcrepl.c -o wcrepl_dll_o1 -L . -lwclibrary -ldl -D USE_DLL

dll_O2: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O2 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O2 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O2 wcrepl.c -o wcrepl_dll_o2 -L . -lwclibrary -ldl -D USE_DLL

dll_O3: wclibrary.c wcrepl.c
	$(CC) $(CFLAGS) -O3 -c -fPIC wclibrary.c
	$(CC) $(CFLAGS) -O3 -shared -o libwclibrary.so wclibrary.o
	$(CC) $(CFLAGS) -O3 wcrepl.c -o wcrepl_dll_o3 -L . -lwclibrary -ldl -D USE_DLL

clean:
	rm -f *.o *.a *.so *.txt