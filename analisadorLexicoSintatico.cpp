#include "analisadorLexicoSintatico.hpp"

std::vector<Token*> Token::listaTokens;
std::vector<Token*> Token::pilhaLexico;
std::vector<int> Token::pilhaSintatico;

int main(int argc, char * argv[]) {
	string * entrada;
	string texto;
	string arquivo;
	if (argc > 1) {
		arquivo = argv[1];
		//cout << "Abrindo arquivo " << arquivo << ": " << endl;
	} else {
		//cout << "Entrada padrao: " << endl;
		while (!cin.eof()) {
			texto.push_back(cin.get());
		}
		
		texto[texto.size()-1] = '\0';
	}
	
	//Token::Lexico(entrada);
	Token::Lexico(texto);
	
	Token * inicio = new Token();
	inicio->setEstado(INICIO);
	Token::pilhaLexico.push_back(inicio);
	
	for (int i =(int) Token::listaTokens.size() - 1 ; i >= 0 ; i--) {
		Token * token;
		token = Token::listaTokens[i];
		Token::pilhaLexico.push_back(token);
	}
	Token::Imprime();
	
	cout << endl;
	
	bool retSintatico = Token::AnalisaSintatico();
	
	cout << "Entrada " << (retSintatico ? "valida" : "invalida");
	

	cout << endl;
	
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
void Token::setPosicao(int posicao,int token) {
	int tam = 0;
	switch(token) {
		case IN:
			tam = 2;
		case OUT:
			tam = 3;
		case IF:
			tam = 2;
		default:
			break;
	}
	posicao -= (tam ? tam - 1 : tam);
	this->setPosicao(posicao);
}

/**
 * Inicio Metodos estaticos
 **/

bool Token::ehLetra(char c) {
	if ((c>='a' && c<='z'))
		return 1;
	return 0;
}
bool Token::ehNumero(char c) {
	if ((c >='0' && c<='9'))
		return 1;
	return 0;
}
bool Token::ehBooleano(char c) {
	if ((c == '0' || c == '1'))
		return 1;
	return 0;
}
int Token::ehOperador(int token) {
	if ((token == AND ) || (token == OR) || (token == OPERADORSSS) || token == OPERADORSE)
		return OPERADOR;
	return token;
}
bool Token::ehOperador(char c) {
	if ((c == '^') || (c == 'V') || (c == '-') || (c == '<') || (c == '\'') || (c == ':'))
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
int Token::ehReservado(int token) {
	if ((token == IF ) || (token == ELSE) || (token == IN) || token == OUT)
		token = RESERVADO;
	return token;
}

int Token::ehBooleano(int token) {
	if ((token == TRUE ) || (token == FALSE))
		token = BOOLEANO;
	return token;
}



int Token::SintaticoRParents() {
	
	bool retorno = true;
	int temp = Token::pilhaSintatico.back();
	Token::pilhaSintatico.pop_back();
	
	try {
		if (temp != LPARENTS)
			throw 1;
	} catch (int e) {
		retorno = false;
	}
	
	return retorno;
}

int Token::SintaticoPontoVirgula() {
	
	bool retorno = false;
	int temp = Token::pilhaSintatico.back();
	//temp = ehReservado(temp);
	switch(temp) {
		case ATRIBUICAO:
			Token::pilhaSintatico.pop_back();
			retorno = true;
			break;
		case IN:
			Token::pilhaSintatico.pop_back();
			retorno = true;
			break;
		case OUT:
			Token::pilhaSintatico.pop_back();
			retorno = true;
			break;
		default:
			retorno = false;
			break;
	}
	return retorno;
}
/**/
bool Token::AnalisaSintatico() {
	while((int) Token::pilhaLexico.size()) {
		if (Token::pilhaLexico.back()->getEstado() == INICIO) return true;
		if (!Token::Sintatico(VAZIO))
			return false;
	}
	return true;
}

/**/
bool Token::Sintatico(int entrada) {
	int token = Token::pilhaLexico.back()->getEstado();
	if (token == INICIO) return true;
	Token::pilhaLexico.pop_back();
	//string aux = Token::ImprimeToken(token,"a");
	//cout << endl << aux << endl;
	bool retorno = false;
	token = ehOperador(token);
	int temp = ehReservado(token);
	switch(entrada) {
		case VAZIO:
			switch(temp) {
				case IDENTIFICADOR:
					token = Token::pilhaLexico.back()->getEstado();
					if (token == ATRIBUICAO) {
						Token::pilhaSintatico.push_back(token);
						Token::pilhaLexico.pop_back();
						retorno = Sintatico(token);
					}
					else
						retorno = false;
					break;
				case RESERVADO:
					if (token == ELSE)
						retorno = false;
					else {
						Token::pilhaSintatico.push_back(token);
						retorno = Sintatico(token);
					}
					break;
				case RCHAVES:
					if (Token::pilhaSintatico.back() == LCHAVES) {
						Token::pilhaSintatico.pop_back(); // tira lchaves
						if ((Token::pilhaSintatico.back() == IF) || (Token::pilhaSintatico.back() == ELSE)) {
							if (Token::pilhaLexico.back()->getEstado() == ELSE) {
								Token::pilhaLexico.pop_back();
								Token::pilhaSintatico.pop_back();
								Token::pilhaSintatico.push_back(ELSE);
								retorno = Sintatico(ELSE);
							}
							else {
								Token::pilhaSintatico.pop_back(); //tira if ou else
								retorno = Sintatico(VAZIO);
							}
						}
						else retorno = false;
						retorno = Sintatico(VAZIO);

					}
					break;
				case INICIO:
					retorno = true;
				default:
					retorno = false;
					break;
			}
			break;
		case IDENTIFICADOR:
			switch (token) {
				case RPARENTS:
					retorno = (SintaticoRParents() ? Sintatico(token) : false);

					break;
				case VIRGULA:
					retorno = Sintatico(token);
					break;
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					//retorno = ( (int) Token::pilhaSintatico.size() == 0 ? true : false);
					break;
				case OPERADOR:
					retorno = Sintatico(token);
					break;
				case NOT:
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
					break;
			}
			break;
		case ATRIBUICAO:
			token = ehBooleano(token);
			switch(token) {
				case IDENTIFICADOR:
					retorno = Sintatico(token);
					break;
				case BOOLEANO:
					retorno = Sintatico(token);
					break;
				case LPARENTS:
					Token::pilhaSintatico.push_back(LPARENTS);
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
					break;
			}
			break;
		case VIRGULA:
			switch(token) {
				case IDENTIFICADOR:
					retorno = Sintatico(token);
					break;
				case LPARENTS:
					Token::pilhaSintatico.push_back(LPARENTS);
					retorno = Sintatico(token);
					break;
				case BOOLEANO:
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case BOOLEANO:
			switch(token) {
				case OPERADOR:
					retorno = Sintatico(token);
					break;
				case NOT:
					retorno = Sintatico(token);
					break;
				case VIRGULA:
					retorno = Sintatico(token);
					break;
				case RPARENTS:
					retorno = (SintaticoRParents() ? Sintatico(token) : false);
					break;
				default:
					retorno = false;
			}
			break;
		case OPERADOR:
			if (Token::pilhaSintatico.back() != IN) {
				switch(token) {
					case IDENTIFICADOR:
						retorno = Sintatico(token);
						break;
					case BOOLEANO:
						retorno = Sintatico(token);
						break;
					case LPARENTS:
						Token::pilhaSintatico.push_back(LPARENTS);
						retorno = Sintatico(token);
						break;
					default:
						retorno = false;
				}
			}
			break;
		case NOT:
			switch(token) {
				case RPARENTS:
					retorno = (Token::SintaticoRParents() ? Sintatico(token) : false);
					break;
				case OPERADOR:
					retorno = Sintatico(token);
					break;
				case NOT:
					retorno = Sintatico(token);
					break;
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					//retorno = ( (int) Token::pilhaSintatico.size() == 0 ? true : false);
					//retorno = true;
					break;
				default:
					retorno = false;
			}
			break;
		case IF:
			switch(token) {
				case LPARENTS:
					Token::pilhaSintatico.push_back(LPARENTS);
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case ELSE:
			switch(token) {
				case LCHAVES:
					Token::pilhaSintatico.push_back(LCHAVES);
					retorno = Sintatico(VAZIO);
					break;
			}
			break;
		case IN:
			switch(token) {
				case IDENTIFICADOR:
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case OUT:
			switch(token) {
				case IDENTIFICADOR:
					retorno = Sintatico(token);
					break;
				case BOOLEANO:
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case LPARENTS:
			if (Token::pilhaSintatico.back() != IN) { // aqui deve ter erro
				token = ehBooleano(token);
				switch(token) {
					case IDENTIFICADOR:
						retorno = Sintatico(token);
						break;
					case BOOLEANO:
						retorno = Sintatico(token);
						break;
					default:
						retorno = false;
				}
			}
			break;
		case RPARENTS:
			switch(token) {
				case NOT:
					retorno = Sintatico(token);
					break;
				case OPERADOR:
					break;
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					//retorno = ( (int) Token::pilhaSintatico.size() == 0 ? true : false);
					//retorno = true;
					break;
				case LCHAVES:
					Token::pilhaSintatico.push_back(LCHAVES);
					retorno = Sintatico(VAZIO);
					break;
				default:
					retorno = false;
			}
			break;
		case LCHAVES:
			switch(token) {
				case IDENTIFICADOR:
					retorno = Sintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
	}
	if (retorno == false) {
		cout << "entrada: " << Token::ImprimeToken(entrada,"IDENTIFICADOR") << " token: " << token << " " << Token::ImprimeToken(token,"IDENTIFICADOR") << endl;
		cout << "pilha sintatico: " << Token::ImprimeToken(Token::pilhaSintatico.back(),"IDENTIFICADOR") << endl;
		cout << "pilha lexico: " << Token::ImprimeToken(Token::pilhaLexico.back()->getPosicao(),"IDENTIFICADOR") << endl;
	}
	return retorno;
}


/**/
/**
 * Retorna uma string com um ou mais tokens
 **/
void Token::Lexico(FILE * Arquivo, int pos) {
   //por enquanto nao faz nada, mas ira chamar o Lexico passando uma string de acordo com a posicao e um arquivo
   
}

void Token::Lexico(string palavra) {

	string s;
	s.clear();
	//estado inicial
	int estado = VAZIO;
	bool tokenizer = false;
	string erro;
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
					if (palavra[i] == '0')
						estado = FALSE;
					if (palavra[i] == '1')
						estado = TRUE;
					tokenizer = true;
				} else if (Token::ehOperador(palavra[i])) {
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
					erro = "ID ";
					erro += palavra[i];
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
				estado = (Token::ehReservado(s) ? Token::PalavraReservada(s) : IDENTIFICADOR );
				if (estado == IDENTIFICADOR)
					novoToken->setId(s);
				i--;
			} else if (estado == ERRO) {
				novoToken->setId(erro);
			}
			
			novoToken->setEstado(estado);
			novoToken->setPosicao(i);
			//insere na lista
			Token::listaTokens.push_back(novoToken);
			//retorna a iteracao 1 passo, para o estado inicial vazio 
			//reseta o estado
			s.clear();

			estado = VAZIO;
			tokenizer = false;
		}
	}

}
void Token::Imprime() {
	int estado;
	int posicao;
	string id;
	string Nome;
	for (int i=0; i < (int)Token::listaTokens.size(); i++) {
		estado = Token::listaTokens[i]->getEstado();
		posicao = Token::listaTokens[i]->getPosicao();
		id = Token::listaTokens[i]->getId();
		Nome = Token::ImprimeToken(estado,id);
		cout << "<" << Nome << "," << posicao << ">";
	}
}

string Token::ImprimeToken(int token,string id) {
	
	string Nome;
	Nome.clear();
	switch(token) {
		case IDENTIFICADOR:
			Nome = id;
			break;
		case IF:
			Nome = "IF";
			break;
		case ELSE:
			Nome = "ELSE";
			break;
		case IN:
			Nome = "IN";
			break;
		case OUT:
			Nome = "OUT";
			break;
		case TRUE:
			Nome = "TRUE";
			break;
		case FALSE:
			Nome = "FALSE";
			break;
		case OR:
			Nome = "OR";
			break;
		case AND:
			Nome = "AND";
			break;
		case NOT:
			Nome = "NOT";
			break;
		case OPERADORSE:
			Nome = "OPERADORSE";
			break;
		case OPERADORSSS:
			Nome = "OPERADORSSS";
			break;
		case ATRIBUICAO:
			Nome = "ATRIBUICAO";
			break;
		case LPARENTS:
			Nome = "LPARENTS";
			break;
		case RPARENTS:
			Nome = "RPARENTS";
			break;
		case LCHAVES:
			Nome = "LCHAVES";
			break;
		case RCHAVES:
			Nome = "RCHAVES";
			break;
		case PONTOVIRGULA:
			Nome = "PONTOVIRGULA";
			break;
		case VIRGULA:
			Nome = "VIRGULA";
			break;
		case INICIO:
			Nome = "INICIO";
			break;
		case VAZIO:
			Nome = "VAZIO";
			break;
		case ERRO:
			Nome = "NAOIDENTIFICADO,";
			Nome += id;
			break;
	}
	return Nome;
}
