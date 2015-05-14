CC = gcc
CFLAGS = -Wall -Werror -g
OBJS = main.o lexer.o
EXE = lisper

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c
.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXE)
