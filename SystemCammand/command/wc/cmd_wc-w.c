#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int count_words = 0;
    int opt;

    // -w 옵션 파싱
    while ((opt = getopt(argc, argv, "w")) != -1) {
        if (opt != 'w') {
            fprintf(stderr, "Usage: %s -w filename\n", argv[0]);
            return 1;
        }
        count_words = 1;
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

    int ch;
    int in_word = 0;
    long word_count = 0;

    // 한 글자씩 읽으며 단어 개수 세기
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) {
            in_word = 0;  // 공백이면 단어 끝
        } else {
            if (!in_word) {
                word_count++;  // 새 단어 시작
                in_word = 1;
            }
        }
    }

    fclose(fp);

    // 출력
    printf("%ld %s\n", word_count, argv[optind]);
    return 0;
}
