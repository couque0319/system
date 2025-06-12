#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LEN 1024

int column = 1;

char *get_field(const char *line, int col) {
    static char copy[MAX_LEN];
    strcpy(copy, line);
    char *token = strtok(copy, " \t\n");
    int i = 1;
    while (token && i < col) {
        token = strtok(NULL, " \t\n");
        i++;
    }
    return token ? token : "";
}

int compare_field(const void *a, const void *b) {
    const char *fa = get_field(*(const char **)a, column);
    const char *fb = get_field(*(const char **)b, column);
    return strcmp(fa, fb);
}

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-k") != 0) {
        fprintf(stderr, "사용법: %s -k <열 번호> <파일명>\n", argv[0]);
        return 1;
    }

    column = atoi(argv[2]);
    if (column <= 0) {
        fprintf(stderr, "열 번호는 1 이상이어야 합니다.\n");
        return 1;
    }

    FILE *fp = fopen(argv[3], "r");
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

    qsort(lines, count, sizeof(char *), compare_field);

    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    return 0;
}
