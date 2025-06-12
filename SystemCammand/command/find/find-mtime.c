#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void find(const char *path, char op, int days) {
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (!dp) return;

    time_t now = time(NULL);

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(fullpath, &statbuf) == 0) {
            time_t mtime = statbuf.st_mtime;
            double diff_days = difftime(now, mtime) / (60 * 60 * 24);

            if ((op == '-' && diff_days < days) ||
                (op == '+' && diff_days > days) ||
                (op == '=' && (int)diff_days == days)) {
                printf("%s\n", fullpath);
            }

            if (S_ISDIR(statbuf.st_mode)) {
                find(fullpath, op, days);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || (argv[2][0] != '-' && argv[2][0] != '+' && argv[2][0] != '=')) {
        fprintf(stderr, "사용법: %s <디렉토리> <-N | +N | =N>\n", argv[0]);
        return 1;
    }

    char op = argv[2][0];
    int days = atoi(argv[2] + 1);

    find(argv[1], op, days);
    return 0;
}
