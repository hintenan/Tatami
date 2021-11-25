CC = gcc
EXE = tatami
SOURCE_PATH = Tatami_Code
OBJECT = tatami.o tatami_node.o syntax_methods.o syntax_trans.o var_fun.o load_module.o
CFLAGS = -Wall -O 


../tatami: $(OBJECT)
	$(CC) -o ../$(EXE) $(OBJECT)
tatami.o: tatami.c
	$(CC) $(CFLAGS) -c tatami.c
tatami_node.o: tatami_node.c
	$(CC) $(CFLAGS) -c tatami_node.c
syntax_methods.o: syntax_methods.c
	$(CC) $(CFLAGS) -c syntax_methods.c
var_fun.o: var_fun.c
	$(CC) $(CFLAGS) -c var_fun.c
syntax_trans.o: syntax_trans.c
	$(CC) $(CFLAGS) -c syntax_trans.c
load_module.o: load_module.c
	$(CC) $(CFLAGS) -c load_module.c



clean:
	rm *.o
