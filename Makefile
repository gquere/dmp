CC = gcc
CFLAGS = -O2 -Wall -Wextra -I./include -L. -ggdb3
LDFLAGS = -fPIC -shared

all: libs bin

clean:
	rm *.so || true
	rm use || true
	rm compare || true
	rm use_queue || true

## BUILD ##
libs: stack dmp queue

bin: use compare use_queue

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


use:
	$(CC) $(CFLAGS) use.c -o use -ldmp -lstack

compare:
	$(CC) $(CFLAGS) compare.c -o compare

use_queue:
	$(CC) $(CFLAGS) use_queue.c -o use_queue -lqueue
