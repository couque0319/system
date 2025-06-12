// 파일명: kill_default.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    // SIGTERM (기본 시그널: 종료 요청)
    if (kill(pid, SIGTERM) == -1) {
        perror("kill");
        return 1;
    }

    printf("Sent SIGTERM to PID %d\n", pid);
    return 0;
}
