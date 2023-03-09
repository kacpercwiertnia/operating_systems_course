CC = gcc
CFLAGS = -Wall

all:
	make static
	make shared

static: wclibrary.c
	$(CC) $(CFLAGS) -c wclibrary.c
	ar rcs libwclibrary.a wclibrary.o
	
shared: wclibrary.c
	$(CC) -fPIC $(CLFAGS) -c wclibrary.c
	$(CC) $(CFLAGS) -shared -o libwclibrary.so wclibrary.o

clean:
	rm -f *.o *.a *.so