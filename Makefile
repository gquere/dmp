CC = gcc
CFLAGS = -O2 -Wall -Wextra -I./include
LDFLAGS = -fPIC -shared -L.

all: libs

libs: stack dmp

stack:
	$(CC) $(CFLAGS) stack.c -o libstack.so $(LDFLAGS)

dmp:
	$(CC) $(CFLAGS) dmp.c -o libdmp.so $(LDFLAGS) -lstack

