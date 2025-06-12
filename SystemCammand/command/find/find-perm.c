#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void find(const char *path, mode_t target_perm) {
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
            mode_t file_perm = statbuf.st_mode & 0777;

            if (file_perm == target_perm) {
                printf("%s\n", fullpath);
            }

            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, target_perm);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <디렉토리> <권한(8진수)>\n", argv[0]);
        return 1;
    }

    mode_t perm = strtol(argv[2], NULL, 8);  // 8진수로 입력 받음

    find(argv[1], perm);
    return 0;
}
