#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 1024

typedef struct {
    char name[256];     // 파일 이름
    time_t mtime;       // 수정 시간
} FileInfo;

// 수정 시간 기준으로 내림차순 정렬 (최신 파일이 먼저)
int compare_mtime(const void *a, const void *b) {
    FileInfo *fa = (FileInfo *)a;
    FileInfo *fb = (FileInfo *)b;
    return (fb->mtime - fa->mtime);
}

int main(int argc, char *argv[]) {
    int sort_by_time = 0;
    int opt;

    // -t 옵션 파싱
    while ((opt = getopt(argc, argv, "t")) != -1) {
        if (opt == 't') {
            sort_by_time = 1;
        } else {
            fprintf(stderr, "Usage: %s [-t]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    FileInfo files[MAX_FILES];
    int count = 0;

    // 디렉토리 내부 항목 읽기
    while ((entry = readdir(dir)) != NULL) {
        // 숨김 파일 제외
        if (entry->d_name[0] == '.')
            continue;

        if (count >= MAX_FILES) {
            fprintf(stderr, "Too many files\n");
            break;
        }

        struct stat st;
        // 파일의 상태 정보(stat)를 가져와서 수정 시간 저장
        if (stat(entry->d_name, &st) == -1) {
            perror("stat");
            continue;
        }

        strncpy(files[count].name, entry->d_name, sizeof(files[count].name));
        files[count].mtime = st.st_mtime;
        count++;
    }

    closedir(dir);

    // -t 옵션이 있을 경우 수정 시간 기준 정렬 수행
    if (sort_by_time) {
        qsort(files, count, sizeof(FileInfo), compare_mtime);
    }

    // 정렬된 파일 목록 출력
    for (int i = 0; i < count; i++) {
        printf("%s  ", files[i].name);
    }

    printf("\n");
    return 0;
}
