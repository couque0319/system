#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

void find(const char *path, uid_t target_uid) {
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
            if (statbuf.st_uid == target_uid) {
                printf("%s\n", fullpath);
            }

            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, target_uid);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <디렉토리> <사용자 이름>\n", argv[0]);
        return 1;
    }

    struct passwd *pw = getpwnam(argv[2]);
    if (!pw) {
        fprintf(stderr, "사용자를 찾을 수 없습니다: %s\n", argv[2]);
        return 1;
    }

    find(argv[1], pw->pw_uid);
    return 0;
}
