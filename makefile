CC = gcc -m32 -g -Wall -ansi -pedantic
OBJ = njvm_main.o njvm_filehandler.o njvm_memory.o njvm_instructions.o

njvm: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) -c $<


