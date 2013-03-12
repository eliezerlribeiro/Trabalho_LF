#ifndef _ANALISADOR_H_
	#define _ANALISADOR_H_
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
	ERRO,
	INICIO
};

class Token {
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
	static string ImprimeToken(int token, string id);
};

class Lexico {
private:
	std::vector<Token*> listaTokens;

public:
	Lexico(FILE *, int);
	Lexico(string);
	
	std::vector<Token *> AnalisaLexico();
private:
	bool ehLetra(char);
	bool ehNumero(char);
	bool ehBooleano(char);
	bool ehOperador(char);
	bool ehSeparador(char);
	bool ehBloco(char);
	bool ehReservado(string);
	int PalavraReservada(string palavra);

public:
	void Imprime();
	
};
class Sintatico {
private:
	std::vector<Token*> listaTokens;
	std::vector<int> pilhaSintatico;
public:	
	Sintatico();
	Sintatico(std::vector<Token*> listaTokens);
	
public:	
	bool AnalisaSintatico();
	bool OperaSintatico(int entrada);

private:
	int SintaticoPontoVirgula();
	int SintaticoRParents();
	int ehOperador(int);
	int ehReservado(int);
	int ehBooleano(int);
	
};

#endif
