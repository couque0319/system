#include <stdio.h>

int main() {
    char name[50];
    int studentID;

    printf("학번을 입력하세요: ");
    scanf("%d", &studentID);

    printf("이름을 입력하세요: ");
    scanf("%s", name);

    printf("\n=== 학생 정보 ===\n");
    printf("학번: %d\n", studentID);
    printf("이름: %s\n", name);

    return 0;
}
