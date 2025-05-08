# 컴퓨터 시스템 구조

## 유닉스 커널(kernel)
하드웨어를 운영 관리하여 다음과 같은 서비스를 제공:
- 파일 관리(File management)
- 프로세스 관리(Process management)
- 메모리 관리(Memory management)
- 통신 관리(Communication management)
- 주변장치 관리(Device management)

## 시스템 호출
- 시스템 호출은 커널에 서비스 요청을 위한 프로그래밍 인터페이스
- 응용 프로그램은 시스템 호출을 통해서 커널에 서비스를 요청한다

## 시스템 호출 과정
(여기에 시스템 호출 과정에 대한 세부 내용을 추가할 수 있습니다)

## 시스템 호출 요약

| 주요 자원 | 시스템 호출 |
|---------|------------|
| 파일 | open(), close(), read(), write(), dup(), lseek() 등 |
| 프로세스 | fork(), exec(), exit(), wait(), getpid(), getppid() 등 |
| 메모리* | malloc(), calloc(), free() 등 |
| 시그널 | signal(), alarm(), kill(), sleep() 등 |
| 프로세스 간 통신 | pipe(), socket() 등 |

## 유닉스에서 파일
- 연속된 바이트의 나열
- 특별한 다른 포맷을 정하지 않음
- 디스크 파일뿐만 아니라 외부 장치에 대한 인터페이스

## 파일 열기: open()
- 파일을 사용하기 위해서는 먼저 open() 시스템 호출을 이용하여 파일을 열어야 한다.
- 파일 디스크립터는 열린 파일을 나타내는 번호이다.
- oflag
  - `O_RDONLY`: 읽기 모드, read() 호출은 사용 가능
  - `O_WRONLY`: 쓰기 모드, write() 호출은 사용 가능
  - `O_RDWR`: 읽기/쓰기 모드, read(), write() 호출 사용 가능
  - `O_APPEND`: 데이터를 쓰면 파일끝에 첨부된다.
  - `O_CREAT`: 해당 파일이 없는 경우에 생성하며 mode는 생성할 파일의 사용권한을 나타낸다.
  - `O_TRUNC`: 파일이 이미 있는 경우 내용을 지운다.
  - `O_EXCL`: O_CREAT와 함께 사용되며 해당 파일이 이미 있으면 오류
  - `O_NONBLOCK`: 넌블로킹 모드로 입출력 하도록 한다.
  - `O_SYNC`: write() 시스템 호출을 하면 디스크에 물리적으로 쓴 후 반환된다

## 파일 생성: creat()
- creat() 시스템 호출
  - path가 나타내는 파일을 생성하고 쓰기 전용으로 연다.
  - 생성된 파일의 사용권한은 mode로 정한다.
  - 기존 파일이 있는 경우에는 그 내용을 삭제하고 연다.
  - 다음 시스템 호출과 동일: `open(path, WRONLY | O_CREAT | O_TRUNC, mode);`
- close() 시스템 호출은 fd가 나타내는 파일을 닫는다.

## 데이터 읽기: read()
- read() 시스템 호출
  - fd가 나타내는 파일에서
  - nbytes 만큼의 데이터를 읽고
  - 읽은 데이터는 buf에 저장한다.
