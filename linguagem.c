^ TOKEN <AND,>
' TOKEN <NOT,>
( TOKEN <LPARENTS,>
) TOKEN <RPARENTS,>
{ TOKEN <LCHAVES,>
} TOKEN <RCHAVES,>
; TOKEN <PONTOVIRGULA,>

v TOKEN <OR,> //Especial pois pode ser VARIAVEL, TRUE, ou OR
	
:= TOKEN <IGUAL,> // Se vir dpeois dos := é toquem

in TOKEN <IN, > 
if TOKEN <IF,>

-> TOKEN <SE,>

<-> TOKEN <SESOMENTESE, >

out TOKEN <OUT, >

else TOKEN <ELSE,>

1 "v" "verdadeiro" "true" TOKEN <TRUE, >
0 "f" "falso" "false" TOKEN <FALSE, >

varivaeis TOKEN <ID, VARIAVEL>
