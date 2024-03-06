

# 실행 흐름

데이터 입력(단순 문자열) -> 렉서(토큰) -> 파서(구문트리) -> 이밸류에이터(실행)

## Lexer
입력받은 raw text를 분석하여 의미단위로 분할하는 과정

공백 기준으로 문자열 분리함. 분리할 때 '"'와 '''는 예외로 처리해야 함 -> 이들로 감싸진 데이터는 하나의 토큰으로 처리.

## Parser
lexer를 거친 token들을 분석하여 구문 트리(Abstract Syntax Tree, 이하 AST)를 생성하는 과정.

이후 생성된 ast를 순회하면서 문법 요소를 바탕으로 실행함.

>>  ### BNF for MINISHELL
>
> \<ALPHA> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
>				A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
>
>	\<DIGIT> ::= 0|1|2|3|4|5|6|7|8|9
>
>	\<NUMBER> ::= \<DIGIT>
>			| \<NUMBER> \<DIGIT>
>
>	\<ALPHA-LIST> ::= \<ALPHA>
>			| \<ALPHA-LIST> \<ALPHA>
>
>	\<WORD> ::= \<ALPHA-LIST>
>			| \<WORD> '_'
>			| '$' \<ALPHA-LIST>
>			| '*'
>
>	\<WORD-LIST> ::= \<WORD>
>				|  \<WORD-LIST> \<WORD>
>
>	\<REDIRECTION> ::=  '>' \<WORD>
>					|  '\<' \<WORD>
>					|  '>>' \<WORD>
>					|  '\<\<' \<WORD>
>
>	\<SIMPLE-COMMAND-ELEMENT> ::= \<WORD>
>							|  \<REDIRECTION>
>
>	\<REDIRECTION-LIST> ::= \<REDIRECTION>
>						|  \<REDIRECTION-LIST> \<REDIRECTION>
>
>	\<SIMPLE-COMMAND> ::=  \<SIMPLE-COMMAND-ELEMENT>
>					|  \<SIMPLE-COMMAND> \<SIMPLE-COMMAND-ELEMENT>
>
>	\<COMMAND> ::=  \<SIMPLE-COMMAND>
>				|  \<SHELL-COMMAND>
>				|  \<SHELL-COMMAND> \<REDIRECTION-LIST>
>
>	\<SHELL-COMMAND> ::=  \<SUBSHELL>
>					|  \<GROUP-COMMAND>
>
>	\<PATTERN-LIST> ::=  \<NEWLINE-LIST> \<PATTERN> ')' \<COMPOUND-LIST>
>					|  \<NEWLINE-LIST> \<PATTERN> ')' \<NEWLINE-LIST>
>					|  \<NEWLINE-LIST> '(' \<PATTERN> ')' \<COMPOUND-LIST>
>					|  \<NEWLINE-LIST> '(' \<PATTERN> ')' \<NEWLINE-LIST>
>
>	\<PATTERN> ::=  \<WORD>
>				|  \<PATTERN> '|' \<WORD>
>
>	\<LIST> ::=   \<NEWLINE-LIST> \<LIST0>
>
>	\<COMPOUND-LIST> ::=  \<LIST>
>					|  \<NEWLINE-LIST> \<LIST1>
>
>	\<LIST0> ::=   \<LIST1> '\n'
>
>	\<LIST1> ::=   \<LIST1> '&&' \<LIST1>
>			|  \<LIST1> '||' \<LIST1>
>			|  \<LIST1> '\n' \<LIST1>
>			|  \<PIPELINE-COMMAND>
>
>	\<LIST-TERMINATOR> ::= '\n'
>
>	\<NEWLINE-LIST> ::=
>					|  \<NEWLINE-LIST> '\n'
>
>	\<SIMPLE-LIST> ::=  \<SIMPLE-LIST1>
>
>	\<SIMPLE-LIST1> ::=  \<SIMPLE-LIST1> '&&' \<SIMPLE-LIST1>
>					|  \<SIMPLE-LIST1> '||' \<SIMPLE-LIST1>
>					|  \<PIPELINE-COMMAND>
>
>	\<PIPELINE-COMMAND> ::= \<PIPELINE>
>
>	\<PIPELINE> ::=
>			\<PIPELINE> '|' \<PIPELINE>
>		|  \<COMMAND>



