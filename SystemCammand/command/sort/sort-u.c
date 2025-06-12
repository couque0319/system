#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LEN 1024

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-u") != 0) {
        fprintf(stderr, "사용법: %s -u <파일명>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    char *lines[MAX_LINES];
    char buffer[MAX_LEN];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), fp) && count < MAX_LINES) {
        lines[count++] = strdup(buffer);
    }
    fclose(fp);

    qsort(lines, count, sizeof(char *), compare);

    // 중복 제거 후 출력
    for (int i = 0; i < count; i++) {
        if (i == 0 || strcmp(lines[i], lines[i - 1]) != 0) {
            printf("%s", lines[i]);
        }
        free(lines[i]);
    }

    return 0;
}
