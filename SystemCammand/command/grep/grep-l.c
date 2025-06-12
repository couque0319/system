#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_file(const char *pattern, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            fclose(fp);
            return 1; // 찾으면 바로 종료
        }
    }

    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 4 || strcmp(argv[1], "-l") != 0) {
        fprintf(stderr, "사용법: %s -l <pattern> <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[2];

    for (int i = 3; i < argc; i++) {
        if (search_file(pattern, argv[i])) {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
