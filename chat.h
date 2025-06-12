#ifndef CHAT_H
#define CHAT_H

#define MAX_MSG_LEN 256

extern char fifo_read[100], fifo_write[100];
extern int fd_read, fd_write;

void create_fifo(const char *name);
void sair(int sig);

#endif
