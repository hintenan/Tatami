CC = gcc
EXE = tatami
OBJECT = tatami.o tatami_node.o syntax_methods.o
CFLAGS = -Wall -O

tatami: $(OBJECT)
	$(CC) -o $(EXE) $(OBJECT)
tatami.o: tatami.c
	$(CC) $(CFLAGS) -c tatami.c
tatami_node.o: tatami_node.c
	$(CC) $(CFLAGS) -c tatami_node.c
syntax_methods.o: syntax_methods.c
	$(CC) $(CFLAGS) -c syntax_methods.c


clean:
	rm *.o tatami
