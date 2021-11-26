CC = gcc
EXE = tatami
SUBDIR = src
SRC_OBJ = tatami.o 
OBJECT =
CFALGS = -Wall -O

tatami: tatami.o 
	$(CC) $(CFLAGS) -o $(EXE) $(SRC_OBJ)

tatami.o: $(SUBDIR)/tatami.c
	$(CC) $(CFLAGS) -c $(SUBDIR)/tatami.c -o tatami.o
tatami_node.o : $(SUBDIR)/tatami_node.c
	$(CC) $(CFLAGS) -c $(SUBDIR)/tatami_node.c -o tatami_node.o

clean:
	rm *.o
