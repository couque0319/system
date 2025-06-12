#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-n") != 0) {
        fprintf(stderr, "사용법: %s -n <pattern> <filename>\n", argv[0]);
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
    int lineno = 1;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            printf("%d:%s", lineno, line);
        }
        lineno++;
    }

    fclose(fp);
    return 0;
}
