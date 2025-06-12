#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s path [suffix]\n", argv[0]);
        return 1;
    }

    char *path = argv[1];
    char *filename = strrchr(path, '/');

    if (filename)
        filename++; // '/' 다음부터 시작
    else
        filename = path;

    if (argc == 3) {
        char *suffix = argv[2];
        size_t len_filename = strlen(filename);
        size_t len_suffix = strlen(suffix);

        if (len_filename > len_suffix &&
            strcmp(filename + len_filename - len_suffix, suffix) == 0) {
            filename[len_filename - len_suffix] = '\0'; // 확장자 제거
        }
    }

    printf("%s\n", filename);
    return 0;
}
