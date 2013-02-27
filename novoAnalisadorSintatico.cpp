#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

int main() {
	cout << "q saco eli" << endl;
}

enum {
	VAZIO = 0, // estado inicial
	LETRA, //letra :3
	IDENTIFICADOR, //qualquer combinacao de uma palavra iniciando por letra e numero
	BOOLEANO, //"verdadeiro "true" "falso" "false"
	IF,
	ELSE,
	IN,
	OUT,
	TRUE, //0
	FALSE, //1
	OR, // v
	AND, // ^
	NOT, // '
	OPERADOR, //<
	OPERADORSE, //->
	OPERADORSSS, //<->
	SEPARADOR, // \n \t \0 " "(espaco)
	ATRIBUICAO, // :
	LPARENTS, // (
	RPARENTS, // )
	LCHAVES, // {
	RCHAVES, // }
	PONTOVIRGULA, // ;
	VIRGULA, // ,
	OUTRO, // ?
	ERRO // ??
};

bool FaseInicio() {
	bool retorno = false;
	int token = letoken()
	switch(token) {
		case IDENTIFICADOR:
			retorno = FaseIdentificador();
			break;
		case IF:
			retorno = FaseIf();
			break;
		case OUT:
		case IN:
	}
	
	
	
	return retorno;
}

bool FaseIdentificador() {
	bool retorno = false;
	int token = leToken();
	if (token == ATRIBUICAO)
		retorno = ExpressaoFuncao();
	else
		retorno = false;
	return retorno;
}

bool FaseIf() {
	bool retorno = false;
	int token = leToken();
	if (token == LPARENTS) {
		retorno = ExpressaoFuncao();
		if(token = leToken() == RPARENTS);
			if(token = leToken() == LCHAVES)
				retorno  = comando
				if letoken == RCHAVES
					
					if(le token == ELSE)
						retorno = condiElse()
					else 
						token-1
	
	}
}

bool ExpressaoFuncao() {
	
	
}
