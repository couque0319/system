#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        return 1;
    }

    char *path = argv[1];
    static char temp[1024];
    strncpy(temp, path, sizeof(temp));
    temp[sizeof(temp) - 1] = '\0';

    char *last_slash = strrchr(temp, '/');

    if (!last_slash) {
        // 슬래시가 없는 경우, 현재 디렉토리
        printf(".\n");
    } else if (last_slash == temp) {
        // 루트 디렉토리인 경우
        *(last_slash + 1) = '\0';
        printf("%s\n", temp);
    } else {
        // 그 외 일반적인 경우
        *last_slash = '\0';
        printf("%s\n", temp);
    }

    return 0;
}
