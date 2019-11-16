CFLAGS=-o
CC=g++

all: myserver myclient

.PHONY: myserver myclient

myserver:
	$(CC) myserver.cpp -o myserver

myclient:
	$(CC) myclient.cpp -o myclient

clean:
	rm -rf myserver myclient
