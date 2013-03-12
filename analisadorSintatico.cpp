#include "analisador.hpp"

Sintatico::Sintatico() {
	this->listaTokens.clear();
	this->pilhaSintatico.clear();
}

Sintatico::Sintatico(std::vector<Token*> listaTokens) {
	this->listaTokens = listaTokens;
	this->pilhaSintatico.clear();
}

bool Sintatico::OperaSintatico(int entrada) {
	
	bool retorno = false;

	int token = ((int)this->listaTokens.size() > 0 ? this->listaTokens.back()->getEstado() : ERRO);
	if (token == ERRO) return false;
	if (token == INICIO) return true;
	//cout << "token: " << token << " this->listaTokens.size(): " << this->listaTokens.size() << endl;
	this->listaTokens.pop_back();

	token = ehOperador(token);
	int temp = ehReservado(token);
	switch(entrada) {
		case VAZIO:
			switch(temp) {
				case IDENTIFICADOR:
					token = this->listaTokens.back()->getEstado();
					if (token == ATRIBUICAO) {
						this->pilhaSintatico.push_back(token);
						this->listaTokens.pop_back();
						retorno = OperaSintatico(token);
					}
					else
						retorno = false;
					break;
				case RESERVADO:
					if (token == ELSE)
						retorno = false;
					else {
						this->pilhaSintatico.push_back(token);
						retorno = OperaSintatico(token);
					}
					break;
				case RCHAVES:
					if (this->pilhaSintatico.back() == LCHAVES) {
						this->pilhaSintatico.pop_back(); // tira lchaves
						if ((this->pilhaSintatico.back() == IF) || (this->pilhaSintatico.back() == ELSE)) {
							if (this->listaTokens.back()->getEstado() == ELSE) {
								this->listaTokens.pop_back();
								this->pilhaSintatico.pop_back();
								this->pilhaSintatico.push_back(ELSE);
								retorno = OperaSintatico(ELSE);
							}
							else {
								this->pilhaSintatico.pop_back(); //tira if ou else
								retorno = OperaSintatico(VAZIO);
							}
						}
						else retorno = false;
						retorno = OperaSintatico(VAZIO);

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
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					break;
				case RPARENTS:
					retorno = (SintaticoRParents() ? OperaSintatico(token) : false);
					break;
				case VIRGULA:
				case OPERADOR:
				case NOT:
					retorno = OperaSintatico(token);
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
				case BOOLEANO:
					retorno = OperaSintatico(token);
					break;
				case LPARENTS:
					this->pilhaSintatico.push_back(LPARENTS);
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
					break;
			}
			break;
		case VIRGULA:
			switch(token) {
				case IDENTIFICADOR:
					retorno = OperaSintatico(token);
					break;
				case LPARENTS:
					this->pilhaSintatico.push_back(LPARENTS);
					retorno = OperaSintatico(token);
					break;
				case BOOLEANO:
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case BOOLEANO:
			switch(token) {
				case OPERADOR:
				case NOT:
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					break;
				case VIRGULA:
					retorno = OperaSintatico(token);
					break;
				case RPARENTS:
					retorno = (SintaticoRParents() ? OperaSintatico(token) : false);
					break;
				default:
					retorno = false;
			}
			break;
		case OPERADOR:
			if (this->pilhaSintatico.back() != IN) {
				switch(token) {
					case IDENTIFICADOR:
						retorno = OperaSintatico(token);
						break;
					case BOOLEANO:
						retorno = OperaSintatico(token);
						break;
					case LPARENTS:
						this->pilhaSintatico.push_back(LPARENTS);
						retorno = OperaSintatico(token);
						break;
					default:
						retorno = false;
				}
			}
			break;
		case NOT:
			switch(token) {
				case RPARENTS:
					retorno = (this->SintaticoRParents() ? OperaSintatico(token) : false);
					break;
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					break;
				case OPERADOR:
				case NOT:
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case IF:
			switch(token) {
				case LPARENTS:
					this->pilhaSintatico.push_back(LPARENTS);
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case ELSE:
			switch(token) {
				case LCHAVES:
					this->pilhaSintatico.push_back(LCHAVES);
					retorno = OperaSintatico(VAZIO);
					break;
			}
			break;
		case IN:
			if (token == IDENTIFICADOR)
				retorno = OperaSintatico(token);
			else 
				retorno = false;
			break;
		case OUT:
			switch(token) {
				case IDENTIFICADOR:
				case BOOLEANO:
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
		case LPARENTS:
			if (this->pilhaSintatico.back() != IN) { // aqui deve ter erro
				token = ehBooleano(token);
				switch(token) {
					case LPARENTS:
						this->pilhaSintatico.push_back(LPARENTS);
						retorno = OperaSintatico(token);
					case IDENTIFICADOR:
					case BOOLEANO:
						retorno = OperaSintatico(token);
						break;
					default:
						retorno = false;
				}
			}
			break;
		case RPARENTS:
			switch(token) {
				case NOT:
				case OPERADOR:
					retorno = OperaSintatico(token);
					break;
					break;
				case PONTOVIRGULA:
					retorno = SintaticoPontoVirgula();
					break;
				case LCHAVES:
					this->pilhaSintatico.push_back(LCHAVES);
					retorno = OperaSintatico(VAZIO);
					break;
				case RPARENTS:
					retorno = (this->SintaticoRParents() ? OperaSintatico(token) : false);
					break;
				default:
					retorno = false;
			}
			break;
		case LCHAVES:
			switch(token) {
				case IDENTIFICADOR:
					retorno = OperaSintatico(token);
					break;
				default:
					retorno = false;
			}
			break;
	}
	if (retorno == false) {
		cout << "entrada: " << Token::ImprimeToken(entrada,"IDENTIFICADOR") << " token: " << token << " " << Token::ImprimeToken(token,"IDENTIFICADOR") << endl;
		cout << "pilha sintatico: " << Token::ImprimeToken(this->pilhaSintatico.back(),"IDENTIFICADOR") << endl;
		cout << "pilha lexico: " << Token::ImprimeToken(this->listaTokens.back()->getPosicao(),"IDENTIFICADOR") << endl;
	}

	return retorno;
}
bool Sintatico::AnalisaSintatico() {
	while((int) this->listaTokens.size()) {
		if (this->listaTokens.back()->getEstado() == INICIO){
			if ( this->pilhaSintatico.size() != 0)
				return false;
			return true;
		}
		if (!OperaSintatico(VAZIO))
			return false;
	}	
	return true;
}


int Sintatico::ehReservado(int token) {
	if ((token == IF ) || (token == ELSE) || (token == IN) || token == OUT)
		token = RESERVADO;
	return token;
}

int Sintatico::ehBooleano(int token) {
	if ((token == TRUE ) || (token == FALSE))
		token = BOOLEANO;
	return token;
}

int Sintatico::ehOperador(int token) {
	if ((token == AND ) || (token == OR) || (token == OPERADORSSS) || token == OPERADORSE)
		return OPERADOR;
	return token;
}

int Sintatico::SintaticoRParents() {
	
	bool retorno = true;
	int temp = this->pilhaSintatico.back();
	this->pilhaSintatico.pop_back();
	
	try {
		if (temp != LPARENTS)
			throw 1;
	} catch (int e) {
		retorno = false;
	}
	
	return retorno;
}

int Sintatico::SintaticoPontoVirgula() {
	
	bool retorno = false;
	int temp = this->pilhaSintatico.back();
	//temp = ehReservado(temp);
	switch(temp) {
		case ATRIBUICAO:
			this->pilhaSintatico.pop_back();
			retorno = true;
			break;
		case IN:
			this->pilhaSintatico.pop_back();
			retorno = true;
			break;
		case OUT:
			this->pilhaSintatico.pop_back();
			retorno = true;
			break;
		default:
			retorno = false;
			break;
	}
	return retorno;
}
