CC = gcc
CFLAGS = -Wall -Werror -g
OBJS = main.o
EXE = lisper

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXE)
