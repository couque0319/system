#include<stdio.h>
#include<ctype.h>

int main()
{
    char ch;

    while (1){
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if(ch == 0){
            break;
        }

        if(isupper(ch)){
            printf("%c의 소문자는 %c 입니다.\n", ch ,tolower(ch));
        }
        else if (islower(ch)){
            printf("%c의 대문자는 %c 입니다.\n", ch ,toupper(ch));
        }
        else{
            return 0;
        }

    }



    return 0;
}