# 구현해야 할 빌트인 함수들

## echo with option -n

> `echo [-n] (string)`

- 쉘의 ***argparser를 거쳐*** 인자들을 처리하면 간단
- 어차피 # 등의 문자는 제거되어 인자로 받을 것이니...
- 표준출력에 arg들을 *공백으로 구분해* 출력 
- 유일한 실행인자인 `-n`만 확인
    - `-n`: 개행 없이 출력
    - `-n`이 없으면 개행을 추가로 출력
- Escape Sequence 처리여부?? (환경에 따라 기본 처리여부가 다름)

## cd with only a relative or absolute path

> `cd [-L|[-P [-e]] [-@] [directory]`

`int chdir(const char *path)` 사용
- 인자가 없으면 홈 디렉토리로 이동
- 상대경로 입력시:
    - 현재경로 + `$CDPATH`에서 탐색
    - 절대경로면 그냥 처리
    - 경로가 `-`이면 `$OLDPWD`로 이동
- 경로는 순서대로 처리
    - `a/b/../c/d`이면, `a/b/`까지 *들어간 후에* `..` 처리
    - 즉, `a/../b`에서 a는 없고 b는 있다면 `a`에 먼저 들어가므로 ENOENT
- `$CDPATH` 사용 or `-`->`$OLDPWD`일 때는 표준출력으로 이동할 경로 출력
- `$PWD`, `$OLDPWD` 환경변수
    - 첫 시작시, `$OLDPWD`는 홈 디렉토리 (사용자의 init point?)
    - `$PWD`는 실행위치 (로더의 실행위치?)

## pwd with no options

> `pwd [-LP]`

`$PWD` 환경변수 출력

## export with no options

> `export [-fn] [-p] [name[=value]]`

환경변수 업데이트
- 인자로 아무것도 없으면 모든 환경변수를 재사용 가능한 형태로(__repr__ 형태!) 출력

## unset with no options

> `unset [-fnv] [name]`

환경변수 삭제
- 읽기전용 환경변수는 삭제하지 말 것

## env with no options or arguments

> `env [OPTION] [-] [NAME=VALUE] [COMMAND [ARG]]`

(인자가 없으면) 환경변수를 모두 출력

## exit with no options

> `exit [n]`

`void exit(int status)` 사용
- n이 지정되면 이 값을 사용
- 지정되지 않으면 마지막 커맨드의 exitcode 사용 (아무런 커맨드도 없었으면 그냥 0인듯?)
