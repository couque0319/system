#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <모드(8진수)> <파일명>\n", argv[0]);
        return 1;
    }

    // 8진수 권한 문자열을 정수로 변환
    mode_t mode = strtol(argv[1], NULL, 8);

    // 권한 변경 시도
    if (chmod(argv[2], mode) != 0) {
        perror("chmod 실패");
        return 1;
    }

    printf("'%s' 권한이 %s로 변경되었습니다.\n", argv[2], argv[1]);
    return 0;
}
