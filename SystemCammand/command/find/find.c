#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void find(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (!dp) return;

    while ((entry = readdir(dp)) != NULL) {
        // 현재 디렉토리(.)와 상위 디렉토리(..)는 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // 전체 경로 구성
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        printf("%s\n", fullpath);  // 파일 또는 디렉터리 출력

        struct stat statbuf;
        if (stat(fullpath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            // 하위 디렉토리면 재귀적으로 탐색
            find(fullpath);
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    const char *start = argc > 1 ? argv[1] : ".";
    find(start);
    return 0;
}

