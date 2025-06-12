#include "chat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

int fd_read, fd_write;
char fifo_read[100], fifo_write[100];

void sair(int sig) {
    printf("\n[INFO] Encerrando o chat...\n");
    close(fd_read);
    close(fd_write);
    unlink(fifo_read);
    unlink(fifo_write);
    exit(0);
}

void* escrever(void *arg) {
    char msg[MAX_MSG_LEN];
    while (1) {
        printf("[Tu] > ");
        fflush(stdout);
        if (fgets(msg, MAX_MSG_LEN, stdin) != NULL) {
            write(fd_write, msg, strlen(msg));
        }
    }
    return NULL;
}

void* ler(void *arg) {
    char msg[MAX_MSG_LEN];
    while (1) {
        ssize_t n = read(fd_read, msg, MAX_MSG_LEN - 1);
        if (n > 0) {
            msg[n] = '\0';
            printf("\n[Outro] > %s", msg);
            printf("[Tu] > ");
            fflush(stdout);
        }
        usleep(200000);
    }
    return NULL;
} 
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <meu_nome> <nome_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *me = argv[1];
    char *dest = argv[2];

    snprintf(fifo_read, sizeof(fifo_read), "fifos/from_%s_to_%s", dest, me);
    snprintf(fifo_write, sizeof(fifo_write), "fifos/from_%s_to_%s", me, dest);

    create_fifo(fifo_read);
    create_fifo(fifo_write);

    printf("[INFO] Abrindo pipes...\n");

    fd_read = open(fifo_read, O_RDONLY | O_NONBLOCK);
    fd_write = open(fifo_write, O_WRONLY);

    if (fd_read == -1 || fd_write == -1) {
        perror("Erro ao abrir FIFO");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, sair);

    pthread_t th_esc, th_leit;
    pthread_create(&th_esc, NULL, escrever, NULL);
    pthread_create(&th_leit, NULL, ler, NULL);

    pthread_join(th_esc, NULL);
    pthread_join(th_leit, NULL);

    return 0;
}
