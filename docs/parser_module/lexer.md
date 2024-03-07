
# lexer

렉서 혹은 토크나이저, 입력받은 문자열을 분해하여 대상의 의미에 따라서 분해함.
분해 방식은 우선순위에 따라서 분해함.

가능한 토큰의 종류(우선순위로), 일단은 공백으로 구분되어야 하며, 예외적으로 '(', ')'만 별도로 공백 없이 처리해야 함.

> ( , ) , | , << , <, >>> , > , $ , *, &&, ||,word(single string, alpha numeric)

분해한 내용은 token이라 함.
token은 구조체로 구현될 예정이며, 구현된 token은 type(int)과 field(string)으로 구성됨.

	typedef struct s_token
	{
		int token_type;		-> 열거형
		ft_string field;
	}	t_token;

렉싱의 결과는 token을 원소로 갖는 vector, token stream이 될 것임.

## 구현 방향

투 포인터를 활용하여 문자열을 순회할 예정임.
