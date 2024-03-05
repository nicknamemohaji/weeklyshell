# readline 라이브러리

> `<readline/readline.h>`, `<readline/history.h>`

## readline 관련

- `char *readline(const char *prompt)`
- `int rl_on_new_line(void)`
- `void rl_redisplay(void)`
- `void rl_replace_line (const char *text, int clear_undo)`

## history 관련

- `void add_history(const char *string)`
- `void rl_clear_history(void)`

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

```c
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */
};
```

- `int stat (const char *pathname, struct stat *statbuf)`
- `int fstat (int fd, struct stat *statbuf)`
- `int lstat (const char *pathname, struct stat *statbuf)`

## CWD 관련

> `<unistd.h>`

- `int chdir(const char *path)`
- `char *getcwd(char *buf, size_t size)`

## FD 관련

> `<unistd.h>`

- `int dup(int oldfd)`
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
- `pid_t waitpid(pid_t pid, int *wstatus, int options)`
- `pid_t wait3(int *wstatus, int options, struct rusage *rusage)`
- `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)`
- `int execve(const char *pathname, char *const argv[], char *const envp[])`

---

# 시그널

signal, sigaction, sigemptyset, sigaddset, kill

---

# TTY

isatty, ttyname, ttyslot

## ioctl

> `<sys/ioctl.h>`

- `int ioctl(int fd, unsigned long request, ...)`

---

# 기타

exit, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## 동적할당

> `<stdlib.h>`

- `void *malloc(size_t size)`
- `void free(void *ptr)`
