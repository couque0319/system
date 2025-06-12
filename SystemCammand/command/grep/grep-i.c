#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 대소문자 무시 비교용 strstr 함수
char *strcasestr_custom(const char *haystack, const char *needle) {
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
            h++;
            n++;
        }
        if (*n == '\0') return (char *)haystack;
        haystack++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-i") != 0) {
        fprintf(stderr, "사용법: %s -i <pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[2];
    const char *filename = argv[3];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strcasestr_custom(line, pattern)) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
