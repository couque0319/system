#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

char type(mode_t mode) {
    if (S_ISREG(mode)) return '-';
    else if (S_ISDIR(mode)) return 'd';
    else if (S_ISCHR(mode)) return 'c';
    else if (S_ISBLK(mode)) return 'b';
    else if (S_ISFIFO(mode)) return 'p';
    else if (S_ISLNK(mode)) return 'l';
    else if (S_ISSOCK(mode)) return 's';
    else return '?';
}

void perm(mode_t mode, char *perms) {
    strcpy(perms, "---------");

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';
}

void printStat(char *pathname, char *filename, struct stat *st) {
    char perms[10];
    char timebuf[64];

    perm(st->st_mode, perms);
    printf("%c%s ", type(st->st_mode), perms);
    printf("%2ld ", (long)st->st_nlink);

    struct passwd *usr = getpwuid(st->st_uid);
    struct group *grp = getgrgid(st->st_gid);

    printf("%s %s ", usr ? usr->pw_name : "?", grp ? grp->gr_name : "?");
    printf("%5ld ", (long)st->st_size);

    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st->st_mtime));
    printf("%s %s\n", timebuf, filename);
}

int main(int argc, char **argv) {
    DIR *dp;
    struct dirent *d;
    struct stat st;
    char *dir;
    char path[BUFSIZ + 1];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0) {
            perror(path);
            continue;
        }

        printStat(path, d->d_name, &st);
    }

    closedir(dp);
    return 0;
}
