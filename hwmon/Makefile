CC = gcc
APP = app
#CFlags = ()

all: build

main:
	$(CC) -c $@.c -o $@.o

build: main
	$(CC) $^.o -o $(APP)

clean:
	rm -f *.o
