#include "analisadorLexicoSintatico.hpp"

int main() {
	cout << "Ola Mundo" << endl;
	return 0;
}

Token::Token() {
	this->setId("");
	this->setEstado(0);
	this->setPosicao(0);
}
string Token::getId() {
	return this->id;
}
int Token::getPosicao() {
	return this->posicao;
}
int Token::getEstado() {
	return this->estado;
}
void Token::setId(string id) {
	this->id = id;
}
void Token::setEstado(int estado) {
	this->estado = estado;
}
void Token::setPosicao(int posicao) {
	this->posicao = posicao;
}


/**
 * Inicio Metodos estaticos
 **/
std::vector<Token*> Token::ListaTokens;

bool Token::ehLetra(char c) {
	if ((c >='A' && c<='Z') || (c>='a' && c<='z') )
		return 1;
	return 0;
}
bool Token::ehNumero(char c) {
	if ((c >='0' && c<='9'))
		return 1;
	return 0;
}
bool Token::ehBooleano(char c) {
	if ((c == '0' && c == '1'))
		return 1;
	return 0;
}
bool Token::ehOperador(char c) {
	if ((c == '^') || (c == 'v') || (c == '-') || (c == '<') || (c == '\'') || (c == ':'))
		return 1;
	return 0;
}

bool Token::ehSeparador(char c) {
	if ((c == ' ') || (c == '\0') || (c == '\t') || (c == '\n'))
		return 1;
	return 0;
}

bool Token::ehBloco(char c) {
	if ((c == '}') || (c == '{') || (c == '(') || (c == ')'))
		return 1;
	return 0;
}

bool Token::ehReservado(string palavra) {
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
int Token::PalavraReservada(string palavra) {
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

/**
 * Retorna uma string com um ou mais tokens
 **/
void Lexico(FILE * Arquivo, int pos) {
   //por enquanto nao faz nada, mas ira chamar o Lexico passando uma string de acordo com a posicao e um arquivo
   
}

void Lexico(string palavra) {

	string s;
	s.clear();
	//estado inicial
	int estado = VAZIO;
	bool tokenizer = false;

	for (int i=0; i < palavra.length(); ++i) {
		switch(estado) {
			case VAZIO:
				if (Token::ehLetra(palavra[i])) {
					//estado inicial eh uma letra, passa pro estado letra
					s += palavra[i];
					estado = LETRA;
					tokenizer = false;
				} else if (Token::ehBooleano(palavra[i])) {
					//estado inicial eh um booleano, true ou false
					if (palavra[i] == 0)
						estado = FALSE;
					if (palavra[i] == 1)
						estado = TRUE;
					tokenizer = true;
				} else if (Token::ehOperador(palavra[i])) {
					//estado inicial eh um operador
					tokenizer = true;
					if (palavra[i] == '^') // estado AND
						estado = AND;
					if (palavra[i] == 'v') // estado OR
						estado = OR;
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
				} else if (Token::ehSeparador(palavra[i])) {
					//estado = SEPARADOR;
					//break;
				} else if (Token::ehBloco(palavra[i])) {
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
					tokenizer = true;
				}
				break;
			case LETRA:
				if (Token::ehLetra(palavra[i])) {
					//continua como letra, concatena e segue o baile
					s += palavra[i];
				} else if (Token::ehNumero(palavra[i])) {
					s += palavra[i];
					estado = IDENTIFICADOR;
				} else {
					//qualquer coisa diferente de letra muda o estado
					tokenizer = true;
				}
				break;
			case BOOLEANO:
				if (Token::ehLetra(palavra[i])) {
					//acrescenta na string
					s += palavra[i];
				} else if (palavra[i] == '\"') {
					//final das aspas verifica se a palavra eh reconhecida ou nao na linguagem
					if (s == "verdadeiro" || s == "true" ) {
						estado = TRUE;
						//palavra booleana reconhecida
					} else if (s == "falso" || s == "false") {
						estado = FALSE;
						//palavra booleana reconhecida
					} else {
						estado = ERRO;
					}
				} else {
					estado = ERRO;
				}
				tokenizer = true;
				break;
			case OPERADOR: // <
				if (palavra[i] == '-')
					estado = OPERADORSSS;
				else {
					estado = ERRO;
					tokenizer = true;
				}
				break;
			case OPERADORSE:
				if(!palavra[i] == '>')
					estado = ERRO;
				tokenizer = true;
				break;
			case OPERADORSSS:
				if(!palavra[i] == '>')
					estado = ERRO;
				tokenizer = true;
				break;
			case ATRIBUICAO:
				if (!palavra[i] == '=')
					estado == ERRO;
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
				estado = (Token::ehReservado(s) ? Token::PalavraReservada(s) : IDENTIFICADOR );
				if (estado == IDENTIFICADOR)
					novoToken->setId(s);
				i--;
			}
			
			novoToken->setEstado(estado);
			novoToken->setPosicao(i);
			//insere na lista
			Token::ListaTokens.push_back(novoToken);
			//retorna a iteracao 1 passo, para o estado inicial vazio 
			//reseta o estado
			s.clear();

			estado = VAZIO;
			tokenizer = false;
		}
	}

}
