CC = gcc
CFLAGS = -Wall -pthread

all: chat

chat: main.c chat.c
        $(CC) $(CFLAGS) -o chat main.c chat.c

clean:
        rm -f chat
        rm -f fifos/from_*
