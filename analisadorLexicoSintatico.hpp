#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

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

class Token {
	public:
		static std::vector<Token*> ListaTokens;
	private:
		string id;
		int estado;
		int posicao;
	public:
		Token();
		string getId();
		int getPosicao();
		int getEstado();
		void setId(string);
		void setEstado(int);
		void setPosicao(int);

		static bool ehLetra(char);
		static bool ehNumero(char);
		static bool ehBooleano(char);
		static bool ehOperador(char);
		static bool ehSeparador(char);
		static bool ehBloco(char);

		static bool ehReservado(string);
		static int PalavraReservada(string palavra);
		static std::vector<Token> * Lexico(FILE *, int);
		static std::vector<Token> * Lexico(string);
};

//typedef class ListaTokens std::vector<Token*>
