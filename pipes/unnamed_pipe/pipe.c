#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // child process
        close(pipe_fd[1]);
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));

        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // convert read data to upper letter
        for (int i = 0; i < bytes_read; i++) {
            buffer[i] = toupper(buffer[i]);
        }

        close(pipe_fd[0]);

        printf("coming data from parent process: %.*s\n", (int)bytes_read, buffer);

        exit(EXIT_SUCCESS);
    } else {
        // parent process
        close(pipe_fd[0]);

        printf("please type a data: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (write(pipe_fd[1], buffer, strlen(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]);

        wait(NULL);
    }

    return 0;
}
