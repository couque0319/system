#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-f") != 0) {
        fprintf(stderr, "사용법: %s -f <원본> <대상>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[2], "rb");
    if (!src) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    remove(argv[3]);  // 대상 파일이 있다면 삭제

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
