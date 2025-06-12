#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// 파일 권한 출력 (예: -rw-r--r--)
void print_permissions(mode_t mode) {
    char perms[11] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (S_ISLNK(mode)) perms[0] = 'l';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    printf("%s ", perms);
}

// 상세 정보 출력
void print_file_info(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("stat");
        return;
    }

    print_permissions(st.st_mode);                      // 파일 권한 출력
    printf("%2ld ", st.st_nlink);                       // 하드링크 수

    struct passwd *pw = getpwuid(st.st_uid);            // 사용자 이름
    struct group *gr = getgrgid(st.st_gid);             // 그룹 이름
    printf("%s %s ", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

    printf("%6ld ", st.st_size);                        // 파일 크기

    char timebuf[80];
    struct tm *timeinfo = localtime(&st.st_mtime);      // 수정 시간
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", timeinfo);
    printf("%s ", timebuf);

    printf("%s\n", filename);                           // 파일 이름
}

int main(int argc, char *argv[]) {
    int show_all = 0;
    int long_format = 0;
    int opt;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "al")) != -1) {
        if (opt == 'a') show_all = 1;
        else if (opt == 'l') long_format = 1;
        else {
            fprintf(stderr, "Usage: %s [-a] [-l]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // 숨김 파일 제외 조건
        if (!show_all && entry->d_name[0] == '.')
            continue;

        if (long_format)
            print_file_info(entry->d_name);  // 상세 출력
        else
            printf("%s  ", entry->d_name);   // 이름만 출력
    }

    if (!long_format)
        printf("\n");

    closedir(dir);
    return 0;
}
