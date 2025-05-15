
# File System Summary

## 📂 파일 시스템 구조
* **부트 블록 (Boot block)**: 부팅을 위한 코드 저장
* **슈퍼 블록 (Super block)**: 전체 파일 시스템 정보 저장
  * 총 블록 수, i-node 개수, 블록 크기 등
* **i-리스트 (i-list)**: i-node들의 목록
* **데이터 블록 (Data block)**: 실제 파일 내용 저장

## 🧱 i-Node란?
* 파일 하나에 하나의 i-node
* 파일 메타정보 포함:
  * 타입, 크기, 권한, 소유자, 접근시간 등
  * 데이터 블록 주소(포인터)

## 📌 블록 포인터
* **직접 포인터**: 10개
* **간접 포인터**: 1개
* **이중 간접 포인터**: 1개

## 🧠 커널 내 파일 입출력 자료구조
* **파일 디스크립터 배열 (Fd array)**
* **열린 파일 테이블 (Open File Table)**
* **동적 i-node 테이블 (Active i-node Table)**

## 📁 파일 상태 정보 - `stat()` 함수

```c
#include <sys/stat.h>
int stat(const char *path, struct stat *buf);
```

### 주요 필드
* `st_mode`: 파일 타입 및 권한
* `st_ino`: i-node 번호
* `st_uid / st_gid`: 소유자 및 그룹
* `st_size`: 파일 크기
* `st_atime / st_mtime / st_ctime`: 시간 정보

## 📄 파일 타입

| 타입 | 매크로 함수 |
|------|------------|
| 일반 파일 | `S_ISREG()` |
| 디렉터리 파일 | `S_ISDIR()` |
| 문자 장치 파일 | `S_ISCHR()` |
| 블록 장치 파일 | `S_ISBLK()` |
| FIFO | `S_ISFIFO()` |
| 소켓 | `S_ISSOCK()` |
| 심볼릭 링크 | `S_ISLNK()` |

## 🔐 파일 권한
* **구조**: `st_mode`의 마지막 9비트
* **분류**: 사용자(user), 그룹(group), 기타(others)
* **권한 종류**: 읽기(r), 쓰기(w), 실행(x)

### 권한 변경 함수

```c
int chmod(const char *path, mode_t mode);
int chown(const char *path, uid_t owner, gid_t group);
int utime(const char *filename, const struct utimbuf *times);
```

## 📁 디렉터리 관련 함수

```c
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dp);
int mkdir(const char *path, mode_t mode);
int rmdir(const char *path);
```

## 🔗 링크
* **하드 링크**: 동일 파일의 또 다른 이름 (i-node 공유)

```c
int link(char *existing, char *new);
int unlink(char *path);
```

* **심볼릭 링크**: 경로 문자열을 저장하는 파일

```c
int symlink(const char *actual, const char *sym);
int readlink(const char *path, char *buf, size_t bufsize);
```

## ✅ 핵심 요약
* 유닉스 파일 시스템은 부트 블록, 슈퍼 블록, i-list, 데이터 블록으로 구성
* 파일은 커널 내부의 다양한 자료구조로 관리됨
* 디렉터리는 i-node를 갖는 특수한 파일이며, 그 안에 이름과 i-node 번호가 저장됨
* 하드 링크는 같은 파일의 다른 이름, 심볼릭 링크는 경로 문자열로 다른 파일을 참조
