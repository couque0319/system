#include <stdio.h>

int main() {
    // ANSI escape sequence: 화면 지우고 커서를 (0,0) 위치로 이동
    printf("\033[2J\033[H");
    return 0;
}
