( TOKEN <LPARENTS,> == 1
) TOKEN <RPARENTS,> == 2
{ TOKEN <LCHAVES,>  == 3
} TOKEN <RCHAVES,>  == 4
; TOKEN <PONTOVIRGULA,> == 5
, TOKEN <VIRGULA,>  == 6

case 22; 
^ TOKEN <AND,> == 7
' TOKEN <NOT,> == 8
:= TOKEN <IGUAL,> == 9// Se vir dpeois dos := é token
-> TOKEN <SE,> == 10
<-> TOKEN <SESOMENTESE, > == 11

v TOKEN <OR,>==12 //Especial pois pode ser VARIAVEL, TRUE, ou OR

//0 1  == 13
"v" "verdadeiro" "true" TOKEN <TRUE, > == 14
 "f" "falso" "false" TOKEN <FALSE, > == 15
" == 21

espaço tabulacao = 22;

else TOKEN <ELSE,> == 16
if TOKEN <IF,> == 17

out TOKEN <OUT, > == 18
in TOKEN <IN, >  == 19

varivaeis TOKEN <ID, VARIAVEL> == 20

invalidos == 0
