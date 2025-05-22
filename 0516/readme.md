
# 📂 7장: 파일 및 레코드 잠금

## 🔐 7.1 파일 잠금

- 파일이나 파일 일부(레코드)를 잠금(lock)하여 동시 접근을 제어
- 주요 함수: `flock(fd, operation)`
  - `LOCK_SH`: 공유 잠금
  - `LOCK_EX`: 배타 잠금
  - `LOCK_UN`: 잠금 해제
  - `LOCK_NB`: 비차단 잠금

### 파일 잠금 예시
```c
flock(fd, LOCK_EX);
...
flock(fd, LOCK_UN);
```

## 🔐 7.2 레코드 잠금

- 파일의 일부 영역만 잠그기
- 함수: `fcntl(fd, cmd, struct flock*)`
- 잠금 유형:
  - `F_RDLCK`: 읽기 잠금
  - `F_WRLCK`: 쓰기 잠금
  - `F_UNLCK`: 잠금 해제

```c
struct flock {
  short l_type;
  off_t l_start;
  short l_whence;
  off_t l_len;
  pid_t l_pid;
};
```

## 🛠 예제: rdlock.c / wrlock.c
- `rdlock`: 읽기 잠금 후 학생 레코드 조회
- `wrlock`: 쓰기 잠금 후 학생 레코드 수정

## 🔧 7.3 lockf() 함수
- `F_LOCK`, `F_TLOCK`, `F_TEST`, `F_ULOCK` 등 간단한 잠금 함수

```c
lockf(fd, F_LOCK, sizeof(record)); // 잠금
lockf(fd, F_ULOCK, sizeof(record)); // 해제
```

## 🚦 7.4 권고 잠금 vs 강제 잠금

| 구분 | 권고 잠금 (advisory) | 강제 잠금 (mandatory) |
|------|----------------------|------------------------|
| 특징 | 규칙 자발적 준수     | 커널이 강제 적용       |
| OS   | Linux, BSD 등        | System V, Solaris 등   |

- 강제 잠금은 set-group-ID 비트 + group-exec 제거 필요
```bash
chmod 2644 mandatory.txt
```

---

# ⚙️ 8장: 프로세스

## 🖥️ 8.1 쉘과 프로세스

- 쉘: 명령어 처리기 (command processor)
- 전면 처리: 쉘이 기다림
- 후면 처리: `&` 사용, 동시에 작업 가능

```bash
(sleep 5; echo done) &
jobs
fg %1
```

## 🧠 8.2 프로그램 실행

- `exec` 계열 함수로 프로세스 이미지 덮어쓰기
- `main(argc, argv)`로 명령줄 인수 전달
- `getenv("HOME")`으로 환경변수 접근 가능

## 🔚 8.3 프로그램 종료

- `exit()`: 뒷정리 후 종료
- `_exit()`: 즉시 종료 (버퍼 처리 X)
- `atexit(func)`: exit 핸들러 등록

```c
atexit(handler_func);
```

## 🆔 8.4 프로세스 ID 및 사용자 ID

- `getpid()`, `getppid()`
- `getuid()`, `geteuid()` / `getgid()`, `getegid()`
- `setuid()`, `seteuid()`, `setgid()`, `setegid()`
- `set-user-id` 실행 권한: 파일 실행 시 UID 변경

```bash
chmod 4755 file
```

## 🧩 8.5 프로세스 이미지 구성

- 텍스트: 실행 코드
- 데이터: 전역/정적 변수
- 힙: malloc으로 할당
- 스택: 함수 호출, 지역 변수
- U-영역: 파일 디스크립터, 디렉토리 등

---

## ✅ 핵심 요약

- 파일/레코드 동시 접근 제어: `flock()`, `fcntl()`, `lockf()`
- 프로세스는 실행 중인 프로그램, 고유 PID 보유
- 쉘은 명령을 처리하고 프로그램 실행 제어
- 환경 변수는 `getenv`, `putenv`, `setenv`로 사용
- 프로세스 종료 시 `exit`, `_exit`, `atexit` 등 활용

