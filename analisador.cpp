#include "analisador.hpp"

bool Lexico::debug;
bool Sintatico::debug;


int main(int argc, char * argv[]) {
	string * entrada;
	string texto;
	string arquivo;
	string strLeitura;
	bool debug = false;
	cout << "Trabalho de Linguagens Formais: " << endl;
	cout << "Analisador Lexico e Sintatico" << endl;
	cout << "Grupo: " << endl;
	cout << " André Silva" << endl;
	cout << " Eliezer Ribeiro" << endl;
	cout << " Rubens Peres" << endl;
	cout << endl << "Digite o texto a ser analisado: " << endl << endl;
	if (argc > 1) {
		cout << "Parametro: " << argv[1] << endl;
		debug = (strcmp(argv[1],"--debug") == 0 ? true : false);
		cout << debug << endl;
	}
	if (argc > 2) {
		arquivo = argv[2];
		//cout << "Abrindo arquivo " << arquivo << ": " << endl;
	} else {
		//cout << "Entrada padrao: " << endl;
		while (cin.good()) {
			texto.push_back(cin.get());
			if (texto[texto.size()-1] == '@') break;
		}
		
		texto[texto.size()-1] = '\0';
	}
	if (debug) {
		cout << "Texto Inserido: " << endl;
		cout << texto;
	}
	Lexico * mLexico = new Lexico(texto);
	Lexico::debug = debug;
	Sintatico::debug = debug;
	
	if (debug) {
		mLexico->Imprime();
		cout << endl;
	}
	std::vector<Token*> listaTokens = mLexico->AnalisaLexico();
	Sintatico * mSintatico = new Sintatico(listaTokens);
	cout << "Reconhecimento Lexico: " << (mLexico->lexicoErro == false ? "Aceito" : "ERRO!") << endl;
	cout << "Reconhecimento Sintatico: " << (mSintatico->AnalisaSintatico() ? "Aceito" : "ERRO!") << endl << endl;
	
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
		case OPERADOR:
			Nome = "OPERADOR";
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
		case BOOLVAR:
			Nome = "BOOLVAR";
			break;
		case BOOLCOND:
			Nome = "BOOLCOND";
			break;
		case CONDICIONAL:
			Nome = "CONDICIONAL";
			break;
		case PARENTSIN:
			Nome = "PARENTSIN";
			break;
		case ENTRADA:
			Nome = "ENTRADA";
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
