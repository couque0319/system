#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fnmatch.h>

void find(const char *path, const char *pattern) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (!dp) return;

    while ((entry = readdir(dp)) != NULL) {
        // 현재/상위 디렉토리 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // 패턴 일치 확인
        if (fnmatch(pattern, entry->d_name, 0) == 0) {
            printf("%s\n", fullpath);
        }

        struct stat statbuf;
        if (stat(fullpath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            find(fullpath, pattern);  // 하위 디렉토리 재귀 탐색
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <디렉토리> <패턴>\n", argv[0]);
        return 1;
    }
    find(argv[1], argv[2]);
    return 0;
}
