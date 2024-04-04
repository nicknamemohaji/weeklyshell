
# 파서 모듈
쉘은 일종의 인터프리터, 입력받은 구문을 해석하여 평가한다.
여기서는 구문 해석을 수행하는 전반을 기술함.

## 실행 흐름

데이터 입력(단순 문자열) -> 렉서(토큰) -> 파서(구문트리) -> 이밸류에이터(실행)
파서 모듈은 렉서 + 파서를 뜻함.

## Lexer

>입력 : raw single string

>출력 : vector of token

입력받은 raw text를 분석하여 의미단위(token)로 분할하는 과정.
분할 결과는 token stream, 즉 token의 벡터임.

## Parser

>입력 : vector of token

>출력 : AST (트리 구조체)

lexer를 거친 token들을 분석하여 구문 트리(Abstract Syntax Tree, 이하 AST)를 생성하는 과정.

이후 생성된 ast를 순회하면서 문법 요소를 바탕으로 실행함.


