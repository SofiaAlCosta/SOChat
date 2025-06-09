CC=gcc
CFLAGS=-Wall
SRC=src
OBJ=obj

all: chat

chat: $(SRC)/main.c $(SRC)/chat.c
	$(CC) $(CFLAGS) -o chat $(SRC)/main.c $(SRC)/chat.c

clean:
	rm -f chat
