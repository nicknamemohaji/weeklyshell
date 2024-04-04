# 로더 모듈 설계

## 요구사항

> 과제에 정의된 내용

- `$PATH`, 절대경로, 상대경로에서 찾아서 프로그램 로딩
    - 명령어에 `/` 포함
        - `/`로 시작: 절대경로
        - 그렇지 않으면: 상대경로
    - 그렇지 않으면
        - 빌트인 확인
        - 빌트인 목록에 없으면: `$PATH` + 상대경로
- 명령어 파이프라인 구현 (`|`)
    - 이전 프로세스의 실행이 끝나면 write pipe를 닫아 deadlock이 발생하지 않도록 잘 처리
    - 파이프환경은 서브쉘이므로 서브쉘을 fork하기 전에 메인쉘에서 파이프를 만들어 넘겨줘야 함
- 리다이렉션 구현
    - 파일입력
        - 일반 파일 (`<`)
        - Heredoc 입력 (`<<`)
            - heredoc을 전처리 서브모듈에서 발견하기 전까지 처리 지연
            - 구분자가 중요
                - quote removal을 거친 delimeter를 실제 구분자로 사용
                - 원본 delimeter에 quote가 있었으면 heredoc 본문에는 expansion을 적용하지 않음
                - 이외에는 본문에 expansion 적용
            - 전처리 모듈에서 구분자가 입력될 때 까지 입력받은 후 임시파일을 만들어 그곳에 저장
            - 실행할 프로세스에서 파일을 표준입력으로 리다이렉션
            - 프로세스 실행이 끝나면 임시파일 삭제
    - 파일출력
        - `O_TRUNC` (`>`)
        - `O_APPEND` (`>>`)
- Expansion 처리
    - 특수문자 `'`
        - 작은따옴표 사이에 있는 내용을 있는 그대로 반환
    - 특수문자 `"`
        - 큰따옴표 안에 있는 `$`을 처리
        - 나머지는 그대로 반환
        - expansion된 결과와 합쳐 하나의 긴 문자열로
    - 특수문자 `$`
        - 쉘의 환경변수와 일치하는 이름이 있으면 그것으로 expansion됨
        - 일치하지 않는다면 null character `""`로 처리
        - 추가로, `$?` 처리
        - (중요!) 로딩시 서브쉘을 여는 조건
            - 서브쉘에서 변경된 환경변수는 다른 쉘에 영향을 미치지 않음
                - 반대로 말하면 서브쉘이 아닌 상황에서는 환경변수 변경(`unset`, `export`)이 영향을 미쳐야 함
                - 환경변수 처리 때문에 실행환경이 서브쉘인지 아닌지가 중요
            - 괄호로 묶인 명령어
                - ex. `declare var=42; (declare var=-42 && echo $var); echo $var`
            - 파이프로 묶인 명령어
                - ex. `declare var=42; declare var=-42 | echo $var; echo $var`
                - 파이프에서는 [*프로세스 각각이*](https://stackoverflow.com/questions/5760640/left-side-of-pipe-is-the-subshell) 서브쉘로 동작!!!!
            - 이외에는 서브쉘 환경이 아님
                - ex. `declare var=42; declare var=-42 && echo $var; echo $var`
    - 특수문자 `*`
        - 현재 실행경로(CWD)의 파일과 매칭하는 와일드카드
        - 인자일때만 확장됨. heredoc에서는 처리되지 않음

> 추가로 정의한 내용

- 환경변수 설정
    - 허용함수에 `setenv` 없음
        - `execve`의 인자로서 환경변수를 전달하는 방식이 유일
    - 쉘 실행시 필수적인 환경변수를 `getenv`로 받아옴
        - `PATH`
        - 말고 더 필요한가...
    - 이후에는 자료구조로 저장
- AST 구조
    - 재귀하향식 파서
    - 이진트리 형태
        - 전위순위(N->L->R)로 탐색하면 실행순서에 맞는 노드를 탐색 가능
    - AST 구조체 (예시)
        - type
            - 중요 심볼 
                - `|`
                - `<`, `>`, `<<`, `>>`
                - `&&`, `||`
                - 괄호로 묶인 우선순위 지정(ex. `cmd1 && (cmd2 | cmd3)`)은 파서에서 해석되어 나옴
            - 명령어
        - field
        - child (left, right)
- 두 개의 서브모듈로 구성
    1. 전처리 모듈
        - 파싱트리 순회
            - 필요한 자료 준비
                - redirection, pipe: 파일 열기
            - 서브쉘 환경이라면 fork
        - argument expansion 진행
            - quote removal(arg, heredoc deliemeter)
            - shell parameter expansion(arg, heredoc content)
            - wildcard expansion(arg)
        - heredoc 입력
    2. 실행 모듈
        - 알맞은 처리를 한 후 프로세스 로드
            - FD들과 관련해 알맞은 처리
                - builtin redirecton 주의 (원본 stdout/stdin fd를 놓치면 안됨)
            - 빌트인이라면 execve 없이 빌트인 함수 직접 실행
            - execv*e* - 환경변수 구조체를 `char **`로 전환한 후 전달
        - 프로세스 종료 이후 정리
            - FD 관련
                - 파이프 정리(데드록 방지를 위한 close)
                - 미사용 FD 정리(close)
            - exit code 관련
                - `$?` 처리를 위해 내부 자료구조에 저장
                - and/or 처리를 위해 실행 모듈을 호출한 전처리기 모듈에 exit code 전달
    3. 환경변수 관련 구조체
        - `t_ld_map_env`
            - 딕셔너리 구조
            - `int count`: 들고있는 관계 개수
            - `t_ld_map_node *node`: 연결리스트의 포인터
                - `char *key`
                - `char *value`
            - 관련 함수
                - `char *ldpre_env_fetch(char *key, t_ld_map_env *env)`
                - `int ldpre_env_add(char *key, char *value, t_ld_map_env *env)`
                - `int ldpre_env_remove(char *key, t_ld_map_env *env)`
                - `char *ldpre_env_tostr(t_ld_map_env *env)`
    4. 실행환경 관련 구조체
        - `t_ld_array_pipe`, `t_ld_array_fd`
            - `int stdin` default -1; else fd
            - `int stdout` default -1; else fd
        - `t_ld_status_execenv`
            - `t_ld_array_pipe pipes`
            - `t_ld_array_fd fds`
            - `t_ld_map_env *env`


---

## convention

- 파일, 함수 이름
    1. 접두사 `ldpre`, `ldexec`
    2. 핵심기능 (ast, fd, pipe, ...)
    3. 세부기능 (traversal, prepare, clean, ...; 없어도 됨)순서
    - ex. `ldpre_ast_traversal.c`, `ldexec_pipe_clean.c`
- 자료형 이름
    - 열거형, 구조체 등 사용시 반드시 typedef 사용
        - 정수형에서 define 매크로 사용은 지양
    - norm 준수, 모듈을 밝힘
        - 접두사 `t_ld_`
    - 쓰임을 밝혀야 함
        - 이때 맥락 우선 (array, status, ... > environ, pipe, fd, ...)
        - ex. `t_ld_array_pipe`
- 변수의 범위
    - 모듈간에 넘어가는 변수는 별도의 이름 규칙 사용
    - 동적할당 사용시 가급적 `malloc` 대신 `ft_vector` 함수 사용
    - 사용하는 라이브러리 함수가 할당하는 함수라면 가급적 호출한 함수 안에서 `free`

---

## 의사코드

> 래퍼 의사코드

```
def loader(tree, env):
    exec_env -> initialize_exec_env(env)
    preprocess(tree, exec_env)
    cleanup(exec_env)
```

```
def cleanup(env):
    if (env.pipe != -1):
        close(env.pipe)
    if (env.fd != -1):
        close(env.fd)
```

> 전처리 서브모듈 의사코드

```
def preprocess(tree, env):
    // 조건부 실행
    if tree.type == OR:
        exit_status = loader(tree.left, env)
        if (exit_status == SUCCESS)
            return exit_status
        else
            return loader(tree.right, env)
    
    if tree.type == AND:
        exit_status = loader(tree.left, env)
        if (exit_status != SUCCESS)
            return exit_status
        else
            return loader(tree.right, env)
    
    // 입출력 리다이렉션
    if tree.type == PIPE:
        env.pipe = prepare_pipe()
        exit_status = loader(tree.left)
        close(env.pipe.stdout)
        if (exit_status != SUCCESS)
            return exit_status
        else
            return loader(tree.right)
    
    if tree.type == REDI:
        if tree.left == FILE:
            env.stdin = open(tree.left)
            return loader(tree.right)
        else
            env.stdout = open(tree.right)
            return loader(tree.left)
        
    
    // 실행
    if tree.type == EXEC:
        // expand
        for arg in tree.arg:
            if arg == ">>":
                heredoc(env)
            else if arg.contains('\''):
                squote_removal(arg)
            else if arg.contains('\"'):
                dquote_removal(arg, env)
            else if arg.contains('$'):
                expand_shellarg(arg, env)
            else if arg[0] == '*':
                expand_wildcard(arg, env)
        // 실행 서브모듈 호출
        return exec(tree, env)
```

> 실행 서브모듈 의사코드

```
def exec(tree, env):
    if env.pipe.stdin != -1:
        dup2(env.pipe.stdin, stdin)
    if env.pipe.stdout != -1:
        dup2(env.pipe.stdout, stdout)
    
    if env.pipe.stdin != -1:
        dup2(env.pipe.stdin, stdin)
    if env.pipe.stdout != -1:
        dup2(env.pipe.stdout, stdout)
    
    cmd_path = find_cmd(tree.cmd, ldpre_env_fetch("PATH", env.env))
    if cmd_path == NULL:
        print_error()
        return -1

    fork()
    execve(cmd_path, cmd.args, ldpre_env_tostr(env.env))
    exit_status = waitpid()
    free(...)
    return exit_status
```
