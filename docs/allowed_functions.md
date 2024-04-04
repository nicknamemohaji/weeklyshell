# readline 라이브러리

> `<readline/readline.h>`, `<readline/history.h>`

## readline 관련

- `char *readline(const char *prompt)`
    - param `prompt`: 사용자에게 출력하는 내용
    - return: 개행이 있었을 때, 사용자가 입력한 버퍼(`rl_line_buffer`)를 리턴함
    - 라이브러리 사용의 시작
        - interactive terminal의 기본이 되는 readline 함수
- `int rl_on_new_line(void)`
    - 라이브러리에 프로그램이 출력했음을 알림
        - 프롬포트 / 사용자 입력과 관련없는 출력
        - 내부적으로 마커를 수정하는 듯
    - 시그널 핸들러에서 사용
        - SIGINT 발생시 이전 입력을 놔두고 다음 프롬프트를 출력할 때 사용
- `void rl_replace_line (const char *text, int clear_undo)`
    - param `text`: 버퍼의 내용을 `text`로 바꿈
    - param `clear_undo`: undo 히스토리를 수정할 지 결정하는 플래그(minishell에서는 사용하지 않음)
    - 시그널 핸들러에서 사용
        - SIGINT 발생시 사용자가 입력했던 내용을 지우는 용도로 사용
        - (setjmp/longjmp 사용이 불가능하므로 핸들러에서 버퍼를 비워야 함)
- `void rl_redisplay(void)`
    - 버퍼의 내용을 바꾼 이후 상황을 적용
    - 시그널 핸들러에서 사용
        - `rl_replace_line`을 통해 버퍼를 바꾼 이후 바뀐 프롬포트 적용

## history 관련

- `void add_history(const char *string)`
    - interactive terminal에서 사용하는 히스토리
    - `add_history`를 통해 등록하면 위아래 커서를 통해 이전에 입력한 값들을 재사용 가능
- `void rl_clear_history(void)`
    - readline 라이브러리가 가지고 있는 히스토리 자료들을 해제함
    - 릭을 줄이기 위해 사용... 효과가 있는지는 모르겠음 😶 (사실 readline에서 발생하는 릭은 신경 안써도 되기는 🤐)

---

# 입출력

## formatted I/O

> `<stdio.h>`

- `int printf(const char *format, ...)`

## errno 관련

> `<stdio.h>`, `<string.h>`, `<errno.h>`

- `char *strerror(int errnum)`
    - 전역변수로 제공되는 `errno`를 `errnum`에 넣으면, 해당하는 에러 메시지 반환
    - (주의) errno는 에러가 *발생했을 때 에만* 갱신됨
        - 정상 실행되었다고 errno가 0으로 세팅되지 않음
        - 가장 마지막으로 저장된 에러 상태 유지
- `void perror(const char *s)`
    - `s`에 이어 에러 메시지를 표준에러에 출력
    - 즉, `write(STDERR, fprintf("%s: %s\n", s, strerror(errno)))`와 같음

## FILE I/O

> `<unistd.h>`

- `ssize_t read(int fd, void *buf, size_t count)`
- `ssize_t write(int fd, const void *buf, size_t count)`

---

# 파일

## OPEN 관련

> `<unistd.h>`, `<fcntl.h>`, `<sys/types.h>`

- `int open(const char *pathname, int flags, mode_t mode)`
    - 플래그: 비트마스크
    - 모드: 비트마스크
- `int close(int fd)`

## stat 관련

> `<unistd.h>`, `<sys/types.h>`, `<sys/stat.h>`

- `int access(const char *pathname, int mode)`
    - 주어진 파일을 읽거나 쓸 수 있는지 권한을 확인
    - RUID 기준이므로, SUID/SGID 비트와 상관없이 체크 가능
    - 모드는 비트마스크로 작동
        - `F_OK`: 파일의 존재 여부 확인
        - `W_OK`, `R_OK`, `X_OK`: 존재 + 권한 확인

- ~~`int stat (const char *pathname, struct stat *statbuf)`~~
- ~~`int fstat (int fd, struct stat *statbuf)`~~
- ~~`int lstat (const char *pathname, struct stat *statbuf)`~~

## CWD 관련

> `<unistd.h>`

- `int chdir(const char *path)`
- `char *getcwd(char *buf, size_t size)`

## FD 관련

> `<unistd.h>`

- ~~`int dup(int oldfd)`~~
- `int dup2(int oldfd, int newfd)`
- `int pipe(int pipefd[2])`

## 디렉토리 관련

> `<sys/types.h>`, `<dirent.h>`

- `DIR *opendir(const char *name)`
- `struct dirent *readdir(DIR *dirp)`
- `int closedir(DIR *dirp)`

## 기타

> `<unistd.h>`

- `int unlink(const char *pathname)`

---


# 프로세스

> `<sys/types.h>`, `<unistd.h>`, `<sys/wait.h>`

> (wait3, wait4) `<sys/resource.h>`, `<sys/time.h>`

- `pid_t fork(void)`
- `pid_t wait(int *wstatus)`
- ~~`pid_t waitpid(pid_t pid, int *wstatus, int options)`~~
- ~~`pid_t wait3(int *wstatus, int options, struct rusage *rusage)`~~
- ~~`pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)`~~
- `int execve(const char *pathname, char *const argv[], char *const envp[])`

---

# 시그널

> `<signal.h>`

- ~~signal~~
- sigaction
- sigemptyset
- sigaddset
- ~~kill~~

---

# TTY

- ~~isatty~~
- ~~ttyname~~
- ~~ttyslot~~

## ioctl

> `<sys/ioctl.h>`

- ~~`int ioctl(int fd, unsigned long request, ...)`~~

## termios

> `<termios.h>`

- tcsetattr
- tcgetattr
- ~~tgetent~~
- ~~tgetflag~~
- ~~tgetnum~~
- ~~tgetstr~~
- ~~tgoto~~
- ~~tputs~~

---

# 기타

- exit
- ~~getenv~~

## 동적할당

> `<stdlib.h>`

- `void *malloc(size_t size)`
- `void free(void *ptr)`
