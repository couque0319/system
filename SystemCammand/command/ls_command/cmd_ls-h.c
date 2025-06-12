#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

// 사람이 읽기 쉬운 크기로 변환
void human_readable_size(off_t size, char *buf, size_t buf_size) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int unit_index = 0;
    double readable_size = (double)size;

    while (readable_size >= 1024 && unit_index < 4) {
        readable_size /= 1024.0;
        unit_index++;
    }

    snprintf(buf, buf_size, "%.1f%s", readable_size, units[unit_index]);
}

int main(int argc, char *argv[]) {
    int human = 0;
    int opt;

    // -h 옵션 파싱
    while ((opt = getopt(argc, argv, "h")) != -1) {
        if (opt == 'h') {
            human = 1;
        } else {
            fprintf(stderr, "Usage: %s [-h]\n", argv[0]);
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
        // 숨김 파일 제외
        if (entry->d_name[0] == '.')
            continue;

        if (human) {
            struct stat st;
            // 파일 상태 정보 조회
            if (stat(entry->d_name, &st) == -1) {
                perror("stat");
                continue;
            }

            char sizebuf[16];
            human_readable_size(st.st_size, sizebuf, sizeof(sizebuf));
            // 파일명과 사람이 읽기 쉬운 크기 출력
            printf("%-20s %6s\n", entry->d_name, sizebuf);
        } else {
            // 파일명만 출력
            printf("%s  ", entry->d_name);
        }
    }

    if (!human)
        printf("\n");

    closedir(dir);
    return 0;
}
