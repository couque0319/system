#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

long parse_size(const char *str) {
    char unit = str[strlen(str) - 1];
    long multiplier = 1;
    char size_str[100];
    strncpy(size_str, str + 1, sizeof(size_str));  // + 또는 - 기호 제외
    size_str[sizeof(size_str) - 1] = '\0';

    if (unit == 'k' || unit == 'K') multiplier = 1024;
    else if (unit == 'M') multiplier = 1024 * 1024;
    else if (unit == 'G') multiplier = 1024 * 1024 * 1024;
    else unit = '\0';  // no unit

    if (unit != '\0')
        size_str[strlen(size_str) - 1] = '\0';  // 단위 제거

    return atol(size_str) * multiplier;
}

void find(const char *path, char op, long target_size) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (!dp) return;

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(fullpath, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode)) {
                if ((op == '+' && statbuf.st_size > target_size) ||
                    (op == '-' && statbuf.st_size < target_size)) {
                    printf("%s\n", fullpath);
                }
            }
            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, op, target_size);
            }
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || (argv[2][0] != '+' && argv[2][0] != '-')) {
        fprintf(stderr, "사용법: %s <디렉토리> <+크기|−크기> (예: +100k)\n", argv[0]);
        return 1;
    }

    long size = parse_size(argv[2]);
    char op = argv[2][0];

    find(argv[1], op, size);
    return 0;
}
