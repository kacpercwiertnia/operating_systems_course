CC = gcc
CFLAGS = -Wall

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
	rm -f *.o *.a *.so