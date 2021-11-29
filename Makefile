CC = gcc
EXE = tatami
SUBDIR = src
SRC_OBJ = tatami.o tatami_node.o syntax_methods.o
OBJECT =
CFALGS = -Wall -O

tatami: $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(EXE)
tatami.o: $(SUBDIR)/tatami.c
	$(CC) $(CFLAGS) -c $(SUBDIR)/tatami.c 
tatami_node.o: $(SUBDIR)/tatami_node.c
	$(CC) $(CFLAGS) -c $(SUBDIR)/tatami_node.c 
syntax_methods.o: $(SUBDIR)/syntax_methods.c
	$(CC) $(CFLAGS) -c $(SUBDIR)/syntax_methods.c

clean:
	rm *.o
