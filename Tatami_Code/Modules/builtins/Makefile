CC = gcc
EXE = libbuiltins.so
OBJECT = builtins.o tatami_node.o
CFLAGS = -Wall -O 


libbuiltins.so: $(OBJECT)
	$(CC) -shared -o $(EXE) $(OBJECT)

builtins.o: builtins.c
	$(CC) -c -Wall -Werror -fpic builtins.c

tatami_node.o: tatami_node.c
	$(CC) -c -Wall -Werror -fpic tatami_node.c