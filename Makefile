CC = gcc
EXE = swinhoii
OBJECT = swinhoii.o swinhoii_node.o syntax_methods.o
CFLAGS = -Wall -O

swinhoii: $(OBJECT)
	$(CC) -o $(EXE) $(OBJECT)
swinhoii.o: swinhoii.c
	$(CC) $(CFLAGS) -c swinhoii.c
swinhoii_node.o: swinhoii_node.c
	$(CC) $(CFLAGS) -c swinhoii_node.c
syntax_methods.o: syntax_methods.c
	$(CC) $(CFLAGS) -c syntax_methods.c


clean:
	rm *.o swinhoii
