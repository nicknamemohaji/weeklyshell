# 입력 모듈 설계

## 요구사항

> 과제에 정의된 내용

- 각 커맨드마다 프롬프트 출력하기
- 실행한 커맨드들에 대한 히스토리 가지기
    - Heredoc에 대해서는 히스토리가 업데이트되지 않아도 됨
- `'`, `"` 처리 
    - 짝이 맞는지 확인
    - 짝이 맞지 않는다면 syntax error 처리
- 프롬포트 모드에서 다음 키조합 처리
    - `Ctrl+C`: 현재 입력 취소, 새로운 프롬포트
    - `Ctrl+D`
        1. 현재 입력이 있으면 아무런 동작도 하지 않음
        2. 현재 입력이 없으면 쉘 종료
    - `Ctrl+\` 처리하기: 아무런 동작도 하지 않음
    - 단, 여기서 등록한 시그널 핸들러는 로더를 호출할 때 기본값으로 복구되어야 함

> 추가로 정의한 내용

- 파서에는 단일라인을 넘김
    - `char *` 형식
- 입력오류의 처리
    - 따옴표들의 짝이 맞지 않는 문장은 입력 모듈에서 처리(`'''` 미허용, `'"'` 허용)
    - 파이프 뒤에 커맨드가 오지 않는 등의 문법 오류는 파서에서 처리
    - 파이프가 생성할 파일의 퍼미션이 없는 등의 오류는 로더/전처리 모듈에서 처리
- 시그널/터미널 세팅
    - 프롬포트 출력 직전에 시그널/터미널을 세팅
    - 입력을 받은 직후 기존 세팅을 복구
    - 이 과정을 매 실행마다 반복

## convention

- 파일, 함수 이름
    1. 접두사 `input_`
    2. 핵심기능 (handler, readline, ...)
    3. 세부기능 (initialize, apply, ...; 없어도 됨)순서
    - ex. `input_handler_apply.c`, `input_handler_restore.c`
    - 함수는 필요에 따라 약어를 사용
        - ex. `in_rl_init()`
- 자료형 이름
    - 열거형, 구조체 등 사용시 반드시 typedef 사용
        - define 매크로 사용은 지양
    - norm 준수, 모듈을 밝힘
        - 접두사 `t_in_`
        - 초기 실행시 환경변수 로딩 관련: `t_ld_`
    - 쓰임을 밝혀햐 함
        - 이때 맥락 우선 (status, fetch, ... > quote, environ, ...)
        - ex. `t_in_status_quote`
- 변수의 범위
    - 모듈간에 넘어가는 변수는 별도의 이름 규칙 사용
    - 동적할당 사용시 가급적 `malloc` 대신 `ft_vector` 함수 사용
    - 사용하는 라이브러리 함수가 할당하는 함수라면 가급적 호출한 함수 안에서 `free`

---

## 의사코드

> 전체 의사코드

```
loader_env -> 필수_환경변수_로딩()
prompt -> "weeklyshell >"
무한 반복:
    시그널_설정()
    터미널_설정()
    input -> readline(prompt)
    시그널_복구()
    터미널_복구()

    if SIGINT:
        rl_replace_line(...)
        continue
    
    add_history(input)
    if 입력_검증(input) == FALSE:
        오류_프롬포트_출력(...)
        continue
    
    parser_ast -> 파서모듈(input);
    로더모듈(parser_ast, loader_env)
    free(input)
    vec_free(parser_ast)

vec_free(loader_env)
exit(0)
```

> 입력 검증 모듈 의사코드

```
def 입력_검증(char *input):
    status -> 상태변수_초기화(&status)
    for c in input:
        if c == '\'':
            if status.dquote == FALSE:
                status.squote = !status.squote
        else if c == '"':
            if status.squote == FALSE:
                status.dquote = !status.dquote
    return status.dquote || status.squote

```
