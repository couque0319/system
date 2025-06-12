#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>

void find(const char *path, gid_t target_gid) {
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
            if (statbuf.st_gid == target_gid) {
                printf("%s\n", fullpath);
            }

            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, target_gid);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    i
