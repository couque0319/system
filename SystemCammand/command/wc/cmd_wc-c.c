#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int count_bytes = 0;
    int opt;

    // -c 옵션 파싱
    while ((opt = getopt(argc, argv, "c")) != -1) {
        if (opt != 'c') {
            fprintf(stderr, "Usage: %s -c filename\n", argv[0]);
            return 1;
        }
        count_bytes = 1;
    }

    if (optind >= argc) {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    FILE *fp = fopen(argv[optind], "rb");  // 바이너리 모드로 열기 (정확한 바이트 계산)
    if (!fp) {
        perror("fopen");
        return 1;
    }

    long byte_count = 0;
    int ch;

    // 한 바이트씩 읽으며 개수 세기
    while ((ch = fgetc(fp)) != EOF) {
        byte_count++;
    }

    fclose(fp);

    // 출력
    printf("%ld %s\n", byte_count, argv[optind]);
    return 0;
}
