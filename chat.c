#include "chat.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void create_fifo(const char *name) {
    mkdir("fifos", 0777);
    if (access(name, F_OK) == -1) {
        if (mkfifo(name, 0666) == -1) {
            perror("Erro ao criar FIFO");
            exit(EXIT_FAILURE);
        }
    }
}
