CC = gcc
FLAG = -c
OUTPUT = -o
OBJ =exe
ALL = common.o main.o

$(OBJ):$(ALL)
	$(CC) $^ $(OUTPUT) $@
%.o:%.c
	$(CC) $(FLAG) $< $(OUTPUT) $@
.PHONY:clean
clean:
	@rm -rf $(ALL) $(OBJ)
	
