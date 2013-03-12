#include "analisador.hpp"

Lexico::Lexico(FILE * Arquivo, int pos) {
   //por enquanto nao faz nada, mas ira chamar o Lexico passando uma string de acordo com a posicao e um arquivo
   
}
/**
 * Construtor principal, atraves de uma palavra cria uma lista de tokens
 **/
Lexico::Lexico(string palavra) {

	string s;
	s.clear();
	//estado inicial
	int estado = VAZIO;
	bool tokenizer = false;
	string erro;
	for (int i=0; i < palavra.length(); ++i) {
		switch(estado) {
			case VAZIO:
				if (ehLetra(palavra[i])) {
					//estado inicial eh uma letra, passa pro estado letra
					s += palavra[i];
					estado = LETRA;
					tokenizer = false;
				} else if (ehBooleano(palavra[i])) {
					//estado inicial eh um booleano, true ou false
					if (palavra[i] == '0')
						estado = FALSE;
					if (palavra[i] == '1')
						estado = TRUE;
					tokenizer = true;
				} else if (ehOperador(palavra[i])) {
					//estado inicial eh um operador
					tokenizer = true;
					if (palavra[i] == '^') // estado AND
						estado = AND;
					if (palavra[i] == 'V') // estado OR
						estado = OR;
					if (palavra[i] == '\'') // estado NOT
						estado = NOT;
					if (palavra[i] == '-') {
						// estado SE
						estado = OPERADORSE;
						tokenizer = false;
					}
					if (palavra[i] == '<') {
						// estado intermediario SESOMENTESE
						estado = OPERADOR;
						tokenizer = false;
					}
					if (palavra[i] == ':') {
						// estado ATRIBUICAO
						estado = ATRIBUICAO;
						tokenizer = false;
					}
				} else if (palavra[i] == '\"'){
					//estado inicial eh aspas, passa para o estado booleano
					estado = BOOLEANO;
					tokenizer = false;
				} else if (ehSeparador(palavra[i])) {
					//estado = SEPARADOR;
					//break;
				} else if (ehBloco(palavra[i])) {
					//estado inicial eh um bloco, passa para o estado de acordo com o caracter
					if (palavra[i] == '}')
						estado = RCHAVES;
					else if (palavra[i] == '{')
						estado = LCHAVES;
					else if (palavra[i] == '(')
						estado = LPARENTS;
					else if (palavra[i] == ')')
						estado = RPARENTS;
					tokenizer = true;
					
				} else if (palavra[i] == ';') {
					//estado eh um ponto e virgula
					estado = PONTOVIRGULA;
					tokenizer = true;
				} else if (palavra[i] == ',') {
					//estado eh uma virgula
					estado = VIRGULA;
					tokenizer = true;
				} else {
					//estado inicial nao identificado
					estado = ERRO;
					erro = "ID ";
					erro += palavra[i];
					tokenizer = true;
				}
				break;
			case LETRA:
				if (ehLetra(palavra[i])) {
					//continua como letra, concatena e segue o baile
					s += palavra[i];
				} else if (ehNumero(palavra[i])) {
					s += palavra[i];
					estado = IDENTIFICADOR;
				} else {
					//qualquer coisa diferente de letra muda o estado
					tokenizer = true;
				}
				break;
			case BOOLEANO:
				if (ehLetra(palavra[i])) {
					//acrescenta na string
					s += palavra[i];
					break;
				} else if (palavra[i] == '\"') {
					//final das aspas verifica se a palavra eh reconhecida ou nao na linguagem
					if (s == "verdadeiro" || s == "true" || s == "v" ) {
						estado = TRUE;
						//palavra booleana reconhecida
					} else if (s == "falso" || s == "false" || s == "f" ) {
						estado = FALSE;
						//palavra booleana reconhecida
					} else {
						estado = ERRO;
						erro = "BOOLEANO_ASPAS";
					}
				} else {
					estado = ERRO;
					erro = "BOOLEANO ";
					erro += palavra[i];
				}
				tokenizer = true;
				break;
			case OPERADOR: // <
				if (palavra[i] == '-')
					estado = OPERADORSSS;
				else {
					estado = ERRO;
					erro = "OPERADOR";
					tokenizer = true;
				}
				break;
			case OPERADORSE:
				if(!palavra[i] == '>') {
					estado = ERRO;
					erro = "OPERADORSE";
				}
				tokenizer = true;
				break;
			case OPERADORSSS:
				if(!palavra[i] == '>') {
					estado = ERRO;
					erro = "OPERADORSSS";
				}
				tokenizer = true;
				break;
			case ATRIBUICAO:
				if (!palavra[i] == '=') {
					estado == ERRO;
					erro = "ATRIBUICAO";
				}
				tokenizer = true;
				break;
			default:
				estado = OUTRO;
				tokenizer = true;
				break;
				
		}
		
		if (tokenizer) {
			//cria um token novo a ser inserido na lista
			Token * novoToken = new Token();
			if (estado == LETRA) {
				estado = (ehReservado(s) ? PalavraReservada(s) : IDENTIFICADOR );
				if (estado == IDENTIFICADOR)
					novoToken->setId(s);
				i--;
			} else if (estado == ERRO) {
				novoToken->setId(erro);
			}
			
			novoToken->setEstado(estado);
			novoToken->setPosicao(i);
			//insere na lista
			listaTokens.push_back(novoToken);
			//retorna a iteracao 1 passo, para o estado inicial vazio 
			//reseta o estado
			s.clear();

			estado = VAZIO;
			tokenizer = false;
		}
	}

}


bool Lexico::ehLetra(char c) {
	if ((c>='a' && c<='z'))
		return 1;
	return 0;
}
bool Lexico::ehNumero(char c) {
	if ((c >='0' && c<='9'))
		return 1;
	return 0;
}
bool Lexico::ehBooleano(char c) {
	if ((c == '0' || c == '1'))
		return 1;
	return 0;
}
bool Lexico::ehOperador(char c) {
	if ((c == '^') || (c == 'V') || (c == '-') || (c == '<') || (c == '\'') || (c == ':'))
		return 1;
	return 0;
}

bool Lexico::ehSeparador(char c) {
	if ((c == ' ') || (c == '\0') || (c == '\t') || (c == '\n'))
		return 1;
	return 0;
}

bool Lexico::ehBloco(char c) {
	if ((c == '}') || (c == '{') || (c == '(') || (c == ')'))
		return 1;
	return 0;
}

bool Lexico::ehReservado(string palavra) {
	bool retorno = false;
	if (palavra == "if")
		retorno = true;
	if (palavra == "else")
		retorno = true;
	if (palavra == "in")
		retorno = true;
	if (palavra == "out")
		retorno = true;
	return retorno;
}
int Lexico::PalavraReservada(string palavra) {
	int retorno = 0;
	if (palavra == "if")
		retorno = IF;
	if (palavra == "else")
		retorno = ELSE;
	if (palavra == "in")
		retorno = IN;
	if (palavra == "out")
		retorno = OUT;
	return retorno;
}

void Lexico::Imprime() {
	int estado;
	int posicao;
	string id;
	string Nome;
	for (int i=0; i < (int)this->listaTokens.size(); i++) {
		estado = this->listaTokens[i]->getEstado();
		posicao = this->listaTokens[i]->getPosicao();
		id = this->listaTokens[i]->getId();
		Nome = Token::ImprimeToken(estado,id);
		cout << "<" << Nome << "," << posicao << ">";
	}
}

/**
 * Retorna uma pilha de tokens para serem tratados pelo analisador sintatico
 **/
std::vector<Token *> Lexico::AnalisaLexico() {
	std::vector<Token *> retorno;

	Token * inicio = new Token();
	inicio->setEstado(INICIO);

	retorno.push_back(inicio);


	for (int i =(int) this->listaTokens.size() - 1 ; i >= 0 ; i--) {
		//Token * token = new Token(&listaTokens[i]);
		Token * token;
		token = listaTokens[i];
		retorno.push_back(token);
	}
	return retorno;
}

