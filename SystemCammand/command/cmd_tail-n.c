#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINES 10000

int main(int argc, char *argv[]) {
    int lines = 10;  // 기본값
    int opt;

    // -n 옵션 파싱
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        if (opt == 'n') {
            lines = atoi(optarg);
        } else {
            fprintf(stderr, "Usage: %s [-n number] filename\n", argv[0]);
            return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    // 최대 MAX_LINES 줄까지 저장할 수 있는 버퍼
    char *linebuf[MAX_LINES];
    int count = 0;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        // 기존 메모리 해제 (재사용)
        if (count >= MAX_LINES) {
            free(linebuf[count % MAX_LINES]);
        }

        linebuf[count % MAX_LINES] = strdup(buffer);  // 줄 복사 저장
        count++;
    }

    fclose(fp);

    int start = (count > lines) ? (count - lines) : 0;

    for (int i = start; i < count; i++) {
        printf("%s", linebuf[i % MAX_LINES]);
        free(linebuf[i % MAX_LINES]);  // 메모리 해제
    }

    return 0;
}
