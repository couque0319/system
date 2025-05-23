# 프로세스 관리 가이드

## 9.1 프로세스 생성

### `fork()` 시스템 호출
- 부모 프로세스가 자식 프로세스를 복제해 생성함
- 자식 프로세스에는 `0`, 부모에게는 자식 PID를 반환함
- 리턴값을 기준으로 부모/자식 프로세스를 구분 가능

```c
pid = fork();
if (pid == 0) {
    // 자식 프로세스
} else {
    // 부모 프로세스
}
```

### 예제 코드

#### 1. `fork1.c`: 기본 fork 예제
```c
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
```

#### 2. `fork2.c`: 부모와 자식에서 다른 메시지 출력
```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("[Child 1] : Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        printf("[Child 2] : Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    printf("[PARENT] : Hello, world ! pid=%d\n", getpid());
}
```

#### 3. `fork3.c`: 두 개의 자식 프로세스를 생성
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2, child, status;
    printf("[%d] 부모 프로세스 시작 \n", getpid());
    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] 자식 프로세스[1] 시작 \n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스[1] 종료 \n", getpid());
        exit(1);
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] 자식 프로세스 #2 시작 \n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스 #2 종료 \n", getpid());
        exit(2);
    }
    // 자식 프로세스 #1의 종료를 기다린다.
    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
    return 0;
}
```

## 9.1.2 프로세스 종료 대기 (`wait`, `waitpid`)

- 자식 프로세스 종료 시까지 대기
- `wait()`는 어떤 자식이든 대기, `waitpid()`는 특정 자식만 대기

#### `wait()` 예제
```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid, child, status;
    printf("[%d] 부모 프로세스 시작 \n", getpid());
    pid = fork();
    if (pid == 0)
    {
        printf("[%d] 자식 프로세스 시작 \n", getpid());
        exit(1);
    }
    child = wait(&status); // 자식 프로세스가 끝나기를 기다린다.
    printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
```

#### `waitpid()` 예제
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid1, pid2, child, status;

    printf("[%d] 부모 프로세스 시작 \n", getpid());

    pid1 = fork();
    if (pid1 == 0)
    {
        printf("[%d] 자식 프로세스[1] 시작 \n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스[1] 종료 \n", getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        printf("[%d] 자식 프로세스 #2 시작 \n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스 #2 종료 \n", getpid());
        exit(2);
    }

    // 자식 프로세스 #1의 종료를 기다린다.
    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);

    return 0;
}
```
