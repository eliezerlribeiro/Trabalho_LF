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
	if ((int)this->pilhaSintatico.size() <= 0) retorno = false;
	else {
		//le o proximo token da fita
		int token = this->listaTokens.back()->getEstado();
		if (token == ERRO) retorno = false;
		else if (token == INICIO && this->pilhaSintatico > 0 && this->pilhaSintatico->back()) retorno = true;
		else {
			//consome o topo da pilha
			int topoPilha = this->pilhaSintatico.back();
			this->pilhaSintatico.pop_back();
			
			//trata o token antes de testar
			token = ehBooleano(token);
			token = ehOperador(token);
			//testa o token
			
			
			
			//chamada recursiva no final do switch case
			//retorno = (retorno ? this->OperaSintatico(token) : retorno);
			
			
			switch(token) {
				case IDENTIFICADOR:
					if (topoPilha == INICIO || topoPilha == LCHAVES) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == LPARENTS) {
						//this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(BOOLVAR);
					} else if (topoPilha == OPERADOR) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(BOOLVAR);
					} else if (topoPilha == IF || topoPilha == ELSE ) {
						this->pilhaSintatico.push_back(token);
					} else {
						retorno = false;
					}
					break;
					
				case OUT:
				case IN:
					//IN e OUT possuem a mesma caracteristica quando sao lidos da fita, apenas se colocam na pilha
					if (topoPilha == INICIO || topoPilha == LCHAVES) {
						if (topoPilha != IF) this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == IF || topoPilha == ELSE ) {
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
					if (topoPilha == IF) {
						this->pilhaSintatico.push_back(token);
					} else {
						retorno = false;
					}
					break;
					
				case RCHAVES:
					if (topoPilha == IF || topoPilha == ELSE) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
					} else
						retorno = false;
					break;
					
				case ATRIBUICAO:
					if (topoPilha == IDENTIFICADOR)
						this->pilhaSintatico.push_back(token);
					else
						retorno = false;
					break;
				
				case OPERADOR:
					if (topoPilha == BOOLVAR)
						this->pilhaSintatico.push_back(token);
					else
						retorno = false;
					break;
				
				case LPARENTS:
					if (topoPilha == IF) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
					} else if (topoPilha == OPERADOR) {
						this->pilhaSintatico.push_back(BOOLVAR);
						this->pilhaSintatico.push_back(token);
					} else
						retorno = false;
					break;
					
				case RPARENTS:
					if (topoPilha == BOOLVAR)
						retorno = true;
					else
						retorno = false;
					break;
				
				case 
				
				
				
				
				
				
				
				
				
				
				
				
				case INICIO:
					//fita no inicio pode ler:
					//coloca o token na pilha IF, IN, OUT, ATRIBUICAO
					if (token == IF || token == IN || token == OUT || token == IDENTIFICADOR) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
						retorno = this->OperaSintatico();
					} else
						retorno = false;
					break;
					
				case IF:
					//	CONDICIONAL -> <LPARENTES> E1 <RPARENTES>  <LCHAVES,> COMANDO <RCHAVES,> COND_ELSE
					//token lido so pode ser LPARENTS
					if (token == LPARENTS) {
						//coloca IF no topo da pilha
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
						retorno = this->OperaSintatico();
					} else
						retorno = false;
					break;
				
				case LPARENTS:
					//pilha tem um lparents, entao soh pode ser uma variavel booleana (BOOLVAR) ou outro lparents
					if (token == IDENTIFICADOR || ehBooleano(token) == BOOLEANO || token == LPARENTS) {
						this->pilhaSintatico.push_back(topoPilha);
						this->pilhaSintatico.push_back(token);
						retorno = this->OperaSintatico();
					} else
						retorno = false;
					break;
					
				case ELSE:
					//topo da pilha else, token lido soh pode ser LCHAVES
					if (token == LCHAVES)
						retorno = this->OperaSintatico();
					else
						retorno = false;
					break;
					
				case BOOLVAR:
					//caso seja uma variavel booleana pode ler um operador ou not ou LPARENTS
					if (ehOperador(token) == OPERADOR || token == NOT) {
						//metodo ehOperador(token), retorna o enum OPERADOR caso seja um dos operadores ou o enum original caso contrario
						this->pilhaSintatico.push_back(ehOperador(token));
						retorno = this->OperaSintatico();
					} else if (token == LPARENTS) {
						this->pilhaSintatico.push_back(token);
						retorno = this->OperaSintatico();
					} else
						retorno = false;
					
					break;
					
				case OPERADOR:
					//caso leia um operador da pilha, soh pode ler um IDENTIFICADOR ou LPARENTS
					if (token == IDENTIFICADOR || token == LPARENTS || ehBooleano(token) == BOOLEANO) {
						this->pilhaSintatico.push_back( (token == IDENTIFICADOR || ehBooleano(token) == BOOLEANO  ? BOOLVAR : token) );
						retorno = this->OperaSintatico();
					} else
						retorno = false;
					
				case IDENTIFICADOR:
					//topo da pilha identificador soh pode ser ATRIBUICAO
					
					
					
					
					
					if (token == IDENTIFICADOR || token == LCHAVES || ehReservado(token) || ehBooleano(token) || token == PONTOVIRGULA)
						retorno = false;
					else {
						if (topoPilha == INICIO || topoPilha == LPARENTS) {
							this->pilhaSintatico.push_back(topoPilha);
							//se a pilha conter LPARENTS ou INICIO, eh erro sintatico, tratamento: b;
							if(token == PONTOVIRGULA) retorno = false;
						}
						if (retorno) {
							//coloca o identificador na pilha
							this->pilhaSintatico.push_back(IDENTIFICADOR);
							
							retorno = this->OperaSintatico(token);
						}
					}
					break;
					
				case BOOLEANO:
					//leu 
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
