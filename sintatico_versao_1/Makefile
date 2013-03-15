#Makefile

#Compilador
CC=g++

# Objects
# Objects
OBJETOS = analisadorLexicoSintaticoV1.o

EXECUTAVEL = analisador

all: $(OBJETOS) 
	$(CC) $(OBJETOS) -o $(EXECUTAVEL)


ladoB: analisadorLexicoSintaticoV1.hpp analisadorLexicoSintaticoV1.cpp
	$(CC) -c analisadorLexicoSintaticoV1.cpp
	$(CC) analisadorLexicoSintaticoV1.o -o analisadorLexicoSintaticoV1

#limpeza
clean:
	rm -rf *.o
