#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void find(const char *path, char type) {
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
            if ((type == 'f' && S_ISREG(statbuf.st_mode)) ||
                (type == 'd' && S_ISDIR(statbuf.st_mode))) {
                printf("%s\n", fullpath);
            }

            // 디렉토리면 계속 재귀 탐색
            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, type);
            }
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || (argv[2][0] != 'f' && argv[2][0] != 'd')) {
        fprintf(stderr, "사용법: %s <디렉토리> <f|d>\n", argv[0]);
        return 1;
    }
    find(argv[1], argv[2][0]);
    return 0;
}
