#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // 숨김 파일 제외
        if (entry->d_name[0] == '.')
            continue;

        // 파일 이름 출력
        printf("%s  ", entry->d_name);
    }

    printf("\n");

    closedir(dir);
    return 0;
}
