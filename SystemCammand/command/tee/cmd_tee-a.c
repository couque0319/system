#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-a") != 0) {
        fprintf(stderr, "Usage: %s -a filename\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "a");  // append 모드로 열기
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char buffer[1024];

    // 표준 입력을 한 줄씩 읽어서
    while (fgets(buffer, sizeof(buffer), stdin)) {
        fputs(buffer, stdout);  // 화면에 출력
        fputs(buffer, fp);      // 파일에 쓰기 (이어쓰기)
    }

    fclose(fp);
    return 0;
}
