#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>

bool ehLetra(char);
bool ehNumero(char);
bool ehOperador(char);
bool ehSeparador(char);
bool ehOutro(char);
bool ehEspaco(char);
bool ehAtribuidor(char);
bool ehAspas(char);

bool ehReservado(string);
bool ehIdentificador(string);
//bool ehExpressao(string);

char * xxx(char * );


enum {
	LETRA = 0,
	NUMERO,
	BOOLEANO,
	OPERADOR, //eh logico
	SEPARADOR,
	ESPACO,
	ATRIBUIDOR,
	ASPAS,
	OUTRO
};

int main() {
	
	int tokenAntigo;
	char c;
	string s;
	
	SINTATICO(PALAVRA OU LINHA) {
		IN
		
		
		token lexico(
	}
	int contador = 0;
	if (ehAlfabeto(c) {
		contador++;
		s += c;
	}
	else{

	while(c = leCaracter) {
		switch(c) {
			case LETRA:
				switch(tokenAntigo) {
					case LETRA:
						s +=c;
						tokenAntigo = IDENTIFICADOR;
						break;
					case NUMERO:
						tokenAntigo = ERRO;
					case BOOLEANO:
						
						if (ehOperador(c)) {
							
						}
				}
				s += c;
				break;
			case BOOLEANO:
				concatena
				ehNumero?
				sim:
					string[0] ehLetra?
						concatena;
				nao:
					
				
		}
	}
	
	return 0;
}
