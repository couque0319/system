#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handle_sigint(int sig) {
    // 무시 처리
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-i") != 0) {
        fprintf(stderr, "Usage: %s -i filename\n", argv[0]);
        return 1;
    }

    signal(SIGINT, handle_sigint);  // Ctrl+C 무시

    FILE *fp = fopen(argv[2], "w");  // 새로 쓰기 모드
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin)) {
        fputs(buffer, stdout);  // 화면 출력
        fputs(buffer, fp);      // 파일 출력
    }

    fclose(fp);
    return 0;
}
 