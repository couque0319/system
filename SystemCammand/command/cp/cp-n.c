#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-n") != 0) {
        fprintf(stderr, "사용법: %s -n <원본> <대상>\n", argv[0]);
        return 1;
    }

    FILE *check = fopen(argv[3], "r");
    if (check) {
        fclose(check);
        printf("'%s' 파일이 이미 존재합니다. 복사하지 않습니다.\n", argv[3]);
        return 0;
    }

    FILE *src = fopen(argv[2], "rb");
    if (!src) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    FILE *dest = fopen(argv[3], "wb");
    if (!dest) {
        perror("대상 파일 열기 실패");
        fclose(src);
        return 1;
    }

    char buf[4096];
    size_t size;
    while ((size = fread(buf, 1, sizeof(buf), src)) > 0) {
        fwrite(buf, 1, size, dest);
    }

    fclose(src);
    fclose(dest);
    return 0;
}
