CC = gcc
CFLAGS = -Wall
SRC = src
OBJ = obj

all: chat

chat: main.c chat.c
	$(CC) $(CFLAGS) -o chat main.c chat.c

clean:
	rm -f chat