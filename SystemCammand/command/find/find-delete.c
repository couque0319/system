#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void delete_recursive(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (!dp) return;

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (lstat(fullpath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                // 디렉토리는 내부 먼저 지우고 나중에 rmdir
                delete_recursive(fullpath);
                rmdir(fullpath);
                printf("디렉토리 삭제됨: %s\n", fullpath);
            } else {
                // 일반 파일/링크/디바이스 삭제
                unlink(fullpath);
                printf("파일 삭제됨: %s\n", fullpath);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <디렉토리>\n", argv[0]);
        return 1;
    }

    delete_recursive(argv[1]);
    return 0;
}
