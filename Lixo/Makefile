#Makefile

#Compilador
CC=g++

# Objects
OBJETOS = analisadorLexico.o analisadorSintatico.o analisador.o

EXECUTAVEL = analisador

all: $(OBJETOS) 
	$(CC) $(OBJETOS) -o $(EXECUTAVEL)

analisadorLexico: analisador.hpp analisadorLexico.cpp
	$(CC) -c analisadorLexico.cpp
analisadorSintatico: analisador.hpp analisadorSintatico.cpp
	$(CC) -c analisadorSintatico.cpp
analisador.o: analisador.hpp analisador.cpp
	$(CC) -c analisador.cpp





ladoB: analisadorLexicoSintaticoAndre.hpp analisadorLexicoSintaticoAndre.cpp
	$(CC) -c analisadorLexicoSintaticoAndre.cpp
	$(CC) analisadorLexicoSintaticoAndre.o -o analisadorLexicoSintaticoAndre

ladoC: analisadorLexicoEli.cpp
	$(CC) -c analisadorLexicoEli.cpp
	$(CC) analisadorLexicoEli.o -o analisadorLexicoEli

#limpeza
clean:
	rm -rf $(OBJETOS)
	rm -rf analisadorLexicoSintatico.o
	rm -rf $(EXECUTAVEL)
	rm -rf saidaAnalisador.txt
