#Makefile

#Compilador
CC=g++

# Objects
OBJETOS = analisadorLexico.o

EXECUTAVEL = anaisadorLexico

all: $(OBJETOS) 
	$(CC) $(OBJETOS) -o $(EXECUTAVEL)

laboB: analisadorLexicoSintatico.o analisadorLexicoSintatico.hpp analisadorLexicoSintatico.cpp
	$(CC) analisadorLexicoSintatico.o -o analisadorLexicoSintatico

analisador: anaisadorLexico.cpp
	$(CC) -c analisadorLexico.cpp

analisadorLexico:
	$(CC) -c analisadorLexicoSintatico.cpp

#limpeza
clean:
	rm -rf $(OBJETOS)
	rm -rf analisadorLexicoSintatico.o
	rm -rf $(EXECUTAVEL)
	rm -rf saidaAnalisador.txt
