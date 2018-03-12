CC =gcc
m:=mmm
x:=$(m)
y:=$(x)bar
x:=later
#.PHONY echo $(x) $(y)
CFLAGS =-Wall -ansi -std=c99 -I include
EXEC=hello

all:$(EXEC)

hello: main.o hello.o
	$(CC) -o hello *.o $(CFLAGS)

hello.o: hello.c
	$(CC) -o hello.o -c hello.c $(CFLAGS)

main.o: main.c  
	$(CC) -o main.o -c main.c $(CFlAGS)

.PHONY clean:
	rm -rf *.o $(EXEC)
