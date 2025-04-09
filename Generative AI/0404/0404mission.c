#include <stdio.h>

int main() {
    int num;       // 입력받을 정수
    int count = 0; // 1의 개수를 저장할 변수
    
    // 0~255 사이의 정수 입력 받기
    printf("0~255 사이의 정수를 입력하세요: ");
    scanf("%d", &num);
    
    // 입력값 범위 체크
    if(num < 0 || num > 255) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }
    
    // 상위 4비트 출력
    printf("상위 4비트: ");
    for(int i = 7; i >= 4; i--) {
        int bit = (num >> i) & 1;  // i번째 비트 추출
        printf("%d", bit);
        count += bit;              // 1의 개수 카운트
    }
    printf("\n");
    
    // 나머지 비트의 1 개수 카운트
    for(int i = 3; i >= 0; i--) {
        count += (num >> i) & 1;
    }
    
    // 전체 1의 개수 출력
    printf("1의 개수: %d\n", count);
    
    return 0;
}
