#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run(char *cmd)
{
    int p[2];

    if (pipe(p) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        close(p[0]);
        close(p[1]);
        return;
    }

    if (pid1 == 0) {
        close(p[0]);

        if (dup2(p[1], 1) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(p[1]);

        execlp("sh", "sh", "-c", cmd, NULL);
        perror("execlp");
        _exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        close(p[0]);
        close(p[1]);
        waitpid(pid1, NULL, 0);
        return;
    }

    if (pid2 == 0) {
        close(p[1]);

        if (dup2(p[0], 0) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(p[0]);

        execlp("wc", "wc", "-c", NULL);
        perror("execlp");
        _exit(1);
    }

    close(p[0]);
    close(p[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        run(argv[i]);
    }

    return 0;
}