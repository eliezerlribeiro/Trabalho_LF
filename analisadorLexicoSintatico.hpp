#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

enum {
	VAZIO = 0,
	IDENTIFICADOR,
	LETRA,
	NUMERO,
	BOOLEANO,
	TRUE,
	FALSE,
	RESERVADO,
	IF,
	ELSE,
	IN,
	OUT,
	OPERADOR,
	OR,
	AND,
	NOT,
	OPERADORSE,
	OPERADORSSS,
	SEPARADOR,
	ATRIBUICAO,
	LPARENTS,
	RPARENTS,
	LCHAVES,
	RCHAVES,
	PONTOVIRGULA,
	VIRGULA,
	OUTRO,
	ERRO
};

class Token {
	public:
		static std::vector<Token*> listaTokens;
		static std::vector<Token*> pilhaLexico;
		static std::vector<int> pilhaSintatico;
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
		void setPosicao(int, int);

		static bool ehLetra(char);
		static bool ehNumero(char);
		static bool ehBooleano(char);
		static bool ehOperador(char);
		static bool ehSeparador(char);
		static bool ehBloco(char);
		
		static int SintaticoPontoVirgula();
		static int SintaticoRParents();

		static int ehOperador(int token);
		static int ehReservado(int token);

		static bool ehReservado(string);
		static int PalavraReservada(string palavra);
		static void Lexico(FILE *, int);
		static void Lexico(string);

		static bool Sintatico(int entrada);
		static bool AnalisaSintatico();


		static void Imprime();
		static string ImprimeToken(int token, string id);
};

//typedef class ListaTokens std::vector<Token*>
