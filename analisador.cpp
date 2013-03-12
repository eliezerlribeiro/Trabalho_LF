#include "analisador.hpp"

int main(int argc, char * argv[]) {
	string * entrada;
	string texto;
	string arquivo;
	if (argc > 1) {
		arquivo = argv[1];
		//cout << "Abrindo arquivo " << arquivo << ": " << endl;
	} else {
		//cout << "Entrada padrao: " << endl;
		while (cin.good()) {
			texto.push_back(cin.get());
		}
		
		texto[texto.size()-1] = '\0';
	}
	
	Lexico * mLexico = new Lexico(texto);
	mLexico->Imprime();
	cout << endl;
	std::vector<Token*> listaTokens = mLexico->AnalisaLexico();
	Sintatico * mSintatico = new Sintatico(listaTokens);
	cout << "Saida: " << mSintatico->AnalisaSintatico() << endl;
	
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
