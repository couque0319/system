// 파일명: kill_with_signal.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sig = SIGTERM; // 기본값

    // 옵션 파싱: -9 또는 -15 같은 형태
    if (argc == 3 && argv[1][0] == '-') {
        sig = atoi(argv[1] + 1);  // '-9' → 9
        pid_t pid = atoi(argv[2]);

        if (kill(pid, sig) == -1) {
            perror("kill");
            return 1;
        }

        printf("Sent signal %d to PID %d\n", sig, pid);
        return 0;
    }

    fprintf(stderr, "Usage: %s -<signal> <PID>\n", argv[0]);
    fprintf(stderr, "Example: %s -9 1234\n", argv[0]);
    return 1;
}
