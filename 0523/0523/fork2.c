#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    { // 자식 프로세스
printf("[Child] : Hello, world pid=%d\n", getpid());
    }
    else
    { // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }
}