#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 1024

// 문자열 비교용 함수 (기본 정렬 기준)
int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    char *lines[MAX_LINES];
    int count = 0;
    char buffer[MAX_LINE_LEN];

    // 한 줄씩 읽어서 메모리에 저장
    while (fgets(buffer, sizeof(buffer), fp)) {
        lines[count] = strdup(buffer);  // strdup: 문자열 복사
        count++;
        if (count >= MAX_LINES) break;
    }
    fclose(fp);

    // 정렬 수행
    qsort(lines, count, sizeof(char *), compare);

    // 출력
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);  // 메모리 해제
    }

    return 0;
}
