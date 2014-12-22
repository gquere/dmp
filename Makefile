CC = gcc
CFLAGS = -O2 -Wall -Wextra -I./include -L. -ggdb3
LDFLAGS = -fPIC -shared

all: libs

clean:
	rm *.so || true

## BUILD ##
libs: stack dmp queue


## INSTALL ##
install: libs
	cp *.so /usr/local/lib/
	mkdir -p /usr/local/include/dmp || true
	cp include/*.h /usr/local/include/dmp/


## TARGETS ##
stack:
	$(CC) $(CFLAGS) src/stack.c -o libstack.so $(LDFLAGS) -lpthread

queue:
	$(CC) $(CFLAGS) src/queue.c -o libqueue.so $(LDFLAGS) -lpthread

dmp:
	$(CC) $(CFLAGS) src/dmp.c -o libdmp.so $(LDFLAGS) -lstack

