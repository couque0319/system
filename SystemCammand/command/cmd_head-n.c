#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int lines = 10;  // 기본값: 10줄
    int opt;

    // -n 옵션 파싱
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        if (opt == 'n') {
            lines = atoi(optarg);  // 문자열을 정수로
        } else {
            fprintf(stderr, "Usage: %s [-n number] filename\n", argv[0]);
            return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char buffer[1024];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
        if (++count >= lines)
            break;
    }

    fclose(fp);
    return 0;
}
