#include "analisador.hpp"

Sintatico::Sintatico() {
	this->listaTokens.clear();
	this->pilhaSintatico.clear();
}

Sintatico::Sintatico(std::vector<Token*> listaTokens) {
	this->listaTokens = listaTokens;
	this->pilhaSintatico.clear();
}

bool Sintatico::OperaSintatico() {
	
	bool retorno = true;
	int tokenOri = 0;
	if ((int)this->pilhaSintatico.size() <= 0) retorno = false;
	else {
		//le o proximo token da fita
		int token = this->listaTokens.back()->getEstado();
		if (Sintatico::debug) cout << "FITA: " << Token::ImprimeToken(token, "ID") << endl;
		this->listaTokens.pop_back();
		//cout << "Leu: " << Token::ImprimeToken(token, "ID") << endl;
		if (token == ERRO) {
			 retorno = false;
		 }
		else if (token == INICIO && (int)this->pilhaSintatico.size() == 1) retorno = true;
		else {
			//consome o topo da pilha
			int topoPilha = this->pilhaSintatico.back();
			this->pilhaSintatico.pop_back();
			
			if (Sintatico::debug) cout << "PILHA: " << Token::ImprimeToken(topoPilha, "ID") << endl;
			if (Sintatico::debug) cout << "Tamanho Pilha: " << this->pilhaSintatico.size() << endl << endl;
			//trata o token antes de testar
			tokenOri = token;
			token = ehBooleano(token);
			token = ehOperador(token);
			//cout << "Leu Depois: " << Token::ImprimeToken(token, "ID") << endl;
			//testa o token
			
			//chamada recursiva no final do switch case
			//retorno = (retorno ? this->OperaSintatico(token) : retorno);
			
			
			switch(token) {
				case IDENTIFICADOR:
					if (topoPilha == INICIO || topoPilha == LCHAVES) {

						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);

					} else if (topoPilha == LPARENTS || topoPilha == OUT) {

						this->pilhaSintatico.push_back(BOOLVAR);

					} else if (topoPilha == IN || topoPilha == VIRGULA) {

						this->pilhaSintatico.push_back(ENTRADA);

					} else if (topoPilha == PARENTSIN) {

						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(ENTRADA);

					} else if (topoPilha == OUT) {

						this->pilhaSintatico.push_back(BOOLVAR);

					} else if (topoPilha == OPERADOR) {

						//this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(BOOLVAR);

					} else if (topoPilha == IF || topoPilha == ELSE ) {

						this->pilhaSintatico.push_back(token);

					} else {

						retorno = false;

					}
					break;
				case BOOLEANO:
					if (topoPilha == ATRIBUICAO || topoPilha == OPERADOR) {
						this->pilhaSintatico.push_back(BOOLVAR);
					} else
						retorno = false;
					break;
				case OUT:
				case IN:
					//IN e OUT possuem a mesma caracteristica quando sao lidos da fita, apenas se colocam na pilha
					if (topoPilha == INICIO || topoPilha == LCHAVES) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
						retorno = true;
					} else if (topoPilha == IF || topoPilha == CONDICIONAL ) {
						this->pilhaSintatico.push_back(token);
					} else {
						retorno = false;
					}
					break;
					
				case IF:
					if (topoPilha == INICIO || topoPilha == LCHAVES) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == IF || topoPilha == ELSE ) {
						this->pilhaSintatico.push_back(token);
					} else {
						retorno = false;
					}
					break;
				case ELSE:
					if (topoPilha == CONDICIONAL) {
						this->pilhaSintatico.push_back(CONDICIONAL);
					} else {
						retorno = false;
					}
					break;
					
				case ATRIBUICAO:
					if (topoPilha == IDENTIFICADOR)
						this->pilhaSintatico.push_back(token);
					else
						retorno = false;
					break;
				
				case OPERADOR:
					if (topoPilha == BOOLVAR || topoPilha == BOOLCOND)
						this->pilhaSintatico.push_back(OPERADOR);
					else
						retorno = false;
					break;
				
				case LPARENTS:
					if (topoPilha == IF) {
						this->pilhaSintatico.push_back(CONDICIONAL);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == IN) {
						this->pilhaSintatico.push_back(PARENTSIN);
					} else if (topoPilha == PARENTSIN) {
						this->pilhaSintatico.push_back(PARENTSIN);
						this->pilhaSintatico.push_back(PARENTSIN);
					} else if (topoPilha == OUT) {
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == OPERADOR || topoPilha == ATRIBUICAO) {
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == LPARENTS) {
						this->pilhaSintatico.push_back(BOOLCOND);
						this->pilhaSintatico.push_back(token);
					} else
						retorno = false;
					break;
					
				case RPARENTS:
					if (topoPilha == BOOLVAR) {
						this->pilhaSintatico.push_back(BOOLCOND);
						retorno = true;
					} else if (topoPilha == BOOLCOND || topoPilha == ENTRADA || topoPilha == PARENTSIN) {
						//consome BOOLCOND
						retorno = true;
					} else
						retorno = false;
					break;
				
				case NOT:
					
					if (topoPilha == BOOLVAR || topoPilha == BOOLCOND) {
						this->pilhaSintatico.push_back(topoPilha);
						retorno = true;
					} else
						retorno = false;
					break;
				
				case LCHAVES:
					//soh pode fazer se todos itens dentro do 
					if (topoPilha == CONDICIONAL) {
						this->pilhaSintatico.push_back(CONDICIONAL);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == BOOLCOND) {
						this->pilhaSintatico.push_back(token);
					} else {
						retorno = false;
					}
					break;
					
				case RCHAVES:
					//teste se é uma RCHAVES e apenas consome o topo da pilha, finalizando um comando
					if (topoPilha == LCHAVES) {
						retorno = true;
					} else 
						retorno = false;
					break;
				case VIRGULA:
					if (topoPilha == ENTRADA) {
						this->pilhaSintatico.push_back(token);
					} else
						retorno = false;
					break;
					
				case PONTOVIRGULA:
					if (topoPilha == BOOLVAR || topoPilha == ENTRADA || topoPilha == BOOLCOND || topoPilha == PARENTSIN)
						retorno = true;
					else
						retorno = false;
					break;
					
				default:
					retorno = false;
					
			}
			//cout << "topoPilha: " << Token::ImprimeToken(topoPilha, "ID") << endl;
			//cout << "back: " << Token::ImprimeToken(this->pilhaSintatico.back(), "ID") << endl;
			retorno = (retorno ? this->OperaSintatico() : retorno);
			if (retorno == false) {
			
			
			}
			
		}
	}
	
	
	
	return retorno;
}
bool Sintatico::AnalisaSintatico() {
	//inicializa a pilha com Z0
	this->pilhaSintatico.push_back(INICIO);
	while((int) this->listaTokens.size()) {
		if (this->listaTokens.back()->getEstado() == INICIO){
			if ( this->pilhaSintatico.size() != 0)
				return false;
			return true;
		}
		if (!OperaSintatico())
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
