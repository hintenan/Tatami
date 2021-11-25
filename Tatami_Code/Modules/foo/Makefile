CC = gcc
EXE = libfoo.so
OBJECT = foo.o
CFLAGS = -Wall -O 


libfoo.so: $(OBJECT)
	$(CC) -shared -o $(EXE) $(OBJECT)

foo.o: foo.c
	$(CC) -c -Wall -Werror -fpic foo.c