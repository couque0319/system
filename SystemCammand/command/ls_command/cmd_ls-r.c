#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 1024

int compare_name(const void *a, const void *b) {
    const char *fa = *(const char **)a;
    const char *fb = *(const char **)b;
    return strcmp(fa, fb);  // 이름 오름차순 정렬
}

int main(int argc, char *argv[]) {
    int reverse = 0;
    int opt;

    // -r 옵션 파싱
    while ((opt = getopt(argc, argv, "r")) != -1) {
        if (opt == 'r') {
            reverse = 1;
        } else {
            fprintf(stderr, "Usage: %s [-r]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char *filenames[MAX_FILES];
    int count = 0;

    // 파일 이름을 배열에 저장
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;

        if (count >= MAX_FILES) {
            fprintf(stderr, "Too many files\n");
            break;
        }

        filenames[count] = strdup(entry->d_name);  // 복사해서 저장
        count++;
    }

    closedir(dir);

    // 이름 기준 정렬
    qsort(filenames, count, sizeof(char *), compare_name);

    // 출력
    if (reverse) {
        // 뒤에서부터 출력
        for (int i = count - 1; i >= 0; i--) {
            printf("%s  ", filenames[i]);
            free(filenames[i]);  // 메모리 해제
        }
    } else {
        for (int i = 0; i < count; i++) {
            printf("%s  ", filenames[i]);
            free(filenames[i]);  // 메모리 해제
        }
    }

    printf("\n");
    return 0;
}
